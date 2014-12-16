#include	"ConnectionConfiguration.hh"

const std::string	ConnectionConfiguration::CONF_FILE = "./connection.conf";
const std::string	ConnectionConfiguration::IP_KEY = "IP";
const std::string	ConnectionConfiguration::PORT_KEY = "PORT";

ConnectionConfiguration::ConnectionConfiguration()
{
  std::stringstream ss;
  if (!_parser.parse(CONF_FILE))
    return ;
  try
    {
      _ip = _parser.getValueByName("IP");
      ss << _parser.getValueByName("PORT");
      ss >> _port;
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

int			ConnectionConfiguration::getPort() const
{
  return (_port);
}

ConnectionConfiguration::~ConnectionConfiguration()
{
}
