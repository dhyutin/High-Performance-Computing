#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "omp.h"

int main(){
    
    int n;
    scanf("%d", &n);
    
    double v1[n], v2[n], ans[n];
    
    for(int i = 0; i < n; i++){
        v1[i] = (float)rand()/(float)(RAND_MAX/n);
        v2[i] = (float)rand()/(float)(RAND_MAX/n);
    }

    for(int i = 0; i < n; i++){
        ans[i] = 0;
    }
    
     for(int i = 0; i < n; i++){
        ans[i] = v1[i] + v2[i];
     }
     
     printf("Serial Program Successfully Executed\n");
        
    return 0;
}
