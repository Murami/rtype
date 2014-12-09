
#ifndef _DYNAMIC_FILE_HH_
# define _DYNAMIC_FILE_HH_

# include <string>

namespace	DynamicFile
{
  class	IDynamicFile
  {
  public:
    virtual ~IDynamicFile() {}

    virtual void	open(const std::string& filename) = 0;
    virtual void	close() = 0;
    virtual void	*loadSymbol(const std::string& symbol) = 0;
  };

  IDynamicFile*	create();
  IDynamicFile*	create(const std::string& filename);
}

#endif /* _DYNAMIC_FILE_HH_ */
