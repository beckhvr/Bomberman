SERVER = server
CLIENT = client
BUILDS = builds
SERVER_SRCS = $(wildcard server/*.c)
CLIENT_SRCS = $(wildcard client/*.c)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
CC = gcc
RM = rm -f
# CFLAGS	=	-ansi -pedantic -W -Wall -Werror `sdl2-config --cflags`
CFLAGS	=	`sdl2-config --cflags`
LDFLAGS	=	`sdl2-config --libs` -lSDL2_image

all : server client

dir:
	mkdir -p $(BUILDS)

server : $(SERVER_OBJS) dir
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(BUILDS)/$(SERVER)

client : $(CLIENT_OBJS) dir
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(BUILDS)/$(CLIENT) $(LDFLAGS)

clean :
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean : clean
	$(RM) $(BUILDS)/*

re : fclean all
