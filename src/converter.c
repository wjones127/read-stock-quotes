/*
 * Trivial implementation of converter function.
 * You may override this file or create your own.
 */
#include "converter.h"

#include <stdlib.h>
#include <stdio.h>

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
    //printf("Number of lines: %d\n", nlines);


    /*
      We convert the characters to integers, and to get the actual integer value,
      we need to subtract the integer representation of the "0" character. For
      speed, we precompute the total value to subtract for 3, 4, and 5 digit
      numbers.
    */
   
    const char* zero_char = "0";
    const int zero = (int)zero_char[0];
    // adjustment constants for different sizes
    const quote_t fix_3d = 111 * zero;
    const quote_t fix_4d = 1111 * zero;
    const quote_t fix_5d = 11111 * zero;
    

    /*
    for (unsigned i = 0; i < 10; i++) {
    printf("%s\n", lines[i]);
        
    printf("Are these equal? %c, %d, %d \n",
    lines[i][0], (int)lines[i][0], (int)lines[i][0] - zero);

    }
    */

    unsigned i;

    for (i = 0; i < nlines; i++) {
        nums[i] = atoi(lines[i]);
        quote_t sum = 0;
        unsigned j;                                        

        // Handle first three digits
        sum = (100 * (int)lines[i][0]) + (10 * (int)lines[i][1]) + (int)lines[i][2];
        
        // Handle last two digits        
        if (__builtin_expect((lines[i][3] != 0), 1))
            {
                sum = (10 * sum) + (int)lines[i][3];
                j = 4;
                if (__builtin_expect((lines[i][4] != 0), 0)) {
                    sum = (10 * sum) + (int)lines[i][4];
                    j = 5;
                }
            }
        else {
            j = 3;
        }

        // Subtract the zero representation
        switch (j) {
        case 3: sum = sum - fix_3d; break;
        case 4: sum = sum - fix_4d; break;
        case 5: sum = sum - fix_5d; break;
        }
        
        //printf("%"PRIu32"\n", sum);
        nums[i] = sum;
    }
}
