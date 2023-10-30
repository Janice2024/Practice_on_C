#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->arrayCounts = NULL;
  counts->size = 0;
  counts->unknownCount = 0;
  return counts;
}

void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknownCount++;
    return;
  }
  for (size_t i = 0; i < c->size; i++) {
    if (!strcmp(c->arrayCounts[i]->oneString, name)) {
      c->arrayCounts[i]->oneCount++;
      return;
    }
  }
  c->size++;
  c->arrayCounts = realloc(c->arrayCounts, c->size * sizeof(*c->arrayCounts));
  c->arrayCounts[c->size - 1] = malloc(sizeof(*c->arrayCounts[c->size - 1]));
  // c->arrayCounts[c->size-1]->oneString=name;
  // c->arrayCounts[c->size - 1]->oneString =
  //     malloc((strlen(name)+1)*sizeof(*c->arrayCounts[c->size - 1]->oneString));
  // strcpy(c->arrayCounts[c->size - 1]->oneString, name);
  c->arrayCounts[c->size - 1]->oneString = strdup(name);
  c->arrayCounts[c->size - 1]->oneCount = 1;
}

void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->size; i++) {
    fprintf(
        outFile, "%s: %ld\n", c->arrayCounts[i]->oneString, c->arrayCounts[i]->oneCount);
  }
  if (c->unknownCount != 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->unknownCount);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->size; i++) {
    free(c->arrayCounts[i]->oneString);
    free(c->arrayCounts[i]);
  }
  free(c->arrayCounts);
  free(c);
}
