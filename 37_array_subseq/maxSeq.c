#include <stdio.h>
#include <stdlib.h>
 
 size_t  maxSeq(int * array, size_t n){
    int max = 1;
    if (n == 0)
    {
       max = 0;
    }
    int incre_num = 1;
    for (int i = 0; i < n; i++)
    {
        if (array[i]<array[i+1])
        {
            incre_num++;
        }
        else{
            if (incre_num>max)
            {
                max = incre_num;
            }
            incre_num = 1; 
        }
    }
    return max;
 }