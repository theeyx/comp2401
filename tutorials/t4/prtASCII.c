#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#define ASCIIMAX 127

int main()
{
    int A;
    char name[20] = "";
    printf("enter name\n");
    //scanf("%c",&name);
    scanf("%s",name);
    for(int i = 0; i < strlen(name);i++){
   // size_t length = strlen(name);
    //for(size_t i = 0; i<length; i++){
    A = name[i];
    printf("ASCII value of character is %d\n", A);
    }

    return 0;
}
