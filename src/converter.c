/*
 * Trivial implementation of converter function.
 * You may override this file or create your own.
 */
#include "converter.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>


void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
    //printf("Number of lines: %d\n", nlines);
    
    const char* zero_char = "0";
    const int zero = (int8_t)zero_char[0];
    

    /*
    for (unsigned i = 3275; i < 3280; i++) {
        printf("%d: %s\n", i, lines[i]);
        
    //    printf("Are these equal? %c, %d, %d \n",
    //lines[i][0], (int)lines[i][0], (int)lines[i][0] - zero);

    }
    */
    
    

    // adjustment constants for different sizes

    /*
    const quote_t fix_4d = 1111 * zero;
    const quote_t fix_3d = 111 * zero;
    const quote_t fix_5d = 11111 * zero;
    */
    
    const quote_t fixes[6] = {111 * zero, 1111 * zero, 11111 * zero };

    
    // Create arrays of digits
    uint8_t digit1[nlines];
    uint8_t digit2[nlines];
    uint8_t digit3[nlines];

    unsigned i;
    
    for (i = 0; i < nlines; i++) {
        digit1[i] = (uint8_t)lines[i][0];
        digit2[i] = (uint8_t)lines[i][1];
        digit3[i] = (uint8_t)lines[i][2];
    }

    // Start by handling first three digits
    for (i = 0; i < nlines; i++) {

        uint8_t *d1 = __builtin_assume_aligned(digit1, sizeof(quote_t));
        uint8_t *d2 = __builtin_assume_aligned(digit2, sizeof(quote_t));
        uint8_t *d3 = __builtin_assume_aligned(digit3, sizeof(quote_t));
        
        nums[i] = (quote_t)(100 * d1[i] + 10 * d2[i] + d3[i]);
        /*        nums[i] = ((int)lines[i][0] * 100) +
                  ((int)lines[i][1] * 10) + (int)lines[i][2]; */
    }

    //    printf("---\n");
    int pow_ten[3] = {1, 10, 100};

    // Then do the rest
    for (i = 0; i < nlines; i++) {
        //nums[i] = atoi(lines[i]);
        int j;

        int has_fourth_digit = lines[i][3] != 0;
        int has_fifth_digit = has_fourth_digit && lines[i][4] != 0;

        j = has_fourth_digit + has_fifth_digit;


        nums[i] = (nums[i] * pow_ten[j]) +
            (has_fourth_digit * pow_ten[j-1] * (int)lines[i][3]) +
            (has_fifth_digit * (int)lines[i][4]) -
            fixes[j];
        /*
        if (has_fourth_digit && !has_fifth_digit) {
            nums[i] = (nums[i] * 10) + (int)lines[i][3];
            j = 4;
        }
        else if (has_fifth_digit) {
            nums[i] = (nums[i] * 100) + ((int)lines[i][3] * 10) +
                (int)lines[i][4];
            j = 5;
        }
        else {
            j = 3;
        }
        */
        /*
        switch (j) {
        case 4: nums[i] = nums[i] - fix_4d; break;
        case 3: nums[i] = nums[i] - fix_3d; break;
        case 5: nums[i] = nums[i] - fix_5d; break;
        }
        */
        //printf("%d: %d, %d\n", i, nums[i], j);
        
        //printf("%"PRIu32"\n", nums[i]);
    }

}
