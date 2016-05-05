/*
 * Trivial implementation of converter function.
 * You may override this file or create your own.
 */
#include "converter.h"

#include <stdlib.h>
#include <stdio.h>

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
    printf("Number of lines: %d\n", nlines);
    const char* zero_char = "0";
    const int zero = (int)zero_char[0];

    for (unsigned i = 0; i < 10; i++) {
        printf("%s\n", lines[i]);
        
        printf("Are these equal? %c, %d, %d \n",
               lines[i][0], (int)lines[i][0], (int)lines[i][0] - zero);

    }

    
    for (unsigned i = 0; i < nlines; i++) {
        //nums[i] = atoi(lines[i]);
        quote_t sum = 0;
        for (unsigned j = 0; lines[i][j] != 0; j++) {
            sum = (10 * sum) + ((int)lines[i][j] - zero);
        }
        //        printf("%"PRIu32"\n", sum);
        nums[i] = sum;
    }
}
