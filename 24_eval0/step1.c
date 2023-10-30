#include <stdlib.h>
#include <stdio.h>

//This file is for Step 1.
//You should do 
//  Step 1 (A): write seq1

int seq1 (int x){
    int y = 3*x-5;
    return y;
}

void print_seq1_range(int low, int high);
//  Step 1 (B): write main to test seq1

int main(){
    printf("seq1(%d) = %d\n",0, seq1(0));
    printf("seq1(%d) = %d\n",1, seq1(1));
    printf("seq1(%d) = %d\n",20, seq1(20));
    printf("seq1(%d) = %d\n",-10, seq1(-10));
    printf("seq1(%d) = %d\n",100, seq1(100));
    printf("seq1(%d) = %d\n",1000, seq1(1000));

    printf("print_seq1_range(%d, %d)\n",0, 0);
    print_seq1_range(0, 0);
    printf("print_seq1_range(%d, %d)\n",0, 1);
    print_seq1_range(0, 1);
    printf("print_seq1_range(%d, %d)\n",0, 2);
    print_seq1_range(0, 2);
    printf("print_seq1_range(%d, %d)\n",-3, 5);
    print_seq1_range(-3, 5);
    printf("print_seq1_range(%d, %d)\n",-10, 10);
    print_seq1_range(-10, 10);
    printf("print_seq1_range(%d, %d)\n",-100, 100);
    print_seq1_range(-100, 100);
}

//  Step 1 (C): write print_seq1_range

void print_seq1_range(int low, int high){
    for (int i = low; i < (high-1); i++)
    {
        printf("%d,",seq1(i));
    }
    if (low<=(high-1))
    {
        printf("%d",seq1(high-1));
    }
    printf("\n");
}

//  Step 1 (D): add test cases to main to test print_seq1_range

// Be sure to #include any header files you need!
