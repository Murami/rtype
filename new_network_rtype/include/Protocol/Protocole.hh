#ifndef PROTOCOLE_HH_
# define PROTOCOLE_HH_

# include <cstring>

# include "NetworkException.hh"
# include "RtypeProtocol.hh"
# include "TcpSocket.hh"
# include "UdpSocket.hh"
# include "ProtocoleObserver.hh"

# ifdef _WIN32
#  include <Windows.h>
# elif __linux__
#  include <netinet/in.h>
# else
#  error Not defined for this platform
# endif

namespace Network
{
	class packet
	{
	public:
		packet(const void *data, const int size);
		~packet();
		char	*getData() const;
		int		getSize() const;
		packet	operator+(const packet &);
	private:
		char	*_data;
		int		_size;
	};

	class Protocole
	{
	public:
		Protocole();
		~Protocole();

		//Tcp
		packet	*pack(const struct Header *) const;
		packet	*pack(const struct Magic *) const;
		packet	*pack(const struct User *) const;
		packet	*pack(const struct Message *) const;
		packet	*pack(const struct RoomConnection *) const;
		packet	*pack(const struct PingPong *) const;
		packet	*pack(const struct Score *) const;
		packet	*pack(const struct MapChange *) const;
		packet	*pack(const struct GameReadyState *) const;
		packet	*pack(const struct EndGame *) const;
		packet	*pack(const struct Room *) const;
		Header			*decode(struct Header *) const;
		Magic			*decode(struct Magic *) const;
		User			*decode(struct User *) const;
		Message			*decode(struct Message *) const;
		RoomConnection	*decode(struct RoomConnection *) const;
		PingPong		*decode(struct PingPong *) const;
		Score			*decode(struct Score *) const;
		MapChange		*decode(struct MapChange *) const;
		GameReadyState	*decode(struct GameReadyState *) const;
		EndGame			*decode(struct EndGame *) const;
		Room			*decode(struct Room *) const;

		//Udp
		packet	*pack(const struct Spawn *) const;
		packet	*pack(const struct PositionEvent *) const;
		packet	*pack(const struct destruction *) const;
		packet	*pack(const struct EntityRequest *) const;
		packet	*pack(const struct Life *) const;
		packet	*pack(const struct Bonus *) const;
		packet	*pack(const struct PingElem *) const;
		packet	*pack(const struct State *) const;
		packet	*pack(const struct Position *) const;
		Position		*decode(Position *state) const;
		State			*decode(State *state) const;
		PingElem		*decode(PingElem *ping) const;
		Bonus			*decode(Bonus *bonus) const;
		Life			*decode(Life *life) const;
		EntityRequest	*decode(EntityRequest *entity) const;
		destruction		*decode(destruction *destru) const;
		PositionEvent	*decode(PositionEvent *posEvent) const;
		Spawn			*decode(Spawn *spawn) const;

		void			hton(Position *posEncoded, const Position *pos) const;
		void			ntoh(Position *posEncoded, const Position *pos) const;
		uint32_t		hton(uint32_t const) const;
		uint16_t		hton(uint16_t const) const;
		uint8_t			hton(uint8_t const) const;
		uint32_t		ntoh(uint32_t const) const;
		uint16_t		ntoh(uint16_t const) const;
		uint8_t			ntoh(uint8_t const) const;
		int32_t			hton(int32_t const) const;
		int16_t			hton(int16_t const) const;
		int8_t			hton(int8_t const) const;
		int32_t			ntoh(int32_t const) const;
		int16_t			ntoh(int16_t const) const;
		int8_t			ntoh(int8_t const) const;
	};

	class ProtocoleTcp : public Protocole
	{
	public:
		ProtocoleTcp();
		bool	unpack(const int &size, TcpSocket *) const;
		void	setup(ITcpProtocoleObserver *TcpObserver);
		virtual void onRead(TcpSocket*) const;
	private:
		ITcpProtocoleObserver	*obs;
	};

	class ProtocoleUdp : public Protocole
	{
	public:
		ProtocoleUdp();
		bool			unpack(const int &size, TcpSocket *) const;
		void			setup(IUdpProtocoleObserver *UdpObserver);
		virtual void	onRead(TcpSocket*) const;
	private:
		IUdpProtocoleObserver	*obs;
	};
}

#endif // !PROTOCOLE_HH_
