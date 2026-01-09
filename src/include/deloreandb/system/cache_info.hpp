#pragma once
#include <optional>
#include "deloreandb/common.hpp"

namespace Delorean
{
struct CacheInfo
{
  u64 L1 = 0;
  u64 L2 = 0;
  u64 L3 = 0;
};

class Cache
{
 public:
  static std::optional<CacheInfo> DetectCacheInfo();
};
}  // namespace Delorean