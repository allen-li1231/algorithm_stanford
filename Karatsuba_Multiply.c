#include <stdio.h>
#include <stdlib.h>
 

int figureCount(int number){
    int count = 0;
    while(number!=0){
        number /= 10;
        count += 1;
    }
    return count;
}

int *numfigure(char *number){
    int num_left_figure, number_figure, inum;
    inum = atoi(number);
    number_figure =figureCount(inum);
    num_left_figure = number_figure / 2;

    int a[2] = {num_left_figure, number_figure - num_left_figure};
    return a;
}

char *splitChar(char *pchar, int left_ary, int right_ary){
    char *left_container, *right_container;
    for (int i=0; i<left_ary; i++){
        left_container[i] = pchar[i];
    }
    int k = 0;
    for (int j=left_ary; j<right_ary; j++){
        right_container[k] = pchar[j];
        k += 1;
    }

    char container[2] = {left_container, right_container};
    return container;
}

int multiplyAlgorithm(int a, int b, int c, int d){
    int ans;
    ans = (a + b)*(c+d) - a*c - b*d;
    return ans;
}

int main(/*char number1, char number2*/){
    printf("Hi there\n");
    int count1, count2, left_ary, right_ary, *pointer_figure,t;
    // scanf really sucks.
/*    printf("Please insert a number:\n");
    scanf("%c", &number1);
    printf("Please insert the other number:\n");
    scanf("%c", &number2);
*/
    char *number1 = "1234";
    char *number2 = "5678";
    t = atoi(number1);
    pointer_figure = numfigure(number1);
    left_ary = pointer_figure[0];
    right_ary = pointer_figure[1];

    char *pointer1_splited = splitChar(number1, left_ary, right_ary);
    int num1_left = atoi(&pointer1_splited[0]);
    int num1_right = atoi(&pointer1_splited[1]);

    pointer_figure = numfigure(number2);
    left_ary = pointer_figure[0];
    right_ary = pointer_figure[1];

    char *pointer2_splited = splitChar(number2, left_ary, right_ary);
    int num2_left = atoi(&pointer2_splited[0]);
    int num2_right = atoi(&pointer2_splited[1]);

    printf(multiplyAlgorithm(num1_left, num1_right, num2_left, num2_right));
}

 // Learning to use enum:
 /*
enum week{
    mon=1, tue, wed, thu, fri, sat, sun
} day;

int main(){
    for (day=mon; day<=sun; day++){
        printf("enum element：%d \n", day);
    }
    return;
}
*/