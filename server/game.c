#include "server.h"

void addPlayer(t_game* game, int new_socket) {
  for (int i = 0; i < 4; i++) {
    if(game->players[i] == NULL) {
      game->players[i] = malloc(sizeof(t_player));
      game->players[i]->address = new_socket;

      game->players[i]->hp = 3;

      // set position X
      if (i < 3) {
        game->players[i]->x = 0;
      } else {
        game->players[i]->x = 100;
      }

      // set position Y
      if ((i % 2) == 1) {
        game->players[i]->y = 0;
      } else {
        game->players[i]->y = 100;
      }

      game->players[i]->direction = 3; // all facing down at first

      // t_player_actions actions;
      // int cooldown;

      break;
    }
  }
}

void handleNewPlayer(t_game* game) {
  struct sockaddr_in socket_in;
  int addrlen = sizeof(socket_in);
  int new_socket;

  if ((new_socket = accept(game->connection_socket, (struct sockaddr *)&socket_in, (socklen_t*)&addrlen)) < 0) {
    perror("accept");
    exit(-1);
  }

  //inform user of socket number - used in send and receive commands
  printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket, inet_ntoa(socket_in.sin_addr), ntohs(socket_in.sin_port));

  if (get_player_count(game) < 4) {
    addPlayer(game, new_socket);
  } else {
    // tell the nicely but firmly to get the fuck away
    printf("let's tell them to fuckoff ... \n");
    send(new_socket, "GET OUT !", 10, 0);
    close(new_socket);
  }
}

void handleReceivedEvent(t_game* game) {
  char buffer[1024];
  struct sockaddr_in socket_in;
  int addrlen = sizeof(socket_in);

  //If something happened on the master socket , then its an incoming connection
  if (FD_ISSET(game->connection_socket, game->socket_list)) {
    handleNewPlayer(game);
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



  // prepare data to be sent :

  t_container container;


  // copy map info
  strcpy(container.map, "\n\n--INCOMMING--\n");
  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      char tmp[100];
      sprintf(tmp, "player %d => x: %d, y: %d, dir: %d\n", i + 1, game->players[i]->x, game->players[i]->y, game->players[i]->direction);
      strcat(container.map, tmp);
    }
  }
  strcat(container.map, "--OVER--\n\n");

  for (i = 0; i < 4; i++)
  {
    if (game->players[i])
    {
      // maybe this should be in a while statement ...
      send(game->players[i]->address, &container, sizeof(container), 0);
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
