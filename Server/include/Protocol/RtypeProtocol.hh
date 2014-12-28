#ifndef		__RTYPE_PROTOCOL_HH__
# define	__RTYPE_PROTOCOL_HH__

# include	<stdint.h>

# if		!defined(__GNUC__) && !defined(__MINGW32__)
#  define PACKED(__body__) __pragma(pack(push, 1)) struct __body__ __pragma(pack(pop))
# else
#  define PACKED(__body__) struct __attribute__((packed)) __body__
# endif

namespace	RtypeProtocol
{
# define	MAX_MSG_SIZE	512

# define	PASS_MD5_SIZE	32

# define	PROTO_NAME_SIZE	32
# define	ROOM_NAME_SIZE	32
# define	MAP_NAME_SIZE	32

# define	USERNAME_SIZE	16
# define	PASSWORD_SIZE	16

# define	MAX_USERS	4

# define	NO_FLAG
# define	FLAG(a)	(1 << a)

# define	INPUT_NONE		NO_FLAG
# define	INPUT_FORWARD		FLAG(0)
# define	INPUT_BACKWARD		FLAG(1)
# define	INPUT_LEFT		FLAG(2)
# define	INPUT_RIGHT		FLAG(3)
# define	INPUT_PRIMARYFIRE	FLAG(4)
# define	INPUT_SECONDARYFIRE	FLAG(5)

static const int UdpPort = 3279;
static const int TcpPort = 3278;
static const uint32_t  minor_version = 0;
static const uint32_t  major_version = 1;
static const int8_t proto_name[] = "RType";

  enum			Type
    {
      T_MAGIC				= 0,
      T_MAGIC_BAD_VERSION		= 1,
      T_MAGIC_ACCEPT			= 2,
      T_CONNECTION			= 3,
      T_CONNECTION_ALREADY_CONNECTED	= 4,
      T_CONNECTION_INTERNAL_ERROR	= 5,
      T_CONNECTION_OK			= 6,
      T_DISCONNECTION			= 7,
      // 8 - obselete
      // 9 - obselete
      T_GETROOMINFO			= 10,
      T_ROOMINFO			= 11,
      T_ROOM_CREATE			= 12,
      T_ROOM_CREATE_ALREADY_EXIST	= 13,
      T_ROOM_CREATE_INTERNAL_ERROR	= 14,
      T_ROOM_CREATE_OK			= 15,
      T_ROOM_JOIN			= 16,
      T_ROOM_JOIN_NOT_FOUND		= 17,
      T_ROOM_JOIN_IS_FULL		= 18,
      T_ROOM_JOIN_BAD_PSWD		= 19,
      T_ROOM_JOIN_OK			= 20,
      T_ROOM_EXIT			= 21,
      T_ROOM_EXIT_OK			= 22,
      T_PING				= 25,
      T_PONG				= 26,
      T_MSG				= 27,
      T_READY				= 28,
      T_GAMESTART			= 29,
      T_GAMEEND				= 30,
      T_SCORE				= 31,
      T_MAPCHANGE			= 32,
      T_PLAYERINFO			= 33,
      T_POSITION			= 34,
      T_SPAWN				= 35,
      T_EVENT				= 36,
      T_DESTRUCTION			= 37,
      T_LIFE				= 38,
      T_BONUS				= 39,
      T_HEADER				= 40,
      T_HIT				= 41,
      T_DEATH				= 42,
      T_ENTITYREQUEST			= 43,
      T_ENTITYINFOS			= 44,
      T_ROOM_JOIN_STARTED		= 45,
      T_ROOM_DELETE			= 46,
      T_ROOM_HOST_LEAVED		= 47
    };

  enum Entity
    {
      T_CAMERA            = 1,
      T_PLAYER_1          = 2,
      T_PLAYER_2          = 3,
      T_PLAYER_3          = 4,
      T_PLAYER_4          = 5,
      T_MONSTER_LITTLE    = 6,
      T_MONSTER_BIG       = 7,
      T_WALL_1            = 10,
      T_WALL_2            = 11,
      T_WALL_3            = 12,
      T_WALL_4            = 13,
      T_BONUS_1           = 14,
      T_BONUS_2           = 15,
      T_BONUS_3           = 16,
      T_BONUS_4           = 17,
      T_MISSILE_FRIENDLY_LITTLE   = 18,
      T_MISSILE_FRIENDLY_BIG      = 19,
      T_MISSILE_ENNEMY_LITTLE     = 20,
      T_MISSILE_ENNEMY_BIG        = 21
    };

  PACKED(Header {
      uint32_t	type;
      uint32_t	data_size;
    };)

  PACKED(Magic {
      uint32_t	minor_version;
      uint32_t	major_version;
      int8_t	proto_name[PROTO_NAME_SIZE];
    };)

  PACKED(User {
      uint8_t	username[USERNAME_SIZE];
      uint16_t	port;
    };)

  PACKED(Message {
      uint32_t	room_id;
      uint32_t	user;
      uint8_t	message[MAX_MSG_SIZE];
    };)

  PACKED(RoomConnection {
      uint32_t	id;
      uint8_t	pass_md5[PASS_MD5_SIZE];
    };)

  PACKED(PingPong {
      uint32_t	id;
    };)

  PACKED(Score {
      uint32_t	user_id;
      uint32_t	score;
    };)

  PACKED(MapChange {
      uint8_t	map_name[MAP_NAME_SIZE];
    };)

  PACKED(GameReadyState {
      uint8_t	ready;
    };)

  PACKED(EndGame {
      uint8_t	victory;
    };)

  PACKED(Room {
      uint32_t	id;
      uint32_t	alive;
      uint8_t	connected_users[MAX_USERS][USERNAME_SIZE];
      uint32_t	nb_connected_users;
      uint8_t	password_flag;
      uint8_t	pass_md5[PASS_MD5_SIZE];
      uint8_t	room_name[ROOM_NAME_SIZE];
      uint8_t	ready_users[MAX_USERS];
      uint8_t	locked;
      uint32_t	users_id[MAX_USERS];
    };)

  //UDP

  PACKED(Position{
      int32_t		x;
      int32_t		y;
      // int8_t		orientation; // obselete
      // int32_t		state;       // obselete
    };)

  PACKED(Spawn{
      uint32_t	id;
      uint32_t	type;
      Position	position;
      uint32_t	life;
    };)

  PACKED(PositionEvent{
      uint32_t	id;
      Position	position;
    };)

  PACKED(Destruction{
      uint32_t	id;
    };)

  PACKED(EntityRequest{
      uint32_t	id;
    };)

  PACKED(Life{
      uint32_t	id;
      uint32_t	life;
    };)

  PACKED(Bonus{
      uint32_t	id;
      uint32_t	type;
    };)

  // obsolete !!!!!!!!
  PACKED(PingElem{
      uint32_t	id;
      Position	pos;
      uint32_t	life;
    };)

  PACKED(State{
      //uint32_t	id;  //inutile
      uint32_t	state;
    };)
}

#endif
