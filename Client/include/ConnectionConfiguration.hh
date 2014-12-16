#ifndef		__CONNECTIONCONFIGURATION_HH__
# define	__CONNECTIONCONFIGURATION_HH__

# include	<string>
# include	<iostream>
# include	<sstream>
# include	"ConfigurationParser.hh"

class		ConnectionConfiguration
{
public:
  const static	std::string	CONF_FILE;
  const static	std::string	IP_KEY;
  const static	std::string	PORT_KEY;

private:
  ConfigurationParser	_parser;
  std::string		_ip;
  int			_port;

public:
  const std::string&	getIp() const;
  int			getPort() const;

public:
  ConnectionConfiguration();
  ~ConnectionConfiguration();
};

std::ostream&		operator<<(std::ostream&, const ConnectionConfiguration&);

#endif
