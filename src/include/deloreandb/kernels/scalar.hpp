#pragma once

#include "deloreandb/common.hpp"
#include "deloreandb/kernels/kernel.hpp"

extern "C" {
ATTR_HOT void Scalar_Add_f32(const f32* noalias a, const f32* noalias b,
                             f32* noalias out, u64 count);

ATTR_HOT void Scalar_Add_f64(const f64* noalias a, const f64* noalias b,
                             f64* noalias out, u64 count);

ATTR_HOT void Scalar_Add_i32(const i32* noalias a, const i32* noalias b,
                             i32* noalias out, u64 count);

ATTR_HOT void Scalar_Add_i64(const i64* noalias a, const i64* noalias b,
                             i64* noalias out, u64 count);

ATTR_HOT void Scalar_Sub_f32(const f32* noalias a, const f32* noalias b,
                             f32* noalias out, u64 count);

ATTR_HOT void Scalar_Sub_f64(const f64* noalias a, const f64* noalias b,
                             f64* noalias out, u64 count);

ATTR_HOT void Scalar_Sub_i32(const i32* noalias a, const i32* noalias b,
                             i32* noalias out, u64 count);

ATTR_HOT void Scalar_Sub_i64(const i64* noalias a, const i64* noalias b,
                             i64* noalias out, u64 count);

ATTR_HOT void Scalar_Mul_f32(const f32* noalias a, const f32* noalias b,
                             f32* noalias out, u64 count);

ATTR_HOT void Scalar_Mul_f64(const f64* noalias a, const f64* noalias b,
                             f64* noalias out, u64 count);

ATTR_HOT void Scalar_Mul_i32(const i32* noalias a, const i32* noalias b,
                             i32* noalias out, u64 count);

ATTR_HOT void Scalar_Mul_i64(const i64* noalias a, const i64* noalias b,
                             i64* noalias out, u64 count);

ATTR_HOT void Scalar_Div_f32(const f32* noalias a, const f32* noalias b,
                             f32* noalias out, u64 count);

ATTR_HOT void Scalar_Div_f64(const f64* noalias a, const f64* noalias b,
                             f64* noalias out, u64 count);

ATTR_HOT void Scalar_Div_i32(const i32* noalias a, const i32* noalias b,
                             i32* noalias out, u64 count);

ATTR_HOT void Scalar_Div_i64(const i64* noalias a, const i64* noalias b,
                             i64* noalias out, u64 count);
}