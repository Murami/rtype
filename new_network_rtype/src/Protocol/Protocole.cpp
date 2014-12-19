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

	packet	*Protocole::pack(const struct Header *header) const
	{
		struct Header	EncodedHeader;

		EncodedHeader.type = hton(header->type);
		EncodedHeader.data_size = hton(header->data_size);
		return (new packet(&EncodedHeader, sizeof(EncodedHeader)));
	}
	packet	*Protocole::pack(const struct Magic *magic) const
	{
		struct Magic magicEncoded;

		magicEncoded.minor_version = hton(magic->minor_version);
		magicEncoded.major_version = hton(magic->major_version);
		for (int i = 0; i != PROTO_NAME_SIZE; i++)
			magicEncoded.proto_name[i] = hton(magic->proto_name[i]);
		return (new packet(&magicEncoded, sizeof(magicEncoded)));
	}
	packet	*Protocole::pack(const struct User *user) const
	{
		struct User	userEncoded;

		for (int i = 0; i != USERNAME_SIZE; i++)
			userEncoded.username[i] = hton(user->username[i]);
		return (new packet(&userEncoded, sizeof(userEncoded)));
	}
	packet	*Protocole::pack(const struct Message *msg) const
	{
		struct Message	msgEncoded;

		msgEncoded.room_id = hton(msg->room_id);
		msgEncoded.user = hton(msg->user);
		for (int i = 0; i != MAX_MSG_SIZE; i++)
			msgEncoded.message[i] = hton(msg->message[i]);
		return (new packet(&msgEncoded, sizeof(msgEncoded)));
	}
	packet	*Protocole::pack(const struct RoomConnection *roomCo) const
	{
		struct RoomConnection	roomCoEncoded;

		roomCoEncoded.id = hton(roomCo->id);
		for (int i = 0; i != PASS_MD5_SIZE; i++)
			roomCoEncoded.pass_md5[i] = hton(roomCo->pass_md5[i]);
		return (new packet(&roomCoEncoded, sizeof(roomCoEncoded)));
	}
	packet	*Protocole::pack(const struct PingPong *pingPong) const
	{
		struct PingPong pingPongEncoded;

		pingPongEncoded.id = hton(pingPong->id);
		return (new packet(&pingPongEncoded, sizeof(pingPongEncoded)));
	}
	packet	*Protocole::pack(const struct Score *score) const
	{
		struct Score scoreEncoded;

		scoreEncoded.score = hton(score->score);
		scoreEncoded.user_id = hton(score->user_id);
		return (new packet(&scoreEncoded, sizeof(scoreEncoded)));
	}
	packet	*Protocole::pack(const struct MapChange *mapChange) const
	{
		struct MapChange mapChangeEncoded;

		for (int i = 0; i != MAP_NAME_SIZE; i++)
			mapChangeEncoded.map_name[i] = hton(mapChange->map_name[i]);
		return (new packet(&mapChangeEncoded, sizeof(mapChangeEncoded)));
	}
	packet	*Protocole::pack(const struct GameReadyState *gameReadyState) const
	{
		struct GameReadyState gameReadyStateEncoded;

		gameReadyStateEncoded.ready = hton(gameReadyState->ready);
		return (new packet(&gameReadyStateEncoded, sizeof(gameReadyStateEncoded)));
	}
	packet	*Protocole::pack(const struct EndGame *endGame) const
	{
		struct EndGame endGameEncoded;

		endGameEncoded.victory = hton(endGame->victory);
		return (new packet(&endGameEncoded, sizeof(endGameEncoded)));
	}
	packet	*Protocole::pack(const struct Room *room) const
	{
		struct Room roomEncoded;

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

	Header	*Protocole::decode(struct Header *header) const
	{
		header->type = ntoh(header->type);
		header->data_size = ntoh(header->data_size);
		return (header);
	}
	Magic	*Protocole::decode(struct Magic *magic) const
	{
		magic->minor_version = ntoh(magic->minor_version);
		magic->major_version = ntoh(magic->major_version);
		for (int i = 0; i != PROTO_NAME_SIZE; i++)
			magic->proto_name[i] = ntoh(magic->proto_name[i]);
		return (magic);
	}
	User	*Protocole::decode(struct User *user) const
	{
		for (int i = 0; i != USERNAME_SIZE; i++)
			user->username[i] = ntoh(user->username[i]);
		return (user);
	}
	Message	*Protocole::decode(struct Message *msg) const
	{
		msg->room_id = ntoh(msg->room_id);
		msg->user = ntoh(msg->user);
		for (int i = 0; i != MAX_MSG_SIZE; i++)
			msg->message[i] = ntoh(msg->message[i]);
		return (msg);
	}
	RoomConnection	*Protocole::decode(struct RoomConnection *roomCo) const
	{
		roomCo->id = ntoh(roomCo->id);
		for (int i = 0; i != PASS_MD5_SIZE; i++)
			roomCo->pass_md5[i] = ntoh(roomCo->pass_md5[i]);
		return (roomCo);
	}
	PingPong	*Protocole::decode(struct PingPong *pingPong) const
	{
		pingPong->id = ntoh(pingPong->id);
		return (pingPong);
	}
	Score	*Protocole::decode(struct Score *score) const
	{
		struct Score scoreEncoded;

		score->score = ntoh(score->score);
		score->user_id = ntoh(score->user_id);
		return (score);
	}
	MapChange	*Protocole::decode(struct MapChange *mapChange) const
	{
		for (int i = 0; i != MAP_NAME_SIZE; i++)
			mapChange->map_name[i] = ntoh(mapChange->map_name[i]);
		return (mapChange);
	}
	GameReadyState	*Protocole::decode(struct GameReadyState *gameReadyState) const
	{
		gameReadyState->ready = ntoh(gameReadyState->ready);
		return (gameReadyState);
	}
	EndGame	*Protocole::decode(struct EndGame *endGame) const
	{
		endGame->victory = ntoh(endGame->victory);
		return (endGame);
	}
	Room	*Protocole::decode(struct Room *room) const
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

	packet	*Protocole::pack(const Spawn *spawn) const
	{
		Spawn encoded;

		encoded.id = hton(spawn->id);
		encoded.life = hton(spawn->life);
		hton(&encoded.position, &spawn->position);
		encoded.type = hton(spawn->type);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const PositionEvent *posEvent) const
	{
		PositionEvent encoded;

		encoded.id = hton(posEvent->id);
		hton(&encoded.position, &posEvent->position);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const destruction *destru) const
	{
		destruction encoded;

		encoded.id = hton(destru->id);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const EntityRequest *entity) const
	{
		EntityRequest encoded;

		encoded.id = hton(entity->id);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const Life *life) const
	{
		Life encoded;

		encoded.id = hton(life->id);
		encoded.life = hton(life->life);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const Bonus *bonus) const
	{
		Bonus encoded;
		
		encoded.id = hton(bonus->id);
		encoded.type = hton(bonus->type);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const PingElem *ping) const
	{
		PingElem encoded;

		encoded.id = hton(ping->id);
		encoded.life = hton(ping->life);
		hton(&encoded.pos, &ping->pos);
		return (new packet(&encoded, sizeof(encoded)));
	}
	packet	*Protocole::pack(const State *state) const
	{
		State encoded;

		encoded.id = hton(state->id);
		encoded.state = hton(state->state);
		return (new packet(&encoded, sizeof(encoded)));
	}

	packet	*Protocole::pack(const Position *pos) const
	{
		Position encoded;

		hton(&encoded, pos);
		return (new packet(&encoded, sizeof(encoded)));
	}


	Position	*Protocole::decode(Position *pos) const
	{
		ntoh(pos, pos);
		return (pos);
	}

	Spawn	*Protocole::decode(Spawn *spawn) const
	{
		spawn->id = ntoh(spawn->id);
		spawn->life = ntoh(spawn->life);
		ntoh(&spawn->position, &spawn->position);
		spawn->type = ntoh(spawn->type);
		return (spawn);
	}
	PositionEvent	*Protocole::decode(PositionEvent *posEvent) const
	{
		posEvent->id = ntoh(posEvent->id);
		ntoh(&posEvent->position, &posEvent->position);
		return (posEvent);
	}
	destruction	*Protocole::decode(destruction *destru) const
	{
		destru->id = ntoh(destru->id);
		return (destru);
	}
	EntityRequest	*Protocole::decode(EntityRequest *entity) const
	{
		entity->id = ntoh(entity->id);
		return (entity);
	}
	Life	*Protocole::decode(Life *life) const
	{
		life->id = ntoh(life->id);
		life->life = ntoh(life->life);
		return (life);
	}
	Bonus	*Protocole::decode(Bonus *bonus) const
	{
		bonus->id = ntoh(bonus->id);
		bonus->type = ntoh(bonus->type);
		return (bonus);
	}
	PingElem	*Protocole::decode(PingElem *ping) const
	{
		ping->id = ntoh(ping->id);
		ping->life = ntoh(ping->life);
		ntoh(&ping->pos, &ping->pos);
		return (ping);
	}
	State	*Protocole::decode(State *state) const
	{
		state->id = ntoh(state->id);
		state->state = ntoh(state->state);
		return (state);
	}


	void			Protocole::hton(Position *posEncoded, const Position *pos) const
	{
		posEncoded->x = hton(pos->x);
		posEncoded->y = hton(pos->y);
		posEncoded->orientation = hton(pos->orientation);
		posEncoded->state = hton(pos->state);
	}

	void			Protocole::ntoh(Position *posEncoded, const Position *pos) const
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
		if (size < sizeof(Header))
			return (false);
		char			*buffer = new char[size];
		struct Header	*header;
		void			*dataAddr = NULL;
		socket->pickData(buffer, size);
		header = (Header *)buffer;
		decode(header);
		int datasize = size - sizeof(Header);
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
		if (header->type == T_MAGIC)
			obs->notify(header->type, decode<Magic>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == T_PLAYERINFO ||
				 header->type == T_CONNECTION)
			obs->notify(header->type, decode<User>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == T_MSG)
			obs->notify(header->type, decode<Message>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == T_ROOMCONNECTION)
			obs->notify(header->type, decode<RoomConnection>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == T_PING ||
				 header->type == T_PONG)
			obs->notify(header->type, decode<PingPong>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == T_SCORE)
			obs->notify(header->type, decode<Score>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == T_MAPCHANGE)
			obs->notify(header->type, decode<MapChange>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == T_MSG)// unknow type for the header
			obs->notify(header->type, decode<GameReadyState>(dataAddr, datasize, header->data_size), socket);
		else if (header->type == T_GAMEEND)
			obs->notify(header->type, decode<EndGame>(dataAddr, datasize, header->data_size, socket);
		else if (header->type == T_ROOMINFO)
			obs->notify(header->type, decode<Room>(dataAddr, datasize, header->data_size), socket);
		else if (header->data_size == 0)
			obs->notify(header->type, socket);
		else
			throw NetworkException("Unknow data");
		delete buffer;
		return (true);
	}

	void	ProtocoleTcp::onRead(TcpSocket *socket, ITcpProtocoleObserver *obs) const
	{
		if (socket->availableDataOnRead() >= sizeof(Header))
		{
			unpack(socket->availableDataOnRead(), socket, obs);
		}
	}

	void	ProtocoleUdp::onRead(TcpSocket *socket) const
	{
		if (socket->availableDataOnRead() >= sizeof(Header))
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
		struct Header	*header;
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