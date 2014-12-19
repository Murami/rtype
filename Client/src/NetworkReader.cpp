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

void			NetworkReader::run()
{
  // Lancement du thread de lecture sur la socket
  // Le thread notifira NetworkReader lors de la lecture d'un packet
}

void			NetworkReader::onReadData(void *data, std::size_t size)
{
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
