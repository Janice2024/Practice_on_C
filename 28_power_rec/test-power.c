#include <stdlib.h>
#include <stdio.h>

unsigned power (unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans){
    unsigned power_ans = power(x, y);
    if(power_ans == expected_ans){
    }
    else{
        exit(EXIT_FAILURE);
        printf("!!!");
    }

}

int main(){
    run_check(0,0,1);
    // run_check('a','b','c');
    // run_check(-1,0,1);
    run_check(2,0,1);
    run_check(2,1,2);
    run_check(2,2,4);
    run_check(1000, 3, 1000000000);
    exit(EXIT_SUCCESS);

}