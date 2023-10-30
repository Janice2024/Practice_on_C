#include <stdlib.h>
#include <stdio.h>

struct _retire_info_t{
    int months;
    double contribution;
    double rate_of_return;
};

typedef struct _retire_info_t retire_info_t;


double initialAmount(double initial, double rate_of_return, double contribution){
  initial = initial * rate_of_return + contribution;
  return initial;
}

void retirement (int startAge,   // in months
                       double initial, // initial savings in dollars
                       retire_info_t working, // info about working
                       retire_info_t retired){ // info about being retired

                       for (int i = startAge; i < (startAge + retired.months + working.months); i++) {
                        printf("Age %3d month %2d you have $%.2lf\n", i / 12, i % 12, initial);
                        if (i < (startAge + working.months)) {
                            initial += initialAmount(initial, working.rate_of_return, working.contribution);
                            }
                        else {
                            initial += initialAmount(initial, retired.rate_of_return, retired.contribution);
                                }
                        }
}

int main(void) {
  retire_info_t working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045 / 12;
  retire_info_t retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01 / 12;
  retirement(327, 21345, working, retired);
  return 0;
}