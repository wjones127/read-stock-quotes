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
    printf("Number of lines: %d\n", nlines);
    const char* zero_char = "0";
    const int zero = (int)zero_char[0];

    /*
    for (unsigned i = 490; i < 500; i++) {
    printf("%s\n", lines[i]);
        
    //    printf("Are these equal? %c, %d, %d \n",
    //lines[i][0], (int)lines[i][0], (int)lines[i][0] - zero);

    }
    */
    

    // adjustment constants for different sizes
    
    const quote_t fix_4d = 1111 * zero;
    const quote_t fix_3d = 111 * zero;
    const quote_t fix_5d = 11111 * zero;
    
    //const quote_t fixes[6] = { 0, 0, 0, 111 * zero, 1111 * zero, 11111 * zero };

    /*
      Handling the first 3 digits using vectors
     */
    /*
    quote_t *digit1 = calloc(nlines, sizeof(quote_t));
    quote_t *digit2 = calloc(nlines, sizeof(quote_t));
    quote_t *digit3 = calloc(nlines, sizeof(quote_t));

    for (i = 0; i < nlines; i++) {
        digit1[i] = (int)lines[i][0];
        digit2[i] = (int)lines[i][1];
        digit3[i] = (int)lines[i][3];
    }

    nums =
    */
    
    

    unsigned i;

    // Start by handling first three digits
    for (i = 1; i < nlines; i++) {
        nums[i] = ((int)lines[i][0] * 100) +
            ((int)lines[i][1] * 10) + (int)lines[i][2];
    }

    // Then do the rest
    for (i = 1; i < nlines; i++) {
        //nums[i] = atoi(lines[i]);
        int j;

        bool has_fourth_digit = lines[i][3] != 0;
        bool has_fifth_digit = has_fourth_digit && lines[i][4] != 0;
        
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
                
        switch (j) {
        case 4: nums[i] = nums[i] - fix_4d; break;
        case 3: nums[i] = nums[i] - fix_3d; break;
        case 5: nums[i] = nums[i] - fix_5d; break;
        }

        //printf("%d\n", nums[i]);
        
        //printf("%"PRIu32"\n", nums[i]);
    }

    /* figure out which are going wrong */
    for (i = 1; i < nlines; i++) {
        if ((uint32_t)atoi(lines[i]) == nums[i])
            printf("%s versus %d\n", lines[i], nums[i]);
    }
}
