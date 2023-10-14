#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "omp.h"

int main(){
    
    int n;
    scanf("%d", &n);
    
    double v1[n], v2[n], v3[n], v4[n], v5[n], ans[n];
    
    for(int i = 0; i < n; i++){
        v1[i] = (float)rand()/(float)(RAND_MAX/n);
        v2[i] = (float)rand()/(float)(RAND_MAX/n);
        v3[i] = (float)rand()/(float)(RAND_MAX/n);
        v4[i] = (float)rand()/(float)(RAND_MAX/n);
        v5[i] = (float)rand()/(float)(RAND_MAX/n);
    }

    for(int i = 0; i < n; i++){
        ans[i] = 0;
    }
     double wallclock_initial = omp_get_wtime();
     #pragma omp parallel
     {int id = omp_get_thread_num();
     //printf("Thread No - %d\n", id);
     #pragma omp for
     for(int i = 0; i < n; i++){
        ans[i] = v1[i] * v2[i] * v3[i] * v4[i] * v5[i];
        //printf("%lf ", ans[i]);
     }
     //printf("\n");
     }
     double wallclock_final = omp_get_wtime();
     
     /*
     double wc_i = omp_get_wtime();
     for(int i = 0; i < n; i++){
        ans[i] = v1[i] + v2[i];
        printf("%lf ", ans[i]);
     }
     double wc_f = omp_get_wtime();
     */
     
     //printf("\n");
     printf("Time : %lf\n", wallclock_final - wallclock_initial);
     
        
    return 0;
}
