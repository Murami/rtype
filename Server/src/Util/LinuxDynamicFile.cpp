
#if defined(__unix__) || defined(__APPLE__)

# include <dlfcn.h>
# include <iostream>
# include "LinuxDynamicFile.hh"

namespace	DynamicFile
{
  LinuxDynamicFile::LinuxDynamicFile()
  {
    _isOpen = false;
  }

  LinuxDynamicFile::LinuxDynamicFile(const std::string& filename)
  {
    _isOpen = false;
    if (!(_handle = dlopen(filename.c_str(), RTLD_LAZY | RTLD_GLOBAL)))
      std::cerr << "dlopen : " << dlerror() << std::endl;
    else
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
    if (!(_handle = dlopen(filename.c_str(), RTLD_LAZY | RTLD_GLOBAL)))
      std::cerr << "dlopen : " << dlerror() << std::endl;
    else
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
      std::cerr << "You don't have an open file" << std::endl;
    else
      {
	res = dlsym(_handle, symbol.c_str());
	if ((error = dlerror()) != NULL)
	  std::cerr << reinterpret_cast<char*>(error) << std::endl;
	else
	  return (res);
      }
    return (NULL);
  }
}

#endif /* __unix__ */
