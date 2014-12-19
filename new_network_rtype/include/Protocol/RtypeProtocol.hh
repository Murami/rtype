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
static const int8_t proto_name[] = "RType";

  enum			Type
    {
      //TCP
      T_MAGIC				                  = 0, //send magic header from client
      T_MAGIC_BAD_VERSION             = 1, //reponse from server
      T_MAGIC_ACCEPT                  = 2, //reponse from server
      T_CONNECTION                    = 3, //send connection request with username from client
      T_CONNECTION_ALREADY_CONENCTED  = 4, //reponse from server
      T_CONNECTION_INTERNAL_ERROR     = 5, //reponse from server
      T_CONNECTION_OK                 = 6, //reponse from server
      T_DISCONNECTION			            = 7, //send from client
      T_ROOMLIST			                = 8, //request room list from client
      T_GETROOMLIST			              = 9, //request room list from client
      T_GETROOMINFO			              = 10,//request room info from client
      T_ROOMINFO                      = 11,//response from server with room info
      T_ROOM_CREATE                   = 12,//client request a new room
      T_ROOM_CREATE_ALREADY_EXIST     = 13,//response from server
      T_ROOM_CREATE_INTERNAL_ERROR    = 14,//response from server
      T_ROOM_CREATE_OK                = 15,//response from server
      T_ROOM_JOIN		                 	= 16,//client request to join a room
      T_ROOM_JOIN_NOT_FOUND           = 17,//response from server
      T_ROOM_JOIN_IS_FULL             = 18,//response from server
      T_ROOM_JOIN_BAD_PSWD            = 19,//response from server
      T_ROOM_JOIN_OK                  = 20,//response from server
      T_ROOM_EXIT                     = 21,//client request for leave the room
      T_ROOM_EXIT_OK                  = 22,//response from server
      T_PING                          = 25,//ping from server
      T_PONG                          = 26,//pong from client
      T_MSG                           = 27,//client or server send a mmessage
      T_READY                         = 28,//client says is ready
      T_GAMESTART                     = 29,//game start from the server

      T_GAMEEND                       = 30,//game end from the server
      T_SCORE                         = 31,//score update from server
      T_MAPCHANGE                     = 32,//map change from server
      T_PLAYERINFO                    = 33,//player info from server
      //UDP
      T_POSITION			= 34,
      T_SPAWN				= 35,
      T_EVENT				= 36,
      T_DESTRUCTION			= 37,
      T_LIFE				= 38,
      T_BONUS				= 39
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
