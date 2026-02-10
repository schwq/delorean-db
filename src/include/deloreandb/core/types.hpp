#pragma once

#include <cassert>
#include "deloreandb/common.hpp"

namespace Delorean
{

enum class ValueType
{
  Int64,
  Int32,
  Float64,
  Float32,
  Boolean,
  String,
  Binary
};

struct StringValue_t
{
  u64 offset;
  u64 mLenght;
};

struct BlobValue_t
{
  u64 offset;
  u64 mLenght;
};

u64 GetTypeSize(ValueType type)
{
  switch (type) {
    case ValueType::Int64:
      return sizeof(i64);

    case ValueType::Int32:
      return sizeof(i32);

    case ValueType::Float64:
      return sizeof(f64);

    case ValueType::Float32:
      return sizeof(f32);

    case ValueType::Boolean:
      return sizeof(bool);

    case ValueType::String:
      return sizeof(StringValue_t);

    case ValueType::Binary:
      return sizeof(BlobValue_t);
  }
  return 0;
}

}  // namespace Delorean