#include "deloreandb/kernels/avx2.hpp"
#include "deloreandb/kernels/kernel.hpp"

extern "C" {
ATTR_HOT void AVX2_Add_f32(const f32* noalias a, const f32* noalias b,
                           f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m256 va = _mm256_load_ps(a + i);
    __m256 vb = _mm256_load_ps(b + i);
    __m256 vc = _mm256_add_ps(va, vb);
    _mm256_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void AVX2_Add_f64(const f64* noalias a, const f64* noalias b,
                           f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m256d va = _mm256_load_pd(a + i);
    __m256d vb = _mm256_load_pd(b + i);
    __m256d vc = _mm256_add_pd(va, vb);
    _mm256_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void AVX2_Add_i32(const i32* noalias a, const i32* noalias b,
                           i32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m256i va = _mm256_load_si256((const __m256i*)(a + i));
    __m256i vb = _mm256_load_si256((const __m256i*)(b + i));
    __m256i vc = _mm256_add_epi32(va, vb);
    _mm256_store_si256((__m256i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void AVX2_Add_i64(const i64* noalias a, const i64* noalias b,
                           i64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m256i va = _mm256_load_si256((const __m256i*)(a + i));
    __m256i vb = _mm256_load_si256((const __m256i*)(b + i));
    __m256i vc = _mm256_add_epi64(va, vb);
    _mm256_store_si256((__m256i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] + b[i];
  }
}

ATTR_HOT void AVX2_Sub_f32(const f32* noalias a, const f32* noalias b,
                           f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m256 va = _mm256_load_ps(a + i);
    __m256 vb = _mm256_load_ps(b + i);
    __m256 vc = _mm256_sub_ps(va, vb);
    _mm256_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void AVX2_Sub_f64(const f64* noalias a, const f64* noalias b,
                           f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m256d va = _mm256_load_pd(a + i);
    __m256d vb = _mm256_load_pd(b + i);
    __m256d vc = _mm256_sub_pd(va, vb);
    _mm256_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void AVX2_Sub_i32(const i32* noalias a, const i32* noalias b,
                           i32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m256i va = _mm256_load_si256((const __m256i*)(a + i));
    __m256i vb = _mm256_load_si256((const __m256i*)(b + i));
    __m256i vc = _mm256_sub_epi32(va, vb);
    _mm256_store_si256((__m256i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void AVX2_Sub_i64(const i64* noalias a, const i64* noalias b,
                           i64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m256i va = _mm256_load_si256((const __m256i*)(a + i));
    __m256i vb = _mm256_load_si256((const __m256i*)(b + i));
    __m256i vc = _mm256_sub_epi64(va, vb);
    _mm256_store_si256((__m256i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] - b[i];
  }
}

ATTR_HOT void AVX2_Mul_f32(const f32* noalias a, const f32* noalias b,
                           f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m256 va = _mm256_load_ps(a + i);
    __m256 vb = _mm256_load_ps(b + i);
    __m256 vc = _mm256_mul_ps(va, vb);
    _mm256_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}

ATTR_HOT void AVX2_Mul_f64(const f64* noalias a, const f64* noalias b,
                           f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m256d va = _mm256_load_pd(a + i);
    __m256d vb = _mm256_load_pd(b + i);
    __m256d vc = _mm256_mul_pd(va, vb);
    _mm256_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}

ATTR_HOT void AVX2_Mul_i32(const i32* noalias a, const i32* noalias b,
                           i32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m256i va = _mm256_load_si256((const __m256i*)(a + i));
    __m256i vb = _mm256_load_si256((const __m256i*)(b + i));
    __m256i vc = _mm256_mullo_epi32(va, vb);
    _mm256_store_si256((__m256i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}

ATTR_HOT void AVX2_Div_f32(const f32* noalias a, const f32* noalias b,
                           f32* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 8 <= count; i += 8) {
    __m256 va = _mm256_load_ps(a + i);
    __m256 vb = _mm256_load_ps(b + i);
    __m256 vc = _mm256_div_ps(va, vb);
    _mm256_store_ps(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] / b[i];
  }
}

ATTR_HOT void AVX2_Div_f64(const f64* noalias a, const f64* noalias b,
                           f64* noalias out, u64 count)
{
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m256d va = _mm256_load_pd(a + i);
    __m256d vb = _mm256_load_pd(b + i);
    __m256d vc = _mm256_div_pd(va, vb);
    _mm256_store_pd(out + i, vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] / b[i];
  }
}
}