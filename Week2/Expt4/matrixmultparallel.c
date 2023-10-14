#include <stdio.h>
#include <math.h>
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
         #pragma omp for collapse(3)
         for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                
                for(int k = 0; k < n; k++){
                    ans[i][j] += v1[i][k]*v2[k][j];
                }
            }
         }
     }
     double wallclock_final = omp_get_wtime();
     

     printf("Time : %lf\n", wallclock_final - wallclock_initial);
     
        
    return 0;
}
