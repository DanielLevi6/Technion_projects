#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

    int size_of_input = 0, exponent_sum = 0, exponent, i;
    
    printf("Enter size of input:\n");

    if (!scanf("%d", &size_of_input) || size_of_input == 0) {
        printf("Invalid size\n");
        return -1;
    }

    int input_array[] = malloc(sizeof(int)*size_of_input);

    printf("Enter numbers:\n");

    for (i = 0; i < size_of_input && scanf("%d", &input_array[i]) ; i++);

    if (i != size_of_input) {
        free(input_array);
        return -1;
    }
    
    for (i = 0; i < size_of_input; i++) {

        exponent = log(input_array[i]);
        exponent_sum += exponent;

        printf("The number %d is a power of 2: %d = 2^%d\n", input_array[i], input_array[i], exponent);
    }

    printf("Total exponent sum is %d", exponent_sum);

    free(input_array);

    return 0;
}