SERVER = server
CLIENT = client
BUILDS = builds
SERVER_SRCS = $(wildcard server/*.c)
CLIENT_SRCS = $(wildcard client/*.c)
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
CC = gcc
RM = rm -f

all : server client

dir:
	mkdir -p $(BUILDS)

server : $(SERVER_OBJS) dir
	$(CC) $(SERVER_OBJS) -o $(BUILDS)/$(SERVER)

client : $(CLIENT_OBJS) dir
	$(CC) $(CLIENT_OBJS) -o $(BUILDS)/$(CLIENT)

clean :
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean : clean
	$(RM) $(BUILDS)/*

re : fclean all
