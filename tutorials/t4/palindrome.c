#include<stdio.h>
#include<string.h>

// This is a forward reference
int palindrome(char *s);

int main() {

  char word[30];


  printf ("Enter a word or \"q\" to stop: ");
  scanf ("%s", word);

  while (strcmp(word, "q") != 0) {
    palindrome(word);
    printf ("Enter a word or \"q\" to stop: ");
    scanf ("%s", word);
  };

  return 0;

}

int palindrome(char *s)
{

  int l = 0;
    int h = strlen(word) - 1;

    // Keep comparing characters while they are same
    while (h > l)
    {
        if (word[l++] != word[h--])
        {
            printf("%s is Not Palindrome", word);
            return;
        }
    }
    printf("%s is palindrome", word);

}
