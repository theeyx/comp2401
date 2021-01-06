// tw4.cpp : correct the errors/warning in the file.




#include "stdio.h"

int fun(int x)
{
    if (x > 5) {
        x++;
        return(x);
    }
    return 0;
}

int main(int argc, char* argv[])
{
 int x=12;

 printf("fun(%d) =%d\n",x,fun(x));

 return 0;
}
