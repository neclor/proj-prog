#include <assert.h>
#include <stdlib.h>

#include "prefixe_suffixe.h"

#include <stdio.h>

int prefixe_suffixe(int *T, const unsigned int N) {
   int p[N];
   unsigned k = 0;

   // initialize with 0
   for (unsigned i = 1; i < N; ++i) {
      p[i] = 0;
   }

   printf("%d, ", p[0]);

   for (unsigned i = 1; i < N; i++) {
      if (T[i] == T[k]) {
         p[i] = ++k;
      } else {
         while (k > 0 && T[i] != T[k]) 
            k = p[k - 1];
      }

      printf("%d, ", p[i]);
   }


   return p[N-1];
}

// gcc code/main-prefixe_suffixe.c code/prefixe_suffixe.c
