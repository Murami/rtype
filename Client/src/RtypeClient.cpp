#include	<cstring>
#include	<stdexcept>

#if defined(__linux__) || defined(__APPLE__)
# include <arpa/inet.h>
#elif defined(WIN32) || defined (_WIN32)
# include <Winsock2.h>
# include <windows.h>
#endif

#include	"MenuController.hh"
#include	"MenuView.hh"
#include	"TcpConnection.hh"
#include	"UdpConnection.hh"
#include	"RtypeClient.hh"
#include	"SoundManager.hh"
#include	"GameController.hh"
#include	"GameView.hh"
#include	"RtypeProtocol.hh"

RtypeClient::RtypeClient()
{
  _mutex.lock();
  _tcpConnection = new TcpConnection(_configuration, &_mutex);
  _tcpConnection->setTcpNetworkListener(this);
  _udpConnection = new UdpConnection(_configuration, &_mutex);
  _udpConnection->setUdpNetworkListener(this);
  _initEntityMap();
}

RtypeClient::~RtypeClient()
{
  delete _menuView;
  delete _menuController;
  delete _window;
}

void		RtypeClient::run()
{
  RtypeProtocol::Header header;
  RtypeProtocol::Magic	magic;

  _window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width,
					       sf::VideoMode::getDesktopMode().height),
				 "Rtype"// , sf::Style::Fullscreen
				 );

  _window->setKeyRepeatEnabled(false);

  _menuView = new MenuView(*_window);
  _menuController = new MenuController(*_menuView);
  _gameView = new GameView();
  _gameController = new GameController(*_gameView);

  _menuView->addObserver(_menuController);
  _menuController->setMenuListener(this);
  _gameView->addObserver(_gameController);
  _gameController->setGameListener(this);

  if (!_tcpConnection->connect())
    throw (std::runtime_error("TCP connect"));

  if (!_udpConnection->connect())
    throw (std::runtime_error("UDP connect"));

  header.type = RtypeProtocol::T_MAGIC;
  header.data_size = sizeof(magic);

  magic.minor_version = htonl(RtypeProtocol::minor_version);
  magic.major_version = htonl(RtypeProtocol::major_version);

  std::memset(&magic.proto_name[0], 0, PROTO_NAME_SIZE);
  std::memcpy(reinterpret_cast<char *>(&magic.proto_name[0]),
  	      RtypeProtocol::proto_name,
  	      std::strlen(reinterpret_cast<const char *>(RtypeProtocol::proto_name)));
  char *buffer = new char[sizeof(header) + sizeof(magic)];
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &magic, sizeof(magic));

  _tcpConnection->startRead();
  _tcpConnection->startWrite();

  _udpConnection->startRead();

  _tcpConnection->write(&buffer[0], sizeof(header) + sizeof(magic));

  _menuView->run(*_window, &_mutex);
  _tcpConnection->stopRead();
  _tcpConnection->stopWrite();
  _tcpConnection->joinRead();
  _tcpConnection->joinWrite();

  _udpConnection->stopRead();
  _udpConnection->joinRead();
}

// IUdpNetworkListener

void	RtypeClient::onPlayerInfo()
{
}

void	RtypeClient::onPosition(RtypeProtocol::PositionEvent position)
{
  _gameController->updateEntityPosition(position.id, position.position);
}

void	RtypeClient::onSpawn(RtypeProtocol::Spawn spawn)
{
  _gameController->spawnEntity(spawn);
}

void	RtypeClient::onDestruction(RtypeProtocol::Destruction destruct)
{
  _gameController->deleteEntity(destruct.id);
}

void	RtypeClient::onLife(RtypeProtocol::Life life)
{
  _gameController->updateLife(life.id, life.life);
}

void	RtypeClient::onBonus()
{
}

void	RtypeClient::onHit()
{
}

void	RtypeClient::onDeath()
{
}

void	RtypeClient::onEntityInfo()
{
}

// IKeyListener

void	RtypeClient::onKeyEvent(uint32_t event)
{
  RtypeProtocol::Header header;
  RtypeProtocol::State state;
  char		buffer[sizeof(state) + sizeof(header)];

  state.state = htonl(event);
  header.type = htonl(RtypeProtocol::T_EVENT);
  header.data_size = htonl(sizeof(state));
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &state, sizeof(state));
  _udpConnection->write(&buffer[0], sizeof(state) + sizeof(header));
}


void	RtypeClient::onRoomLeaveFromGame()
{
  RtypeProtocol::Header header;

  header.type = RtypeProtocol::T_ROOM_EXIT;
  header.data_size = 0;
  _tcpConnection->write(&header, sizeof(header));
}

void	RtypeClient::onExitFromGame()
{
  onRoomLeaveFromMenu();
}

void	RtypeClient::onEntityRequestFromGame(uint32_t id)
{
  RtypeProtocol::Header header;
  RtypeProtocol::EntityRequest request;
  char		buffer[sizeof(header) + sizeof(request)];

  header.type = htonl(RtypeProtocol::T_ENTITYREQUEST);
  header.data_size = htonl(sizeof(request));
  request.id = htonl(id);
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &request, sizeof(request));
  _udpConnection->write(&buffer[0], sizeof(header) + sizeof(request));
}

// ITcpNetworkListener

void	RtypeClient::onMagicBadVersion()
{
  throw (std::runtime_error("connect to server : bad magic version"));
}

void	RtypeClient::onMagicAccept()
{
}

void	RtypeClient::onConnectionAlreadyConnected()
{
}

void	RtypeClient::onConnectionInternalError()
{
}

void	RtypeClient::onConnectionOk()
{
}

void	RtypeClient::onDisconnection()
{
  _menuView->stop();
  _menuView->setGameRunning(false);
}

void	RtypeClient::onRoomInfo(RtypeProtocol::Room room)
{
  _menuController->setPlayersNameList(room);

  if (room.alive)
    _menuController->addToRoomList(room);
  else
    _menuController->deleteFromRoomList(room);
}

void	RtypeClient::onRoomCreateAlreadyExist(RtypeProtocol::Room)
{
}

void	RtypeClient::onRoomCreateInternalError(RtypeProtocol::Room)
{
}

void	RtypeClient::onRoomCreateOk()
{
}

void	RtypeClient::onRoomJoinNotFound(RtypeProtocol::Room)
{
}

void	RtypeClient::onRoomJoinIsFull(RtypeProtocol::Room)
{
}

void	RtypeClient::onRoomJoinBadPswd(RtypeProtocol::Room)
{
}

void	RtypeClient::onRoomJoinOk()
{
  _menuController->joinRoom();
}

void	RtypeClient::onRoomExitOk(RtypeProtocol::Room)
{
  RtypeProtocol::Header header;
  header.type = RtypeProtocol::T_ROOM_EXIT;
  header.data_size = 0;
  _tcpConnection->write(&header, sizeof(header));
}

void	RtypeClient::onPing(RtypeProtocol::PingPong)
{
}

void	RtypeClient::onGameStart()
{
  _menuView->setGameRunning(true);
}

bool	RtypeClient::letStart()
{
  _gameView->run(*_window, &_mutex);
  _menuView->reset();
  _menuView->run(*_window, &_mutex);
  return (true);
}

void	RtypeClient::onGameEnd(RtypeProtocol::EndGame end)
{
  bool	b;

  b = (bool) end.victory;
  _gameController->gameEnd(b);
}

void	RtypeClient::onScore(RtypeProtocol::Score)
{
}

void	RtypeClient::onMessage(RtypeProtocol::Message)
{
}

void	RtypeClient::onHostLeftRoom()
{
}

void	RtypeClient::onDeleteRoom(RtypeProtocol::Room room)
{
  _menuController->deleteFromRoomList(room);
}

void	RtypeClient::onServerExited()
{
  _gameView->onExit();
  _gameView->stop();
  _menuView->setGameRunning(false);
  _menuView->stop();
}

bool	RtypeClient::onConnectFromMenu(const std::string & login)
{
  RtypeProtocol::Header header;
  RtypeProtocol::User user;
  char	*buffer = new char[sizeof(header) + sizeof(user)];

  SoundManager::Play("bip");
  header.type = RtypeProtocol::T_CONNECTION;
  header.data_size = sizeof(RtypeProtocol::User);
  strcpy(reinterpret_cast<char *>(&user.username[0]), login.c_str());
  user.port = htons(_udpConnection->getLocalPort());
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &user, sizeof(user));
  _tcpConnection->write(&buffer[0], sizeof(header) + sizeof(user));
  return (true);
}

bool	RtypeClient::onDisconnectFromMenu()
{
  RtypeProtocol::Header header;

  header.type = RtypeProtocol::T_DISCONNECTION;
  header.data_size = 0;
  _menuView->stop();
  _menuView->setGameRunning(false);
  _tcpConnection->write(&header, sizeof(header));
  return (true);
}

bool	RtypeClient::onRoomConnectFromMenu(int id, const std::string& pass)
{
  RtypeProtocol::Header header;
  RtypeProtocol::RoomConnection room;
  char buffer[sizeof(header) + sizeof(room)];

  header.type = RtypeProtocol::T_ROOM_JOIN;
  header.data_size = sizeof(room);
  room.id = htonl(id);
  strcpy(reinterpret_cast<char *>(room.pass_md5), pass.c_str());
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &room, sizeof(room));
  _tcpConnection->write(&buffer, sizeof(header) + sizeof(room));
  return (true);
}

bool	RtypeClient::onRoomLeaveFromMenu()
{
  RtypeProtocol::Header header;

  header.type = RtypeProtocol::T_ROOM_EXIT;
  header.data_size = 0;
  _tcpConnection->write(&header, sizeof(header));
  return (true);
}

bool	RtypeClient::onUserReadyFromMenu()
{
  RtypeProtocol::Header header;

  header.type = RtypeProtocol::T_READY;
  header.data_size = 0;
  _tcpConnection->write(&header, sizeof(header));
  return (true);
}

bool	RtypeClient::onUserMessageFromMenu(RtypeProtocol::Message)
{
  return (true);
}

bool	RtypeClient::onCreateRoomFromMenu(const std::string& roomName,
					  const std::string& password)
{
  RtypeProtocol::Header header;
  RtypeProtocol::Room	room;
  char			buffer[sizeof(header) + sizeof(room)];

  header.type = RtypeProtocol::T_ROOM_CREATE;
  header.data_size = sizeof(room);
  std::memset(&room, 0, sizeof(room));
  strcpy(reinterpret_cast<char *>(room.room_name), roomName.c_str());
  strcpy(reinterpret_cast<char *>(room.pass_md5), password.c_str());
  std::memcpy(&buffer[0], &header, sizeof(header));
  std::memcpy(&buffer[sizeof(header)], &room, sizeof(room));
  _tcpConnection->write(&buffer[0], sizeof(header) + sizeof(room));
  return (true);
}

void	RtypeClient::_initEntityMap()
{
  _entityMap[1] = RtypeProtocol::T_CAMERA;
  _entityMap[2] = RtypeProtocol::T_PLAYER_1;
  _entityMap[3] = RtypeProtocol::T_PLAYER_2;
  _entityMap[4] = RtypeProtocol::T_PLAYER_3;
  _entityMap[5] = RtypeProtocol::T_PLAYER_4;
  _entityMap[6] = RtypeProtocol::T_MONSTER_LITTLE;
  _entityMap[7] = RtypeProtocol::T_MONSTER_BIG;
  _entityMap[10] = RtypeProtocol::T_WALL_1;
  _entityMap[11] = RtypeProtocol::T_WALL_2;
  _entityMap[12] = RtypeProtocol::T_WALL_3;
  _entityMap[13] = RtypeProtocol::T_WALL_4;
  _entityMap[14] = RtypeProtocol::T_BONUS_1;
  _entityMap[15] = RtypeProtocol::T_BONUS_2;
  _entityMap[16] = RtypeProtocol::T_BONUS_3;
  _entityMap[17] = RtypeProtocol::T_BONUS_4;
  _entityMap[18] = RtypeProtocol::T_MISSILE_FRIENDLY_LITTLE;
  _entityMap[19] = RtypeProtocol::T_MISSILE_FRIENDLY_BIG;
  _entityMap[20] = RtypeProtocol::T_MISSILE_ENNEMY_LITTLE;
  _entityMap[21] = RtypeProtocol::T_MISSILE_ENNEMY_BIG;
}
