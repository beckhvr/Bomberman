#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAXBUF 1024

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

    while (1) {
      bzero(buffer, MAXBUF);

      if (recv(connexion_socket, buffer, sizeof(buffer), 0) == 0) {
        printf("server disconnected\n");
        break;
      }

      // // 1 chance sur 20 d'envoyer un evenement.
      // int tmp = rand() % 20;
      // if (tmp < 10) {
      //   send(connexion_socket, "EVENT", 6, 0);
      // }

      printf("recieved: %s\n", buffer);
    }
  }

  /*---Clean up---*/
  close(connexion_socket);
  return 0;
}

