#include	"ConnectionConfiguration.hh"

const std::string	ConnectionConfiguration::CONF_FILE = "./connection.conf";
const std::string	ConnectionConfiguration::IP_KEY = "IP";
const std::string	ConnectionConfiguration::PORT_TCP_KEY = "PORT_TCP";
const std::string	ConnectionConfiguration::PORT_UDP_KEY = "PORT_UDP";

ConnectionConfiguration::ConnectionConfiguration()
{
  std::stringstream ssTcp;
  std::stringstream ssUdp;

  if (!_parser.parse(CONF_FILE))
    return ;
  try
    {
      _ip = _parser.getValueByName(IP_KEY);
      ssTcp << _parser.getValueByName(PORT_TCP_KEY);
      ssTcp >> _portTcp;
      ssUdp << _parser.getValueByName(PORT_UDP_KEY);
      ssUdp >> _portUdp;
    }
  catch (std::runtime_error& e)
    {
      std::cerr << e.what() << std::endl;
      return;
    }
}

const std::string&	ConnectionConfiguration::getIp() const
{
  return (_ip);
}

int			ConnectionConfiguration::getPortTcp() const
{
  return (_portTcp);
}

int			ConnectionConfiguration::getPortUdp() const
{
  return (_portUdp);
}

ConnectionConfiguration::~ConnectionConfiguration()
{
}
