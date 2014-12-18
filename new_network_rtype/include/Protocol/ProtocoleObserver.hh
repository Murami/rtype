#ifndef PROTOCOLEOBSERVER_HH_
# define PROTOCOLEOBSERVER_HH_

# include "TcpSocket.hh"
# include "UdpSocket.hh"
# include "RtypeProtocol.hh"

namespace Network
{
	class ITcpProtocoleObserver
	{
	public:
		~ITcpProtocoleObserver()
		{}
		virtual void	notify(int const &type, const Magic *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, const User *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, const Message *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, const RoomConnection *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, const PingPong *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, const Score *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, const MapChange *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, const GameReadyState *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, const EndGame *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, const Room *, TcpSocket *) const = 0;
		virtual void	notify(int const &type, TcpSocket *) const = 0;
	};

	class IUdpProtocoleObserver
	{
	public:
		~IUdpProtocoleObserver()
		{}
		virtual void	notify(int const &type, const PositionEvent *, UdpSocket *) const = 0;
		virtual void	notify(int const &type, const Spawn *, UdpSocket *) const = 0;
		virtual void	notify(int const &type, const Position *, UdpSocket *) const = 0;
		virtual void	notify(int const &type, const destruction *, UdpSocket *) const = 0;
		virtual void	notify(int const &type, const Life *, UdpSocket *) const = 0;
		virtual void	notify(int const &type, const Bonus *, UdpSocket *) const = 0;
		virtual void	notify(int const &type, UdpSocket *) const = 0;
	};
}

#endif // !PROTOCOLEOBSERVER_HH_
