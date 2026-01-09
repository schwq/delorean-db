#include "deloreandb/mem/arena_alloc.hpp"
#include <cassert>

using namespace Delorean;

ArenaAllocator::~ArenaAllocator()
{
  for (const auto& chunk : mChunks) {
    std::free(chunk.mBuffer);
  }
  Debug::LogInfo("Arena allocator was been free!");
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

  Debug::LogInfo("Allocating memory size: [%d] alignment: [%d]", size,
                 alignment);

  if (size > mChunkSize) {
    AddChunk(size, alignment);

    Debug::LogInfo(
        "Adding bigger chunk to hold size: [%d] current chunk size [%d]", size,
        mChunkSize);

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
  Debug::LogInfo("Reset arena allocator was be called!");
}

void ArenaAllocator::AddChunk(u64 size, u64 alignment)
{
  alignment = std::max<u64>(64, alignment);
  size = AlignUp(size, std::max<u64>(64, alignment));

  std::byte* buffer =
      static_cast<std::byte*>(std::aligned_alloc(alignment, size));
  if (!buffer) {
    throw std::bad_alloc();
  }
  mChunks.push_back({.mBuffer = buffer, .mCapacity = size, .mOffset = 0});
  Debug::LogInfo("Adding chunk! Current count of chunks: [%d]", mChunks.size());
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