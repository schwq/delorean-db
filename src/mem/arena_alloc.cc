#include "deloreandb/mem/arena_alloc.hpp"
#include <cassert>

using namespace Delorean;

ArenaAllocator::~ArenaAllocator()
{
  for (const auto& chunk : mChunks) {
    std::free(chunk.mBuffer);
  }
}

static INLINE u64 AlignUp(u64 value, u64 alignment)
{
  return (value + alignment - 1) & ~(alignment - 1);
}

void* ArenaAllocator::Alloc(u64 size, u64 alignment)
{
  assert((alignment & (alignment - 1)) == 0 &&
         "Alignment must be power of two");

  size = AlignUp(size, alignment);

  if (size > mChunkSize) {
    AddChunk(size, alignment);

    ArenaAllocatorChunk& large = mChunks.back();
    large.mOffset = size;
    return large.mBuffer;
  }

  ArenaAllocatorChunk& chunk = mChunks.back();
  u64 current = reinterpret_cast<u64>(chunk.mBuffer) + chunk.mOffset;
  u64 aligned = AlignUp(current, alignment);
  u64 newOffset = aligned - reinterpret_cast<u64>(chunk.mBuffer) + size;

  if (newOffset > chunk.mCapacity) {
    AddChunk(mChunkSize, alignment);
    return Alloc(size, alignment);
  }

  chunk.mOffset = newOffset;
  return reinterpret_cast<void*>(aligned);
}

void ArenaAllocator::Reset()
{
  for (auto& chunk : mChunks) {
    chunk.mOffset = 0;
  }
  mChunks.resize(1);
}

void ArenaAllocator::AddChunk(u64 size, u64 alignment)
{
  alignment = std::max<u64>(64, alignment);
  size = AlignUp(size, alignment);

  std::byte* buffer =
      static_cast<std::byte*>(std::aligned_alloc(alignment, size));
  if (!buffer) {
    throw std::bad_alloc();
  }
  mChunks.push_back({.mBuffer = buffer, .mCapacity = size, .mOffset = 0});
}

u64 ArenaAllocator::Capacity() const
{
  return mChunkSize;
}

u64 ArenaAllocator::Remainder() const
{
  const ArenaAllocatorChunk& chunk = mChunks.back();
  return chunk.mCapacity - chunk.mOffset;
}

u64 ArenaAllocator::ChunksCount() const
{
  return mChunks.size();
}