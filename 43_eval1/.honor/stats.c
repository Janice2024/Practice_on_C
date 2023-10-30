#include "stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
// any other headers you need here

player_t parseLine(char * line) {
  // STEP 1: write me
  player_t answer;
  if ((line == NULL) || (strlen(line) == 0))
  {
    fprintf(stderr, "Empty Line!\n");
    exit(EXIT_FAILURE);
  }
  char * firstColon = strchr(line,':');
  char * secondColon = strrchr(line,':');
  char * terminator = strrchr(line,'\0');
  if ((firstColon == NULL) || (secondColon == NULL))
  {
    fprintf(stderr, "No Colon!\n");
    exit(EXIT_FAILURE);
  }
  int nameLength = secondColon - firstColon;
  if (nameLength == 0)
  {
    fprintf(stderr, "Add a name!\n");
    exit(EXIT_FAILURE);
  }
  int numberLength = terminator - secondColon;
  if (numberLength == 0)
  {
    fprintf(stderr, "Add a number!\n");
    exit(EXIT_FAILURE);
  }
  // strncpy(answer.name, line, nameLength);
  // char num_in_char[5];
  // answer.number= atoi(strncpy(num_in_char, (firstColon + 1), numberLength));

  // if (*(secondColon+1) == 'G')
  // {
  //   answer.position = GUARD;
  // }
  // else if (*(secondColon+1) == 'C')
  // {
  //   answer.position = CENTER;
  // }
  // else{
  //   answer.position = FORWARD;
  // }
  // strcpy(answer.name, 'John');
  answer.number = 10;
  answer.position = FORWARD;
  answer.games = 0;
  answer.points = 0;
  answer.rebounds = 0;
  return answer;
}

void addGame(player_t * roster,
             size_t n_players,
             unsigned number,
             unsigned rebounds,
             unsigned points) {
  // STEP 2: write me
}

void printDoubleDouble(player_t * roster, size_t n_players) {
  // STEP 3: write me
}

void printPosPoints(player_t * roster, size_t n_players) {
  // STEP 4: write me
}
