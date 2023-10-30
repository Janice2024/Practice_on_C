#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

 void test_maxSeq(int * array, size_t n, size_t expected_ans) {
  if (expected_ans != maxSeq(array, n)) {
    printf("Find an error!");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int a0[] = {5, 4, 3, 2, 1};
  int a1[] = {1, 2, 3, 4, 5};
  int a2[] = {1, 3, 2, 4, 5};
  int a3[] = {1, 1 ,1, 0, 0};
  int a4[] = {0};
  int a5[] = {};
  int a6[] = {0,0,0,0,0,0,0};
  int a7[] = {1,-4,9,-4,5};
  int a8[] = {1, 2 , 3, -4, 4, 4};
  int a9[] = {4, 4, -4, 1, 2 , 3};
  

  test_maxSeq(a0, 5, 1);
  test_maxSeq(a1, 5, 5);
  test_maxSeq(a2, 5, 3);
  test_maxSeq(a3, 5, 1);
  test_maxSeq(a4, 1, 1);
  test_maxSeq(a5, 0, 0);
  test_maxSeq(a6, 7, 1);
  test_maxSeq(a7, 5, 2);
  test_maxSeq(a8, 6, 3);
  test_maxSeq(a9, 6, 4);
  printf("Pass!");
  exit(EXIT_SUCCESS);
}