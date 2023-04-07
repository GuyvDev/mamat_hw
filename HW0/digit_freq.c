// 123456789
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define ASCII_CHAR_TO_NUMBER 48
#define MAX_LEN_STRING 1000
#define AMOUNT_COUNT_NUMBERS 10
#define FIRST_COUNTING_NUMBER '0'
#define LAST_COUNTING_NUMBER '9'

void print_array (int array[], int len);

/**
 * @breif Count the number of times each number appears in a given string
 * @return A string that represents the counting,
 *         the first number represents the amount of 0, 
 *         the second number represents the amount of 1, and so on
*/
int main() {

    char string[MAX_LEN_STRING];
    int count_numbers[AMOUNT_COUNT_NUMBERS] = { 0 }, i, str_len;

    scanf("%s", string);
    str_len = strlen(string);

    for (i = 0; i < str_len; i++) {
        if ((string[i] >= FIRST_COUNTING_NUMBER) &&
            (string[i] <= LAST_COUNTING_NUMBER)) {
            count_numbers[string[i] - ASCII_CHAR_TO_NUMBER]++;
        }
    }

    print_array(count_numbers, AMOUNT_COUNT_NUMBERS);
    return 0;
}

void print_array (int array[], int len)
{
    int i;

    for (i = 0; i < len - 1; i++) { 
        printf("%d ", array[i]);
    }

    //  The last num print witout spacing
    printf("%d\n", array[i]);
}