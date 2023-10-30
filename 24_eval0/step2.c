#include <stdlib.h>
#include <stdio.h>

//This file is for Step 2.
//You should do 
//  Step 2 (A): write seq2
int seq2 (int x){
    int y;
    if (x>=2)
    {
        y=(x-2)*(x-2)-2;
    }
    else{
        y=(2-x)*(2-x)-2;
    }
    return y;
}
int sum_seq2(int low, int high);
//  Step 2 (B): write main to test seq2
int main(){
    printf("seq2(%d) = %d\n",-100,seq2(-100));
    printf("seq2(%d) = %d\n",-10,seq2(-10));
    printf("seq2(%d) = %d\n",-3,seq2(-3));
    printf("seq2(%d) = %d\n",0,seq2(0));
    printf("seq2(%d) = %d\n",1,seq2(1));
    printf("seq2(%d) = %d\n",20,seq2(20));
    printf("sum_seq2(%d, %d) = %d\n",0,1,sum_seq2(0,1));
    printf("sum_seq2(%d, %d) = %d\n",0,2,sum_seq2(0,2));
    printf("sum_seq2(%d, %d) = %d\n",3,6,sum_seq2(3,6));
    printf("sum_seq2(%d, %d) = %d\n",-10,10,sum_seq2(-10,10));
    printf("sum_seq2(%d, %d) = %d\n",9,7,sum_seq2(9,7));
}


//  Step 2 (C): write sum_seq2
int sum_seq2(int low, int high){
    int sum=0;
    for (int i=low;i<high;i++){
        sum += seq2(i);
    }
    return sum;
}

//  Step 2 (D): add test cases to main to test sum_seq2
// 
// Be sure to #include any header files you need!

