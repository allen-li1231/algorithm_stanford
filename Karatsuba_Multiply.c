#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
 

void numFigure(const char *number, unsigned long *left_ary, unsigned long *right_ary){
    unsigned long num_left_figure, number_figure;
    number_figure =strlen(number);
    *left_ary = number_figure / 2;
    *right_ary = number_figure - *left_ary;
}


void splitChar(const char *pchar, unsigned long left_ary, unsigned long right_ary, char *left_container, char *right_container){
    unsigned long i = 0;
    for (i = 0; i < left_ary; i ++){
        left_container[i] = pchar[i];
    }
    left_container[i] = 0;
    unsigned long k = 0;
    for (unsigned long j = left_ary; j < left_ary + right_ary; j ++){
        right_container[k] = pchar[j];
        k += 1;
    }
    right_container[k] = 0;
}


void leftAlignCharWithZero(char *number, unsigned long zero_count, char *aligned_number){
    unsigned long L = strlen(number);
    char *p, *temp = malloc(sizeof(char)*(zero_count + L + 1));
    memset(temp, 0, sizeof(char)*(zero_count + L + 1));

    for (unsigned long i = 0; i < zero_count; i ++){
        temp[i] = '0';
    }
    p = temp;
    p += zero_count;
    strncpy(p, number, L);
    memcpy(aligned_number, temp, zero_count + L);
    aligned_number[zero_count + L] = 0;
    free(temp);
}


void appendZero(char *appended, char *num, unsigned long zero_count){
    unsigned long L = strlen(num);
    char *p = appended;
    p += L;
    memcpy(appended, num, L);
    for (unsigned long i = 0; i < zero_count; i ++, p ++){
        *p = '0';
    }
    *p = '\0';
}


void reverseChar(char *container, char *num){
    unsigned long len = strlen(num);
    char *p, *temp = malloc(sizeof(char) * (len + 1));
    memset(temp, 0, sizeof(char) * (len + 1));
    for (unsigned long i = 0, k = len - 1; i < len; i ++, k --){
        temp[k] = num[i];
    }
    temp[len] = '\0';
    p = temp;
    while (*(p++) == '0'){
        if (*p == '\0') break;
        len --;
    }
    p --;
    memcpy(container, p, len);
    free(temp);
    container[len] = '\0';
}


void addWithCarry(char *ans, char *digit1, char *digit2, char *carry){
    char temp1[2] = {0}, temp2[2] = {0}, temp3[2] = {0};
    temp1[0] = digit1[0];
    temp2[0] = digit2[0];
    temp3[0] = carry[0];
    int dig_ans, cry_ans;
    dig_ans = (atoi(temp1) + atoi(temp2) + atoi(temp3)) % 10;
    cry_ans = (atoi(temp1) + atoi(temp2) + atoi(temp3)) / 10;
    sprintf(ans, "%d%d", cry_ans, dig_ans);
}


void minusWithCarry(char *digit1, char *digit2, char *carry, char *ans){
    char temp1[2] = {0}, temp2[2] = {0}, temp3[2] = {0};
    temp1[0] = digit1[0];
    temp2[0] = digit2[0];
    temp3[0] = carry[0];
    int dig_ans, cry_ans, d1 = atoi(temp1), d2 = atoi(temp2), c = atoi(temp3);
    if (d1 < d2 + c){
        dig_ans = 10 + d1 - d2 - c;
        cry_ans = 1;
    }
    else {
        dig_ans = d1 - d2 - c;
        cry_ans = 0;
    }
    sprintf(ans, "%d%d", cry_ans, dig_ans);
}


void addChar(char *ans, char *num1, char *num2){
    unsigned long L1 = strlen(num1) - 1, L2 = strlen(num2) - 1, j;
    char dig_ans[3] = {0};
    char z[2] = {'0', '\0'};
    char *p1;
    char *p2;
    if (L1 < L2){
        L1 += L2;
        L2 = L1 - L2;
        L1 -= L2;
        p1 = num2;
        p2 = num1;
    }
    else {
        p1 = num1;
        p2 = num2;
    }
    p1 += L1;
    p2 += L2;
    
    char *v = malloc(sizeof(char)*(L1 + 3));
    memset(v, 0, sizeof(char)*(L1 + 3));
    for (j = 0, p1, p2; j <= L1; j ++, p1 --, p2 --){
        if (j > L2){
            addWithCarry(dig_ans, p1, z, &dig_ans[0]);
            v[j] = dig_ans[1];
        }
        else{
            addWithCarry(dig_ans, p1, p2, &dig_ans[0]);
            v[j] = dig_ans[1];
        }
    }
    if (dig_ans[0] != '0'){v[j] = dig_ans[0];}
    reverseChar(ans, v);
    free(v);
}


void minusChar(char *ans, char *num1, char *num2){
    unsigned long L1 = strlen(num1) - 1, L2 = strlen(num2) - 1;
    char dig_ans[3] = {0};
    char z[2] = {'0', '\0'}, t1[2] = {'0', '\0'}, t2[2] = {'0', '\0'};
    char *p1;
    char *p2;
    t1[0] = num1[0];
    t2[0] = num2[0];
    if ((L1 < L2) || ((atol(t1) < atol(t2)) && (L1 == L2))){
        L1 += L2;
        L2 = L1 - L2;
        L1 -= L2;
        p1 = num2;
        p2 = num1;
    }
    else {
        p1 = num1;
        p2 = num2;
    }
    p1 += L1;
    p2 += L2;

    char *v = malloc(sizeof(char)*(L1 + 2));
    memset(v, 0, sizeof(char)*(L1 + 2));
    for (unsigned long i = 0; i <= L1; i ++, p1 --, p2 --){
        if (i > L2){minusWithCarry(p1, z, &dig_ans[0], dig_ans);}
        else{minusWithCarry(p1, p2, &dig_ans[0], dig_ans);}
        
        if ((i == L1) && (dig_ans[1] == '0')){
            v[i] = '\0';
        }
        else {v[i] = dig_ans[1];}
    }
    reverseChar(ans, v);
    free(v);
}


void multiplyKaratsuba(char *ans, char *number1, char *number2){
    unsigned long left_ary, right_ary, *pointer_figure;
    char *level_ans, *num1, *num2;
    unsigned long len1 = strlen(number1);
    unsigned long len2 = strlen(number2);
    
    if (len1 >= len2){
        char *aligned_number = malloc(len1+1);
        leftAlignCharWithZero(number2, len1 - len2, aligned_number);
        num1 = number1;
        num2 = aligned_number;
    }
    else
    {
        char *aligned_number = malloc(len2+1);
        leftAlignCharWithZero(number1, len2 - len1, aligned_number);
        num2 = number2;
        num1 = aligned_number;
    }

    unsigned long L = strlen(num1);
    if (L > 9){           // 9 is maximum length of a unsigned long number to multiply itself.
        char *num1_left = malloc(sizeof(char)*(L/2 + 2));
        char *num1_right = malloc(sizeof(char)*(L/2 + 2));
        char *num2_left = malloc(sizeof(char)*(L/2 + 2));
        char *num2_right = malloc(sizeof(char)*(L/2 + 2));
        char *bd = malloc(sizeof(char)*(L + 2));
        char *ac = malloc(sizeof(char)*(L + 2));
        char *a_add_b = malloc(sizeof(char)*(L + 2));
        char *c_add_d = malloc(sizeof(char)*(L + 2));
        char *a_add_b_mul_c_add_d = malloc(sizeof(char)*(2*L + 1));
        char *minus_ac = malloc(sizeof(char)*(2*L + 1));
        char *minus_bd = malloc(sizeof(char)*(2*L + 1));
        char *answer = malloc(sizeof(char)*(2*L + 1));
        char *ac_with_zero = malloc(sizeof(char)*(2*L + 1));
        char *minus_bd_with_zero = malloc(sizeof(char)*(L + 1));
        memset(minus_bd_with_zero, 0, sizeof(char)*(2*L + 1));
        memset(ac_with_zero, 0, sizeof(char)*(L + 1));
        memset(answer, 0, sizeof(char)*(2*L + 1));
        memset(minus_bd, 0, sizeof(char)*(2*L + 1));
        memset(minus_ac, 0, sizeof(char)*(2*L + 1));
        memset(a_add_b_mul_c_add_d, 0, sizeof(char)*(2*L + 1));
        memset(c_add_d, 0, sizeof(char)*(L + 2));
        memset(a_add_b, 0, sizeof(char)*(L + 2));
        memset(ac, 0, sizeof(char)*(L + 2));
        memset(bd, 0, sizeof(char)*(L + 2));
        memset(num2_right, 0, sizeof(char)*(L/2 + 2));
        memset(num2_left, 0, sizeof(char)*(L/2 + 2));
        memset(num1_right, 0, sizeof(char)*(L/2 + 2));
        memset(num1_left, 0, sizeof(char)*(L/2 + 2));

        numFigure(num1, &left_ary, &right_ary);
        splitChar(num1, left_ary, right_ary, num1_left, num1_right);
        splitChar(num2, left_ary, right_ary, num2_left, num2_right);

        multiplyKaratsuba(bd, num1_right, num2_right);
        multiplyKaratsuba(ac, num1_left, num2_left);

        addChar(a_add_b, num1_left, num1_right);
        addChar(c_add_d, num2_left, num2_right);

        multiplyKaratsuba(a_add_b_mul_c_add_d, a_add_b, c_add_d);

        minusChar(minus_ac, a_add_b_mul_c_add_d, ac);
        minusChar(minus_bd, minus_ac, bd);

        appendZero(ac_with_zero, ac, 2*right_ary);
        appendZero(minus_bd_with_zero, minus_bd, right_ary);

        addChar(answer, ac_with_zero, bd);
        addChar(ans, answer, minus_bd_with_zero);

/*        free(a_add_b_mul_c_add_d);
        free(a_add_b);
        free(c_add_d);
        free(ac);
        free(minus_bd);
        free(minus_ac);
        free(minus_bd_with_zero);
        free(ac_with_zero);
        free(bd);
        free(answer);
        free(num1_left);
        free(num1_right);
        free(num2_left);
        free(num2_right);*/
    }
    else {
        sprintf(ans, "%lu", atol(number1) * atol(number2));
        ans[strlen(ans)] = '\0';
    }
}

int main(/*int argc, char *argv[]*/){
    printf("Hi, there.\n");
    
    char number1[] = "3141592653589793238462643383279502884197169399375105820974944592";
    char number2[] = "2718281828459045235360287471352662497757247093699959574966967627";

    char *ans = malloc(sizeof(char)*(strlen(number1) + strlen(number2)+1));
    memset(ans, 0, strlen(number1) + strlen(number2)+1);

    minusChar(ans, number1, number2);
    addChar(ans, number1, number2);
    multiplyKaratsuba(ans, number1, number2);
    printf("Multiply answer: \n%s\n", ans);

    free(ans);
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