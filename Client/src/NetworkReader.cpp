#include	<iostream>
#include	"TcpConnection.hh"
#include	"NetworkReader.hh"
#include	"INetworkListener.hh"
#include	"RtypeProtocol.hh"

const int	NetworkReader::BUFFER_SIZE = 4096;

NetworkReader::NetworkReader(TcpConnection& tcpConnection) :
  _tcpConnection(tcpConnection)
{
  _expectedPacket = RtypeProtocol::T_HEADER;
  _tcpListener = NULL;
}

int			NetworkReader::run()
{
  char			buffer[4096];
  std::size_t		received;

  // Faire le buffer tournant circulaire
  std::cout << "\033[42mBeginning to read...\033[0m" << std::endl;
  while (_tcpConnection.isRunning() &&
	 _tcpConnection.socket().receive(buffer, 4096, received) == sf::Socket::Done)
    {
      std::cout << "\033[43mTreating datas...\033[0m" << std::endl;
      onReadData(buffer, received);
    }
  std::cout << "\033[44mEnding Thread...\033[0m" << std::endl;
  return (0);
}

void			NetworkReader::onReadData(void *, std::size_t)
{
  std::cout << "\033[41m" << __FUNCTION__ << "\033[0m" << std::endl;
  // Lors de la reception d'un packet, cette methode sera appelee.
  // Elle construira la bonne structure pour l'envoyer au RtypeClient (listener)
  // Et en fonction du type recu, il faudra changer le type de packet attendu
}

void			NetworkReader::setExpectedPacket(RtypeProtocol::Type packetType)
{
  _expectedPacket = packetType;
}

RtypeProtocol::Type	NetworkReader::getExpectedPacket()
{
  return (_expectedPacket);
}

NetworkReader::~NetworkReader() {}
