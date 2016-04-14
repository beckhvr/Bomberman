SERVER = server
CLIENT = client
SERVER_SRCS = server.c
CLIENT_SRCS = client.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
CC = gcc
RM = rm -f

all : server client

server : $(SERVER_OBJS)
	$(CC) $(SERVER_OBJS) -o server

client : $(CLIENT_OBJS)
	$(CC) $(CLIENT_OBJS) -o client

clean :
	$(RM) $(SERVER_OBJS) $(CLIENT_OBJS)

fclean : clean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)

re : fclean all
