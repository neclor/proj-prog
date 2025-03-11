#include <assert.h>
#include <stdlib.h>

#include "prefixe_suffixe.h"


// ===== Prototypes =====


static int solution_1(int *T, const unsigned int N);
static int solution_2(int *T, const unsigned int N);


// ===== Code =====


int prefixe_suffixe(int *T, const unsigned int N) {
   int s1 = solution_1(T, N);
   int s2 = solution_2(T, N);
   if (s1 == s2) return s1;
   return -1;
}

/* 
 * Solution 1
 * Сomplexity: O(n)
 */
static int solution_1(int *T, const unsigned int N) {
   assert(N > 0);

   int p[N];
   unsigned int k = 0;

   for (unsigned int i = 0; i < N; ++i) p[i] = 0; // initialize p[N] with 0

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

   return p[N-1];
}

/* 
 * Solution 2
 * Сomplexity: O(n^2)
 */
static int solution_2(int *T, const unsigned int N) {
   assert(N > 0);

   for (unsigned int k = N - 1; k >= 1; --k) {
      int flag = 1;

      for (unsigned int i = 0; i <= k - 1; i++) {
         if (T[i] != T[N - k + i]) {
            flag = 0;
            break;
         }
      }

      if (flag) return k;
   }

   return 0;
}

// gcc code/main-prefixe_suffixe.c code/prefixe_suffixe.c
// ./a.out