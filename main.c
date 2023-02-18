#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 8
#define MAX 100000

int *alpha_n_k;
struct array_object {
    int *array;
    int array_size;
};
struct array_object power(int x, int n);
int multiply(int x, int res[], int res_size);
struct array_object multiply_two_arrays(int *a,int l1, char *plaintext);
int *reverse_array(int *array, int array_size);
struct array_object add_two_arrays(int *array_1, int array_1_size, int *array_2, int array_2_size);
int calculate_module(int *X_k, int array_size, int F_t);
struct array_object divide_arrays(int *dividend, int dividend_size, int divisor);

int *calculate_FNT(char *plaintext[N], int t);

//START OF MAIN FUNCTION
int main() {
//    printf("F_t = %d\n", F_t);
    int *temp_X;
    int temp_X_size;
    int alpha = 4;
    char *plaintext[N] = {"65", "110", "97", "108", "121", "115", "105", "115"};

    for(int i = 0; i < N; i++){
        printf("x_n[%d] = ", i);
        for(int j = 0; j < 3; j++){
            if(plaintext[i][j] != NULL){
                printf("%c", plaintext[i][j]);
            }
        }
        printf("\n");
    }

    int *X_k = (int *) calloc(N, sizeof(int));
    X_k = calculate_FNT(plaintext, 3);
//FREE UP ALLOCATED MEMORY
            free(temp_X);
            temp_X = NULL;
    return 0;
} //END OF MAIN FUNCTION

    //Function of multiplying two arrays
    struct array_object multiply_two_arrays(int *a,int l1, char *plaintext){

        struct array_object product_of_array;
//        int a[100],b[100];
        int b[100];
//        int ans[200] = {0};

        int i, j, tmp;
        int l2 = strlen(plaintext);

//        printf("l1 = %d\n", l1);
//        printf("l2 = %d\n", l2);
//
        for(i = l2-1,j=0;i>=0;i--,j++){
            b[j] = plaintext[i]-'0';
        }

        for(i = 0; i < l1; i++){
//            printf("alpha_n_k[%d] = %d\n", i, a[i]);
        }

        for(i = 0; i < l2; i++){
//            printf("x_n[%d] = %d\n", i, b[i]);
        }
        int *ans = (int *)calloc((l1+l2), sizeof (int));
        for(i = 0;i < l2;i++){
            for(j = 0;j < l1;j++){
                ans[i+j] += b[i]*a[j];
            }
        }

        for(i = 0;i < l1+l2;i++){
            tmp = ans[i]/10;
            ans[i] = ans[i]%10;
            ans[i+1] = ans[i+1] + tmp;
        }

        for(i = l1+l2; i>= 0;i--){
            if(ans[i] > 0){
                break;
            }
        }
        product_of_array.array = ans;
        product_of_array.array_size = l1+l2;
        return product_of_array;
    }

// This function multiplies x with the number represented by res[].
// res_size is size of res[] or
// number of digits in the number
// represented by res[].
// This function uses simple school mathematics for multiplication.
// This function may value of res_size and returns the new value of res_size
int multiply(int x, int res[], int res_size){
    // Initialize carry
    int carry = 0;

    // One by one multiply n with
    // individual digits of res[]
    for (int i = 0; i < res_size; i++){
        int prod = res[i] * x + carry;

        // Store last digit of 'prod' in res[]
        res[i] = prod % 10;

        // Put rest in carry
        carry = prod / 10;
    }

    // Put carry in res and increase result size
    while (carry){
        res[res_size] = carry % 10;
        carry = carry / 10;
        res_size++;
    }
    return res_size;
}

//FUNCTION TO CALCULATE POWER OF A NUMBER x
struct array_object power(int x, int n) {
    struct array_object array_input;
    array_input.array = (int *) calloc(MAX, sizeof(int));
    array_input.array_size = 0;
    int *res = (int *) calloc(MAX, sizeof(int));
    int res_size = 0;
    int temp = x;

    // Initialize result
    while (temp != 0) {
        res[res_size++] = temp % 10;
            temp = temp / 10;
    }

    // printing value "1" for power = 0
    if (n == 0) {
        res[0] = 1;
    }
        // Multiply x n times (x^n = x*x*x....n times)
        // The loop start from 2 as i = 2, it means x^2 = x * x
        // i = 0: x^0 = 1
        // i = 1: x ^ 1 = x

    for (int i = 2; i <= n; i++) {
        res_size = multiply(x, res, res_size);
    }
    array_input.array = res;
    array_input.array_size = res_size;
    return array_input;
}
//FUNCTION DECLARATION TO REVERSE THE ARRAY
int *reverse_array(int *array, int array_size){
    int *temp_array = (int *) calloc(array_size, sizeof(int));
    for(int  i = 0; i < array_size; i++){
        temp_array[array_size-1-i] = array[i];
    }
    for(int  i = 0; i < array_size; i++){
        array[i] = temp_array[i];
    }
    return array;
}

//FUNCTION DECLARATION TO ADD TWO DYNAMIC ARRAYS
struct array_object add_two_arrays(int *array_1, int array_1_size, int *array_2, int array_2_size){
    int carry = 0;
    int temp_sum = 0;
    int *sum = (int *) calloc(100, sizeof(int));
    int sum_size;
    int index;

    struct array_object result;
//    printf("array_1_size = %d\n", array_1_size);
//    printf("array_2_size = %d\n", array_2_size);
    if(array_1_size <= array_2_size){
        //ADDING TWO ARRAYS WHEN SIZE OF FIRST ARRAY IS EQUAL OR SMALLER THAN SECOND ARRAY
//        printf("Condition #1: array_1_size <= array_2_size\n");
        array_1 = reverse_array(array_1, array_1_size);
        array_2 = reverse_array(array_2, array_2_size);

        for(index = 0; index < array_1_size; index++){
            temp_sum = ((array_1[index] + array_2[index]) + carry);
//            printf("%d + %d + %d = %d\n", array_1[index], array_2[index], carry, temp_sum);
            sum[index] = temp_sum % 10;
//            printf("sum[%d] = %d\n", index, sum[index]);
            carry = (temp_sum >= 10)? 1:0;
//            printf("carry = %d\n", carry);
        }

        for(index = array_1_size; index < array_2_size; index++){
            temp_sum = (array_2[index] + carry);
//            printf("temp_sum = %d\n", temp_sum);
            sum[index] = temp_sum % 10;
//            printf("sum[%d] = %d\n", index, sum[index]);
            carry = (temp_sum >= 10)? 1:0;
        }

        if(carry){
//            printf("carry = %d\n", carry);
//            printf("index = %d\n", index);
            sum[index] = carry;
//            printf("sum[%d] = %d\n", index, sum[index]);
            result.array_size = index + 1;
        } else{
            result.array_size = index;
        }
    }else if(array_1_size > array_2_size){
        //ADDING TWO ARRAYS WHEN SIZE OF FIRST ARRAY IS SMALLER THAN SECOND ARRAY
//        printf("Condition #2: array_1_size > array_2_size\n");//
        array_1 = reverse_array(array_1, array_1_size);
        array_2 = reverse_array(array_2, array_2_size);

        for(index = 0; index < array_2_size; index++){
            temp_sum = ((array_1[index] + array_2[index]) + carry);
            sum[index] = temp_sum % 10;
            carry = (temp_sum >= 10)? 1:0;
        }

        for(index = array_2_size; index < array_1_size; index++){ //i = 1, 2
            temp_sum = (array_1[index] + carry);
            sum[index] = temp_sum % 10;
            carry = (temp_sum >= 10)? 1:0;
        }

        if(carry){
//            printf("carry = %d\n", carry);
            sum[index] = carry;
//            printf("sum[%d] = %d\n", index, sum[index]);
            result.array_size = index + 1;
        } else{
            result.array_size = index;
        }

//        printf("result.array_size = %d\n", result.array_size);
    }

    for(int i = 0; i < result.array_size; i++){
//        printf("sum[%d] = %d\n", i, sum[i]);
    }
    result.array = reverse_array(sum, result.array_size);
    result.array = sum;
    return result;
}

//FUNCTION DECLARATION OF CALCULATING MOD Ft
int calculate_module(int *X_k, int array_size, int F_t){
    long long int temp = 0;
    for(int i = 0; i < array_size; i++){
        temp = (10 * temp) + X_k[i];
        //printf("%d = 10 * %d + %d\n", temp, temp, X_k[i]);
        temp %= F_t;
//        printf("temp = %d\n", temp);
    }
    return  temp;
}

struct array_object divide_arrays(int *dividend, int dividend_size, int divisor){
    struct array_object result_array;
    int *result = (int *)calloc(dividend_size, sizeof(int));
    int index = 0;
    for(int i = 0; i < dividend_size; i++){
        result[index] = dividend[i]/divisor;
        dividend[i+1] = dividend[i+1] + ((dividend[i] % divisor) * 10);
        index++;
    }
    result_array.array_size = index;
    result_array.array = result;
    return result_array;
}

int* calculate_FNT(char *plaintext[N], int t){
        int F_t = (1 << (1 << t)) + 1;// Ft = 2^(2^t)
        int *X_k = (int *) calloc(N, sizeof(int));
        //    printf("F_t = %d\n", F_t);
        int *temp_X;
        int temp_X_size;
        int alpha = 4;


        //     char *plaintext[N] = {"65", "119", "16", "238", "197", "27", "209", "163"};
        struct array_object sum_result;
        int alpha_nk_size;
        int product_size;
        struct array_object output_from_function;
        struct array_object output_of_product;
        struct array_object temp_sum;
        //---------------------
        for (int k = 0; k < N; k++) {
        //        printf("k = %d\n", k);
        //ASSIGNMENT OF INITIAL VALUES FOR temp_sum FOR ADDING TWO ARRAYS
        temp_sum.array_size = 2;
        temp_sum.array = (int *) calloc(temp_sum.array_size, sizeof(int));
        for (int i = 0; i < temp_sum.array_size; i++) {
        temp_sum.array[i] = 0;
        }
        for (int n = 0; n < N; n++) {
        //calculation of alpha^(n*k)
        //            printf("n = %d\n", n);
        //            printf("nk = %d\n", n * k);

        //CALCULATION OF alpha_n_k
        output_from_function = power(alpha, n * k);
        alpha_nk_size = output_from_function.array_size;
        alpha_n_k = (int *) calloc(alpha_nk_size, sizeof(int));
        alpha_n_k = output_from_function.array;

        for (int i = 0; i < alpha_nk_size; i++) {
        //                printf("alpha_n_k[%d] = %d\n", i, alpha_n_k[i]);
        }

        //CALCULATE THE MULTIPLICATION OF EACH PRODUCT TERM FOR X(k)]
        output_of_product = multiply_two_arrays(alpha_n_k, alpha_nk_size, plaintext[n]);
        temp_X_size = output_of_product.array_size;
        temp_X = (int *) calloc(temp_X_size, sizeof(int));
        temp_X = output_of_product.array;

        //CALLING REVERSE FUNCTION TO REVERSE temp_X TO MATCH WITH PLAINTEXT ARRAY INDEXING e.g. MSB AT O ARRAY INDEX
        temp_X = reverse_array(temp_X, temp_X_size);
        //            printf("temp_X_size = %d\n", temp_X_size);
        for (int i = 0; i < temp_X_size; i++) {
        //                printf("temp_X[%d] = %d\n", i, temp_X[i]);
        }

        //CALLING FUNCTION TO ADD TWO DYNAMIC ARRAYS
        temp_sum = add_two_arrays(temp_X, temp_X_size, temp_sum.array, temp_sum.array_size);
        temp_sum.array = temp_sum.array;
        temp_sum.array_size = temp_sum.array_size;

        for (int i = 0; i < temp_sum.array_size; i++) {
        //                printf("temp_sum.array[%d] = %d\n", i, temp_sum.array[i]);
        }
        //            printf("--------------------------------------------------------------------------------\n");
        }
        //        struct array_object i_temp_sum;
        //        i_temp_sum = divide_arrays(temp_sum.array, temp_sum.array_size, N);
        X_k[k] = calculate_module(temp_sum.array, temp_sum.array_size, F_t);
        //        X_k = calculate_module( i_temp_sum.array,  i_temp_sum.array_size, F_t);

        printf("X_k[%d] = %d\n",k, X_k[k]);
        }
        return X_k;
} //END OF MAIN FUNCTION

