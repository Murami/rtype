
#if defined (WIN32) || defined (_WIN32)

# include <iostream>
# include "WindowDirent.hh"

namespace	Dirent
{
  WindowDirent::WindowDirent(std::string directory)
  {
    _isOpen = false;
    if (directory.size() > MAX_PATH - 3)
      std::cerr << "Error: The directory path is too long (" << directory << ")" << std::endl;
    else
      {
	_handle = FindFirstFile((directory + "/*").c_str(), &_ffd);
	if (_handle == INVALID_HANDLE_VALUE)
	  std::cerr << "Error: Can't open the directory " << directory << std::endl;
	else
	  _isOpen = true;
      }
  }

  WindowDirent::~WindowDirent()
  {
    if (_isOpen)
      {
	FindClose(_handle);
	_isOpen = false;
      }
  }

  std::list<std::string>	WindowDirent::getFilesName()
  {
    std::list<std::string>	res;
    
    if (_isOpen)
      {
	do
	  {
	    if (_ffd.cFileName[0] != '.')
	      res.push_back(_ffd.cFileName);
	  } while (FindNextFile(_handle, &_ffd) != 0);
      }
    return (res);
  }

  std::list<std::string>	WindowDirent::getFilesNameByExtension(std::string ext)
  {
    std::list<std::string>	res;
    std::string				filename_ext;

    if (_isOpen)
      {
	ext = "." + ext;
	do
	  {
	    if (_ffd.cFileName[0] != '.')
	      {
		filename_ext = &_ffd.cFileName[strlen(_ffd.cFileName) - ext.size()];
		if (filename_ext == ext)
		  res.push_back(_ffd.cFileName);
	      }
	  } while (FindNextFile(_handle, &_ffd) != 0);
      }

    return (res);
  }

}

#endif /* WIN32 */
