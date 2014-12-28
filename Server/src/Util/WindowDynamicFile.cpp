#include <stdexcept>
#if defined (WIN32) || defined (_WIN32)

# include "WindowDynamicFile.hh"

namespace	DynamicFile
{
  WindowDynamicFile::WindowDynamicFile()
  {
	  _isOpen = false;
  }

  WindowDynamicFile::WindowDynamicFile(const std::string& filename)
  {
	  _handle = LoadLibrary(filename.c_str());
	  if (_handle == NULL)
		  throw (std::runtime_error("Can't open the library " + filename));
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
		  throw (std::runtime_error("Can't open the library \"" + filename + "\"\n" + str));
	  }
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
		  throw (std::runtime_error("You don't have an open file"));
	  res = reinterpret_cast<void *>(GetProcAddress(_handle, TEXT(name.c_str())));
	  if (res == NULL)
	  {
		  char *str;

		  FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			  NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&str, 0, NULL);
		  throw (std::runtime_error("Can't load the symbol \"" + name + "\"\n" + str));
	  }
	  return (res);
  }
}

#endif /* WIN32 */