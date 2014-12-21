#ifndef PROTOCOLE_HH_
# define PROTOCOLE_HH_

# include <cstring>

# include "ProtocolException.hh"
# include "RtypeProtocol.hh"
# include "Network/TcpSocket.hh"
# include "UdpSocket.hh"
# include "ProtocoleObserver.hh"

# ifdef _WIN32
#  include <Windows.h>
# elif __linux__ || __APPLE__
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
    packet	*pack(const RtypeProtocol::Header *) const;
    packet	*pack(const RtypeProtocol::Magic *) const;
    packet	*pack(const RtypeProtocol::User *) const;
    packet	*pack(const RtypeProtocol::Message *) const;
    packet	*pack(const RtypeProtocol::RoomConnection *) const;
    packet	*pack(const RtypeProtocol::PingPong *) const;
    packet	*pack(const RtypeProtocol::Score *) const;
    packet	*pack(const RtypeProtocol::MapChange *) const;
    packet	*pack(const RtypeProtocol::GameReadyState *) const;
    packet	*pack(const RtypeProtocol::EndGame *) const;
    packet	*pack(const RtypeProtocol::Room *) const;
    RtypeProtocol::Header		*decode(RtypeProtocol::Header *) const;
    RtypeProtocol::Magic		*decode(RtypeProtocol::Magic *) const;
    RtypeProtocol::User			*decode(RtypeProtocol::User *) const;
    RtypeProtocol::Message		*decode(RtypeProtocol::Message *) const;
    RtypeProtocol::RoomConnection	*decode(RtypeProtocol::RoomConnection *) const;
    RtypeProtocol::PingPong		*decode(RtypeProtocol::PingPong *) const;
    RtypeProtocol::Score		*decode(RtypeProtocol::Score *) const;
    RtypeProtocol::MapChange		*decode(RtypeProtocol::MapChange *) const;
    RtypeProtocol::GameReadyState	*decode(RtypeProtocol::GameReadyState *) const;
    RtypeProtocol::EndGame		*decode(RtypeProtocol::EndGame *) const;
    RtypeProtocol::Room			*decode(RtypeProtocol::Room *) const;

    //Udp
    packet	*pack(const RtypeProtocol::Spawn *) const;
    packet	*pack(const RtypeProtocol::PositionEvent *) const;
    packet	*pack(const RtypeProtocol::destruction *) const;
    packet	*pack(const RtypeProtocol::EntityRequest *) const;
    packet	*pack(const RtypeProtocol::Life *) const;
    packet	*pack(const RtypeProtocol::Bonus *) const;
    packet	*pack(const RtypeProtocol::PingElem *) const;
    packet	*pack(const RtypeProtocol::State *) const;
    packet  *pack(const RtypeProtocol::Position *) const;
    RtypeProtocol::Position     *decode(RtypeProtocol::Position *state) const;
    RtypeProtocol::State			*decode(RtypeProtocol::State *state) const;
    RtypeProtocol::PingElem			*decode(RtypeProtocol::PingElem *ping) const;
    RtypeProtocol::Bonus			*decode(RtypeProtocol::Bonus *bonus) const;
    RtypeProtocol::Life				*decode(RtypeProtocol::Life *life) const;
    RtypeProtocol::EntityRequest		*decode(RtypeProtocol::EntityRequest *entity) const;
    RtypeProtocol::destruction			*decode(RtypeProtocol::destruction *destru) const;
    RtypeProtocol::PositionEvent		*decode(RtypeProtocol::PositionEvent *posEvent) const;
    RtypeProtocol::Spawn			*decode(RtypeProtocol::Spawn *spawn) const;

    template<typename T>
    T	*decode(void *data, const int size, const int headerSize) const
    {
      std::cout << "size : " << size << std::endl;
      std::cout << "sizeof : " << sizeof(T) << std::endl;
      std::cout << "headerSize : " << headerSize << std::endl;
      if (size < sizeof(T) || headerSize != sizeof(T))
	throw RtypeProtocol::ProtocolException("Error with data");
      return (decode(static_cast<T *>(data)));
    }

    void			hton(RtypeProtocol::Position *posEncoded, const RtypeProtocol::Position *pos) const;
    void			ntoh(RtypeProtocol::Position *posEncoded, const RtypeProtocol::Position *pos) const;
    uint32_t		hton(uint32_t const) const;
    uint16_t		hton(uint16_t const) const;
    uint8_t		hton(uint8_t const) const;
    uint32_t		ntoh(uint32_t const) const;
    uint16_t		ntoh(uint16_t const) const;
    uint8_t		ntoh(uint8_t const) const;
    int32_t		hton(int32_t const) const;
    int16_t		hton(int16_t const) const;
    int8_t		hton(int8_t const) const;
    int32_t		ntoh(int32_t const) const;
    int16_t		ntoh(int16_t const) const;
    int8_t		ntoh(int8_t const) const;
  };

  class ProtocoleTcp : public Protocole
  {
  public:
    ProtocoleTcp();
    bool		unpack(const int &size, TcpSocket *, ITcpProtocoleObserver *obs) const;
    virtual void	onRead(TcpSocket *, ITcpProtocoleObserver *obs) const;
  };

  class ProtocoleUdp : public Protocole
  {
  public:
    ProtocoleUdp();
    bool			unpack(UdpSocket *, IUdpProtocoleObserver *obs) const;
    virtual void		onRead(UdpSocket *, IUdpProtocoleObserver *obs) const;
  private:
    IUdpProtocoleObserver	*obs;
  };
}

#endif // !PROTOCOLE_HH_
