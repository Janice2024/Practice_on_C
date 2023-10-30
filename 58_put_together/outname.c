#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  char * suffix = ".counts";
  int outputLength = strlen(inputName) + strlen(suffix) + 1;
  char * outputName = malloc(outputLength * sizeof(*outputName));
  strcpy(outputName, inputName);
  strcat(outputName, suffix);
  return outputName;
}
