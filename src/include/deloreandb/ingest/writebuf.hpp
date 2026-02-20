#pragma once

#include <cstring>
#include "deloreandb/core/schema.hpp"
#include "deloreandb/core/types.hpp"
#include "deloreandb/mem/arena_alloc.hpp"
namespace Delorean
{
constexpr u32 VECTORBASE_CAPACITY = 1024;

constexpr u32 WRITEBUF_CAPACITY = VECTORBASE_CAPACITY * 4;

struct WriteBuf
{

  const Schema* mSchema = nullptr;

  u8* mData = nullptr;

  u32 mRowStride = 0;
  u32 mCapacity = 0;
  u32 mSize = 0;

  std::vector<u32> mColumnOffsets;

  ArenaAllocator* mArena = nullptr;

  WriteBuf(const Schema* schema, ArenaAllocator* arena, u32 capacity)
      : mSchema(schema), mArena(arena), mCapacity(capacity)
  {
    Compute();
    mData = arena->AllocType_SIMD<u8>(mRowStride * mCapacity, 64);
  }

  void Reset() { mSize = 0; }

  INLINE bool Full() const { return mSize >= mCapacity; }

  INLINE u8* GetRowPtr(u32 row) { return mData + (row * mRowStride); }

  INLINE void AppendRow(const void* rowData)
  {
    if (Full()) {
      // FLUSH
      return;
    }

    u8* dst = GetRowPtr(mSize);
    std::memcpy(dst, rowData, mRowStride);
    mSize++;
  }

  template <typename T>
  INLINE void WriteValue(u32 row, u32 colIdx, const T& value)
  {
    assert(row < mCapacity);
    assert(colIdx < mColumnOffsets.size());

    u8* rowPtr = GetRowPtr(row);
    u8* dst = rowPtr + mColumnOffsets[colIdx];
    std::memcpy(dst, &value, sizeof(T));
  }

 private:
  static u32 Align(u32 offset, u32 align)
  {
    return (offset + align - 1) & ~(align - 1);
  }

  void Compute()
  {
    mColumnOffsets.clear();
    mColumnOffsets.reserve(mSchema->mColumns.size());

    u32 offset = 0;

    for (const auto& col : mSchema->mColumns) {
      auto size = GetTypeSize(col.mType);
      auto align = size;

      offset = Align(offset, align);
      mColumnOffsets.push_back(offset);
      offset += size;
    }

    mRowStride = Align(offset, 32);
  }
};

}  // namespace Delorean