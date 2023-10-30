#include <stdlib.h>
#include <stdio.h>

//This file is for Step 3.
//You should do 
//  Step 3 (A): write seq3
int seq3(int x, int y){
    return (y+4)*(x-1)+3;
}

//  Step 3 (B): write main to test seq3
int count_neg_seq3_range(int xLow, int xHi, int yLow, int yHi);
int main(){
    printf("seq3(%d, %d) = %d\n",-10,-10,seq3(-10,-10));
    printf("seq3(%d, %d) = %d\n",-7,-7,seq3(-7,-7));
    printf("seq3(%d, %d) = %d\n",-5,-5,seq3(-5,-5));
    printf("seq3(%d, %d) = %d\n",-10,10,seq3(-10,10));
    printf("seq3(%d, %d) = %d\n",-7,7,seq3(-7,7));
    printf("seq3(%d, %d) = %d\n",-5,5,seq3(-5,5));
    printf("seq3(%d, %d) = %d\n",10,-10,seq3(10,-10));
    printf("seq3(%d, %d) = %d\n",7,-7,seq3(7,-7));
    printf("seq3(%d, %d) = %d\n",5,-5,seq3(5,-5));
    printf("seq3(%d, %d) = %d\n",0,4,seq3(0,4));
    printf("seq3(%d, %d) = %d\n",5,0,seq3(5,0));
    printf("seq3(%d, %d) = %d\n",0,0,seq3(0,0));
    printf("seq3(%d, %d) = %d\n",3,1,seq3(3,1));
    printf("seq3(%d, %d) = %d\n",2,7,seq3(2,7));
    printf("seq3(%d, %d) = %d\n",5,5,seq3(5,5));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",1,0,0,3, count_neg_seq3_range(1, 0, 0, 3));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",0,0,0,3, count_neg_seq3_range(0, 0, 0, 3));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",0,2,3,0, count_neg_seq3_range(0, 2, 3, 0));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",0,2,0,3, count_neg_seq3_range(0, 2, 0, 3));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",-3,2,-4,3, count_neg_seq3_range(-3, 2, -4, 3));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",0,3,0,3, count_neg_seq3_range(0, 3, 0, 3));

     printf("seq3(%d, %d) = %d\n",-10,-10,seq3(-9,-9));
    printf("seq3(%d, %d) = %d\n",-6,-6,seq3(-6,-6));
    printf("seq3(%d, %d) = %d\n",-4,-4,seq3(-4,-4));
    printf("seq3(%d, %d) = %d\n",-9,9,seq3(-9,9));
    printf("seq3(%d, %d) = %d\n",-6,6,seq3(-6,6));
    printf("seq3(%d, %d) = %d\n",-4,4,seq3(-4,4));
    printf("seq3(%d, %d) = %d\n",9,-9,seq3(9,-9));
    printf("seq3(%d, %d) = %d\n",6,-6,seq3(6,-6));
    printf("seq3(%d, %d) = %d\n",4,-4,seq3(4,-4));
    printf("seq3(%d, %d) = %d\n",1,5,seq3(1,5));
    printf("seq3(%d, %d) = %d\n",6,0,seq3(6,0));
    printf("seq3(%d, %d) = %d\n",0,0,seq3(0,0));
    printf("seq3(%d, %d) = %d\n",4,2,seq3(4,2));
    printf("seq3(%d, %d) = %d\n",3,8,seq3(3,8));
    printf("seq3(%d, %d) = %d\n",6,6,seq3(6,6));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",2,1,1,4, count_neg_seq3_range(2, 1, 1, 4));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",1,1,1,4, count_neg_seq3_range(1, 1, 1, 4));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",1,3,4,1, count_neg_seq3_range(1, 3, 4, 1));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",1,3,1,4, count_neg_seq3_range(1, 3, 1, 4));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",-2,3,-3,4, count_neg_seq3_range(-2, 3, -3, 4));
    printf("count_neg_seq3_range(%d, %d, %d, %d) = %d\n",1,4,1,4, count_neg_seq3_range(1, 4, 1, 4));
}

//  Step 3 (C): write count_neg_seq3_range
int count_neg_seq3_range(int xLow, int xHi, int yLow, int yHi){
    int neg_num=0;
    for (int i = xLow; i < xHi; i++)
    {
        for (int j = yLow; j < yHi; j++)
        {
            if(seq3(i,j)<0){
                neg_num++;
            }
        }
        
    }
    return neg_num;
}

//  Step 3 (D): add test cases to main to test count_neg_seq3_range
// 
// Be sure to #include any header files you need!

