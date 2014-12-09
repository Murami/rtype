
#ifndef _DIRENT_HH_
# define _DIRENT_HH_

# include <list>
# include <string>

namespace	Dirent
{
  class	IDirent
  {
  public:
    virtual ~IDirent() {}
    virtual std::list<std::string>	getFilesName() = 0;
    virtual std::list<std::string>	getFilesNameByExtension(std::string) = 0;
  };

  IDirent	*create(std::string directory);
  extern std::string	separator;
}

#endif /* _DIRENT_HH_ */
