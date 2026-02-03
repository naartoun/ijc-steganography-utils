/** 
 * @file eratosthenes.c
 * 
 * Řešení IJC-DU1, příklad a), 23.3.2025
 * Autor: Radim Kopunec (xkopunr00), FIT
 * Přeloženo: gcc 13.3
 * 
 * @brief Nalezení prvočíselných bitů v poli
 */

#include "eratosthenes.h"
#include "bitset.h"
#include <stdbool.h>

/** Externí inline funkce */
#ifdef USE_INLINE
extern void bitset_free(bitset_t bitset);
extern bitset_index_t bitset_size(bitset_t bitset);
extern void bitset_fill(bitset_t bitset, bool value);
extern void bitset_setbit(bitset_t bitset, bitset_index_t index, bool value);
extern bitset_index_t bitset_getbit(bitset_t bitset, bitset_index_t index);
#endif

/** Externí inline pro kontrolu mezí */
extern void index_out_of_range_check(bitset_t bitset, bitset_index_t index);

/**
 * @brief Funkce Eratosthenova algoritmu nalezení prvočísel
 * 
 * Zaplní pole @param bitset pomocí a poté
 * přepisuje bity na neprvočíselných indexech na 0
 * 
 * @param bitset Pole bitů
 */
void Eratosthenes(bitset_t bitset) {
    bitset_fill(bitset, true);
    bitset_setbit(bitset, 0, false);
    bitset_setbit(bitset, 1, false);
    bitset_index_t size_in_bits = bitset_size(bitset);

    for (bitset_index_t i = 2; (i * i) < size_in_bits; i++) {
        if (bitset_getbit(bitset, i) == 1) {
            bitset_index_t j = i * i;
            while (j < size_in_bits) {
                bitset_setbit(bitset, j, false);
                j += i;
            }
        }
    }
}
