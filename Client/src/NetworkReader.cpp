#include	<iostream>
#include	<cstring>

#include	"TcpConnection.hh"
#include	"NetworkReader.hh"
#include	"INetworkListener.hh"
#include	"RtypeProtocol.hh"

NetworkReader::NetworkReader(TcpConnection& tcpConnection) :
  _tcpConnection(tcpConnection)
{
  _expectedPacket = RtypeProtocol::T_HEADER;
  _tcpListener = NULL;
}

int			NetworkReader::run(Util::Mutex* mutex)
{
  char			buffer[4096];
  std::size_t		received;

  // Faire le buffer tournant circulaire
  std::cout << "\033[42mBeginning to read...\033[0m" << std::endl;
  while (_tcpConnection.isReading() &&
	 _tcpConnection.socket().receive(buffer, 4096, received) == sf::Socket::Done)
    {
      mutex->lock();
      std::cout << "\033[43mTreating datas...\033[0m" << std::endl;
      onReadData(buffer, received);
      mutex->unlock();
    }
  std::cout << "\033[44mEnding Thread...\033[0m" << std::endl;
  return (0);
}

void			NetworkReader::onReadData(void *data, std::size_t)
{
  RtypeProtocol::Header	header;
  RtypeProtocol::Magic	magic;

  std::cout << "\033[41m" << __FUNCTION__ << "\033[0m" << std::endl;
  std::memcpy(&header, data, sizeof(header));
  std::memcpy(&magic, static_cast<char *>(data) + sizeof(header), sizeof(magic));

  switch (header.type)
    {
    case RtypeProtocol::T_MAGIC_BAD_VERSION:
      std::cout << "Received bad magic version" << std::endl;
      break;
    case RtypeProtocol::T_MAGIC_ACCEPT:
      std::cout << "Received good magic number" << std::endl;
      break;
    default:
      std::cout << "unknown header" << std::endl;
      break;
    }

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
