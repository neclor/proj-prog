/**
 * \file prefixe_suffixe.h
 * \brief Header for calculating the length of the longest subarray at the prefix and suffix.
 * \author Pavlov Aleksandr
 * \version 2.0
 * \date 11/03/2025
 *
 * Implements p-compatibility between T1 and T2
*/

#ifndef _PREFIXE_SUFFIXE_H
#define _PREFIXE_SUFFIXE_H 1

/**
 * Сalculating the length of the longest subarray at the prefix and suffix.
 * 
 * Сomplexity: O(n^2)
 * 
 * @param T: input array.
 * @param N: length of array T.
 * 
 * @pre: T != NULL, 0 < N
 * @post: T == T_0
 * 
 * @return: length of the longest subarray at the prefix and suffix
 */
int prefixe_suffixe(int *T, const unsigned int N);

#endif // _PREFIXE_SUFFIXE_H
