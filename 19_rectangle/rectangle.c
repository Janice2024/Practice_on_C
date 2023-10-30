#include <stdio.h>
#include <stdlib.h>

// I've provided "min" and "max" functions in case they are useful to you
int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

// Declare your rectangle_t struct here!

typedef struct{
  int x;
  int y;
  int width;
  int height;
} rectangle_t;



rectangle_t canonicalize(rectangle_t r) {
  if(r.width < 0){
    r.x = r.x + r.width;
    r.width = -r.width;
  }
  if(r.height < 0){
    r.y = r.y + r.height;
    r.height = -r.height;
  }
  return r;
}

rectangle_t intersection(rectangle_t r1, rectangle_t r2) {
  rectangle_t r3;
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);
  int x_max = max(r1.x, r2.x);
  int y_max = max(r1.y, r2.y);
  r3.x = x_max;
  r3.y = y_max;

  int x_min_width; //to determine if they are overlapping
  int y_min_height;
  int x_max_width; //to determine if they are overlapping
  int y_max_height;
  int x_min = min(r1.x, r2.x);
  int y_min = min(r1.y, r2.y);

  if (x_min == r1.x){
    x_min_width = r1.width;
    x_max_width = r2.width;
  }
  else{
    x_min_width = r2.width;
    x_max_width = r1.width;
  }
  if (y_min == r1.y){
    y_min_height = r1.height;
    y_max_height = r2.height;
  }
  else{
    y_min_height = r2.height;
    y_max_height = r1.height;
  }
  if (((x_min + x_min_width - x_max) < 0) | ((y_min+y_min_height - y_max)<0)){
    r3.width=0;
    r3.height=0;
  }
  else if((x_max+x_max_width<x_min+x_min_width)&&(y_max+y_max_height < y_min+y_min_height)){
    r3.width=x_max_width;
    r3.height=y_max_height;
  }

  else{
    r3.width = (x_min+x_min_width - x_max);
    r3.height = (y_min+y_min_height - y_max);
  }

  // r3.width = max(0, (x_min+key_width - x_max));
  // r3.height = max (0, (y_min+key_height - y_max)); 
  return r3;
}

// You should not need to modify any code below this line
void printRectangle(rectangle_t r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d, %d) to (%d, %d)\n", r.x, r.y, r.x + r.width, r.y + r.height);
  }
}

int main(void) {
  rectangle_t r1;
  rectangle_t r2;
  rectangle_t r3;
  rectangle_t r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);

  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  // test everything with r1
  rectangle_t i = intersection(r1, r1);
  printf("intersection(r1, r1): ");
  printRectangle(i);

  i = intersection(r1, r2);
  printf("intersection(r1, r2): ");
  printRectangle(i);

  i = intersection(r1, r3);
  printf("intersection(r1, r3): ");
  printRectangle(i);

  i = intersection(r1, r4);
  printf("intersection(r1, r4): ");
  printRectangle(i);

  // test everything with r2
  i = intersection(r2, r1);
  printf("intersection(r2, r1): ");
  printRectangle(i);

  i = intersection(r2, r2);
  printf("intersection(r2, r2): ");
  printRectangle(i);

  i = intersection(r2, r3);
  printf("intersection(r2, r3): ");
  printRectangle(i);

  i = intersection(r2, r4);
  printf("intersection(r2, r4): ");
  printRectangle(i);

  // test everything with r3
  i = intersection(r3, r1);
  printf("intersection(r3, r1): ");
  printRectangle(i);

  i = intersection(r3, r2);
  printf("intersection(r3, r2): ");
  printRectangle(i);

  i = intersection(r3, r3);
  printf("intersection(r3, r3): ");
  printRectangle(i);

  i = intersection(r3, r4);
  printf("intersection(r3, r4): ");
  printRectangle(i);

  // test everything with r4
  i = intersection(r4, r1);
  printf("intersection(r4, r1): ");
  printRectangle(i);

  i = intersection(r4, r2);
  printf("intersection(r4, r2): ");
  printRectangle(i);

  i = intersection(r4, r3);
  printf("intersection(r4, r3): ");
  printRectangle(i);

  i = intersection(r4, r4);
  printf("intersection(r4, r4): ");
  printRectangle(i);

  return EXIT_SUCCESS;
}
