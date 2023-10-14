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

     for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            ans[i][j] = v1[i][j] + v2[i][j];
        }
     }
     printf("Successfully Executed Serial Code\n");
         
    return 0;
}
