#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "only one input file!\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Fail to open!\n");
    exit(EXIT_FAILURE);
  }
  catarray_t * catarray = NULL;
  storyLines_t * storylines = readStory(f);

  for (size_t k = 0; k < storylines->i; k++) {
    if (storylines->lines[k][0] == '_') {
      printf("%s", chooseWord(storylines->lines[k] + 1, catarray));
    }
    else {
      printf("%s", storylines->lines[k]);
    }
  }

  freeLines(storylines);

  if (fclose(f) != 0) {
    perror("Fail to close!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
