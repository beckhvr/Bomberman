#include "server.h"

void handleReceivedEvent() {
  t_event event;
  struct sockaddr_in socket_in;
  int addrlen = sizeof(socket_in);

  //If something happened on the master socket , then its an incoming connection
  if (FD_ISSET(game->connection_socket, game->socket_list)) {
    accept_new_player();
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
          if ((valread = read(sd, &event, sizeof(t_event))) == 0) {
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
            game->players[i]->events->x += event.x;
            game->players[i]->events->y += event.y;
            game->players[i]->events->direction = event.direction;
            game->players[i]->events->bomb = event.bomb;
          }
        }
      }
    }
  }
}

void sendDataToPlayers() {
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


void run_game_cycle() {
  int i;

  // bombs

  // flames

  // @TODO: clean this up, and check for colisions !!
  for (i = 0; i < 4; i++) {
    if (game->players[i]) {
      game->players[i]->x += game->players[i]->events->x;
      if (game->players[i]->x < 0) {
        game->players[i]->x = 0;
      }
      if (game->players[i]->x > 100) {
        game->players[i]->x = 100;
      }
      game->players[i]->y += game->players[i]->events->y;
      if (game->players[i]->y < 0) {
        game->players[i]->y = 0;
      }
      if (game->players[i]->y > 100) {
        game->players[i]->y = 100;
      }
      game->players[i]->direction = game->players[i]->events->direction;
      if (game->players[i]->events->bomb > 0) {
        printf("PLACING BOMB at : %d - %d\n", game->players[i]->x, game->players[i]->y);
        game->players[i]->events->bomb = 0;
      }
    }
  }



  // blocks

}



void game_loop() {
  int max;
  int activity;
  struct timeval timeout;
  fd_set socket_list;

  game->socket_list = &socket_list;
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;

  // TODO: listen to user input, so we can specify when we want to exit the server and clean up connections !!

  while (game->isRunning) {
    max = init_file_listener();
    activity = select(max + 1, game->socket_list, NULL, NULL, &timeout);

    if (activity < 0) {
      game->isRunning = 0;
    } else if (activity > 0) {
      handleReceivedEvent();
    }

    // here, process game to calculate movement, explosions, lose of life ...
    run_game_cycle();

    // we have a little wait period, for the moment it is 1 second
    usleep(160000);
    sendDataToPlayers();
  }
}
