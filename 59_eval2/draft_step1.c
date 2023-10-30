#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rand_story.h"

//step 1: parse the story template
//Read each line per time
//Devide current line into several pieces according to the blank needed to be filled
//store these pices in lines[]. if it is a blank surrounded by _, replace it
void readStory(void * f) {
  char ** lines = NULL;  // to hold the whole story
  char * line = NULL;    //the beginning of each line
  size_t sz;
  size_t i = 0;  //the size of lines
  size_t j = 0;  //where to put a new entry in lines

  while (getline(&line, &sz, f) >= 0) {
    char * curr = line;
    char * end = strchr(curr, '\0');
    while (end > curr) {  //reading the line when it is not over
                          // printf("hhh");
      char * _left = strchr(curr, '_');
      if (_left != NULL) {
        char * _right = strchr(_left + 1, '_');
        if (_right == NULL) {
          fprintf(stderr, "No right _ !\n");
        }
        i = i + 2;
        lines =
            realloc(lines,
                    i * sizeof(*lines));  //two parts: one before "_", one between "_"s
        lines[j] = strndup(curr, (_left - curr));
        // printf("lines[%ld]:%s\n", j, lines[j]);
        j++;
        lines[j] = strndup(_left, (_right - _left));
        // printf("lines[%ld]:%s\n", j, lines[j]);
        j++;
        curr = _right + 1;
      }
      else {
        i = i + 1;
        lines = realloc(lines, i * sizeof(*lines));
        lines[j] = strndup(curr, (end - curr));
        // printf("lines[%ld]:%s\n", j, lines[j]);
        j++;
        curr = end;
      }
    }
  }
  free(line);
  // printf("i:%ld\n", i);
  for (size_t k = 0; k < i; k++) {
    if (lines[k][0] == '_') {
      printf("%s", chooseWord(lines[1] + 1, NULL));
    }
    else {
      printf("%s", lines[k]);
    }
    free(lines[k]);
  }
  free(lines);
}
