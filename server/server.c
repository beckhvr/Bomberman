#include "server.h"


/*-----------------------------------------------------------------------------
------(More or less done)------------------------------------------------------
-----------------------------------------------------------------------------*/

// creating a socket to handle entering connexions.
int create_connection_socket(port) {
  int connection_socket;
  struct sockaddr_in socket_in;
  char yes;

  if ((connection_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    return -1;

  memset(&socket_in, 0, sizeof socket_in);
  socket_in.sin_family = AF_INET;
  socket_in.sin_port = htons(port);
  socket_in.sin_addr.s_addr = INADDR_ANY;
  yes = '1';
  setsockopt(connection_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));

  if ((bind(connection_socket, (struct sockaddr*)&socket_in, sizeof(socket_in))) != 0)
  {
    close(connection_socket);
    return -1;
  }

  if ((listen(connection_socket, 4)) != 0)
  {
    close(connection_socket);
    return -1;
  }

  return connection_socket;
}

// returns max file listener
int initFileListener(t_game* game) {
  int max;
  int i;

  FD_ZERO(game->socket_list);
  FD_SET(game->connection_socket, game->socket_list);
  max = game->connection_socket;

  for (i = 0 ; i < 4; i++)
  {
    if (game->players[i] != NULL)
    {
      FD_SET(game->players[i]->address, game->socket_list);
      if(game->players[i]->address > max)
      {
        max = game->players[i]->address;
      }
    }
  }

  return max;
}



















/*-----------------------------------------------------------------------------
------(To Work on)-------------------------------------------------------------
-----------------------------------------------------------------------------*/

void handleReceivedEvent(t_game* game) {
  struct sockaddr_in socket_in;
  int addrlen = sizeof(socket_in);
  int new_socket;
  char buffer[1024];

  //If something happened on the master socket , then its an incoming connection
  if (FD_ISSET(game->connection_socket, game->socket_list)) {
    if ((new_socket = accept(game->connection_socket, (struct sockaddr *)&socket_in, (socklen_t*)&addrlen)) < 0) {
      perror("accept");
      exit(-1);
    }

    //inform user of socket number - used in send and receive commands
    printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket, inet_ntoa(socket_in.sin_addr), ntohs(socket_in.sin_port));


    // make sure we have enough space here
    int nbPlayers = 0;
    for (int i = 0; i < 4; i++) {
      if(game->players[i] != NULL) {
        nbPlayers++;
      }
    }



    // for test purposes :
    // nbPlayers = 4;



    if (nbPlayers < 4) {
      //send new connection greeting message
      char *message = "WELCOME\n";
      if(send(new_socket, message, strlen(message), 0) != strlen(message)) {
        perror("send");
      }

      //add new socket to array of sockets
      for (int i = 0; i < 4; i++) {
        if(game->players[i] == NULL) {
          game->players[i] = malloc(sizeof(t_player));
          game->players[i]->address = new_socket;
          break;
        }
      }
    } else {
      printf("let's tell them to fuckoff ... \n");
      // tell the nicely but firmly to get the fuck away
      char *refuseMessage = "no more space";
      send(new_socket, refuseMessage, strlen(refuseMessage), 0);
      close(new_socket);
    }
  }
  //else its some IO operation on some other socket
  else {
    // check each socket
    for (int i = 0; i < 4; i++) {

      if (game->players[i]) {
        int sd = game->players[i]->address;
        int valread;

        // triggers when it finds the socket that emited an event
        if (FD_ISSET(sd, game->socket_list)) {

          //Check if it was for closing , and also read the incoming message
          // did it disconnect ?
          if ((valread = read(sd , buffer, 1024)) == 0) {
            //Somebody disconnected , get his details and print
            getpeername(sd , (struct sockaddr*)&socket_in , (socklen_t*)&addrlen);
            printf("Host disconnected , ip %s , port %d \n" , inet_ntoa(socket_in.sin_addr) , ntohs(socket_in.sin_port));

            //Close the socket and mark as 0 in list for reuse
            close(sd);
            free(game->players[i]);
            game->players[i] = NULL;
          }
          // if not, then it's a regular event, as in a user input ...
          else {
            printf("player %d has sent: %s\n", i, buffer);
            //set the string terminating NULL byte on the end of the data read
            // send(sd , "message\0", 8, 0);
          }
        }
      }
    }
  }


}







void sendDataToPlayers(t_game* game) {
  int i;

  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      // maybe this should be in a while statement ...
      send(game->players[i]->address, "INFO", 5, 0);
    }
  }
}











void game_loop(t_game* game) {
  int max;
  int activity;
  struct timeval timeout;
  fd_set socket_list;

  game->socket_list = &socket_list;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  // TODO: listen to user input, so we can specify when we want to exit the server and clean up connections !!

  while (game->isRunning) {
    max = initFileListener(game);
    activity = select(max + 1, game->socket_list, NULL, NULL, &timeout);

    if (activity < 0) {
      printf("select error");
      game->isRunning = 0;
    } else if (activity > 0) {
      handleReceivedEvent(game);
    }

    // we have a little wait period, for the moment it is 1 second
    sleep(1);
    sendDataToPlayers(game);
  }
}




int init_map(t_game* game) {

  // init all the lists for blocks, bombs and flames

  return 0;
}

void free_map(t_game* game) {

}

void init_players(t_game* game)
{
  int i;

  for (i = 0; i < 4; i++) {
    game->players[i] = NULL;
  }
}

void free_players(t_game* game)
{
  int i;

  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      close(game->players[i]->address);
      free(game->players[i]);
    }
  }
}


int main(int argc, char const *argv[])
{
  t_game game;

  if ((game.connection_socket = create_connection_socket(3334)) < 0) {
    printf("unable to setup listener socket\n");
    return (-1);
  }

  // init map
  if (init_map(&game) < 0) {
    close(game.connection_socket);
    printf("unable to init map\n");
    return (-1);
  }

  // init players
  init_players(&game);

  // init game
  game.isRunning = 1;
  game_loop(&game);

  free_map(&game);
  // free lists of bombs and flames ...
  free_players(&game);
  close(game.connection_socket);
  return 0;
}
