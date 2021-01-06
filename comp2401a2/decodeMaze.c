//include libraries
#include <stdio.h>

//define constants
#define NUM_BITS 32
#define MINI_BITS 8
#define MINI_MERGE 14

//declare function prototypes
void printEncodedMaze(int [], unsigned char);
void printEncodedMazeWithPath(int [], int [], unsigned char);
void encode8by8Maze(char inputMaze[MINI_BITS][MINI_BITS], int encodedMaze[MINI_BITS]);
void merge8by8Mazes(int topLeft[MINI_BITS], int topRight[MINI_BITS],int bottomLeft[MINI_BITS], int bottomRight[MINI_BITS],int finalMaze[MINI_MERGE]);
char isPathInMaze(int[], int[], unsigned char);



int main(){
	//declaring variables
	int maze[NUM_BITS] = {-1, -2146430423,-1109928277,-1525661045,-1602496045,-1358950569,-1451509759,-1927115297,-1578180479,-1354977603,-1476294999,-2084818261,-1163749757,-1964319689,-1341614619,-1750141691,-1256060947,-1515522751,-1204136611,-1955867371,-1190652827,-1553272339,-1100839163,-1999963019,-631368865,-1882138047,-1172944163,-1412279803,-1567107339,-164346691,-2138762879,-1};
	int pathMaze[NUM_BITS] = {0, 0, 0, 0, 12, 8, 56, 32, 8032, 4416, 134115648, 67354944, 67109184, 67109312, 133169152,
1048576, 1835008, 262144, 262144, 262144, 458752, 65536, 65536, 65536, 65536, 983040, 67633152, 67633152, 201850880, 164102144, 259522560, 0};
	int pathMaze2[MINI_MERGE] = {0, 4096, 4096, 4096, 4096, 7936, 256, 256, 448, 112, 16, 28, 6, 0};
	int miniTopLeft[MINI_BITS];
	int miniTopRight[MINI_BITS];
	int miniBotLeft[MINI_BITS];
	int miniBotRight[MINI_BITS];
	int finalMaze[MINI_MERGE];
	int *arrayPointers[4] = {miniTopLeft, miniTopRight, miniBotLeft, miniBotRight};

	char miniMaze1[MINI_BITS][MINI_BITS] =
   {{1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,0,1}, //hardcode for topleft
    {1,0,1,0,1,1,0,1},
    {1,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,1,0,1,0,1,1},
    {1,1,1,1,1,1,1,1}};
	char miniMaze2[MINI_BITS][MINI_BITS] =
   {{1,1,1,1,1,1,1,1},
    {1,0,0,0,0,1,0,1}, //hardcode for topright
    {1,1,1,1,0,1,0,1},
    {1,0,0,1,0,1,1,1},
    {1,1,0,0,0,0,0,1},
    {1,1,1,1,0,1,1,1},
    {1,0,0,0,0,1,0,1},
    {1,1,1,1,1,1,1,1}};
	char miniMaze3[MINI_BITS][MINI_BITS] =
   {{1,1,1,1,1,1,1,1},
    {1,0,1,0,0,0,1,1}, //hardcode for botleft
    {1,0,1,0,1,0,0,1},
    {1,0,1,0,1,0,1,1},
    {1,0,1,0,1,0,1,1},
    {1,0,1,0,1,0,1,1},
    {1,0,0,0,1,0,0,1},
    {1,1,1,1,1,1,1,1}};
	char miniMaze4[MINI_BITS][MINI_BITS] =
   {{1,1,1,1,1,1,1,1},
    {1,0,1,0,1,0,1,1}, //hardcode for botright
    {1,0,1,0,0,0,0,1},
    {1,0,0,0,1,1,1,1},
    {1,1,1,0,1,0,0,1},
    {1,0,0,0,0,0,1,1},
    {1,1,0,1,1,0,0,1},
    {1,1,1,1,1,1,1,1}};

  //prints 32x32 maze
	printEncodedMaze(maze,NUM_BITS);
	puts("\n");

  //prints the maze with path
	printEncodedMazeWithPath(maze,pathMaze,NUM_BITS);

	 //tells user if the path fits in the maze
	char result = isPathInMaze(maze,pathMaze,NUM_BITS);
	if(result == 1){
		puts("path fits in maze");
	}else{
		puts("path does not fit in maze");
	}
	puts("\n");

	//prints each individual 8x8 maze
	encode8by8Maze(miniMaze1, miniTopLeft);
	printEncodedMaze(miniTopLeft,MINI_BITS);
	puts("\n");
	encode8by8Maze(miniMaze2, miniTopRight);
	printEncodedMaze(miniTopRight,MINI_BITS);
	puts("\n");
	encode8by8Maze(miniMaze3, miniBotLeft);
	printEncodedMaze(miniBotLeft,MINI_BITS);
	puts("\n");
	encode8by8Maze(miniMaze4, miniBotRight);
	printEncodedMaze(miniBotRight,MINI_BITS);
	puts("\n");

	//prints merged 8x8 maze
	merge8by8Mazes(miniTopLeft,miniTopRight,miniBotLeft, miniBotRight,finalMaze);
	printEncodedMaze(finalMaze,MINI_MERGE);

	//prints 256 combinations of 4, 8x8 mazes along with telling user if path fits in the maze
  int isPathInMazeCount = 0;
	for(int tl = 0; tl<4; ++tl){
		for(int bl = 0; bl<4; ++bl){
			for(int tr = 0; tr<4; ++tr){
				for(int br = 0; br<4; ++br){
					merge8by8Mazes(arrayPointers[tl],arrayPointers[bl],arrayPointers[tr],arrayPointers[br],finalMaze);
					printf("\nAbout to print combination %d,%d,%d,%d\n",tl+1,bl+1,tr+1,br+1);
					printEncodedMaze(finalMaze,MINI_MERGE);
					char result = isPathInMaze(finalMaze,pathMaze2,MINI_MERGE);
					if(result == 1){
						printf("Found maze that fits path. %d match.\n", ++isPathInMazeCount);
					}
				}
			}
		}
	}
}



//function that prints encoded maze with @ as the walls
//assume that maze will always be a square
void printEncodedMaze(int arrayMaze[], unsigned char size){
	for(int r=0; r<size; ++r){
	   	for(int c=0; c<NUM_BITS; ++c){
	               int mask =1 << (NUM_BITS - 1 - c);
		       if(mask & arrayMaze[r]){
		       		printf("@");
		       }
		       else{
		                printf(" ");
		       }
		}
		puts("");
	}
}



//function that prints the encooded maze with hardcoded path for 32x32
void printEncodedMazeWithPath(int arrayMaze[], int path[], unsigned char size){
	for(int r=0; r<size; ++r){
	   	for(int c=0; c<NUM_BITS; ++c){
	               int mask =1 << (NUM_BITS - 1 - c);
		       if(mask & arrayMaze[r]){
		       		printf("@");
		       }
		       else if(mask & path[r]){
		       		printf(".");
		       }
		       else{
		                printf(" ");
		       }
		}
		puts("");
	}
}



//function that extracts 8x8 maze from given hardcode
void encode8by8Maze(char inputMaze[MINI_BITS][MINI_BITS], int encodedMaze[MINI_BITS]){
	for( int r = 0; r<MINI_BITS; ++r){
		encodedMaze[r] = 0;
 		for(int c = 0; c<MINI_BITS; ++c){
 			if(inputMaze[r][c] == 1){
 			        int mask = 1 << (NUM_BITS - 1 -c);
 				encodedMaze[r] |= mask;
 			}
 		}
 	}
}



//function that merges the 4, 8x8 mazes
void merge8by8Mazes(int topLeft[MINI_BITS], int topRight[MINI_BITS],int bottomLeft[MINI_BITS], int bottomRight[MINI_BITS],int finalMaze[MINI_MERGE]){
	for(int r =0; r<MINI_BITS-1; ++r){
		finalMaze[r] = 0;
		for(int c=0; c<MINI_BITS-1; ++c){         //topleft part
			int mask = 1 << (NUM_BITS - 1 - c);
			if(topLeft[r] & mask){
				finalMaze[r] |= mask;
			}
		}
	}

	for(int r =1; r<MINI_BITS; ++r){
		finalMaze[r+MINI_BITS-2] = 0;
		for(int c=0; c<MINI_BITS-1; ++c){      //botleft part
			int mask = 1 << (NUM_BITS - 1 - c);
			if(bottomLeft[r] & mask){
				finalMaze[r+MINI_BITS-2] |= mask;
			}
		}
	}

	for(int r =0; r<MINI_BITS-1; ++r){
		for(int c=1; c<MINI_BITS; ++c){
			int mask = 1 << (NUM_BITS - 1 - c);    //topright part
			if(topRight[r] & mask){
				int mask2 = 1 << (NUM_BITS - MINI_BITS - c + 1);
				finalMaze[r] |= mask2;
			}
		}
	}

	for(int r =1; r<MINI_BITS; ++r){
		for(int c=1; c<MINI_BITS; ++c){
			int mask = 1 << (NUM_BITS - 1 - c);    //botright part
			if(bottomRight[r] & mask){
				int mask2 = 1 << (NUM_BITS - MINI_BITS - c + 1);
				finalMaze[r+MINI_BITS-2] |= mask2;
			}
		}
	}
}



// function that lets user know if given path fits the maze, meaning it doesnt hit any walls
char isPathInMaze(int arrayMaze[], int path[], unsigned char size){
	for(int r=0; r<size; ++r){
			for(int c=0; c<NUM_BITS; ++c){
			     int mask =1 << (NUM_BITS - 1 - c);
					 if((mask & arrayMaze[r])&&(mask & path[r])){
							return 0;
					 }
		}
	}
	return 1;
}
