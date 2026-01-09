#pragma once

#include <concepts>
#include <vector>
#include "deloreandb/common.hpp"

namespace Delorean

{

struct ArenaAllocatorChunk
{
  std::byte* mBuffer = nullptr;
  u64 mCapacity = 0;
  u64 mOffset = 0;
};

class ArenaAllocator
{
 public:
  explicit ArenaAllocator(u64 chunk_size) : mChunkSize(chunk_size)
  {
    AddChunk(mChunkSize, 64);
  }

  /**
   * @brief Returns the capacity of the chunks in the arena. 
   * 
   * @return u64 The capacity
   */
  u64 Capacity() const;

  /**
   * @brief Returns the remainder space in the current chunk.
   * 
   * @return u64 The remainder space
   */
  u64 Remainder() const;

  /**
   * @brief Returns the chunk count of the arena.
   * 
   * @return u64 The chunk count 
   */
  u64 ChunksCount() const;

  /**
   * @brief Destroy the Arena Allocator object and free all the chunks
   * 
   */
  ~ArenaAllocator();

  /**
   * @brief Allocates memory in the arena to the given Type 
   * 
   * @tparam T The type
   * @param count Count of objects to allocate memory for
   * @return T* The pointer to the start of the memory block to be used
   */
  template <typename T>
  T* AllocType(u64 count = 1)
  {
    static_assert(!std::is_void_v<T>);
    void* mem = Alloc(sizeof(T) * count, alignof(T));
    return reinterpret_cast<T*>(mem);
  }

  /**
   * @brief Allocates memory in the anena to the given Type with alignment for SIMD 
   * 
   * @tparam T The type
   * @param count Count of objects to allocate memory for  
   * @param simd_alignment Alignment to be compared std::max(alignof(T), alignment)
   * @return T* The pointer to the start of the memory block to be used
   */
  template <typename T>
  T* AllocType_SIMD(u64 count, u64 simd_alignment)
  {
    static_assert(!std::is_void_v<T>);
    const u64 align = std::max(alignof(T), simd_alignment);
    void* mem = Alloc(sizeof(T) * count, align);
    return reinterpret_cast<T*>(mem);
  }

  /**
   * @brief Allocates memory in the anena
   * 
   * @param size The size of the memory block
   * @param alignment The alignment of the data
   * @return void* The pointer to the start of the memory block to be used
   */
  void* Alloc(u64 size, u64 alignment = alignof(std::max_align_t));

  /**
   * @brief Resets the arena
   * 
   */
  void Reset();

  // Non-copyable, non-movable type
  ArenaAllocator(const ArenaAllocator&) = delete;
  ArenaAllocator(ArenaAllocator&&) = delete;

 private:
  /**
   * @brief When the current chunk of memory is full (or almost) we add another chunk of memory to the arena
   * 
   */
  void AddChunk(u64 size, u64 alignment = alignof(std::max_align_t));

  /**
   * @brief All the chunks of memory in the arena
   * 
   */
  std::vector<ArenaAllocatorChunk> mChunks;

  /**
   * @brief The size of each chunk 
   * 
   */
  u64 mChunkSize = 0;
};
}  // namespace Delorean