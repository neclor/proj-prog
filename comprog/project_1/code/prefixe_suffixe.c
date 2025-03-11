#include <assert.h>
#include <stdlib.h>

#include "prefixe_suffixe.h"


// ===== Prototypes =====


/**
 * Sp _
 * Checking if a prefix of length k matches the suffix of the given array.
 * 
 * Сomplexity: O(n)
 * 
 * @param T: input array.
 * @param N: length of array T.
 * @param k: length of prefix and suffix.
 * 
 * @pre: T != NULL, 0 < N, 0 < k < N
 * @post: T == T_0
 * 
 * @return:
 *     0 Prefix and suffix are NOT equal
 *     1 Prefix and suffix are equal
 */
static int pref_equal_suff(int *T, const unsigned int N, unsigned int k);


// ===== Code =====


int prefixe_suffixe(int *T, const unsigned int N) {
   assert((T != NULL) && (0 < N));

   for (unsigned int k = N - 1; k > 0; --k) {
      if (pref_equal_suff(T, N, k)) return k;
   }
   return 0;
}

static int pref_equal_suff(int *T, const unsigned int N, const unsigned int k) {
   assert((T != NULL) && (0 < N) && (0 < k && k < N));

   for (unsigned int i = 0; i <= k - 1; i++) {
      if (T[i] != T[N - k + i]) return 0;
   }
   return 1;
}

// gcc code/main-prefixe_suffixe.c code/prefixe_suffixe.c
// ./a.out
