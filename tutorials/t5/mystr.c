#include "mystr.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

int myStrCmp(char *s1, char *s2)
{
// recursion condition
// if (s1 is not empty and s2 is not empty and the characters pointed to by s1 and s2 are the
 // same) then recurse by advancing s1 and s2 to point to the next character
if (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
return(myStrCmp(++s1, ++s2));
}
// one of the strings may be empty or they contain different characters
// return -1 if *s1 precedes *s2 in the lexicographic order
if (*s1 < *s2) return(-1);
else return (*s1 > *s2);
}
