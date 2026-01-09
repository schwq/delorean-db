
#ifdef _WIN32
#ifdef _WIN64
#define DELOREAN_SYSTEM_WINDOWS_x64
#include <Windows.h>
#else
#error "This engine does not support Windows x86 build"
#endif

#elif defined(__MINGW32__)
#defne DELOREAN_SYSTEM_WINDOWS_MING32
#include <Window.h>

#elif defined(__APPLE__) || defined(__MACH__)
#define DELOREAN_SYSTEM_MACOS

#elif defined(__ANDROID__)
#define DELOREAN_SYSTEM_ANDROID
#error "This engine does not support Android builds"

#elif defined(__linux__)
#define DELOREAN_SYSTEM_LINUX

#else
#error "This engine cannot find the current plataform being used"
#endif
