#ifndef END_POINT_HH
# define END_POINT_HH

#include <string>

namespace Network
{

  class EndPoint
  {
  public:
    EndPoint(unsigned int port, const std::string & host);
    ~EndPoint();

    void			setPort(unsigned int port);
    void			setHost(const std::string & host);

    unsigned int		getPort() const;
    const std::string &		getHost() const;

  private:
    unsigned int		_port;
    std::string			_host;
  };

}

#endif
