#pragma once

#include <string_view>

namespace Delorean
{

class DeloreanDB
{
 public:
  static DeloreanDB& GetInstance()
  {
    static DeloreanDB instance;
    return instance;
  }

 private:
  explicit DeloreanDB() {}

  DeloreanDB(const DeloreanDB&) = delete;
  DeloreanDB& operator=(const DeloreanDB&) = delete;
};

}  // namespace Delorean