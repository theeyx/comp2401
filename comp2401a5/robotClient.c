#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "simulator.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000




// This is the main function that simulates the "life" of the robot
// The code will exit whenever the robot fails to communicate with the server
int main() {
  // ... ADD SOME VARIABLE HERE ... //
  int clientSocket, addrSize, bytesReceived;
  struct sockaddr_in serverAddr;
  char inStr[80]; // stores user input from keyboard
  unsigned char buffer[80]; // stores sent and received data
  // Set up the random seed
  srand(time(NULL));

  // Register with the server
  // Create socket
 clientSocket = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
 if (clientSocket < 0) {
 printf("*** CLIENT ERROR: Could open socket.\n");
 exit(-1);
 }
 // Setup address
 memset(&serverAddr, 0, sizeof(serverAddr));
 serverAddr.sin_family = AF_INET;
 serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
 serverAddr.sin_port = htons((unsigned short) SERVER_PORT);
  // Send register command to server.  Get back response data
  // and store it.   If denied registration, then quit.
 addrSize = sizeof(serverAddr);
 buffer[0] = 1;
 sendto(clientSocket, buffer, sizeof(buffer), 0,
      (struct sockaddr *) &serverAddr, addrSize);

 bytesReceived = recvfrom(clientSocket, buffer, sizeof(buffer), 0,
       (struct sockaddr *) &serverAddr, &addrSize);

//buffer[bytesReceived];
if(buffer[0] == 5){
  printf("we got back response from the server\n");
   int x = buffer[1] * 256;
   int x1 = abs(x + buffer[2]);
   int y = buffer[3] * 256;
   int y1 = abs(y + buffer[4]);
   int i = buffer[5];
   int d = buffer[6];



  printf("robot id %d returned (%d,%d) and direction %d\n",i,x1,y1,d);


  exit(0);

}

if(buffer[0] == 6){
  printf("we got NOT-OK response from server\n");
  exit(0);
}

  // Go into an infinite loop exhibiting the robot behavior
  while (1) {
    // Check if can move forward

    // Get response from server.

    // If ok, move forward
    // Otherwise, we could not move forward, so make a turn.
    // If we were turning from the last time we collided, keep
    // turning in the same direction, otherwise choose a random
    // direction to start turning.

    // Send update to server

    // Uncomment line below to slow things down a bit
    // usleep(1000);
  }
}
