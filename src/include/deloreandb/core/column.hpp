
#include <cstring>
#include <type_traits>
#include "deloreandb/common.hpp"
#include "deloreandb/mem/arena_alloc.hpp"
namespace Delorean
{

template <typename T>
class Column
{
 public:
  explicit Column(ArenaAllocator& arena, u64 count) : mCount(count)
  {
    mData = arena.AllocType_SIMD<T>(count, 64);
  }

  T& operator[](u64 i) { return mData[i]; }
  const T& operator[](u64 i) const { return mData[i]; }

  T* Data() { return mData; }
  u64 Count() const { return mCount; }

  // Dont copy raw pointers
  MAKE_NON_COPYABLE(Column)

  void Copy(ArenaAllocator& arena, Column<T>& other)
  {
    if (this == &other)
      return;
    static_assert(std::is_trivially_copyable_v<T>,
                  "Column Copy requires trivially copyable T");
    mCount = other.Count();
    const u64 size = mCount * sizeof(T);
    mData = arena.AllocType_SIMD<T>(mCount, 64);
    std::memcpy(mData, other.Data(), size);
  }

 private:
  T* mData;
  u64 mCount;
};

}  // namespace Delorean