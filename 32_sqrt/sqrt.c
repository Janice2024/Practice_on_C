#include <stdio.h>
#include <stdlib.h>

int square_root(int x, int * perfect) {
  if (x<0)
  {
    * perfect = 0;
    return -1;
  }
  else{
    for (long i = 0; i < x+1; i++)
    {
      if (x == (i*i))
      {
        * perfect = 1;
        return i;
      }
      else if ((i*i<x) && ((i+1)*(i+1)>x))
      {
        * perfect = 0;
        return i;
      }
    }

  }
  

  return 0;
}

/* helper function to call square_root and print whether the input is a 
   perfect square or not */
void test_one(int x) {
  int perfect;
  int rt = square_root(x, &perfect);
  if (perfect) {
    printf("sqrt(%d) is %d, perfect square\n", x, rt);
  }
  else {
    printf("sqrt(%d) is %d, NOT perfect square\n", x, rt);
  }
}

int main(void) {
  test_one(4);
  test_one(5);
  test_one(0);
  test_one(-1);
  test_one(-4);
  // test with the largest int that does not cause any operation in
  // square_root to overflow
  test_one(2147395600);
  // test with the one less than the largest int that does not cause
  // any operation in square_root to overflow
  test_one(2147395599);
  return EXIT_SUCCESS;
}
