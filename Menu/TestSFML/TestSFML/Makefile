SRC	=	main.cpp		\
		MenuController.cpp	\
		Menu.cpp		\
		MenuView.cpp		\

OBJ	=	$(SRC:.cpp=.o)

NAME	=	rtype

CXX	=	g++

CXXFLAGS +=	-W -Wall -Wextra -std=c++11 $(IFLAGS) $(LDFLAGS)

IFLAGS	=	-I.

LDFLAGS	=	-lsfml-window -lsfml-graphics -lsfml-system -ltgui

RM	=	rm -f

$(NAME)	:	$(OBJ)
		$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS)

all	:	$(NAME)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
