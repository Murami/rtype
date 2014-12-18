##
## Makefile for  in /home/otoshigami/Workspace/Epitech/git/cpp_bomberman
## 
## Made by otoshigami
## Login   <otoshigami@epitech.net>
## 
## Started on  Sun Jun 15 08:48:53 2014 otoshigami
## Last update Wed Dec 17 21:31:11 2014 anto
##

## FILES

NAME		=	rtype

SRC		=	main				\
			Util/Vec2			\
			Util/IDGenerator		\
			Util/Time			\
			Physic/Body			\
			Physic/World			\
			Physic/BodyEventMove		\
			Physic/BodyEventCollide		\
			Physic/BodyEventReceiver	\
			Game/CoreEventReceiver		\
			Game/EntityEventReceiver	\
			Game/EntityEventMove		\
			Game/EntityEventLife		\
			Game/CollisionReceiver		\
			Game/Entity			\
			Game/Core			\
			Game/CollisionEvent		\
			Game/Player			\
			Game/Projectile			\
			Game/Monster			\
			Game/DestroyableSet		\
			Game/CoreEventDestroy		\
			Game/CoreEventSpawn		\
			Util/Mutex			\
			Util/Lock			\
			Util/Thread			\
			Application/Room		\
			Application/ClientRoom


SRC_EXT		=	.cpp

## DIRECTORIES

DOBJ		=	obj
DSRC		=	src
DBIN		=	.

## COMPILATION

DINC		=	include

CFLAGS		=	-Wall		\
			-Wextra		\
			-std=c++11

MAKED		=	make --no-print-directory -C

## LINKAGE

LIB		=	pthread
DLIB		=
LDFLAGS		=

## RUNS

CC		=	g++ -fmax-errors=5
# CC		=	clang++
RM		=	rm -rf
MD		=	mkdir -p

####################
## INTERNAL RULES ##
####################

## CONSTANTS

DBGBOOL		=	no

PROFILE		=	no

DBG		=	-g3		\
			-ggdb

WERROR		=	-Werror

## FILES

OBJ		=	$(addsuffix .o, $(SRC))
_SRC		=	$(addsuffix $(SRC_EXT), $(SRC))

## DIRECTORIES

DINC		:=	$(addsuffix /, $(DINC))
DOBJ		:=	$(addsuffix /, $(DOBJ))
DSRC		:=	$(addsuffix /, $(DSRC))
DBIN		:=	$(addsuffix /, $(DBIN))

## COMPILATION ARGS

CINC		=	$(addprefix -I, $(DINC))

COBJ		=	$(addprefix $(DOBJ), $(OBJ))
CSRC		=	$(addprefix $(DSRC), $(_SRC))
CNAME		=	$(addprefix $(DBIN), $(NAME))

## LINKAGE ARGS

LIB		:=	$(addprefix -l, $(LIB))
DLIB		:=	$(addsuffix /, $(DLIB))
DLIB		:=	$(addprefix -L, $(DLIB))

## FLAGS

ifeq ($(DBGBOOL), yes)
	CFLAGS  += $(DBG)
endif

ifeq ($(DBGBOOL), no)
	CFLAGS	+= $(WERROR)
endif

ifeq ($(PROFILE), yes)
	CFLAGS	+= -pg
	LDFLAGS += -pg
endif

CFLAGS		+=	$(CINC)
LDFLAGS		+=	$(DLIB)				\
			$(LIB)

## MISC RULES

MAKEOBJ		= $(addprefix $(DOBJ), %.o) : $(addprefix $(addprefix $(DSRC), %), $(SRC_EXT))

all:	$(CNAME)

dbg:	$(CNAME)

$(CNAME):	$(COBJ)
		@$(MD) $(DBIN)
		@$(CC) $(COBJ) -o $(CNAME) $(LDFLAGS)

$(COBJ):	$(MAKEOBJ)
		@$(MD) $(DOBJ)
		@for dir in `cd $(DSRC); ls -d */ 2> /dev/null`; \
		do \
		if [ ! -d "$(DOBJ)$$dir" ];then \
			$(MD) $(DOBJ)$$dir; \
		fi \
		done
		@echo "Compilation : $<"
		@$(CC) -c $< -o $@ $(CFLAGS)

clean:
		@$(RM) $(COBJ)

fclean:		clean
		@$(RM) $(CNAME)

re:		fclean all
redbg:		fclean dbg

.PHONY:		fclean clean all dbg re
