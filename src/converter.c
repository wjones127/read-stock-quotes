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

               }*/

    // adjustment constants for different sizes
    const int fix_4d = 1111 * zero;
    const int fix_3d = 111 * zero;
    const int fix_5d = 11111 * zero;

    // Tried to use OpenMP to do the conversion in parallel,
    // but it actually was slower.
    unsigned i;
    //#pragma omp parallel for private(i)
    for (i = 0; i < nlines; i++) {
        //nums[i] = atoi(lines[i]);
        quote_t sum = 0;
        unsigned j;
        for (j = 0; lines[i][j] != 0; j++) {
            sum = (10 * sum) + ((int)lines[i][j]);
        }

        //printf("stopped at j = %d\n", j);
        // If it's a 4-digit number (most common case)
        switch (j) {
        case 4: sum = sum - fix_4d; break;
        case 3: sum = sum - fix_3d; break;
        case 5: sum = sum - fix_5d; break;
        }
        /*        if (j == 4) sum = sum - fix_4d;
        else if (j == 3) sum = sum - fix_3d;
        else sum = sum - fix_5d;*/
        
        //printf("%"PRIu32"\n", sum);
        nums[i] = sum;
    }
}
