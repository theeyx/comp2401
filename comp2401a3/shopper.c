#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//defines
#define GROCERY_COUNT 12

//global const variables
const int MAX_BAGS = 30; //max number of bags allowed in a cart
const float MAX_BAG_WEIGHT = 5.0;
const int MAX_BAG_ITEMS = 25;
const int MAX_CART_ITEMS = 100;

//the structs and typedefs
typedef struct{
  char  *name;
  float price;
  float weight;
  int perish;
}GroceryItem;

typedef struct{
  GroceryItem** listItems;
  int numItems;
  float totalWeight;
}Bag;

typedef struct{
  GroceryItem** looseItems;
  int numLooseItems;
  Bag** packedBags;
  int numPackedBags;
}Cart;


//function prototypes
int addItemToCart(GroceryItem* gItemPtr, Cart* cartPtr);
int addItemToBag(GroceryItem* gItemPtr, Bag* bagPtr);
int removeItemFromBag(GroceryItem* gItemPtr, Bag* bagPtr);
void printGroceryItem(GroceryItem* gItemPtr);
void packCart(Cart* cartPtr);
void printBag(Bag* bagPtr, int bagNum);
void printCart(Cart* cartPtr);
void removePerish(Cart* cartPtr);

int main(){
    GroceryItem  testItems[GROCERY_COUNT];
    char *sampleItemNames[] = {"Smart-Ones Frozen Entrees", "SnackPack Pudding", "Breyers Chocolate Icecream", "Nabob Coffee", "Gold Seal Salmon", "Ocean Spray Cranberry Cocktail", "Heinz Beans Original", "Lean Ground Beef", "5-Alive Frozen Juice", "Coca-Cola 12-pack", "Toilet Paper - 48 pack", "Crate of milk"};
    float sampleItemPrices[] = {1.99, 0.99, 2.99, 3.99, 1.99, 2.99, 0.79, 4.94, 0.75, 3.49, 40.96, 12.99};
    float sampleItemWeights[] = {0.311, 0.396, 2.27, 0.326, 0.213, 2.26, 0.477, 0.75, 0.426, 5.112, 10.89f, 6.18f};
    int sampleItemPerish[] = {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1};

    //populate grocery items
    for(int i =0; i<GROCERY_COUNT; ++i){
        testItems[i].name = sampleItemNames[i];
        testItems[i].price = sampleItemPrices[i];
        testItems[i].weight = sampleItemWeights[i];
        testItems[i].perish = sampleItemPerish[i];
    }

    //create some bags
  /*  Bag testBag1 ={NULL,0,0.0};
    Bag testBag2 ={NULL,0,0.0};
    Bag testBag3 ={NULL,0,0.0};
    Bag testBag4 ={NULL,0,0.0};
    Bag testBag5 ={NULL,0,0.0};*/

    //create some carts
    Cart testCart1 = {NULL,0,NULL,0};
  /*  Cart testCart2 = {NULL,0,NULL,0};
    Cart testCart3 = {NULL,0,NULL,0};
    Cart testCart4 = {NULL,0,NULL,0};
    Cart testCart5 = {NULL,0,NULL,0};*/
/*
    int result = addItemToCart(&testItems[0],&testCart1);
    printf("result = %d\n",result);
    result = addItemToBag(&testItems[1],&testBag1);
    printf("result = %d\n",result);
  //  result = removeItemFromBag(&testItems[2],&testBag1);
//    printf("result = %d\n",result);
  //  result = removeItemFromBag(&testItems[1],&testBag1);
    //printf("result = %d\n",result);

    printGroceryItem(&testItems[11]);
    packCart(&testCart1);
    printBag(&testBag1,2);*/

    int randomNumber;
    srand(time(NULL));
    printf("before packing\n\n");
    for(int i = 1; i<=50; ++i){
      randomNumber = (rand()%GROCERY_COUNT);
      addItemToCart(&testItems[randomNumber],&testCart1);
    }
    printCart(&testCart1);
    printf("after packing\n\n");
    packCart(&testCart1);
    printCart(&testCart1);
    printf("after removing perish\n\n");
    removePerish(&testCart1);
    printCart(&testCart1);

    //free up dynamic memory
    //release memory for bags
    for(int i = 0; i<testCart1.numPackedBags ;++i){
      free(testCart1.packedBags[i]->listItems);
      free(testCart1.packedBags[i]);
    }
    free(testCart1.looseItems);
    free(testCart1.packedBags);
}



int addItemToCart(GroceryItem* gItemPtr, Cart* cartPtr){
  //checks if we have reached max number of items allowed in cart
  if(cartPtr->numLooseItems >= MAX_CART_ITEMS){
    return 0;
  }

  ++(cartPtr->numLooseItems);
  cartPtr->looseItems = realloc(cartPtr->looseItems,(sizeof(GroceryItem*))*(cartPtr->numLooseItems));
  if(cartPtr->looseItems == NULL){
    return 0;
  }else{
     cartPtr->looseItems[(cartPtr->numLooseItems)-1] = gItemPtr;
     return 1;
  }
}



int addItemToBag(GroceryItem* gItemPtr, Bag* bagPtr){
  ++(bagPtr->numItems);
  bagPtr->listItems = realloc(bagPtr->listItems,(sizeof(GroceryItem*))*(bagPtr->numItems));
  if(bagPtr->listItems == NULL){
    return 0;
  }else{
     bagPtr->listItems[(bagPtr->numItems)-1] = gItemPtr;
     bagPtr->totalWeight += gItemPtr->weight;
    // printf("total weight in addItemToBag() : %.3f",bagPtr->totalWeight);
     return 1;
  }
}



int removeItemFromBag(GroceryItem* gItemPtr, Bag* bagPtr){
  //search for pointer in the array of pointers
  int i = 0;
  //checks if index is less than number of items in bag and if we didnt find
  //the grocery item then increment by 1
  while((i < bagPtr->numItems)&&(bagPtr->listItems[i] != gItemPtr)){
    ++i;
  }

  //did we find pointer to grocery item?
  if(i >= bagPtr->numItems){
    return 0; //didnt find it so return false
  }

  //overwrite the item being deleted with item at end of list
  bagPtr->listItems[i] = bagPtr->listItems[(bagPtr->numItems)-1];

  //from this point similar to add item to bag, only we do the reverse
  --(bagPtr->numItems);
  bagPtr->listItems = realloc(bagPtr->listItems,(sizeof(GroceryItem*))*(bagPtr->numItems));
  bagPtr->totalWeight -= gItemPtr->weight;
  return 1;
}



void printGroceryItem(GroceryItem* gItemPtr){
  printf("%s",gItemPtr->name);
  printf(" weighing %.3fkg",gItemPtr->weight);
  printf(" with price $%.2f\n",gItemPtr->price);
}



void packCart(Cart* cartPtr){
  int index = 0;
  int bagNum = -1;
  float totalWeight = MAX_BAG_WEIGHT + 1.0; //this will force creation of first bag
  int countItems = MAX_BAG_ITEMS + 1; //this will also force creation of first bag

  //create initial dynamically alloceted array of bags
  cartPtr->packedBags = malloc(sizeof(Bag*)*MAX_BAGS);
  while(index < cartPtr->numLooseItems){
    if(cartPtr->looseItems[index]->weight <= MAX_BAG_WEIGHT){
      //are we starting to pack first bag?
      if((cartPtr->looseItems[index]->weight + totalWeight > MAX_BAG_WEIGHT)||
          countItems >= MAX_BAG_ITEMS){
        ++bagNum;
        totalWeight = 0.0;
        countItems = 0;
        cartPtr->packedBags[bagNum] = malloc(sizeof(Bag));
        cartPtr->packedBags[bagNum]->listItems = NULL;
        cartPtr->packedBags[bagNum]->numItems = 0;
        cartPtr->packedBags[bagNum]->totalWeight = 0.0;
      }
      //we have done necessary checks. safe to add item to bag
      int result = addItemToBag(cartPtr->looseItems[index], cartPtr->packedBags[bagNum]);
      if(result != 1){
        puts("ERROR - addItemToBag() returned 0 in packCart()");
      }

      totalWeight += cartPtr->looseItems[index]->weight;
      ++countItems;

      //for now remove loose item from cart by setting pointer to null
      //later we will remove null items
      cartPtr->looseItems[index] = NULL;
    }
    ++index;
  }

  //do some necessary cleanup
  //first we will pack loose items array
  index = 0;
  while(index < cartPtr->numLooseItems){
    if(cartPtr->looseItems[index] == NULL){
      for(int i = index; (i+1) < cartPtr->numLooseItems; i++){
        cartPtr->looseItems[i] = cartPtr->looseItems[i+1];
      }
      --cartPtr->numLooseItems;
    }else{
      ++index;
    }
  }
  cartPtr->looseItems = realloc(cartPtr->looseItems,(sizeof(GroceryItem*))*(cartPtr->numLooseItems));

  //resize packed bags array to correct size
  cartPtr->packedBags = realloc(cartPtr->packedBags,sizeof(Bag*)*(bagNum+1));
  cartPtr->numPackedBags = bagNum+1;
}



void printBag(Bag* bagPtr, int bagNum){
  //first find the heaviest item
  float heaviestItem = 0.0;
  for(int i = 0; i<bagPtr->numItems; ++i){
    if(bagPtr->listItems[i]->weight > heaviestItem){
      heaviestItem = bagPtr->listItems[i]->weight;
    }
  }

  //output total weight and bag number
  printf("BAG %d (Total Weight = %.3fkg)\n",bagNum,bagPtr->totalWeight);

  //loop through all of the items in the bag displaying them
  for(int i = 0; i<bagPtr->numItems; ++i){
    if(bagPtr->listItems[i]->weight == heaviestItem){
      printf("  *");
    }else{
      printf("   ");
    }
    printGroceryItem(bagPtr->listItems[i]);
  }
}



void printCart(Cart* cartPtr){
    for(int index = 0; index< cartPtr->numLooseItems; ++index){
      printGroceryItem(cartPtr->looseItems[index]);
    }

    puts("");
    for(int index = 0; index< cartPtr->numPackedBags; ++index){
      printBag(cartPtr->packedBags[index],index+1);
      puts("");
    }
}



void removePerish(Cart* cartPtr){
  for(int i = 0; i < cartPtr->numLooseItems; ++i){
    if(cartPtr->looseItems[i]->perish == 1){
      cartPtr->looseItems[i] = NULL; //set to null for now
    }
  }

  //pack looseItems array
  int index = 0;
  while(index < cartPtr->numLooseItems){
    if(cartPtr->looseItems[index] == NULL){
      for(int i = index; (i+1) < cartPtr->numLooseItems; i++){
        cartPtr->looseItems[i] = cartPtr->looseItems[i+1];
      }
      --cartPtr->numLooseItems;
    }else{
      ++index; // Only increment index if item was not NULL
    }
  }

//loop through every bag in the cart
  for(int bag = 0; bag<cartPtr->numPackedBags; ++bag){
    //loop through every item in a bag
    int item = 0;
    while (item < cartPtr->packedBags[bag]->numItems){
      if(cartPtr->packedBags[bag]->listItems[item]->perish == 1){
        int result = removeItemFromBag(cartPtr->packedBags[bag]->listItems[item],cartPtr->packedBags[bag]);
        if(result != 1){
          puts("ERROR-removeItemFromBag() returned 0 in the function removePerish()");
        }
      }
      else
      {
          ++item; // only increment if item was not deleted
      }
    }
  }
}
