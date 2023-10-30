#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void rotateMatrix(FILE * f) {
  int matrix[12][12] = {{0}};
  int c;
  int i = 0;
  int j = 0;

  while ((c=fgetc(f))!= EOF){
      matrix[i][j] = c;
      if (j>11)
      {
        fprintf(stderr, "A line with incorrect number of characters!\n");
        exit(EXIT_FAILURE);
      }
      j++;
    if (c == '\n')
    {
      if (j != 11)
      {
        fprintf(stderr, "A line with incorrect number of characters!\n");
        exit(EXIT_FAILURE);
      }
      matrix[i][j+1] = '\0';
      i++;
      j = 0; 
    }
  }
  //   if (isalpha(c) || c == ' ')
  //   {
  //     matrix[i][j] = c;
  //     if (j>9)
  //     {
  //       fprintf(stderr, "A line with incorrect number of characters!\n");
  //       exit(EXIT_FAILURE);
  //     }
  //     j++;
      
  //   }
  //   if (c == '\n')
  //   {
  //     matrix[i][j] = c;
  //     if (j != 10)
  //     {
  //       fprintf(stderr, "A line with incorrect number of characters!\n");
  //       exit(EXIT_FAILURE);
  //     }
  //     matrix[i][j+1] = '\0';
  //     i++;
  //     j = 0; 
  //   }
  //   else{        
  //     fprintf(stderr, "Should put in a char!\n");
  //     exit(EXIT_FAILURE);
  //   }
  // }

  if (!((i ==10) && (j==0)) ){
    fprintf(stderr, "Incorrect number of lines!\n");
    exit(EXIT_FAILURE);
  }

  for (int j = 0; j < 10; j++) {
    for (int i = 10-1; i >= 0; i--) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: incorect arg number");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open file");
    return EXIT_FAILURE;
  }
  rotateMatrix(f);
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}