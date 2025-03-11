#include <stdio.h>

#include "prefixe_suffixe.h"


int main(){
   const unsigned int N1 = 9;
   const unsigned int N2 = 10;
   const unsigned int N3 = 9;

   int T1[9] = {1,4,2,4,5,1,4,2,4};
   int T2[10] = {1,2,3,2,1,1,2,3,2,1};
   int T3[9] = {3,2,3,2,1,2,3,2,1};

   printf("Length longest prefix/suffix of T1: %u\n", prefixe_suffixe(T1, N1)); // 4
   printf("Length longest prefix/suffix of T2: %u\n", prefixe_suffixe(T2, N2)); // 5
   printf("Length longest prefix/suffix of T3: %u\n", prefixe_suffixe(T3, N3)); // 0

   int my_test_1[17] = {1,2,3,4,1,2,3,1,2,3,4,1,2,3,4,1,2};
   printf("My test 1: %u\n", prefixe_suffixe(my_test_1, 17)); // 6

   int my_test_2[5] = {0,0,0,0,0};
   printf("My test 2: %u\n", prefixe_suffixe(my_test_2, 5)); // 4
}
