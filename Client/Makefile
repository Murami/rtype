SRC	=	src/main.cpp				\
		src/ConnectionConfiguration.cpp		\
		src/ConfigurationParser.cpp		\
		src/TcpConnection.cpp			\

NAME	=	server

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++

CXXFLAGS +=	-W -Wall -Wextra -std=c++11 $(LDFLAGS) $(IFLAGS)

LDFLAGS	+=	-lsfml-network -lsfml-system

IFLAGS	=	-I./include

RM	=	rm -f

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
