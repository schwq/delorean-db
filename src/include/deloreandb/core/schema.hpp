#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include "deloreandb/core/types.hpp"

namespace Delorean
{

struct SchemaColumn
{
  std::string mName;
  ValueType mType;

  bool bIsPrimaryKey = false;
};

struct Schema
{
  std::vector<SchemaColumn> mColumns;

  enum SchemaError
  {
    None,
    EmptySchema,
    DuplicateColumn,
    MissingPrimaryKey,
    MultiplePrimaryKeys,
    EmptyColumnName
  };

  static SchemaError Validate(const Schema& schema)
  {

    if (schema.mColumns.empty())
      return EmptySchema;

    u64 primaryKeysCount = 0;

    std::unordered_set<std::string> names;
    names.reserve(schema.mColumns.size());

    for (const auto& col : schema.mColumns) {
      if (col.mName.empty())
        return EmptyColumnName;

      if (!names.insert(col.mName).second)
        return DuplicateColumn;

      if (col.bIsPrimaryKey)
        primaryKeysCount++;
    }
    if (primaryKeysCount != 1)
      return (primaryKeysCount > 1) ? MultiplePrimaryKeys : MissingPrimaryKey;

    return None;
  }
};

}  // namespace Delorean