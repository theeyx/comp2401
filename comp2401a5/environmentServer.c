#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "simulator.h"

#define SERVER_PORT 6000


Environment    environment;  // The environment that contains all the robots





// Handle client requests coming in through the server socket.  This code should run
// indefinitiely.  It should repeatedly grab an incoming messages and process them.
// The requests that may be handled are STOP, REGISTER, CHECK_COLLISION and STATUS_UPDATE.
// Upon receiving a STOP request, the server should get ready to shut down but must
// first wait until all robot clients have been informed of the shutdown.   Then it
// should exit gracefully.
void *handleIncomingRequests(void *e) {
//instances
	char   online = 1;
	int serverSocket;
	struct sockaddr_in serverAddr, clientAddr;
	int status, addrSize, bytesReceived;
	fd_set readfds, writefds;
	unsigned char buffer[30];
	char *response = "OK";

//create sockett
	serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (serverSocket < 0) {
		printf("*** SERVER ERROR: Could not open socket.\n");
		exit(-1);
	}

	//server adress setup
	memset(&serverAddr, 0, sizeof(serverAddr)); // zeros the struct
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serverAddr.sin_port = htons((unsigned short) SERVER_PORT);

	//binds server socket
	status = bind(serverSocket,(struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (status < 0) {
 		printf("*** SERVER ERROR: Could not bind socket.\n");
 		exit(-1);
 	}

	while (online) {
		// ... WRITE YOUR CODE HERE ... //
		FD_ZERO(&readfds);
		FD_SET(serverSocket, &readfds);
	  FD_ZERO(&writefds);
		FD_SET(serverSocket, &writefds);
	  status = select(FD_SETSIZE, &readfds, &writefds, NULL, NULL);
		if (status == 0) { // Timeout occurred, no client ready
 		}
		else if (status < 0) {
 			printf("*** SERVER ERROR: Could not select socket.\n");
 			exit(-1);
		}else{
			addrSize = sizeof(clientAddr);
 			bytesReceived = recvfrom(serverSocket, buffer, sizeof(buffer),0, (struct sockaddr *) &clientAddr, &addrSize);


			if(buffer[0] == 2){

				break;
				//set shutdown flag  0
				//exit loop
			}

			if(buffer[0]==1 && environment.numRobots < 20){
				printf("command recieved\n");
				srand(time(NULL));
				buffer[0] = 5;

					int i;
					//int x1,x2,y1,y2;

					environment.robots[i];
					// x -> random num between 15 585
					environment.robots[i].x = rand()%(585+1-15)+15;
					printf("value x is %f\n", environment.robots[i].x);
					environment.robots[i].y = rand()%(585+1-15)+15;
					printf("value y is %f\n", environment.robots[i].y);
					environment.robots[i].direction = rand()%181;
					// x = 202, 444
					// x1 = 0.78 [0000 0000: 00], 1.73 [0000 0001]
					// x2 = 202 [1100 1010: 202], 188 [1011 1100]
					 unsigned char x1 = environment.robots[i].x/256;
				//	 printf("value x1 is %d\n", x1);
					 unsigned char x2 = (unsigned int)environment.robots[i].x%256;
					// printf("value x2 is %d\n", x2);
					 unsigned char y1 = environment.robots[i].y/256;
					// printf("value y1 is %d\n", y1);
					 unsigned char y2 = (unsigned int)environment.robots[i].y%256;
					// printf("value y2 is %d\n", y2);
					 unsigned char dir = environment.robots[i].direction;

					buffer[1] = x1;
					buffer[2] = x2;
					buffer[3] = y1;
					buffer[4] = y2;
					buffer[5] = i;
					buffer[6] = dir;

					i++;
					environment.numRobots++;
 				sendto(serverSocket, buffer, sizeof(buffer), 0,
 								(struct sockaddr *) &clientAddr, addrSize);

				printf("command sent to client\n");
			}else{
				buffer[0] = 6;
				sendto(serverSocket, buffer, sizeof(buffer), 0,
 								(struct sockaddr *) &clientAddr, addrSize);
				break;
			}
		}
  }
		// ... WRITE ANY CLEANUP CODE HERE ... //
	close(serverSocket);
	printf("closing server socket\n");
	environment.shutDown = 1;
	printf("shutdown the server\n");
//	pthread_exit(NULL);
}




int main() {
	// So far, the environment is NOT shut down
	environment.shutDown = 0;

	pthread_t t1, t2;

	pthread_create(&t1,NULL,handleIncomingRequests,&environment);
	pthread_create(&t2,NULL,redraw,&environment);

  pthread_join(t1,NULL);
  pthread_join(t2,NULL);

	//environment.shutDown = 1;

	// Set up the random seed
	srand(time(NULL));

	// Spawn an infinite loop to handle incoming requests and update the display

	// Wait for the update and draw threads to complete
}
