#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//define constants
const int totalPackages = 24;
const int maxBox = 6;
const int length = 5;
const int width = 4;
const double priceS = 5.99;
const double priceM = 10.99;
const double priceL = 19.99;
const char empty = ' ';
const char small = 'S';
const char medium = 'M';
const char large = 'L';

//function prototypes
int boxPackages(int print,unsigned int quantityL, unsigned int quantityM, unsigned int quantityS);

int main(){

	srand(time(NULL));
	unsigned int quantityL = rand()%(totalPackages+1); //generate random number of large between 0 and total packages
	unsigned int quantityM = rand()%(totalPackages+1 - quantityL);
	unsigned int quantityS = totalPackages - quantityL - quantityM;
	double costL = quantityL * priceL;
	double costM = quantityM * priceM;
	double costS = quantityS * priceS;
	double costTotal = costS + costM + costL;
	double hst = costTotal * 0.13;

	int numBoxes = boxPackages(0, quantityL, quantityM,  quantityS); // initialize number of boxes from function
	float shipPrice = numBoxes * 1.49;
	float totalAmount = costTotal + hst + shipPrice;

	printf("\n");
	printf("Order:  Large = %d, Medium = %d, Small = %d \n",quantityL,quantityM,quantityS);
	printf("\n");
	printf("Small (%02d units)     $%7.2f \n",quantityS,costS);
	printf("Medium (%02d units)    $%7.2f \n",quantityM,costM);
	printf("Large (%02d units)     $%7.2f \n",quantityL,costL);
	printf("-----------------------------------\n");
	printf("Total                $%7.2f \n",costTotal);
	printf("Shipping (%d boxes)   $%7.2f \n",numBoxes,shipPrice);
	printf("HST (13%c)            $%7.2f\n",'%',hst);
	printf("-----------------------------------\n");
	printf("Amount Charged       $%7.2f\n",totalAmount);
	printf("\n");
	printf("Individual boxes are packed as follows: \n\n");

	//prints the packages in boxes
	boxPackages(1, quantityL, quantityM,  quantityS);


}

//function that prints the packages into boxes as well as telling you how many boxes used
int boxPackages(int print,unsigned int quantityL, unsigned int quantityM, unsigned int quantityS){
	char box[length][width];

	int packagesRemaining = totalPackages;
	unsigned int largeLeft = quantityL;
	unsigned int mediumLeft = quantityM;
	unsigned int smallLeft = quantityS;
	unsigned int numBoxes = 0;

	while((packagesRemaining > 0) && (numBoxes<maxBox)){
		++numBoxes;
		//initialize empty box
		for(unsigned int r = 0; r<length; ++r){
			for(unsigned c = 0; c<width; ++c){
				box[r][c] = empty;
			}
		}

		//first add as many large packages as possible
		for(int r = 0; (r<(length-1)) && (largeLeft >0); ++r){
			for(int c = 0; (c<(width-1))&&(largeLeft >0); ++c){

				if(box[r][c] == empty){
					box[r][c] = box[r+1][c] = box[r][c+1] = box[r+1][c+1] = large;
					--largeLeft;
					--packagesRemaining;
				}
			}
		}

		//second add as many medium packages as possible
		for(int r = 0; (r<(length-1)) && (mediumLeft >0); ++r){
			for(int c = 0; c<width && (mediumLeft >0); ++c){

				if(box[r][c] == empty){
					box[r][c] = box[r+1][c] = medium;
					--mediumLeft;
					--packagesRemaining;
				}
			}
		}

		for(int r = 0; r<length && (mediumLeft >0); ++r){
			for(int c = 0; (c<(width-1)) && (mediumLeft >0); ++c){

				if(box[r][c] == empty){
					box[r][c] = box[r][c+1] = medium;
					--mediumLeft;
					--packagesRemaining;
				}
			}
		}

		//third add as many small packages as possible
		for(int r = 0; r<length && (smallLeft >0); ++r){
			for(int c = 0; c<width && (smallLeft >0); ++c){

				if(box[r][c] == empty){
					box[r][c] = small;
					--smallLeft;
					--packagesRemaining;
				}
			}
		}

		//prints the boxes
		if(print){
			for(int r = 0; r < length; ++r){
				for(int c = 0; c < width; ++c){
					printf("%c",box[r][c]);
				}
				puts("");
			}
			puts("");
		}

	}

	//checks if out of bounds
	if((numBoxes == maxBox)&&(packagesRemaining>0)){
		puts("We ran out of boxes");
		return maxBox;
	}
	else{
		return numBoxes;
	}
}
