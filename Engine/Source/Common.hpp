#pragma once

#include <cstdint>
#include <source_location>
#include <string_view>
#ifndef __cplusplus
#error "This is a c++ header! Something must went wrong"
#endif

#if __cplusplus >= 202302L
#pragma message "Generating c++23 code"
#else
#error "This code and features is meant to run on c++23"
#endif

#ifdef __has_cpp_attribute
#define HAS_ATTRIBUTE(attribute) __has_cpp_attribute(attribute)
#else
#define HAS_ATTRIBUTE(attribute)
#endif

#ifdef __has_include
#define HAS_INCLUDE(header) __has_include(header)
#else
#define HAS_INCLUDE(header)
#endif

#ifdef __cpp_inline_variables
#define INLINE inline
#else
#define INLINE
#endif

#if HAS_ATTRIBUTE(deprecated)
#define DEPRECATED(msg) [[deprecated(msg)]]
#else
#define DEPRECATED(msg)
#endif

#if HAS_ATTRIBUTE(nodiscard)
#define NODISCARD(msg) [[nodiscard(msg)]]
#else
#define NODISCARD(msg)
#endif

#if HAS_ATTRIBUTE(noreturn)
#define NORETURN [[noreturn]]
#else
#define NORETURN
#endif

#if __cpp_constexpr >= 201304  // Check for a specific version of a feature
#define CONSTEXPR constexpr
#else
#define CONSTEXPR inline
#endif

#include <iostream>
#include <print>
#include <string>

#define KB(kb) (kb * 1024)
#define MB(mb) (KB(mb * 1024))
#define GB(gb) (MB(gb * 1024))

typedef u_int64_t u64;
typedef u_int32_t u32;
typedef u_int16_t u16;
typedef u_int8_t u8;
typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

namespace Delorean
{

static std::string VerbosityToStr(int verbosity)
{
  switch (verbosity) {
    case 0:
      return "[INF]: ";
    case -1:
      return "[ERR]: ";
    default:
      return "[WRN]: ";
  }
}

struct format_string
{
  std::string_view str;
  std::source_location loc;

  format_string(const char* str, const std::source_location& loc =
                                     std::source_location::current())
      : str(str), loc(loc)
  {}
};

template <typename... T>
inline void Log(int verbosity, const format_string& fmt, T&&... args)
{
  const auto& loc = fmt.loc;
  std::string message(std::vformat(fmt, std::make_format_args(args)...));
  std::string out = VerbosityToStr(verbosity) + message;
  std::println("{}:{}: {}", loc.file_name(), loc.line(), out);
}

template <typename... T>
inline void LogInfo(std::string_view fmt, T&&... args)
{
  Log(0, fmt, std::forward<T>(args)...);
}
template <typename... T>
inline void LogWarn(std::string_view fmt, T&&... args)
{
  Log(1, fmt, std::forward<T>(args)...);
}
template <typename... T>
inline void LogErr(std::string_view fmt, T&&... args)
{
  Log(-1, fmt, std::forward<T>(args)...);
}
template <typename... T>
inline void NotImplemented(std::string_view fmt, T&&... args)
{
  LogWarn("[NOT IMPLEMENTED]: {}", fmt, std::forward<T>(args)...);
}

namespace Debug
{
template <typename... T>
inline void Log(int verbosity, std::string_view fmt, T&&... args)
{
#ifdef DEBUG_ENABLED
  std::string message(std::vformat(fmt, std::make_format_args(args)...));
  std::string out = VerbosityToStr(verbosity) + message;
  std::cout << out << std::endl;
#endif
}

template <typename... T>
inline void LogInfo(std::string_view fmt, T&&... args)
{
  Log(0, fmt, std::forward<T>(args)...);
}
template <typename... T>
inline void LogWarn(std::string_view fmt, T&&... args)
{
  Log(1, fmt, std::forward<T>(args)...);
}
template <typename... T>
inline void LogErr(std::string_view fmt, T&&... args)
{
  Log(-1, fmt, std::forward<T>(args)...);
}
template <typename... T>
inline void NotImplemented(std::string_view fmt, T&&... args)
{
  LogWarn("[NOT IMPLEMENTED]: {}", fmt, std::forward<T>(args)...);
}
}  // namespace Debug
}  // namespace Delorean