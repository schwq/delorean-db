#include "deloreandb/system/cache_info.hpp"
#include <optional>

namespace Delorean
{

std::optional<CacheInfo> Cache::DetectCacheInfo()
{
  return std::nullopt;
}

}  // namespace Delorean