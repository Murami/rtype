#include <stdexcept>
#if defined (WIN32) || defined (_WIN32)

# include <iostream>
# include "WindowDynamicFile.hh"

namespace	DynamicFile
{
  WindowDynamicFile::WindowDynamicFile()
  {
    _isOpen = false;
  }

  WindowDynamicFile::WindowDynamicFile(const std::string& filename)
  {
    _isOpen = false;
    _handle = LoadLibrary(filename.c_str());
    if (_handle == NULL)
      std::cerr << "Can't open the library " << filename << std::endl;
    else
      _isOpen = true;
  }

  WindowDynamicFile::~WindowDynamicFile()
  {
    if (_isOpen == true)
      FreeLibrary(_handle);
  }

  void	WindowDynamicFile::open(const std::string& filename)
  {
    if (_isOpen == true)
      {
	FreeLibrary(_handle);
	_isOpen = false;
      }
    if ((_handle = LoadLibrary(TEXT(filename.c_str()))) == NULL)
      {
	char *str;

	FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		       NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&str, 0, NULL);
	std::cerr << "Can't open the library \"" << filename << "\"\n" << str << std::endl;
      }
    else
      _isOpen = true;
  }

  void	WindowDynamicFile::close()
  {
    if (_isOpen == true)
      FreeLibrary(_handle);
    _isOpen = false;
  }

  void*	WindowDynamicFile::loadSymbol(const std::string& name)
  {
    void	*res;

    if (!_isOpen)
      std::cerr << "You don't have an open file" << std::endl;
    else
      {
	res = reinterpret_cast<void *>(GetProcAddress(_handle, TEXT(name.c_str())));
	if (res == NULL)
	  {
	    char *str;

	    FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			   NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&str, 0, NULL);
	    std::cerr << "Can't load the symbol \"" << name << "\"\n" << str << std::endl;
	  }
	else
	  return (res);
      }
    return (NULL);
  }
}

#endif /* WIN32 */
