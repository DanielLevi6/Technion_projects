#include <stdio.h>
#include <stdlib.h>

#define NOT_VALID 0
#define ERROR -1
#define VALID 1

int scanSizeOfInput(int size);
int scanInputNumbers(int size_of_input, int *input_array);
int printExponent(int num);
int logBase2ForPowerOf2Number(int num);

int main() {
    int size_of_input = 0, exponent_sum = 0;
    size_of_input = scanSizeOfInput(size_of_input);

    if (size_of_input == NOT_VALID) {
        return NOT_VALID;
    }

    int *input_array = malloc(sizeof(int)*size_of_input);

    if (input_array == NULL || scanInputNumbers(size_of_input, input_array) == NOT_VALID) {
        free(input_array);
        return NOT_VALID;
    }

    for (int i = 0; i < size_of_input; i++) {
        exponent_sum += printExponent(input_array[i]);
    }

    printf("Total exponent sum is %d\n", exponent_sum);
    free(input_array);

    return 0;
}

//Scans the size of input numbers
int scanSizeOfInput(int size) {
    printf("Enter size of input:\n");

    if (scanf("%d", &size) <= 0 || size <= 0) {
        printf("Invalid size\n");
        return NOT_VALID;
    }

    return size;
}

//Scans the input numbers to an array if they are valid
int scanInputNumbers(int size_of_input, int *input_array) {
    printf("Enter numbers:\n");

    for (int i = 0; i < size_of_input; i++) {
        if (scanf("%d", &input_array[i]) <= 0) {
            printf("Invalid number\n");
            return NOT_VALID;
        }
    }

    return VALID;
}

//Prints and returns the exponent of a power of 2 number   
int printExponent(int num) {
    if (num <= 0) {
        return NOT_VALID;
    }

    int exponent = logBase2ForPowerOf2Number(num);

    if (exponent < 0) {
        return NOT_VALID;
    }
    
    printf("The number %d is a power of 2: %d = 2^%d\n", num, num, exponent);

    return exponent;
}

//Calculates log base 2 of a power of 2 number 
int logBase2ForPowerOf2Number(int num) {
    int exponent = 0;

    while (num > 1) {

        if (num % 2 != 0) {
            return ERROR;
        }
        
        num /= 2;
        ++exponent; 
    }

    return exponent;
}