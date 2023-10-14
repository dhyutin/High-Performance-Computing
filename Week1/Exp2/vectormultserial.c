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

     for(int i = 0; i < n; i++){
        ans[i] = v1[i] * v2[i] * v3[i] * v4[i] * v5[i];
     }
     printf("Successfully Executed Serial Program\n");    
    return 0;
}
