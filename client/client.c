#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "../shared/shared.h"

#define MAXBUF 1024

int get_nth_bit(char* c, int bit)
{
  return (*c >> bit) & 1;
}


void ascii_map(char* c)
{

  if (get_nth_bit(c, 0) == 1)
  {
    // this is clearly having some sort of nervous breakdown, I am no longer setting the first bit.
    printf("F");
    return;
  }

  if (get_nth_bit(c, 1) == 1)
  {
    printf("-");
    return;
  }

  if (get_nth_bit(c, 3) == 1)
  {
    printf("B");
    return;
  }

  printf(" ");
  return;
}

int main()
{
  int connexion_socket;
  char address[1024] = "127.0.0.1";
  int port = 3334;
  struct sockaddr_in dest;
  char buffer[MAXBUF];

  /*---Open socket for streaming---*/
  if ((connexion_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("unable to open socket\n");
    return -1;
  }

  /*---Initialize server address/port struct---*/
  bzero(&dest, sizeof(dest));
  dest.sin_family = AF_INET;
  dest.sin_port = htons(port);


  if (inet_aton(address, &dest.sin_addr.s_addr) == 0) {
    printf("error processing address\n");
    return -1;
  }

  /*---Connect to server---*/
  if (connect(connexion_socket, (struct sockaddr*)&dest, sizeof(dest)) != 0) {
    printf("unable to connect\n");
    return -1;
  }


  if ((recv(connexion_socket, buffer, 1024, 0)) == 0) {
    printf("something went wrong\n");
  } else if (strcmp(buffer, "no more space") == 0) {
    printf("no connection for me !");
  } else {
    // we recieved the welcome message, proceeed to listen on the socket.

    t_container container;

    while (1) {
      bzero(&container, sizeof(container));
      if (recv(connexion_socket, &container, sizeof(container), 0) == 0) {
        printf("server disconnected\n");
        break;
      }

      // 1 chance sur 20 d'envoyer un evenement.
      int tmp = rand() % 20;
      if (tmp < 10) {
        // on envoi des events au hazard.

        t_event event;

        if (tmp < 3) {
          event.x = -1;
          event.y = 0;
          event.direction = 1;
          event.bomb = 1;
        } else if (tmp < 6) {
          event.x = 1;
          event.y = 1;
          event.direction = 1;
          event.bomb = 0;
        } else {
          event.x = 0;
          event.y = -1;
          event.direction = 1;
          event.bomb = 0;
        }

        send(connexion_socket, &event, sizeof(event), 0);
      }




      printf("\n\n--Start--\n");
      // decoding what we received:
      for (int i = 0; i < 4; i++) {
        if (container.players[i].playing == 1) {
          printf("player %d => x:%d y:%d facing:%d hp:%d\n", i, container.players[i].x, container.players[i].y, container.players[i].direction, container.players[i].hp);
        }
      }

      // reading map
      for (int i = 0; i < 144; i++)
      {
        if (i % 12 == 0) {
          printf("\n");
        }
        ascii_map(&container.map[i]);
        // this is the current block;
        //container.map[i]
      }
      printf("\n");
      printf("--end--\n\n");

      // this should be in client actually












    }
  }

  /*---Clean up---*/
  close(connexion_socket);
  return 0;
}

