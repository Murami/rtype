
#include "IDynamicFile.hh"

#if defined (__unix__) || defined(__APPLE__)
# include "LinuxDynamicFile.hh"
#elif defined (WIN32) || (_WIN32)
# include "WindowDynamicFile.hh"
#endif

IDynamicFile*	create(const std::string& filename)
{
#if defined(__unix__)
  return (new LinuxDynamicFile(filename));
#elif defined(_WIN32) || defined(WIN32)
  return (new WindowDynamicFile(filename));
#else
#error "OS not supported"
#endif
  (void)filename;
  return (NULL);
}

IDynamicFile*	create()
{
#if defined(__unix__) || defined(__APPLE__)
  return (new LinuxDynamicFile());
#elif defined(_WIN32) || defined(WIN32)
  return (new WindowDynamicFile());
#else
#error "OS not supported"
#endif
  return (NULL);
}
