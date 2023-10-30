#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"
#include "rand_story.h"

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "two input file!\n");
    return EXIT_FAILURE;
  }
  FILE * words = fopen(argv[1], "r");
  FILE * story = fopen(argv[2], "r");
  if ((words == NULL) || (story == NULL)) {
    fprintf(stderr, "Fail to open!\n");
    exit(EXIT_FAILURE);
  }
  writeNewStory(words, story);

  if (fclose(words) != 0) {
    perror("Fail to close!");
    return EXIT_FAILURE;
  }
  if (fclose(story) != 0) {
    perror("Fail to close!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
