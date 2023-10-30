#include "rand_story.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//step 1: parse the story template
//Read each line per time
//Devide current line into several pieces according to the blank needed to be filled
//store these pices in lines[]. if it is a blank surrounded by _, replace it
void freeLines(storyLines_t * storyLines) {
  for (size_t k = 0; k < storyLines->i; k++) {
    free(storyLines->lines[k]);
  }
  free(storyLines->lines);
  free(storyLines);
}

storyLines_t * readStory(void * f) {
  storyLines_t * storyLines = malloc(sizeof(*storyLines));
  storyLines->lines = NULL;  // to hold the whole story
  storyLines->i = 0;         //the size of lines
  char * line = NULL;        //the beginning of each line
  size_t sz;
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
          exit(EXIT_FAILURE);
        }
        storyLines->i = storyLines->i + 2;
        storyLines->lines = realloc(
            storyLines->lines,
            storyLines->i *
                sizeof(
                    *storyLines->lines));  //two parts: one before "_", one between "_"s
        storyLines->lines[j] = strndup(curr, (_left - curr));
        // printf("lines[%ld]:%s\n", j, lines[j]);
        j++;
        storyLines->lines[j] = strndup(_left, (_right - _left));
        // printf("lines[%ld]:%s\n", j, lines[j]);
        j++;
        curr = _right + 1;
      }
      else {
        storyLines->i = storyLines->i + 1;
        storyLines->lines =
            realloc(storyLines->lines, storyLines->i * sizeof(*storyLines->lines));
        storyLines->lines[j] = strndup(curr, (end - curr));
        // printf("lines[%ld]:%s\n", j, lines[j]);
        j++;
        curr = end;
      }
    }
  }
  free(line);
  // printf("i:%ld\n", i);
  return storyLines;
}

//step2: read the words

//read key and value; Decide if the key is in the arr;
//if yes, put the value into according category;
//if no, put the key into arr and put the values in category;

// to decide if a key is in catarray
int inarr(char * key, catarray_t * catarray) {
  for (int i = 0; i < catarray->n; i++) {
    if (!strcmp(key, catarray->arr[i].name)) {
      return i;
    }
  }
  return -1;
}

catarray_t * parseWords(void * f) {
  catarray_t * catarray = malloc(sizeof(*catarray));
  catarray->n = 0;
  catarray->arr = NULL;
  char * line = NULL;
  size_t sz;
  int i;

  while (getline(&line, &sz, f) >= 0) {
    //evaluate the format
    char * colon = strchr(line, ':');
    if (colon == line) {
      fprintf(stderr, "Add a key!\n");
      exit(EXIT_FAILURE);
    }
    char * newline = strchr(line, '\n');
    if (newline == colon + 1) {
      fprintf(stderr, "Add a value!\n");
      exit(EXIT_FAILURE);
    }
    char * key = strndup(line, (colon - line));
    char * value = strndup(colon + 1, (newline - colon - 1));
    if ((i = inarr(key, catarray)) != -1) {  //if key is already in the array
      catarray->arr[i].words =
          realloc(catarray->arr[i].words,
                  (catarray->arr[i].n_words + 1) * sizeof(*catarray->arr[i].words));
      catarray->arr[i].words[catarray->arr[i].n_words] = strndup(value, strlen(value));
      catarray->arr[i].n_words++;
    }
    else {
      catarray->arr = realloc(catarray->arr, (catarray->n + 1) * sizeof(*catarray->arr));
      catarray->arr[catarray->n].name = strndup(key, strlen(key));
      catarray->arr[catarray->n].words =
          malloc(sizeof(*catarray->arr[catarray->n].words));
      catarray->arr[catarray->n].words[0] = strndup(value, strlen(value));
      catarray->arr[catarray->n].n_words = 1;
      catarray->n++;
    }

    free(key);
    free(value);
  }
  free(line);
  return catarray;
}

void freecata(catarray_t * catarray) {
  for (size_t i = 0; i < catarray->n; i++) {
    free(catarray->arr[i].name);
    for (size_t j = 0; j < catarray->arr[i].n_words; j++) {
      free(catarray->arr[i].words[j]);
    }
    free(catarray->arr[i].words);
  }
  free(catarray->arr);
  free(catarray);
}

//step3: read the words

void writeStory(void * words, void * story) {
  // printf("hello");
  storyLines_t * storylines = readStory(story);
  catarray_t * catarray = parseWords(words);
  for (size_t k = 0; k < storylines->i; k++) {
    if (storylines->lines[k][0] == '_') {
      printf("%s", chooseWord(storylines->lines[k] + 1, catarray));
    }
    else {
      printf("%s", storylines->lines[k]);
    }
  }

  freeLines(storylines);
  freecata(catarray);
}

//step4: devide the story into several pieces.
//For each piece, decide if it is in the 'name'.
//For every blank being filled, stored the value in dic

void writeNewStory(void * words, void * story) {
  // printf("hello");
  storyLines_t * storylines = readStory(story);
  catarray_t * catarray = parseWords(words);
  char ** dic = NULL;  // words that has been printed out
  size_t n = 0;        // the num of dic
  for (size_t k = 0; k < storylines->i; k++) {
    // printf("lines[%ld]:%s\n", k, storylines->lines[k]);
    if (storylines->lines[k][0] == '_') {
      int isFound = 0;
      for (size_t i = 0; i < catarray->n; i++) {
        if (!strcmp(storylines->lines[k] + 1, catarray->arr[i].name)) {
          isFound = 1;
        }
      }
      if (isFound == 1) {
        dic = realloc(dic, (n + 1) * sizeof(*dic));
        dic[n] = (char *)chooseWord(storylines->lines[k] + 1, catarray);
        printf("%s", dic[n]);

        // for (size_t p = 0; p < n; p++) {
        //   printf("dic[%ld]:%s\n", p, dic[p]);
        // }

        n++;
      }
      else if (isFound == 0) {
        if ((atoi(storylines->lines[k] + 1) >= 1) &&
            ((atoi(storylines->lines[k] + 1) <= n))) {
          dic = realloc(dic, (n + 1) * sizeof(*dic));
          dic[n] = dic[(n - atoi(storylines->lines[k] + 1))];
          printf("%s", dic[n]);
          // for (size_t p = 0; p < n; p++) {
          //   printf("dic[%ld]:%s\n", p, dic[p]);
          // }
          n++;
        }
        else {
          fprintf(stderr, "Not a valid blank!\n");
          exit(EXIT_FAILURE);
        }
      }
    }
    else {
      printf("%s", storylines->lines[k]);
    }
  }
  free(dic);
  freeLines(storylines);
  freecata(catarray);
}
