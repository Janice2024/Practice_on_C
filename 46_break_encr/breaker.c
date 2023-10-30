#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int max_index(int * array, int size){    
    int index = 0;
    for (int i = 0; i < (size-1); i++)
    {
        if (array[index]<array[i+1])
        {
            index = i+1;
        }
        
    }
    return index;
}


void breaker(FILE * f){
  int c;
  int key;
  int alphs[26] = {0};
  int max;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      alphs[c-'a'] += 1;
    }
  }
  max = max_index(alphs,26);
  if (max >= 4) {
    key = max - 4;
  }
  else {
    key = 26 - 4 + max;
  }
  printf("%d\n",key);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr,"Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  breaker(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}