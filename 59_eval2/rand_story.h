#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include "provided.h"

//any functions you want your main to use

typedef struct storyLines {
  char ** lines;
  size_t i;
} storyLines_t;
storyLines_t * readStory(void * f);

void freeLines(storyLines_t * storyLines);

catarray_t * parseWords(void * f);
void freecata(catarray_t * catarray);
int inarr(char * kay, catarray_t * catarray);  // to decide if a key is in catarray

void writeStory(void * words, void * story);
void writeNewStory(void * words, void * story);

#endif
