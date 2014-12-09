
#ifndef _LINUX_DIRENT_HH_
# define _LINUX_DIRENT_HH_

# include <dirent.h>
# include "IDirent.hh"

namespace	Dirent
{
  class	LinuxDirent : public IDirent
  {
  public:
    LinuxDirent(std::string directory);
    ~LinuxDirent();
    
    std::list<std::string>	getFilesName();
    std::list<std::string>	getFilesNameByExtension(std::string ext);
    
  private:
    DIR*	_dir;
  };
}

#endif /*_LINUX_DIRENT_HH_ */
