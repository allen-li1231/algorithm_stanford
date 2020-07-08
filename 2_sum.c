#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

long container[1000000] = {0};

void readFile(){
    FILE *pf = fopen("./algo1-programming_prob-2sum.txt", "r");
    char buff[30] = {0};
    int i = 0;
    while (!feof(pf)){
        fgets(buff, 30, pf);
        container[i] = atol(buff);
        i++;
    }
}



int main(){
    readFile();
    int ans = 0;
   hash_table *H = newHash(NULL, NULL, 317);
   for (int i=0; i<1000000; i++){
       addHash(H, container[i]);
   }

    for (long t=-10000; t<=10000; t++){
        for (int i=0; i<1000000; i++){
            if (lookupHash(H, t-container[i])){
                ans++;
                break;
            }
        }
    }
    printf("ans: %d\n", ans);
    free(H);
}
