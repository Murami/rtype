#if defined(__linux__) || defined(__APPLE__)

# include <stdexcept>
# include <string.h>
# include "LinuxDirent.hh"

LinuxDirent::LinuxDirent(std::string directory)
{
  _dir = opendir(directory.c_str());
  if (_dir == NULL)
    throw (std::runtime_error("Error: Can't open the directory " + directory));
}

LinuxDirent::~LinuxDirent()
{
  closedir(_dir);
}

std::list<std::string>	LinuxDirent::getFilesName()
{
  struct dirent			*s_dir;
  std::list<std::string>	res;

  while ((s_dir = readdir(_dir)) != NULL)
    {
      if (s_dir->d_name[0] != '.')
	res.push_back(s_dir->d_name);
    }
  return (res);
}

std::list<std::string>	LinuxDirent::getFilesNameByExtension(std::string ext)
{
  struct dirent			*s_dir;
  std::list<std::string>	res;
  std::string			filename_ext;

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
  return (res);  
}

#endif /* __unix__ __APPLE__*/
