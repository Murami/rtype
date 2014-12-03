SRC	=	src/main.cpp				\
		src/ConnectionConfiguration.cpp		\
		src/ConfigurationParser.cpp		\
		src/TcpConnection.cpp			\
		src/RtypeClient.cpp			\
		src/MenuController.cpp			\
		src/MenuView.cpp			\

NAME	=	server

OBJ	=	$(SRC:.cpp=.o)

CXX	=	g++

CXXFLAGS +=	-W -Wall -Wextra -std=c++11 $(LDFLAGS) $(IFLAGS) -ggdb -g3

LDFLAGS	+=	-lsfml-network -lsfml-system -lsfml-graphics -lsfml-window -ltgui

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
