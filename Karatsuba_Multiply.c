#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
/*
int figureCount(int number){
    int count = 0;
    while(number!=0){
        number /= 10;
        count += 1;
    }
    return count;
}
*/
void numfigure(const char *number, int *left_ary, int *right_ary){
    int num_left_figure, number_figure;
    number_figure =strlen(number);
    *left_ary = number_figure / 2;
    *right_ary = number_figure - *left_ary;
}

void splitChar(const char *pchar, int left_ary, int right_ary, char *left_container, char *right_container){
    int i=0;
    for (i=0; i < left_ary; i++){
        left_container[i] = pchar[i];
    }
    left_container[i+1] = 0;
    int k = 0;
    for (int j=left_ary; j<left_ary + right_ary; j++){
        right_container[k] = pchar[j];
        k += 1;
    }
    right_container[k] = 0;
}

long long  algorithm(long long a, long long b, long long c, long long d, int right_figure){
    long long ans;
    ans = a*c*pow(10, 2*right_figure) + b*d + ((a+b)*(c+d)-a*c-b*d)*pow(10, right_figure);
    return ans;
}

long long multiply(char *number1, char *number2){
    int left_ary, right_ary, *pointer_figure;
    char num1_left[9] = {0}, num1_right[9] = {0}, num2_left[9] = {0}, num2_right[9] = {0};
    numfigure(number1, &left_ary, &right_ary);
    splitChar(number1, left_ary, right_ary, num1_left, num1_right);
    splitChar(number2, left_ary, right_ary, num2_left, num2_right);
    

    
    
    
    long long  left1 = atoll(num1_left), right1 = atoll(num1_right), left2 = atoll(num2_left), right2 = atoll(num2_right);
    long long  ans = algorithm(left1, right1, left2, right2, right_ary);
}

int main(/*int argc, char *argv[]*/){
    printf("Hi there\n");
    // scanf really sucks.
/*    printf("Please insert a number:\n");
    scanf("%c", &number1);
    printf("Please insert the other number:\n");
    scanf("%c", &number2);
*/
    char *number1 = "120";
    char *number2 = "500";
    const long long *ans;

    ans = multiply(number1, number2);
    printf("answer: %lld\n", ans);
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