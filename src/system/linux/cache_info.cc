#include "deloreandb/system/cache_info.hpp"
#include <fstream>
#include <optional>
#include <string>
#include "deloreandb/common.hpp"

#ifdef DELOREAN_SYSTEM_LINUX
namespace Delorean
{

static u64 ReadCacheSize(const std::string& path)
{
  std::ifstream f(path);
  std::string s;
  f >> s;
  u64 v = std::stoul(s);
  if (s.back() == 'K')
    v = KB(v);
  if (s.back() == 'M')
    v = MB(v);
  return v;
}

std::optional<CacheInfo> Cache::DetectCacheInfo()
{
  CacheInfo info;
  info.L1 = ReadCacheSize("/sys/devices/system/cpu/cpu0/cache/index0/size");
  info.L2 = ReadCacheSize("/sys/devices/system/cpu/cpu0/cache/index2/size");
  info.L3 = ReadCacheSize("/sys/devices/system/cpu/cpu0/cache/index3/size");
  return info;
}
#endif
}