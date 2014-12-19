#ifndef		__RTYPE_PROTOCOL_HH__
# define	__RTYPE_PROTOCOL_HH__

# include	<stdint.h>

# ifdef		WIN32
#  pragma pack(push, 1)
#  define PACKED(__body__) struct __body__
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

static const uint32_t  minor_version = 0;
static const uint32_t  major_version = 1;
static const uint8_t proto_name[] = "RType";

  enum			Type
    {
      //TCP
      T_MAGIC				= 0,
      T_MAGIC_BAD_VERSION		= 52,
      T_MAGIC_ACCEPT			= 53,

      T_CONNECTION			= 1,
      T_DISCONNECTION			= 2,
      T_ROOMLIST			= 3,
      T_GETROOMLIST			= 4,
      T_GETROOMINFO			= 5,
      T_ROOMINFO			= 6,
      T_ROOMCONNECTION			= 7,
      T_ROOMDISCONNECTION		= 8,
      T_PING				= 9,
      T_PONG				= 10,
      T_GAMESTART			= 11,
      T_GAMEEND				= 12,
      T_SCORE				= 13,
      T_MAPCHANGE			= 14,
      T_PLAYERINFO			= 15,
      T_MSG				= 16,
      T_HEADER				= 17,
      //UDP
      T_POSITION			= 18,
      T_SPAWN				= 19,
      T_EVENT				= 20,
      T_DESTRUCTION			= 21,
      T_LIFE				= 22,
      T_BONUS				= 23
    };

  PACKED(Header {
      uint32_t	type;
      uint32_t	data_size;
    };)

  PACKED(Magic {
      uint32_t	minor_version;
      uint32_t	major_version;
      uint8_t	proto_name[PROTO_NAME_SIZE];
    };)

  PACKED(User {
      uint8_t	username[USERNAME_SIZE];
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
      uint8_t	connected_users[MAX_USERS][USERNAME_SIZE];
      uint32_t	nb_connected_users;
      uint8_t	password_flag;
      uint8_t	room_name[ROOM_NAME_SIZE];
      uint8_t	ready_users[MAX_USERS];
      uint8_t	locked;
      uint32_t	users_id[MAX_USERS];
    };)

  //UDP

  PACKED(Position{
      int32_t		x;
      int32_t		y;
      int8_t		orientation;
      int32_t		state;
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

  PACKED(destruction{
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

  PACKED(PingElem{
      uint32_t	id;
      Position	pos;
      uint32_t	life;
    };)

  PACKED(State{
      uint32_t	id;
      uint32_t	state;
    };)
}

#endif
