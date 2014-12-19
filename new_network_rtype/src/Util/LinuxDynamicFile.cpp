#if defined(__linux__) || defined(__APPLE__)

# include <stdexcept>
# include <dlfcn.h>
# include "LinuxDynamicFile.hh"

LinuxDynamicFile::LinuxDynamicFile()
{
  _isOpen = false;
}

LinuxDynamicFile::LinuxDynamicFile(const std::string& filename)
{
  if (!(_handle = dlopen(filename.c_str(), RTLD_LAZY)))
    throw (std::runtime_error(dlerror()));
  _isOpen = true;
}

LinuxDynamicFile::~LinuxDynamicFile()
{
  if (_isOpen == true)
    dlclose(_handle);
}

void	LinuxDynamicFile::open(const std::string& filename)
{
  if (_isOpen == true)
    {
      dlclose(_handle);
      _isOpen = false;
    }
  if (!(_handle = dlopen(filename.c_str(), RTLD_LAZY)))
    throw (std::runtime_error(dlerror()));
  _isOpen = true;
}

void	LinuxDynamicFile::close()
{
  if (_isOpen == true)
    dlclose(_handle);
  _isOpen = false;
}

void*	LinuxDynamicFile::loadSymbol(const std::string& symbol)
{
  void	*res;
  void	*error;

  if (!_isOpen)
    throw (std::runtime_error("You don't have an open file"));
  res = dlsym(_handle, symbol.c_str());
  if ((error = dlerror()) != NULL)
    throw (std::runtime_error(reinterpret_cast<char*>(error)));
  return (res);
}

#endif /* __unix__ */
