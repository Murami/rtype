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
  const static	std::string	PORT_TCP_KEY;
  const static	std::string	PORT_UDP_KEY;

private:
  ConfigurationParser	_parser;
  std::string		_ip;
  int			_portTcp;
  int			_portUdp;

public:
  const std::string&	getIp() const;
  int			getPortTcp() const;
  int			getPortUdp() const;

public:
  ConnectionConfiguration();
  ~ConnectionConfiguration();
};

std::ostream&		operator<<(std::ostream&, const ConnectionConfiguration&);

#endif
