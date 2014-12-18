
#ifndef _WINDOW_DIRENT_HH_
# define _WINDOW_DIRENT_HH_

# include <windows.h>
# include "IDirent.hh"

class	WindowDirent : public IDirent
{
public:
  WindowDirent(std::string directory);
  ~WindowDirent();

  std::list<std::string>	getFilesName();
  std::list<std::string>	getFilesNameByExtension(std::string ext);

private:
  HANDLE			_handle;
  WIN32_FIND_DATA	_ffd;
};

#endif
