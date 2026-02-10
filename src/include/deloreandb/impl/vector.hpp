#pragma once

#include <immintrin.h>
#include <cassert>
#include <type_traits>
#include "deloreandb/common.hpp"
#include "deloreandb/core/types.hpp"
#include "deloreandb/mem/arena_alloc.hpp"

#define FLOAT32_SIMD_THRESHOLD 32
#define FLOAT64_SIMD_THRESHOLD FLOAT32_SIMD_THRESHOLD
#define UNREACHABLE __builtin_unreachable()

namespace Delorean
{

struct VectorBase
{

  void* mData;
  u64 mCount;
  ValueType mType;
};

template <typename T>
inline T* GetVectorData(VectorBase& vec)
{
  return reinterpret_cast<T*>(vec.mData);
}

struct AddOP
{
  template <typename T>
  static inline T Scalar(T a, T b)
  {
    return a + b;
  }

  static inline __m256 Simd_f32(__m256 a, __m256 b)
  {
    return _mm256_add_ps(a, b);
  }
  static inline __m256d Simd_f64(__m256d a, __m256d b)
  {
    return _mm256_add_pd(a, b);
  }

  static inline __m256i Simd_i64(__m256i a, __m256i b)
  {
    return _mm256_add_epi64(a, b);
  }

  static inline __m256i Simd_i32(__m256i a, __m256i b)
  {
    return _mm256_add_epi32(a, b);
  }
};

struct SubOP
{
  template <typename T>
  static inline T Scalar(T a, T b)
  {
    return a - b;
  }

  static inline __m256 Simd_f32(__m256 a, __m256 b)
  {
    return _mm256_sub_ps(a, b);
  }
  static inline __m256d Simd_f64(__m256d a, __m256d b)
  {
    return _mm256_sub_pd(a, b);
  }
  static inline __m256i Simd_i64(__m256i a, __m256i b)
  {
    return _mm256_sub_epi64(a, b);
  }

  static inline __m256i Simd_i32(__m256i a, __m256i b)
  {
    return _mm256_sub_epi32(a, b);
  }
};

struct MulOP
{
  template <typename T>
  static inline T Scalar(T a, T b)
  {
    return a * b;
  }

  static inline __m256 Simd_f32(__m256 a, __m256 b)
  {
    return _mm256_mul_ps(a, b);
  }
  static inline __m256d Simd_f64(__m256d a, __m256d b)
  {
    return _mm256_mul_pd(a, b);
  }
  static inline __m256i Simd_i64(__m256i a, __m256i b) { UNREACHABLE; }

  static inline __m256i Simd_i32(__m256i a, __m256i b)
  {
    return _mm256_mullo_epi32(a, b);
  }
};

struct DivOP
{
  template <typename T>
  static inline T Scalar(T a, T b)
  {
    return a / b;
  }

  static inline __m256 Simd_f32(__m256 a, __m256 b)
  {
    return _mm256_div_ps(a, b);
  }
  static inline __m256d Simd_f64(__m256d a, __m256d b)
  {
    return _mm256_div_pd(a, b);
  }

  static inline __m256i Simd_i64(__m256i a, __m256i b) { UNREACHABLE; }

  static inline __m256i Simd_i32(__m256i a, __m256i b) { UNREACHABLE; }
};

template <typename T, typename Op>
void ComputeScalar(T* a, T* b, T* out, u64 n)
{
  for (u64 i = 0; i < n; i++) {
    out[i] = Op::Scalar(a[i], b[i]);
  }
}

template <typename Op>
void ComputeSIMD_f32(f32* noalias a, f32* noalias b, f32* noalias out, u64 n)
{
  u64 i = 0;

  for (; i + 8 <= n; i += 8) {
    __m256 va = _mm256_loadu_ps(a + i);
    __m256 vb = _mm256_loadu_ps(b + i);
    __m256 vc = Op::Simd_f32(va, vb);
    _mm256_store_ps(out + i, vc);
  }
  for (; i < n; i++) {
    out[i] = Op::Scalar(a[i], b[i]);
  }
}

template <typename Op>
void ComputeSIMD_f64(f64* noalias a, f64* noalias b, f64* noalias out, u64 n)
{
  u64 i = 0;

  for (; i + 4 <= n; i += 4) {
    __m256d va = _mm256_loadu_pd(a + i);
    __m256d vb = _mm256_loadu_pd(b + i);
    __m256d vc = Op::Simd_f64(va, vb);
    _mm256_store_pd(out + i, vc);
  }
  for (; i < n; i++) {
    out[i] = Op::Scalar(a[i], b[i]);
  }
}

template <typename Op>
void ComputeSIMD_i32(i32* noalias a, i32* noalias b, i32* noalias out, u64 n)
{
  u64 i = 0;

  for (; i + 8 <= n; i += 8) {
    __m256i va = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(a + i));
    __m256i vb = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(b + i));
    __m256i vc = Op::Simd_i32(va, vb);
    _mm256_store_si256((__m256i*)(out + i), vc);
  }
  for (; i < n; i++) {
    out[i] = Op::Scalar(a[i], b[i]);
  }
}
template <typename Op>
void ComputeSIMD_i64(i64* noalias a, i64* noalias b, i64* noalias out, u64 n)
{
  u64 i = 0;

  for (; i + 4 <= n; i += 4) {
    __m256i va = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(a + i));
    __m256i vb = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(b + i));
    __m256i vc = Op::Simd_i64(va, vb);
    _mm256_store_si256((__m256i*)(out + i), vc);
  }
  for (; i < n; i++) {
    out[i] = Op::Scalar(a[i], b[i]);
  }
}

template <typename T, typename Op>
void Eval(VectorBase& va, VectorBase& vb, VectorBase& vo)
{
  T* a = GetVectorData<T>(va);
  T* b = GetVectorData<T>(vb);
  T* o = GetVectorData<T>(vo);

  const u64 count = va.mCount;

  if constexpr (std::is_same_v<T, f32>) {
    ComputeSIMD_f32<Op>(a, b, o, count);
  }
  else if constexpr (std::is_same_v<T, f64>) {
    ComputeSIMD_f64<Op>(a, b, o, count);
  }
  else if constexpr (std::is_same_v<T, i32>) {

    if constexpr (std::is_same_v<Op, DivOP>) {
      ComputeScalar<T, Op>(a, b, o, count);
    }
    else {
      ComputeSIMD_i32<Op>(a, b, o, count);
    }
  }
  else if constexpr (std::is_same_v<T, i64>) {
    if constexpr (std::is_same_v<Op, MulOP> || std::is_same_v<Op, DivOP>) {
      ComputeScalar<T, Op>(a, b, o, count);
    }
    else {
      ComputeSIMD_i64<Op>(a, b, o, count);
    }
  }
  else {
    ComputeScalar<T, Op>(a, b, o, count);
  }
}

template <typename Op>
void OpVectors(ArenaAllocator& arena, VectorBase& a, VectorBase& b,
               VectorBase& out)
{

  assert(a.mType == b.mType);
  assert(a.mCount == b.mCount);

  out.mType = a.mType;
  out.mCount = a.mCount;

  u64 size = a.mCount * GetTypeSize(a.mType);
  out.mData = arena.Alloc(size, 64);

  switch (a.mType) {
    case ValueType::Int32:
      Eval<i32, Op>(a, b, out);
      break;
    case ValueType::Int64:
      Eval<i64, Op>(a, b, out);
      break;
    case ValueType::Float64:
      Eval<f64, Op>(a, b, out);
      break;
    case ValueType::Float32:
      Eval<f32, Op>(a, b, out);
      break;
    default:
      //LogWarn("Type cannot be added!");
      return;
  }
}

}  // namespace Delorean
