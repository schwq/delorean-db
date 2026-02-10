#pragma once

#include "deloreandb/kernels/kernel.hpp"

ATTR_HOT ATTR_SSE41 void SSE41_Mul_i32(const i32* noalias a,
                                       const i32* noalias b, i32* noalias out,
                                       u64 count);