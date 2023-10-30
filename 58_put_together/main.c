#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  counts_t * counts = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "No such a file\n");
    return NULL;
  }
  char * line = NULL;
  size_t sz = 0;

  while ((getline(&line, &sz, f)) >= 0) {
    char * key = malloc((strlen(line)) * sizeof(*key));
    strncpy(key, line, (strlen(line) - 1));
    // char * p = strchr(line, '\n');
    // size_t len = p - line;
    // char * key = malloc((len + 1) * sizeof(*key));
    // strncpy(key, line, p - line);
    // printf("len:%ld, strlen:%ld \n", len, strlen(line));
    key[(strlen(line) - 1)] = '\0';
    // key[len] = '\0';
    addCount(counts, lookupValue(kvPairs, key));
    free(key);
  }
  free(line);
  if (fclose(f) != 0) {
    fprintf(stderr, "Fail to close!");
  }
  return counts;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 2) {
    fprintf(stderr, "More than 2 files!\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    if (f != NULL) {
      printCounts(c, f);
    }
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Fail to close!");
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
