#include "Protocole.hh"

namespace Network
{
	packet::packet(const void *data, const int size)
	{
		_data = new char[size];
		_size = size;
		std::memcpy(_data, data, size);
	}

	packet::~packet()
	{
		delete (_data);
	}

	char	*packet::getData() const
	{
		return (_data);
	}

	int		packet::getSize() const
	{
		return (_size);
	}

	packet	packet::operator+(const packet &add)
	{
		int	i;
		int k;
		int addSize = add.getSize();
		int size = _size;
		char *addData = add.getData();
		char *data = _data;

		_data = new char[size + addSize];
		i = 0;
		k = 0;
		while (k != size)
		{
			_data[i] = data[k];
			k++;
			i++;
		}
		k = 0;
		while (k != addSize)
		{
			_data[i] = addData[k];
			i++;
			k++;
		}
		return (*this);
	}

	Protocole::Protocole()
	{}

	Protocole::~Protocole()
	{}

	packet	*Protocole::pack(const RtypeProtocol::Header *header) const
	{
		RtypeProtocol::Header	EncodedHeader;

		EncodedHeader.type = hton(header->type);
		EncodedHeader.data_size = hton(header->data_size);
		return (new packet(&EncodedHeader, sizeof(EncodedHeader)));
	}
	packet	*Protocole::pack(const RtypeProtocol::Magic *magic) const
	{
		RtypeProtocol::Magic magicEncoded;

		magicEncoded.minor_version = hton(magic->minor_version);
		magicEncoded.major_version = hton(magic->major_version);
		std::cout << "avant " << magic->proto_name << std::endl;
		for (int i = 0; i != PROTO_NAME_SIZE; i++)
			magicEncoded.proto_name[i] = hton(magic->proto_name[i]);
		std::cout << "apres " << magicEncoded.proto_name << std::endl;
		return (new packet(&magicEncoded, sizeof(magicEncoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::User *user) const
	{
		RtypeProtocol::User	userEncoded;

		for (int i = 0; i != USERNAME_SIZE; i++)
			userEncoded.username[i] = hton(user->username[i]);
		return (new packet(&userEncoded, sizeof(userEncoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::Message *msg) const
	{
		RtypeProtocol::Message	msgEncoded;

		msgEncoded.room_id = hton(msg->room_id);
		msgEncoded.user = hton(msg->user);
		for (int i = 0; i != MAX_MSG_SIZE; i++)
			msgEncoded.message[i] = hton(msg->message[i]);
		return (new packet(&msgEncoded, sizeof(msgEncoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::RoomConnection *roomCo) const
	{
		RtypeProtocol::RoomConnection	roomCoEncoded;

		roomCoEncoded.id = hton(roomCo->id);
		for (int i = 0; i != PASS_MD5_SIZE; i++)
			roomCoEncoded.pass_md5[i] = hton(roomCo->pass_md5[i]);
		return (new packet(&roomCoEncoded, sizeof(roomCoEncoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::PingPong *pingPong) const
	{
		RtypeProtocol::PingPong pingPongEncoded;

		pingPongEncoded.id = hton(pingPong->id);
		return (new packet(&pingPongEncoded, sizeof(pingPongEncoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::Score *score) const
	{
		RtypeProtocol::Score scoreEncoded;

		scoreEncoded.score = hton(score->score);
		scoreEncoded.user_id = hton(score->user_id);
		return (new packet(&scoreEncoded, sizeof(scoreEncoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::MapChange *mapChange) const
	{
		RtypeProtocol::MapChange mapChangeEncoded;

		for (int i = 0; i != MAP_NAME_SIZE; i++)
			mapChangeEncoded.map_name[i] = hton(mapChange->map_name[i]);
		return (new packet(&mapChangeEncoded, sizeof(mapChangeEncoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::GameReadyState *gameReadyState) const
	{
		RtypeProtocol::GameReadyState gameReadyStateEncoded;

		gameReadyStateEncoded.ready = hton(gameReadyState->ready);
		return (new packet(&gameReadyStateEncoded, sizeof(gameReadyStateEncoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::EndGame *endGame) const
	{
		RtypeProtocol::EndGame endGameEncoded;

		endGameEncoded.victory = hton(endGame->victory);
		return (new packet(&endGameEncoded, sizeof(endGameEncoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::Room *room) const
	{
		RtypeProtocol::Room roomEncoded;

		roomEncoded.id = hton(room->id);
		for (int i = 0; i != MAX_USERS; i++)
		{
			for (int k = 0; k != USERNAME_SIZE; k++)
				roomEncoded.connected_users[i][k] = hton(room->connected_users[i][k]);
		}
		roomEncoded.nb_connected_users = hton(room->nb_connected_users);
		roomEncoded.password_flag = hton(room->password_flag);
		for (int i = 0; i != ROOM_NAME_SIZE; i++)
			roomEncoded.room_name[i] = hton(room->room_name[i]);
		for (int i = 0; i != MAX_USERS; i++)
			roomEncoded.ready_users[i] = hton(room->ready_users[i]);
		roomEncoded.locked = hton(room->locked);
		for (int i = 0; i != MAX_USERS; i++)
			roomEncoded.users_id[i] = hton(room->users_id[i]);
		return (new packet(&roomEncoded, sizeof(roomEncoded)));
	}

	RtypeProtocol::Header	*Protocole::decode(RtypeProtocol::Header *header) const
	{
		header->type = ntoh(header->type);
		header->data_size = ntoh(header->data_size);
		return (header);
	}
	RtypeProtocol::Magic	*Protocole::decode(RtypeProtocol::Magic *magic) const
	{
		magic->minor_version = ntoh(magic->minor_version);
		magic->major_version = ntoh(magic->major_version);
		std::cout << "avant " << magic->proto_name << std::endl;
		for (int i = 0; i != PROTO_NAME_SIZE; i++)
			magic->proto_name[i] = ntoh(magic->proto_name[i]);
		std::cout << "apres " << magic->proto_name << std::endl;
		return (magic);
	}
	RtypeProtocol::User	*Protocole::decode(RtypeProtocol::User *user) const
	{
		for (int i = 0; i != USERNAME_SIZE; i++)
			user->username[i] = ntoh(user->username[i]);
		return (user);
	}
	RtypeProtocol::Message	*Protocole::decode(RtypeProtocol::Message *msg) const
	{
		msg->room_id = ntoh(msg->room_id);
		msg->user = ntoh(msg->user);
		for (int i = 0; i != MAX_MSG_SIZE; i++)
			msg->message[i] = ntoh(msg->message[i]);
		return (msg);
	}
	RtypeProtocol::RoomConnection	*Protocole::decode(RtypeProtocol::RoomConnection *roomCo) const
	{
		roomCo->id = ntoh(roomCo->id);
		for (int i = 0; i != PASS_MD5_SIZE; i++)
			roomCo->pass_md5[i] = ntoh(roomCo->pass_md5[i]);
		return (roomCo);
	}
	RtypeProtocol::PingPong	*Protocole::decode(RtypeProtocol::PingPong *pingPong) const
	{
		pingPong->id = ntoh(pingPong->id);
		return (pingPong);
	}
	RtypeProtocol::Score	*Protocole::decode(RtypeProtocol::Score *score) const
	{
		RtypeProtocol::Score scoreEncoded;

		score->score = ntoh(score->score);
		score->user_id = ntoh(score->user_id);
		return (score);
	}
	RtypeProtocol::MapChange	*Protocole::decode(RtypeProtocol::MapChange *mapChange) const
	{
		for (int i = 0; i != MAP_NAME_SIZE; i++)
			mapChange->map_name[i] = ntoh(mapChange->map_name[i]);
		return (mapChange);
	}
	RtypeProtocol::GameReadyState	*Protocole::decode(RtypeProtocol::GameReadyState *gameReadyState) const
	{
		gameReadyState->ready = ntoh(gameReadyState->ready);
		return (gameReadyState);
	}
	RtypeProtocol::EndGame	*Protocole::decode(RtypeProtocol::EndGame *endGame) const
	{
		endGame->victory = ntoh(endGame->victory);
		return (endGame);
	}
	RtypeProtocol::Room	*Protocole::decode(RtypeProtocol::Room *room) const
	{
		room->id = ntoh(room->id);
		for (int i = 0; i != MAX_USERS; i++)
		{
			for (int k = 0; k != USERNAME_SIZE; k++)
				room->connected_users[i][k] = ntoh(room->connected_users[i][k]);
		}
		room->nb_connected_users = ntoh(room->nb_connected_users);
		room->password_flag = ntoh(room->password_flag);
		for (int i = 0; i != ROOM_NAME_SIZE; i++)
			room->room_name[i] = ntoh(room->room_name[i]);
		for (int i = 0; i != MAX_USERS; i++)
			room->ready_users[i] = ntoh(room->ready_users[i]);
		room->locked = ntoh(room->locked);
		for (int i = 0; i != MAX_USERS; i++)
			room->users_id[i] = ntoh(room->users_id[i]);
		return (room);
	}

	packet	*Protocole::pack(const RtypeProtocol::Spawn *spawn) const
	{
		RtypeProtocol::Spawn encoded;

		encoded.id = hton(spawn->id);
		encoded.life = hton(spawn->life);
		hton(&encoded.position, &spawn->position);
		encoded.type = hton(spawn->type);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::PositionEvent *posEvent) const
	{
		RtypeProtocol::PositionEvent encoded;

		encoded.id = hton(posEvent->id);
		hton(&encoded.position, &posEvent->position);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::destruction *destru) const
	{
		RtypeProtocol::destruction encoded;

		encoded.id = hton(destru->id);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::EntityRequest *entity) const
	{
		RtypeProtocol::EntityRequest encoded;

		encoded.id = hton(entity->id);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::Life *life) const
	{
		RtypeProtocol::Life encoded;

		encoded.id = hton(life->id);
		encoded.life = hton(life->life);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::Bonus *bonus) const
	{
		RtypeProtocol::Bonus encoded;
		
		encoded.id = hton(bonus->id);
		encoded.type = hton(bonus->type);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::PingElem *ping) const
	{
		RtypeProtocol::PingElem encoded;

		encoded.id = hton(ping->id);
		encoded.life = hton(ping->life);
		hton(&encoded.pos, &ping->pos);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const RtypeProtocol::State *state) const
	{
		RtypeProtocol::State encoded;

		encoded.id = hton(state->id);
		encoded.state = hton(state->state);
		return (new packet(&encoded, sizeof(encoded)));
	}

	packet	*Protocole::pack(const RtypeProtocol::Position *pos) const
	{
		RtypeProtocol::Position encoded;

		hton(&encoded, pos);
		return (new packet(&encoded, sizeof(encoded)));
	}


	RtypeProtocol::Position	*Protocole::decode(RtypeProtocol::Position *pos) const
	{
		ntoh(pos, pos);
		return (pos);
	}

	RtypeProtocol::Spawn	*Protocole::decode(RtypeProtocol::Spawn *spawn) const
	{
		spawn->id = ntoh(spawn->id);
		spawn->life = ntoh(spawn->life);
		ntoh(&spawn->position, &spawn->position);
		spawn->type = ntoh(spawn->type);
		return (spawn);
	}
	RtypeProtocol::PositionEvent	*Protocole::decode(RtypeProtocol::PositionEvent *posEvent) const
	{
		posEvent->id = ntoh(posEvent->id);
		ntoh(&posEvent->position, &posEvent->position);
		return (posEvent);
	}
	RtypeProtocol::destruction	*Protocole::decode(RtypeProtocol::destruction *destru) const
	{
		destru->id = ntoh(destru->id);
		return (destru);
	}
	RtypeProtocol::EntityRequest	*Protocole::decode(RtypeProtocol::EntityRequest *entity) const
	{
		entity->id = ntoh(entity->id);
		return (entity);
	}
	RtypeProtocol::Life	*Protocole::decode(RtypeProtocol::Life *life) const
	{
		life->id = ntoh(life->id);
		life->life = ntoh(life->life);
		return (life);
	}
	RtypeProtocol::Bonus	*Protocole::decode(RtypeProtocol::Bonus *bonus) const
	{
		bonus->id = ntoh(bonus->id);
		bonus->type = ntoh(bonus->type);
		return (bonus);
	}
	RtypeProtocol::PingElem	*Protocole::decode(RtypeProtocol::PingElem *ping) const
	{
		ping->id = ntoh(ping->id);
		ping->life = ntoh(ping->life);
		ntoh(&ping->pos, &ping->pos);
		return (ping);
	}
	RtypeProtocol::State	*Protocole::decode(RtypeProtocol::State *state) const
	{
		state->id = ntoh(state->id);
		state->state = ntoh(state->state);
		return (state);
	}


	void			Protocole::hton(RtypeProtocol::Position *posEncoded, const RtypeProtocol::Position *pos) const
	{
		posEncoded->x = hton(pos->x);
		posEncoded->y = hton(pos->y);
		posEncoded->orientation = hton(pos->orientation);
		posEncoded->state = hton(pos->state);
	}

	void			Protocole::ntoh(RtypeProtocol::Position *posEncoded, const RtypeProtocol::Position *pos) const
	{
		posEncoded->x = ntoh(pos->x);
		posEncoded->y = ntoh(pos->y);
		posEncoded->orientation = ntoh(pos->orientation);
		posEncoded->state = ntoh(pos->state);
	}

	uint32_t		Protocole::hton(uint32_t const value) const
	{
		return (htonl(value));
	}
	uint16_t		Protocole::hton(uint16_t const value) const
	{
		return (htons(value));
	}
	uint8_t			Protocole::hton(uint8_t const value) const
	{
		return (value);
	}
	uint32_t		Protocole::ntoh(uint32_t const value) const
	{
		return (ntohl(value));
	}
	uint16_t		Protocole::ntoh(uint16_t const value) const
	{
		return (ntohs(value));
	}
	uint8_t			Protocole::ntoh(uint8_t const value) const
	{
		return (value);
	}

	int32_t		Protocole::hton(int32_t const value) const
	{
		return (htonl(value));
	}
	int16_t		Protocole::hton(int16_t const value) const
	{
		return (htons(value));
	}
	int8_t			Protocole::hton(int8_t const value) const
	{
		return (value);
	}
	int32_t		Protocole::ntoh(int32_t const value) const
	{
		return (ntohl(value));
	}
	int16_t		Protocole::ntoh(int16_t const value) const
	{
		return (ntohs(value));
	}
	int8_t			Protocole::ntoh(int8_t const value) const
	{
		return (value);
	}

	bool	ProtocoleTcp::unpack(const int &size, TcpSocket *socket, ITcpProtocoleObserver *obs) const
	{
		if (size < sizeof(RtypeProtocol::Header))
			return (false);
		char			*buffer = new char[size];
		RtypeProtocol::Header	*header;
		void			*dataAddr = NULL;
		socket->pickData(buffer, size);
		header = (RtypeProtocol::Header *)buffer;
		decode(header);
		int datasize = size - sizeof(RtypeProtocol::Header);
		if (size < header->data_size + sizeof(RtypeProtocol::Header))
		{
			delete buffer;
			return (false);
		}
		if (header->data_size > 0)
		{
			dataAddr = header + sizeof(RtypeProtocol::Header);
			socket->consumeData(sizeof(RtypeProtocol::Header) + header->data_size);
		}
		if (header->type == RtypeProtocol::T_MAGIC)
			obs->notify(header->type, decode<RtypeProtocol::Magic>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == RtypeProtocol::T_PLAYERINFO ||
				 header->type == RtypeProtocol::T_CONNECTION)
			obs->notify(header->type, decode<RtypeProtocol::User>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == RtypeProtocol::T_MSG)
			obs->notify(header->type, decode<RtypeProtocol::Message>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == RtypeProtocol::T_ROOMCONNECTION)
			obs->notify(header->type, decode<RtypeProtocol::RoomConnection>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == RtypeProtocol::T_PING ||
				 header->type == RtypeProtocol::T_PONG)
			obs->notify(header->type, decode<RtypeProtocol::PingPong>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == RtypeProtocol::T_SCORE)
			obs->notify(header->type, decode<RtypeProtocol::Score>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == RtypeProtocol::T_MAPCHANGE)
			obs->notify(header->type, decode<RtypeProtocol::MapChange>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == RtypeProtocol::T_MSG)// unknow type for the header
			obs->notify(header->type, decode<RtypeProtocol::GameReadyState>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == RtypeProtocol::T_GAMEEND)
			obs->notify(header->type, decode<RtypeProtocol::EndGame>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == RtypeProtocol::T_ROOMINFO)
			obs->notify(header->type, decode<RtypeProtocol::Room>(dataAddr, datasize, header->data_size), socket);
		else if (header->data_size == 0)
			obs->notify(header->type, socket);
		else
			throw NetworkException("Unknow data");
		delete buffer;
		return (true);
	}

	void	ProtocoleTcp::onRead(TcpSocket *socket, ITcpProtocoleObserver *obs) const
	{
		if (socket->availableDataOnRead() >= sizeof(RtypeProtocol::Header))
		{
			unpack(socket->availableDataOnRead(), socket, obs);
		}
	}

	void	ProtocoleUdp::onRead(TcpSocket *socket) const
	{
		if (socket->availableDataOnRead() >= sizeof(RtypeProtocol::Header))
		{
			unpack(socket->availableDataOnRead(), socket);
		}
	}

	bool	ProtocoleUdp::unpack(const int &size, TcpSocket *socket) const
	{
		/*
		if (size < sizeof(Header))
			return (false);
		char			*buffer = new char[size];
		RtypeProtocol::Header	*header;
		void			*dataAddr = NULL;
		socket->pickData(buffer, size);
		header = (Header *)buffer;
		decode(header);
		if (size < header->data_size + sizeof(Header))
		{
			delete buffer;
			return (false);
		}
		if (header->data_size > 0)
		{
			dataAddr = header + sizeof(Header);
			socket->consumeData(sizeof(Header)+header->data_size);
		}
		if (dataAddr)
		{
			if (header->type == T_POSITION)
				obs->notify(header->type, decode((PositionEvent *)dataAddr), socket);
			else if (header->type == T_SPAWN)
				obs->notify(header->type, decode((Spawn *)dataAddr), socket);
			else if (header->type == T_EVENT)
				obs->notify(header->type, decode((Position *)dataAddr), socket);
			else if (header->type == T_DESTRUCTION)
				obs->notify(header->type, decode((destruction *)dataAddr), socket);
			else if (header->type == T_LIFE)
				obs->notify(header->type, decode((Life *)dataAddr), socket);
			else if (header->type == T_BONUS)
				obs->notify(header->type, decode((Bonus *)dataAddr), socket);
			else
				throw NetworkException("Unknow data");
		}
		else
			obs->notify(header->type, socket);
		delete buffer;
		*/
		return (true);
	}

	ProtocoleTcp::ProtocoleTcp()
	{
	}

	ProtocoleUdp::ProtocoleUdp()
	{
	}

	void	ProtocoleUdp::setup(IUdpProtocoleObserver *UdpObserver)
	{
		obs = UdpObserver;
	}

}