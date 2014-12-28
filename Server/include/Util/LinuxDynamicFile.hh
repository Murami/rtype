
#ifndef _LINUX_DYNAMIC_FILE_HH_
# define _LINUX_DYNAMIC_FILE_HH_

# include <string>
# include "IDynamicFile.hh"

namespace	DynamicFile
{
  class	LinuxDynamicFile : public IDynamicFile
  {
  public:
    LinuxDynamicFile();
    LinuxDynamicFile(const std::string& filename);
    ~LinuxDynamicFile();

    void	open(const std::string& filename);
    void	close();
    void	*loadSymbol(const std::string& symbol);

  private:
    void	*_handle;
    bool	_isOpen;
  };
}
#endif /* _LINUX_DYNAMIC_FILE_HH_ */
