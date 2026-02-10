#include "deloreandb/kernels/sse2.hpp"
#include <emmintrin.h>
#include "deloreandb/kernels/kernel.hpp"

extern "C" {
ATTR_HOT void SSE2_Add_f32(const f32* noalias a, const f32* noalias b,
                           f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m128 va = _mm_load_ps(a + i);
    __m128 vb = _mm_load_ps(b + i);
    __m128 vc = _mm_add_ps(va, vb);
    _mm_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void SSE2_Add_f64(const f64* noalias a, const f64* noalias b,
                           f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 2 <= count; i += 2) {
    __m128d va = _mm_load_pd(a + i);
    __m128d vb = _mm_load_pd(b + i);
    __m128d vc = _mm_add_pd(va, vb);
    _mm_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void SSE2_Add_i32(const i32* noalias a, const i32* noalias b,
                           i32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m128i va = _mm_load_si128((const __m128i*)(a + i));
    __m128i vb = _mm_load_si128((const __m128i*)(b + i));
    __m128i vc = _mm_add_epi32(va, vb);
    _mm_store_si128((__m128i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void SSE2_Add_i64(const i64* noalias a, const i64* noalias b,
                           i64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 2 <= count; i += 2) {
    __m128i va = _mm_load_si128((const __m128i*)(a + i));
    __m128i vb = _mm_load_si128((const __m128i*)(b + i));
    __m128i vc = _mm_add_epi64(va, vb);
    _mm_store_si128((__m128i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void SSE2_Sub_f32(const f32* noalias a, const f32* noalias b,
                           f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m128 va = _mm_load_ps(a + i);
    __m128 vb = _mm_load_ps(b + i);
    __m128 vc = _mm_sub_ps(va, vb);
    _mm_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void SSE2_Sub_f64(const f64* noalias a, const f64* noalias b,
                           f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 2 <= count; i += 2) {
    __m128d va = _mm_load_pd(a + i);
    __m128d vb = _mm_load_pd(b + i);
    __m128d vc = _mm_sub_pd(va, vb);
    _mm_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void SSE2_Sub_i32(const i32* noalias a, const i32* noalias b,
                           i32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m128i va = _mm_load_si128((const __m128i*)(a + i));
    __m128i vb = _mm_load_si128((const __m128i*)(b + i));
    __m128i vc = _mm_sub_epi32(va, vb);
    _mm_store_si128((__m128i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void SSE2_Sub_i64(const i64* noalias a, const i64* noalias b,
                           i64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 2 <= count; i += 2) {
    __m128i va = _mm_load_si128((const __m128i*)(a + i));
    __m128i vb = _mm_load_si128((const __m128i*)(b + i));
    __m128i vc = _mm_sub_epi64(va, vb);
    _mm_store_si128((__m128i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void SSE2_Mul_f32(const f32* noalias a, const f32* noalias b,
                           f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m128 va = _mm_load_ps(a + i);
    __m128 vb = _mm_load_ps(b + i);
    __m128 vc = _mm_mul_ps(va, vb);
    _mm_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}

ATTR_HOT void SSE2_Mul_f64(const f64* noalias a, const f64* noalias b,
                           f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 2 <= count; i += 2) {
    __m128d va = _mm_load_pd(a + i);
    __m128d vb = _mm_load_pd(b + i);
    __m128d vc = _mm_mul_pd(va, vb);
    _mm_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}

ATTR_HOT void SSE2_Mul_i32(const i32* noalias a, const i32* noalias b,
                           i32* noalias out, u64 count)
{
  UNREACHABLE;
}

ATTR_HOT void SSE2_Mul_i64(const i64* noalias a, const i64* noalias b,
                           i64* noalias out, u64 count)
{
  UNREACHABLE;
}

ATTR_HOT void SSE2_Div_f32(const f32* noalias a, const f32* noalias b,
                           f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m128 va = _mm_load_ps(a + i);
    __m128 vb = _mm_load_ps(b + i);
    __m128 vc = _mm_div_ps(va, vb);
    _mm_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] / b[i];
  }
}

ATTR_HOT void SSE2_Div_f64(const f64* noalias a, const f64* noalias b,
                           f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 2 <= count; i += 2) {
    __m128d va = _mm_load_pd(a + i);
    __m128d vb = _mm_load_pd(b + i);
    __m128d vc = _mm_div_pd(va, vb);
    _mm_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] / b[i];
  }
}

ATTR_HOT void SSE2_Div_i32(const i32* noalias a, const i32* noalias b,
                           i32* noalias out, u64 count)
{
  UNREACHABLE;
}

ATTR_HOT void SSE2_Div_i64(const i64* noalias a, const i64* noalias b,
                           i64* noalias out, u64 count)
{
  UNREACHABLE;
}
}