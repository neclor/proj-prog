#include <stdio.h>

#include "prefixe_suffixe.h"


int main(){
   const unsigned int N1 = 9;
   const unsigned int N2 = 10;
   const unsigned int N3 = 9;
   int T1[9] = {1,4,2,4,5,1,4,2,4};
   int T2[10] = {1,2,3,2,1,1,2,3,2,1};
   int T3[9] = {3,2,3,2,1,2,3,2,1};
   int TM[17] = {1,2,3,4,1,2,3,1,2,3,4,1,2,3,4,1,2};

   printf("Longueur plus long préfixe/suffixe de T1: %u\n", prefixe_suffixe(T1, N1)); // 4
   printf("Longueur plus long préfixe/suffixe de T2: %u\n", prefixe_suffixe(T2, N2)); // 5
   printf("Longueur plus long préfixe/suffixe de T3: %u\n", prefixe_suffixe(T3, N3)); // 0

   printf("my test: %u\n", prefixe_suffixe(TM, 17)); // 6
}
