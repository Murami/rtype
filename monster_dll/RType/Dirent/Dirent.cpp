
#include "IDirent.hh"

#if defined (__unix__)
# include "LinuxDirent.hh"
#elif defined (WIN32) || defined (_WIN32)
# include "WindowDirent.hh"
#endif
IDirent*	create(std::string directory)
{
#if defined(__unix__)
  return (new LinuxDirent(directory));
#elif defined(_WIN32) || defined (WIN32)
  return (new WindowDirent(directory));
#else
#error "OS not supported"
#endif
  (void)directory;
  return (NULL);
}

#if defined(__unix__)
  std::string separator = "/";
#elif defined(_WIN32) || defined (WIN32)
  std::string separator = "\\";
#else
#error "OS not supported"
#endif
