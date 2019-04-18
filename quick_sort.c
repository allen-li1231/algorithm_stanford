//@Author: Allen Lee        2019/3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int choose_pivot(int *array, int left_idx, int right_idx) {         //rule of the game
    //return right_idx;
    return left_idx;
    //return (right_idx - left_idx) / 2
}


void readFile(int *container){
    FILE *fp =  NULL;
    char buff[6] = {0};
    fp = fopen("Quicksort.txt", "r");

    int i=0;
    while (!feof(fp)){
        fgets(buff, 7, fp);
        if (buff[0] != '\n') container[i++] = atoi(buff);
    }
    fclose(fp);
}

//truncated:
/*int sortAndCount(int *num_ary, int left_idx, int right_idx){//, int left, int right){
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
    int L = sortAndCount(num_ary, left_idx, pivot_idx-1);
    int R = sortAndCount(num_ary, pivot_idx+1, right_idx);
    return L + R + count;
}
*/

int sortAndCount(int *num_ary, int left_idx, int right_idx){
    if (right_idx - left_idx < 1) return 0;

    int i=left_idx, j=right_idx, temp;
    int pivot_idx = choose_pivot(num_ary, left_idx, right_idx);
    int pivot = num_ary[pivot_idx];
    while (i < j){
        while (i < j && num_ary[i] <= pivot){
            i++;
        };
        while (j > i && num_ary[j] >= pivot){
            j--;
        };

        temp = num_ary[i];
        num_ary[i] = num_ary[j];
        num_ary[j] = temp;
    }

    if ((pivot_idx < i && pivot > num_ary[i]) || (pivot_idx > i && pivot < num_ary[i])){
        num_ary[pivot_idx] = num_ary[i];
        num_ary[i] = pivot;
        pivot_idx = i;
    }
    else if ((pivot_idx > i && pivot > num_ary[i]) || (pivot_idx < i && pivot < num_ary[i])){
        num_ary[pivot_idx] = num_ary[i-1];
        num_ary[i-1] = pivot;
        pivot_idx = i-1;
    }

    int count = right_idx - left_idx;
    int L = sortAndCount(num_ary, left_idx, pivot_idx-1);
    int R = sortAndCount(num_ary, pivot_idx+1, right_idx);
    printf("count: %d, L: %d, R: %d\n", count, L, R);
    return count + L + R;
}


int main(){
    int num_ary[10000];
    readFile(num_ary);
    //int num_ary[4] = {4,1,3,2};
    int right_idx = sizeof(num_ary)/sizeof(num_ary)[0] - 1;
    int count = sortAndCount(num_ary, 0, right_idx);

    //check if correctly sorted
    for (int i=0; i<=right_idx; i++){
        if (i+1 != num_ary[i]){
            printf("Wrong sort: ary[%d] = %d\n", i, num_ary[i]);
        }
    }
    printf("Homework Answer: %d\n", count);
}