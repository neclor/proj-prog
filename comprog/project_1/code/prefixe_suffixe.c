#include <assert.h>
#include <stdlib.h>

#include "prefixe_suffixe.h"

#include <stdio.h>


/*
 * Explication:
 * 
 *  
 * a b a b x a b a b b
 * 0 0 1 2 0 1 2 3 4 0 
 * 
 * a b a b
 * 0 0 1 2
 * 
*/

int prefixe_suffixe(int *T, const unsigned int N) {
   int p[N];
   unsigned k = 0;

   // initialize p[N] with 0
   for (unsigned i = 0; i < N; ++i) {
      p[i] = 0;
   }

//     ------------- ------------- 
// T = a b c d a b c a b c d a b c d a b
// p = 0 0 0 0 1 2 3 1 2 3 4 5 6 7 4

   unsigned int i = 1;
   while (i < N) {
      if (T[i] == T[k]) {
         ++k;
         p[i] = k;
         ++i;
      } else {
         if (k == 0) {
            p[i] = 0;
            ++i;
         } else {
            k = p[k - 1];
         }
      }
   }

   for (unsigned i = 0; i < N; ++i) {
      printf("%d, ", p[i]);
   }

   return p[N-1];
}

// gcc code/main-prefixe_suffixe.c code/prefixe_suffixe.c

// -----   -----
// a b c d a b c a b c d a b c d a b
// 
// 0 0 0 0 1 2 3 1 2 3 4 5 6 7 4 5 6
//