#include <immintrin.h>
#include "deloreandb/kernels/kernel.hpp"

extern "C" {
ATTR_HOT void AVX512_Add_f32(const f32* noalias a, const f32* noalias b,
                             f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 16 <= count; i += 16) {
    __m512 va = _mm512_load_ps(a + i);
    __m512 vb = _mm512_load_ps(b + i);
    __m512 vc = _mm512_add_ps(va, vb);
    _mm512_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void AVX512_Add_f64(const f64* noalias a, const f64* noalias b,
                             f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m512d va = _mm512_load_pd(a + i);
    __m512d vb = _mm512_load_pd(b + i);
    __m512d vc = _mm512_add_pd(va, vb);
    _mm512_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void AVX512_Add_i32(const i32* noalias a, const i32* noalias b,
                             i32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 16 <= count; i += 16) {
    __m512i va = _mm512_load_si512((const __m512i*)(a + i));
    __m512i vb = _mm512_load_si512((const __m512i*)(b + i));
    __m512i vc = _mm512_add_epi32(va, vb);
    _mm512_store_si512((__m512i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void AVX512_Add_i64(const i64* noalias a, const i64* noalias b,
                             i64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m512i va = _mm512_load_si512((const __m512i*)(a + i));
    __m512i vb = _mm512_load_si512((const __m512i*)(b + i));
    __m512i vc = _mm512_add_epi64(va, vb);
    _mm512_store_si512((__m512i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void AVX512_Sub_f32(const f32* noalias a, const f32* noalias b,
                             f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 16 <= count; i += 16) {
    __m512 va = _mm512_load_ps(a + i);
    __m512 vb = _mm512_load_ps(b + i);
    __m512 vc = _mm512_sub_ps(va, vb);
    _mm512_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void AVX512_Sub_f64(const f64* noalias a, const f64* noalias b,
                             f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m512d va = _mm512_load_pd(a + i);
    __m512d vb = _mm512_load_pd(b + i);
    __m512d vc = _mm512_sub_pd(va, vb);
    _mm512_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void AVX512_Sub_i32(const i32* noalias a, const i32* noalias b,
                             i32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 16 <= count; i += 16) {
    __m512i va = _mm512_load_si512((const __m512i*)(a + i));
    __m512i vb = _mm512_load_si512((const __m512i*)(b + i));
    __m512i vc = _mm512_sub_epi32(va, vb);
    _mm512_store_si512((__m512i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void AVX512_Sub_i64(const i64* noalias a, const i64* noalias b,
                             i64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m512i va = _mm512_load_si512((const __m512i*)(a + i));
    __m512i vb = _mm512_load_si512((const __m512i*)(b + i));
    __m512i vc = _mm512_sub_epi64(va, vb);
    _mm512_store_si512((__m512i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void AVX512_Mul_f32(const f32* noalias a, const f32* noalias b,
                             f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 16 <= count; i += 16) {
    __m512 va = _mm512_load_ps(a + i);
    __m512 vb = _mm512_load_ps(b + i);
    __m512 vc = _mm512_mul_ps(va, vb);
    _mm512_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}

ATTR_HOT void AVX512_Mul_f64(const f64* noalias a, const f64* noalias b,
                             f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m512d va = _mm512_load_pd(a + i);
    __m512d vb = _mm512_load_pd(b + i);
    __m512d vc = _mm512_mul_pd(va, vb);
    _mm512_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}

ATTR_HOT void AVX512_Mul_i32(const i32* noalias a, const i32* noalias b,
                             i32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 16 <= count; i += 16) {
    __m512i va = _mm512_load_si512((const __m512i*)(a + i));
    __m512i vb = _mm512_load_si512((const __m512i*)(b + i));
    __m512i vc = _mm512_mullo_epi32(va, vb);
    _mm512_store_si512((__m512i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}

ATTR_HOT void AVX512_Mul_i64(const i64* noalias a, const i64* noalias b,
                             i64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m512i va = _mm512_load_si512((const __m512i*)(a + i));
    __m512i vb = _mm512_load_si512((const __m512i*)(b + i));
    __m512i vc = _mm512_mullo_epi64(va, vb);
    _mm512_store_si512((__m512i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}

ATTR_HOT void AVX512_Div_f32(const f32* noalias a, const f32* noalias b,
                             f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 16 <= count; i += 16) {
    __m512 va = _mm512_load_ps(a + i);
    __m512 vb = _mm512_load_ps(b + i);
    __m512 vc = _mm512_div_ps(va, vb);
    _mm512_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] / b[i];
  }
}

ATTR_HOT void AVX512_Div_f64(const f64* noalias a, const f64* noalias b,
                             f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m512d va = _mm512_load_pd(a + i);
    __m512d vb = _mm512_load_pd(b + i);
    __m512d vc = _mm512_div_pd(va, vb);
    _mm512_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] / b[i];
  }
}
}