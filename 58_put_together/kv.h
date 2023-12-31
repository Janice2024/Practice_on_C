#ifndef __KV_H__
#define __KV_H__
#include <stdlib.h>

struct _kvpair_t {
  char key[40];
  char value[40];
  // char * key;
  // char * value;
};
typedef struct _kvpair_t kvpair_t;

struct _kvarray_t {
  kvpair_t ** kvpair;
  size_t size;
};
typedef struct _kvarray_t kvarray_t;

kvarray_t * readKVs(const char * fname);

void freeKVs(kvarray_t * pairs);

void printKVs(kvarray_t * pairs);

char * lookupValue(kvarray_t * pairs, const char * key);

#endif
