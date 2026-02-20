#include "deloreandb/kernels/kernel.hpp"
#include "deloreandb/kernels/scalar.hpp"

#ifdef DELOREAN_AVX512
#include "deloreandb/kernels/avx512.hpp"

#elif defined(DELOREAN_AVX2) && !defined(DELOREAN_AVX512)
#include "deloreandb/kernels/avx2.hpp"

#elif defined(DELOREAN_SSE41)
#include "deloreandb/kernels/sse41.hpp"

#elif defined(DELOREAN_SSE2)
#include "deloreandb/kernels/sse2.hpp"

#endif

using namespace Delorean;

const Delorean::KernelFunTable& Delorean::GetKernels()
{
  static KernelFunTable table = [] {
    KernelFunTable t{};

    t.Add_f32 = Scalar_Add_f32;
    t.Add_f64 = Scalar_Add_f64;
    t.Add_i32 = Scalar_Add_i32;
    t.Add_i64 = Scalar_Add_i64;
    t.Sub_f32 = Scalar_Sub_f32;
    t.Sub_f64 = Scalar_Sub_f64;
    t.Sub_i32 = Scalar_Sub_i32;
    t.Sub_i64 = Scalar_Sub_i64;
    t.Mul_f32 = Scalar_Mul_f32;
    t.Mul_f64 = Scalar_Mul_f64;
    t.Mul_i32 = Scalar_Mul_i32;
    t.Mul_i64 = Scalar_Mul_i64;
    t.Div_f32 = Scalar_Div_f32;
    t.Div_f64 = Scalar_Div_f64;
    t.Div_i32 = Scalar_Div_i32;
    t.Div_i64 = Scalar_Div_i64;

#ifdef DELOREAN_AVX512

    t.Add_f32 = AVX512_Add_f32;
    t.Add_f64 = AVX512_Add_f64;
    t.Add_i32 = AVX512_Add_i32;
    t.Add_i64 = AVX512_Add_i64;
    t.Sub_f32 = AVX512_Sub_f32;
    t.Sub_f64 = AVX512_Sub_f64;
    t.Sub_i32 = AVX512_Sub_i32;
    t.Sub_i64 = AVX512_Sub_i64;
    t.Mul_f32 = AVX512_Mul_f32;
    t.Mul_f64 = AVX512_Mul_f64;
    t.Mul_i32 = AVX512_Mul_i32;
    t.Mul_i64 = AVX512_Mul_i64;
    t.Div_f32 = AVX512_Div_f32;
    t.Div_f64 = AVX512_Div_f64;

#elif defined(DELOREAN_AVX2) && !defined(DELOREAN_AVX512)

    t.Add_f32 = AVX2_Add_f32;
    t.Add_f64 = AVX2_Add_f64;
    t.Add_i32 = AVX2_Add_i32;
    t.Add_i64 = AVX2_Add_i64;
    t.Sub_f32 = AVX2_Sub_f32;
    t.Sub_f64 = AVX2_Sub_f64;
    t.Sub_i32 = AVX2_Sub_i32;
    t.Sub_i64 = AVX2_Sub_i64;
    t.Mul_f32 = AVX2_Mul_f32;
    t.Mul_f64 = AVX2_Mul_f64;
    t.Mul_i32 = AVX2_Mul_i32;
    t.Div_f32 = AVX2_Div_f32;
    t.Div_f64 = AVX2_Div_f64;

#elif defined(DELOREAN_SSE41)

    t.Mul_i32 = SSE41_Mul_i32;

#elif defined(DELOREAN_SSE2)

    t.Add_f32 = SSE2_Add_f32;
    t.Add_f64 = SSE2_Add_f64;
    t.Add_i32 = SSE2_Add_i32;
    t.Add_i64 = SSE2_Add_i64;
    t.Sub_f32 = SSE2_Sub_f32;
    t.Sub_f64 = SSE2_Sub_f64;
    t.Sub_i32 = SSE2_Sub_i32;
    t.Sub_i64 = SSE2_Sub_i64;
    t.Mul_f32 = SSE2_Mul_f32;
    t.Mul_f64 = SSE2_Mul_f64;
    t.Div_f32 = SSE2_Div_f32;
    t.Div_f64 = SSE2_Div_f64;

#endif

    return t;
  }();
  return table;
}