#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main() {
   int clientSocket, addrSize, bytesReceived;
   struct sockaddr_in serverAddr;
   int inStr[80]; // stores user input from keyboard
   char buffer[80]; // stores sent and received data

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

 // Go into loop to commuincate with server now
 while (1) {
   addrSize = sizeof(serverAddr);

 // Get a command from the user
   printf("CLIENT: Enter positive integer to send to server ... ");
   scanf("%d", inStr);

 // Send command string to server
   //memcpy(buffer,inStr,sizeof(int));
   printf("CLIENT: Sending \"%d\" to server.\n", *inStr);
   sendto(clientSocket, inStr, sizeof(inStr), 0,
   (struct sockaddr *) &serverAddr, addrSize);

 // Get response from server, should be "OK"
   bytesReceived = recvfrom(clientSocket, buffer, 80, 0,
   (struct sockaddr *) &serverAddr, &addrSize);
   buffer[bytesReceived] = 0; // put a 0 at the end so we can display the string
   printf("CLIENT: Got back response \"%s\" from server.\n", buffer);

   if (*inStr == -1)
    break;
 }
 close(clientSocket); // Don't forget to close the socket !
 printf("CLIENT: Shutting down.\n");
}
