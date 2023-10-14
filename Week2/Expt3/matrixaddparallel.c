#include <stdio.h>
#include <stdlib.h>
#include "omp.h"

int main(){
    
    int n;
    scanf("%d", &n);
    
    double v1[n][n], v2[n][n], ans[n][n];
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            v1[i][j] = (float)rand()/(float)(RAND_MAX/n);
            v2[i][j] = (float)rand()/(float)(RAND_MAX/n);
            ans[i][j] = 0;
        }

    }

     double wallclock_initial = omp_get_wtime();
     #pragma omp parallel
     {
         int id = omp_get_thread_num();
         //printf("Thread No - %d\n", id);
         #pragma omp for collapse(2)
         for(int i = 0; i < n; i++){
            // #pragma omp for
            for(int j = 0; j < n; j++){
                ans[i][j] = v1[i][j] + v2[i][j];
            }
         }
     }
     double wallclock_final = omp_get_wtime();
     

     printf("Time : %lf\n", wallclock_final - wallclock_initial);
     
        
    return 0;
}
