
#ifndef _WINDOW_DYNAMIC_FILE_HH_
# define _WINDOW_DYNAMIC_FILE_HH_

# include <windows.h>
# include "IDynamicFile.hh"

class	WindowDynamicFile : public IDynamicFile
{
public:
  WindowDynamicFile();
  WindowDynamicFile(const std::string& filename);
  ~WindowDynamicFile();

  void	open(const std::string& filename);
  void	close();
  void	*loadSymbol(const std::string& symbol);

private:
  bool		_isOpen;
  HMODULE	_handle;
};

#endif /* _WINDOW_DYNAMIC_FILE_HH_ */
