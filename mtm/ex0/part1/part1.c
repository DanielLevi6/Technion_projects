#include <stdio.h>
#include <stdlib.h>

int my_log2(int num);

int main() {

    int size_of_input = 0, exponent, exponent_sum = 0, i;
    
    printf("Enter size of input:\n");

    if (!scanf("%d", &size_of_input) || size_of_input <= 0) {
        printf("Invalid size\n");
        return 0;
    }

    int *input_array = malloc(sizeof(int)*size_of_input);

    printf("Enter numbers:\n");

    for (i = 0; i < size_of_input; i++) {

        if (scanf("%d", &input_array[i]) <= 0) {

            printf("Invalid number\n");
            free(input_array);

            return 0;
        }
    }
    
    for (i = 0; i < size_of_input; i++) {

        if (input_array[i] <= 0) 
            continue;

        exponent = my_log2(input_array[i]);

        if (exponent < 0)
            continue;

        exponent_sum += exponent;

        printf("The number %d is a power of 2: %d = 2^%d\n", input_array[i], input_array[i], exponent);
    }

    printf("Total exponent sum is %d\n", exponent_sum);

    free(input_array);

    return 0;
}

int my_log2(int num) {

    int exponent = 0;

    while (num > 1) {

        if (num % 2 != 0)
            return -1;
        
        num /= 2;
        ++exponent; 
    }

    return exponent;
}