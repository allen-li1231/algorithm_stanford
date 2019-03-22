#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int choose_pivot(int *array, int left_idx, int right_idx) {
    return left_idx;
}


void readFile(int *container){
    FILE *fp =  NULL;
    char buff[7] = {0};
    fp = fopen("IntegerArray.txt", "r");

    int i=0;
    while (!feof(fp)){
        fgets(buff, 7, fp);
        if (buff[0] != '\n') container[i++] = atoi(buff);
    }
    fclose(fp);
}


int sortAndPartition(int *num_ary, int left_idx, int right_idx){//, int left, int right){
    if (right_idx-left_idx < 1) return 0;

    int i = left_idx, j = right_idx, temp = 0;
    int pivot_idx = choose_pivot(num_ary, left_idx, right_idx);
    int pivot = num_ary[pivot_idx];
    //{2,1,8,4,7,6,9,5,3}
    while (i < j){
        if (num_ary[i] > pivot){
            temp = num_ary[j];
            num_ary[j] = num_ary[i];
            num_ary[i] = temp;
            --j;
        }
        else {
            if (num_ary[i] == pivot) pivot_idx = i;
            ++i;
        }
    }
    if (num_ary[i] < pivot){
        num_ary[pivot_idx] = num_ary[i];
        pivot_idx = i;
        num_ary[i] = pivot;
    }
    else if (num_ary[i] > pivot) {
        num_ary[pivot_idx] = num_ary[i-1];
        pivot_idx = i-1;
        num_ary[i-1] = pivot;
    }
    //count += pivot_idx - left_idx;
    //count += right_idx - pivot_idx;
    int count = right_idx - left_idx;
    int L = sortAndPartition(num_ary, left_idx, pivot_idx-1);
    int R = sortAndPartition(num_ary, pivot_idx+1, right_idx);
    return L + R + count;
}


int main(){
    int num_ary[100001]= {0};
    readFile(num_ary);
    //int ary[5] = {2,4,1,3,5};
    int count = sortAndPartition(num_ary, 0, 100000);
    printf("Homework answer: %d\n", count);
}