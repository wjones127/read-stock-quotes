/*
 * Trivial implementation of converter function.
 * You may override this file or create your own.
 */
#include "converter.h"
#include <emmintrin.h>
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
    
    __m128i fix_3_vec = _mm_set1_epi16(fix_3d);
    __m128i fix_4_vec = _mm_set1_epi16(fix_4d);
    __m128i fix_5_vec = _mm_set1_epi16(fix_5d);
    
    /*
    for (unsigned i = 0; i < 10; i++) {
    printf("%s\n", lines[i]);
        
    printf("Are these equal? %c, %d, %d \n",
    lines[i][0], (int)lines[i][0], (int)lines[i][0] - zero);

    }
    */

    unsigned i;

    /*
      Creating vectors of 8 16-bit integers.
      Tutorial: http://felix.abecassis.me/2011/09/cpp-getting-started-with-sse/
    */
    __m128i hundreds = _mm_set1_epi16(100);
    __m128i tens = _mm_set1_epi16(10);
    __m128i zeros = _mm_set1_epi16(0);

    for (i = 0; i < nlines; i += 8) {
        //nums[i] = atoi(lines[i]);
        //quote_t sum = 0;

        // Get digits
        uint16_t digit1[8];
        uint16_t digit2[8];
        uint16_t digit3[8];
        uint16_t digit4[8];
        uint16_t digit5[8];

        for (unsigned j = i; j < i + 8; j++) {
            digit1[j-i] = (uint16_t)lines[j][0];
            digit2[j-i] = (uint16_t)lines[j][1];
            digit3[j-i] = (uint16_t)lines[j][2];
            digit4[j-i] = (uint16_t)lines[j][3];
            digit5[j-i] = (uint16_t)lines[j][4];
        }

        __m128i *d1_ptr = (__m128i*)digit1;
        __m128i *d2_ptr = (__m128i*)digit2;
        __m128i *d3_ptr = (__m128i*)digit3;
        __m128i *d4_ptr = (__m128i*)digit4;
        __m128i *d5_ptr = (__m128i*)digit5;

        /*
          Handle the first three digits using vector operations.
          -> This adds the vectors: _mm_add_epi16();
          -> This multiplies the vectors: _mm_mullo_epi16(); (ignoring oveflow)
          Reference: https://software.intel.com/sites/landingpage/IntrinsicsGuide/
        */
        __m128i sum3 = _mm_add_epi16(_mm_mullo_epi16(hundreds, d1_ptr),
                                     _mm_add_epi16(_mm_mullo_epi16(tens, d2_ptr),
                                                   d3_ptr));
        
        // Handle first three digits
        //sum = (100 * (int)lines[i][0]) + (10 * (int)lines[i][1]) + (int)lines[i][2];
        
        // Handle last two digits

        // __m128i _mm_cmpeq_epi16

        // Compute 4-digit sum and 5-digit sum
        __m128i sum4 = _mm_add_epi16(_mm_mullo_epi16(tens, sum3), d4_ptr);
        __m128i sum5  = _mm_add_epi16(_mm_mullo_epi16(tens, sum4), d5_ptr);

        // Create 4-digit and 5-digit masks
        __m128i mask4 = _mm_cmpgt_epi16(d4_ptr, zeros);
        __m128i mask5 = _mm_and_si128(_mm_cmpgt_epi16(d5_ptr, zeros), mask4);
        __m128i mask3 = !mask4;
        mask4 = _mm_andnot_si128(mask5, mask4);

        // Subtract the zero representations
        sum3 = _mm_sub_epi16(sum3, fix_3_vec);
        sum4 = _mm_sub_epi16(sum4, fix_4_vec);
        sum5 = _mm_sub_epi16(sum5, fix_5_vec);

        // Mask into one sum
        sum3 = _mm_and_si128(sum4, mask3);
        sum4 = _mm_and_si128(sum4, mask4);
        sum5 = _mm_and_si128(sum4, mask4);
        sum3 = _mm_or_si128(sum3, _mm_or_si128(sum4, sum5));

        int16_t sum[8] __attribute__ ((aligned (16))) = (int16_t) sum3;
        
        for (unsigned j = i; j < i + 8; j++) {
            nums[j] = sum[j-i];
        }

        
        /*
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
            } */
        /*
        // Subtract the zero representation
        switch (j) {
        case 3: sum = sum - fix_3d; break;
        case 4: sum = sum - fix_4d; break;
        case 5: sum = sum - fix_5d; break;
        }*/
        
        //printf("%"PRIu32"\n", sum);
        //nums[i] = sum;
    }
}
