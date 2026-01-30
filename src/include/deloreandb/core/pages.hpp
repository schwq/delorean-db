#include <cassert>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include "deloreandb/common.hpp"

namespace Delorean
{

constexpr u64 PAGE_SIZE = KB(64);
constexpr u64 PAGE_MAGIC_N = 0xA3FC;

struct PageHeader
{
  u64 mMagicNum = PAGE_MAGIC_N;
  u64 mID = 0;
  u64 mColType = 0;
  u64 mCount = 0;
  u64 mMax = 0;
  u64 mMin = 0;
  u64 mFlags = 0;
};

struct Page
{
  PageHeader mHeader;
  std::byte mData[PAGE_SIZE - sizeof(PageHeader)];
};

class PageManager
{
 public:
  explicit PageManager(const std::string& path)
  {
    mFile.open(path, std::ios::binary | std::ios::in | std::ios::out |
                         std::ios::trunc);
    if (!mFile.is_open()) {
      LogErr("PageManager cannot open the file: {}", path);
    }
  }

  void Write(u64 id, const Page& page)
  {
    mFile.seekp(id * PAGE_SIZE);
    mFile.write(reinterpret_cast<const char*>(&page), PAGE_SIZE);
  }

  void Read(u64 id, Page& page)
  {
    mFile.seekg(id * PAGE_SIZE);
    mFile.read(reinterpret_cast<char*>(&page), PAGE_SIZE);
  }

  MAKE_NON_COPYABLE(PageManager)

 private:
  std::fstream mFile;
};

class PageStorageManager
{
 public:
  explicit PageStorageManager(const std::string& storagePath)
      : mStoragePath(storagePath)
  {
    if (!std::filesystem::exists(storagePath)) {
      LogErr("Path given to storage the pages is non valid: {}", storagePath);
    }
  }

  MAKE_NON_COPYABLE(PageStorageManager)

 private:
  std::string mStoragePath;
};

class BufferPool
{
 public:
  Page* GetPage(u64 id, PageManager& pm)
  {
    if (mPages.contains(id))
      return &mPages[id];

    Page page;
    pm.Read(id, page);
    mPages[id] = page;
    return &mPages[id];
  }

  void Flush(PageManager& pm)
  {
    for (auto& [id, page] : mPages) {
      pm.Write(id, page);
    }
  }

 private:
  std::unordered_map<u64, Page> mPages;
};

}  // namespace Delorean