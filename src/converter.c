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
    const char* zero_char = "0";
    const int zero = (int)zero_char[0];

    /*
    for (unsigned i = 0; i < 10; i++) {
    printf("%s\n", lines[i]);
        
    printf("Are these equal? %c, %d, %d \n",
    lines[i][0], (int)lines[i][0], (int)lines[i][0] - zero);

    }
    */

    // adjustment constants for different sizes
    
    const quote_t fix_4d = 1111 * zero;
    const quote_t fix_3d = 111 * zero;
    const quote_t fix_5d = 11111 * zero;
    
    //const quote_t fixes[3] = {111 * zero, 1111 * zero, 11111 * zero };
    //const uint8_t pow_ten[4] = {1, 1, 10, 100};
    

    unsigned i;

    for (i = 0; i < nlines; i++) {
        //nums[i] = atoi(lines[i]);
        quote_t sum = 0;
        unsigned j;                                        

        // Handle first three digits
        sum = (100 * (int)lines[i][0]) + (10 * (int)lines[i][1]) + (int)lines[i][2];

        // Handle last two digits
        /*sum = (sum * pow_ten[j+1]) + (four_digits * pow_ten[j] * d4) +
          (five_digits * d5) - fixes[j];*/

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
            

        //printf("stopped at j = %d\n", j);
        // If it's a 4-digit number (most common case)

        switch (j) {
        case 4: sum = sum - fix_4d; break;
        case 3: sum = sum - fix_3d; break;
        case 5: sum = sum - fix_5d; break;
        }

        //sum = sum - fixes[j];
        
        /*        if (j == 4) sum = sum - fix_4d;
        else if (j == 3) sum = sum - fix_3d;
        else sum = sum - fix_5d;*/
        
        //printf("%"PRIu32"\n", sum);
        nums[i] = sum;
    }
}
