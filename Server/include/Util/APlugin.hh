#ifndef	_PLUGIN_HH_
# define _PLUGIN_HH_

# include <string>

class	APlugin
{
public:
  virtual ~APlugin() {}
  const std::string&	getName() const;

protected:
  std::string	_name;
};

#endif /* _PLUGIN_HH_ */
