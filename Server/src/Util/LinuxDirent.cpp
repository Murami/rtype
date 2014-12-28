
#if defined (__unix__) || defined (__APPLE__)

# include <iostream>
# include <string.h>
# include "LinuxDirent.hh"

namespace	Dirent
{
  LinuxDirent::LinuxDirent(std::string directory)
  {
    _isOpen = false;
    _dir = opendir(directory.c_str());
    if (_dir == NULL)
      std::cerr << "Error: Can't open the directory " << directory << std::endl;
    else
      _isOpen = true;
  }

  LinuxDirent::~LinuxDirent()
  {
    if (_isOpen == true)
      closedir(_dir);
  }

  std::list<std::string>	LinuxDirent::getFilesName()
  {
    struct dirent			*s_dir;
    std::list<std::string>	res;

    if (_isOpen)
      {
	while ((s_dir = readdir(_dir)) != NULL)
	  {
	    if (s_dir->d_name[0] != '.')
	      res.push_back(s_dir->d_name);
	  }
      }
    return (res);
  }

  std::list<std::string>	LinuxDirent::getFilesNameByExtension(std::string ext)
  {
    struct dirent			*s_dir;
    std::list<std::string>	res;
    std::string			filename_ext;

    if (_isOpen)
      {
	ext = "." + ext;
	while ((s_dir = readdir(_dir)) != NULL)
	  {
	    if (s_dir->d_name[0] != '.')
	      {
		filename_ext = &s_dir->d_name[strlen(s_dir->d_name) - ext.size()];
		if (filename_ext == ext)
		  res.push_back(s_dir->d_name);

	      }
	  }
      }
    return (res);
  }
}
#endif /* __unix__ */
