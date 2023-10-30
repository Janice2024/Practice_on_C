#include "stats.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// any other headers you need here

/*
Step 1: here I divide the input into three parts based on the colons.
Name is the part of string before the first colon.
Number is between the first colon and second colon.
Position is a specified character after the second colon.
*/

player_t parseLine(char * line) {
  player_t answer;
  if ((line == NULL) || (strlen(line) == 0)) {
    fprintf(stderr, "Empty Line!\n");
    exit(EXIT_FAILURE);
  }
  char * firstColon = strchr(line, ':');
  char * secondColon = strrchr(line, ':');
  // char * terminator = strrchr(line,'\0');
  if ((firstColon == NULL) || (secondColon == NULL)) {
    fprintf(stderr, "No Colon!\n");
    exit(EXIT_FAILURE);
  }
  int nameLength = firstColon - line;
  if (nameLength == 0) {
    fprintf(stderr, "Add a name!\n");
    exit(EXIT_FAILURE);
  }
  if (nameLength > 64) {
    fprintf(stderr, "Name should be shorter than 64 characters!\n");
    exit(EXIT_FAILURE);
  }

  int numberLength = secondColon - firstColon;
  if (numberLength == 0) {
    fprintf(stderr, "Add a number!\n");
    exit(EXIT_FAILURE);
  }
  strncpy(answer.name, line, nameLength);
  answer.name[nameLength] = '\0';
  char num_in_char[5];
  answer.number = atoi(strncpy(num_in_char, (firstColon + 1), numberLength));

  if (*(secondColon + 1) == 'G') {
    answer.position = GUARD;
  }
  else if (*(secondColon + 1) == 'C') {
    answer.position = CENTER;
  }
  else if (*(secondColon + 1) == 'F') {
    answer.position = FORWARD;
  }
  else {
    fprintf(stderr, "Put in a correct location!\n");
    exit(EXIT_FAILURE);
  }
  answer.games = 0;
  answer.points = 0;
  answer.rebounds = 0;
  return answer;
}

/*
Step 2: here I find the specific player according to the given number.
Change fields of the player. If there is no such a person, put an error.
*/
void addGame(player_t * roster,
             size_t n_players,
             unsigned number,
             unsigned rebounds,
             unsigned points) {
  if (roster == NULL) {
    fprintf(stderr, "Put in a valid roster!\n");
    exit(EXIT_FAILURE);
  }
  player_t * target;
  for (int i = 0; i < n_players; i++) {
    if (roster[i].number == number) {
      target = (roster + i);
      break;
    }
  }
  if (target == NULL) {
    fprintf(stderr, "Not in the roster!\n");
    exit(EXIT_FAILURE);
  }
  target->rebounds += rebounds;
  target->points += points;
  target->games++;
}

/*
Step 3: here I find suitable players based on his or her fields.
*/
void printDoubleDouble(player_t * roster, size_t n_players) {
  if (roster == NULL) {
    fprintf(stderr, "Put in a valid roster!\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < n_players; i++) {
    if ((roster[i].rebounds >= 10) && (roster[i].points >= 10)) {
      printf("%s\n", roster[i].name);
    }
  }
}

/*
Step 4: Here we want to find the position with the most points.
I create two arrays: one records the points, and the other records the location.
These are linked by index.
*/

int findMaxIndex(int * arr, int size) {
  int max = arr[0];
  int index = 0;
  for (int i = 1; i < size; i++) {
    if (max < arr[i]) {
      max = arr[i];
      index = i;
    }
  }
  return index;
}

void printPosPoints(player_t * roster, size_t n_players) {
  if (roster == NULL) {
    fprintf(stderr, "Put in a valid roster!\n");
    exit(EXIT_FAILURE);
  }
  int max_index;  //The index of the positions with the highest points
  int points[3] = {0};
  const char * positions[] = {"Centers", "Forwards", "Guards"};
  for (int i = 0; i < n_players; i++) {
    if (roster[i].position == CENTER) {
      points[0] += roster[i].points;
    }
    else if (roster[i].position == FORWARD) {
      points[1] += roster[i].points;
    }
    else {
      points[2] += roster[i].points;
    }
  }
  max_index = findMaxIndex(points, 3);
  printf(
      "%s had the most points with %d points\n", positions[max_index], points[max_index]);
}
