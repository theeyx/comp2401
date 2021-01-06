#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "simulator.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000


int main() {
  // ... ADD SOME VARIABLES HERE ... //
  int clientSocket, addrSize, bytesReceived;
  struct sockaddr_in serverAddr;
  char inStr[80];
  char buffer[80];

  // Register with the server
  // ... WRITE SOME CODE HERE ... //
 clientSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
 if (clientSocket < 0) {
   printf("*** CLIENT ERROR: Could open socket.\n");
   exit(-1);
 }

 memset(&serverAddr, 0, sizeof(serverAddr));
 serverAddr.sin_family = AF_INET;
 serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
 serverAddr.sin_port = htons((unsigned short) SERVER_PORT);

  // Send command string to server
  // ... WRITE SOME CODE HERE ... //ye
  addrSize = sizeof(serverAddr);
  buffer[0] = 2;
  sendto(clientSocket, buffer, sizeof(buffer), 0,
        (struct sockaddr *) &serverAddr, addrSize);
}
