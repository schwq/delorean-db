#pragma once

#include "deloreandb/common.hpp"

#define FLOAT32_SIMD_THRESHOLD 32
#define FLOAT64_SIMD_THRESHOLD FLOAT32_SIMD_THRESHOLD
#define UNREACHABLE __builtin_unreachable()
#define ATTR_HOT __attribute__((hot))

#define ATTR_AVX2 __attribute__((target("avx2")))
#define ATTR_SSE2 __attribute__((target("sse2")))
#define ATTR_SSE41 __attribute__((target("sse4.1")))
#define ATTR_AVX512 __attribute__((target("avx512")))

namespace Delorean
{

inline bool HasSSE2()
{
  static bool v = __builtin_cpu_supports("sse2");
  return v;
}
inline bool HasAVX2()
{
  static bool v = __builtin_cpu_supports("avx2");
  return v;
}
inline bool HasAVX512()
{
  static bool v = __builtin_cpu_supports("avx512f");
  return v;
}

struct KernelFunTable
{

  using FunOp_i64 = void (*)(const i64*, const i64*, i64*, u64);
  using FunOp_i32 = void (*)(const i32*, const i32*, i32*, u64);
  using FunOp_f64 = void (*)(const f64*, const f64*, f64*, u64);
  using FunOp_f32 = void (*)(const f32*, const f32*, f32*, u64);

  FunOp_i64 Add_i64;
  FunOp_i64 Sub_i64;
  FunOp_i64 Mul_i64;
  FunOp_i64 Div_i64;

  FunOp_i32 Add_i32;
  FunOp_i32 Sub_i32;
  FunOp_i32 Mul_i32;
  FunOp_i32 Div_i32;

  FunOp_f64 Add_f64;
  FunOp_f64 Sub_f64;
  FunOp_f64 Mul_f64;
  FunOp_f64 Div_f64;

  FunOp_f32 Add_f32;
  FunOp_f32 Sub_f32;
  FunOp_f32 Mul_f32;
  FunOp_f32 Div_f32;
};

const KernelFunTable& Kernels()
{
  static KernelFunTable table = [] {
    KernelFunTable t{};

    // TODO:

    return t;
  }();
  return table;
}

}  // namespace Delorean