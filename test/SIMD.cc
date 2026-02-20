#include <gtest/gtest.h>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include <type_traits>
#include "deloreandb/common.hpp"
#include "deloreandb/kernels/kernel.hpp"
#include "deloreandb/kernels/scalar.hpp"
#include "deloreandb/mem/arena_alloc.hpp"

constexpr u64 WARMUP_TESTS = 10;
constexpr u64 TESTS = 20;
constexpr u64 SEED = 43;
const auto* kernels = &Delorean::GetKernels();

const std::vector<u64> Ns = {3, 8, 10, 11, 220, 1000, 1000000};

template <typename T>
T randomVal(std::mt19937& gen)
{
  if constexpr (std::is_floating_point_v<T>) {
    static thread_local std::uniform_real_distribution<T> dist(1.0, 1000.0);
    return dist(gen);
  }
  else {
    static thread_local std::uniform_int_distribution<i64> dist(1, 1000);
    return static_cast<T>(dist(gen));
  }
}

template <typename T>
struct BenchmarkSIMDKernelOutput
{
  T* C;
  T* out;
};

template <typename T, typename KernelFn, typename ScalarFn>
BenchmarkSIMDKernelOutput<T> BenchmarkSIMDKernel(
    Delorean::ArenaAllocator& arena, KernelFn fn, ScalarFn sn, u64 N)
{

  auto A = arena.AllocType_SIMD<T>(N, 64);
  auto B = arena.AllocType_SIMD<T>(N, 64);
  auto C = arena.AllocType_SIMD<T>(N, 64);
  auto out = arena.AllocType_SIMD<T>(N, 64);

  std::mt19937 gen(SEED);

  for (u64 i = 0; i < N; i++) {
    A[i] = randomVal<T>(gen);
    B[i] = A[i] + 1;
  }

  sn(A, B, C, N);

  for (u64 i = 0; i < WARMUP_TESTS; i++) {
    fn(A, B, out, N);
  }

  auto start = std::chrono::steady_clock::now();

  for (u64 i = 0; i < TESTS; i++) {
    fn(A, B, out, N);
  }

  auto end = std::chrono::steady_clock::now();

  auto duration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();

  return {C, out};
}

TEST(SIMD, Mul_f64)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());

  Delorean::ArenaAllocator arena(sizeof(f64) * Nmax * 4);

  for (const auto N : Ns) {
    auto result =
        BenchmarkSIMDKernel<f64>(arena, kernels->Mul_f64, Scalar_Mul_f64, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_NEAR(result.C[i], result.out[i], 1e-12);
    }

    arena.Reset();
  }
}

TEST(SIMD, Mul_f32)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(f32) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<f32>(arena, kernels->Mul_f32, Scalar_Mul_f32, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_NEAR(result.C[i], result.out[i], 1e-12);
    }

    arena.Reset();
  }
}

TEST(SIMD, Mul_i32)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(i32) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<i32>(arena, kernels->Mul_i32, Scalar_Mul_i32, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_EQ(result.C[i], result.out[i]);
    }

    arena.Reset();
  }
}
TEST(SIMD, Mul_i64)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(i64) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<i64>(arena, kernels->Mul_i64, Scalar_Mul_i64, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_EQ(result.C[i], result.out[i]);
    }

    arena.Reset();
  }
}
TEST(SIMD, Add_f64)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(f64) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<f64>(arena, kernels->Add_f64, Scalar_Add_f64, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_NEAR(result.C[i], result.out[i], 1e-12);
    }

    arena.Reset();
  }
}
TEST(SIMD, Add_f32)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(f32) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<f32>(arena, kernels->Add_f32, Scalar_Add_f32, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_NEAR(result.C[i], result.out[i], 1e-12);
    }

    arena.Reset();
  }
}
TEST(SIMD, Add_i32)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(i32) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<i32>(arena, kernels->Add_i32, Scalar_Add_i32, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_EQ(result.C[i], result.out[i]);
    }

    arena.Reset();
  }
}
TEST(SIMD, Add_i64)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(i64) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<i64>(arena, kernels->Add_i64, Scalar_Add_i64, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_EQ(result.C[i], result.out[i]);
    }

    arena.Reset();
  }
}
TEST(SIMD, Sub_f64)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(f64) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<f64>(arena, kernels->Sub_f64, Scalar_Sub_f64, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_NEAR(result.C[i], result.out[i], 1e-12);
    }

    arena.Reset();
  }
}
TEST(SIMD, Sub_f32)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(f32) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<f32>(arena, kernels->Sub_f32, Scalar_Sub_f32, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_NEAR(result.C[i], result.out[i], 1e-12);
    }

    arena.Reset();
  }
}
TEST(SIMD, Sub_i32)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(i32) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<i32>(arena, kernels->Sub_i32, Scalar_Sub_i32, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_EQ(result.C[i], result.out[i]);
    }

    arena.Reset();
  }
}
TEST(SIMD, Sub_i64)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(i64) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<i64>(arena, kernels->Sub_i64, Scalar_Sub_i64, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_EQ(result.C[i], result.out[i]);
    }

    arena.Reset();
  }
}
TEST(SIMD, Div_f64)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(f64) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<f64>(arena, kernels->Div_f64, Scalar_Div_f64, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_NEAR(result.C[i], result.out[i], 1e-12);
    }

    arena.Reset();
  }
}

TEST(SIMD, Div_f32)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(f32) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<f32>(arena, kernels->Div_f32, Scalar_Div_f32, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_NEAR(result.C[i], result.out[i], 1e-12);
    }

    arena.Reset();
  }
}

TEST(SIMD, Div_i32)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(i32) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<i32>(arena, kernels->Div_i32, Scalar_Div_i32, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_EQ(result.C[i], result.out[i]);
    }

    arena.Reset();
  }
}

TEST(SIMD, Div_i64)
{
  auto Nmax = *std::max_element(Ns.begin(), Ns.end());
  Delorean::ArenaAllocator arena(sizeof(i64) * Nmax * 4);

  for (const auto N : Ns) {

    auto result =
        BenchmarkSIMDKernel<i64>(arena, kernels->Div_i64, Scalar_Div_i64, N);

    for (u64 i = 0; i < N; i++) {
      ASSERT_EQ(result.C[i], result.out[i]);
    }

    arena.Reset();
  }
}