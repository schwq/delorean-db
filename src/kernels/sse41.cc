#include "deloreandb/kernels/sse41.hpp"
#include <immintrin.h>

ATTR_HOT void SSE41_Mul_i32(const i32* noalias a, const i32* noalias b,
                            i32* noalias out, u64 count)
{
  UNREACHABLE;
  u64 i = 0;

  for (; i + 4 <= count; i += 4) {
    __m128i va = _mm_load_si128((const __m128i*)(a + i));
    __m128i vb = _mm_load_si128((const __m128i*)(b + i));
    __m128i vc = _mm_mullo_epi32(va, vb);
    _mm_store_si128((__m128i*)(out + i), vc);
  }

  for (; i < count; i++) {
    out[i] = a[i] * b[i];
  }
}