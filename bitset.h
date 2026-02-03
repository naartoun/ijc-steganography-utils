/** 
 * @file bitset.h
 * 
 * Řešení IJC-DU1, příklad a), 23.3.2025
 * Autor: Radim Kopunec (xkopunr00), FIT
 * Přeloženo: gcc 13.3
 * 
 * @brief Definice maker a inline funkcí pro práci s polem bitů
 */

#ifndef BITSET_H
#define BITSET_H

#include "error.h"
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

/** Maximální možná velikost pole unsigned long pro alokaci */
#define MAX_ALLOC_SIZE 1073741824UL
/** Velikost jednoho prvku pole v bitech */
#define ELEMENT_SIZE (CHAR_BIT * sizeof(unsigned long))

/** Datový typ pro indexaci pole bitů */
typedef unsigned long bitset_index_t;
/** Datová struktura pro pole bitů */
typedef unsigned long* bitset_t;

/** Proměnná pro kontrolu alokace */
extern int alloc_used;

/** Funkce na kontrolu mezí */
inline void index_out_of_range_check(bitset_t bitset, bitset_index_t index) {
    bitset_index_t max_index = bitset[0] - 1;
    if (index > max_index) {
        if (alloc_used)
            free(bitset);
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", index, max_index);
    }
}

/*******************************************************************************
 * Makra pro vytvoření pole bitů
 ******************************************************************************/
/**
 * @brief Vytvoří a vynuluje pole unsigned long
 * 
 * @param bitset Jméno pole
 * @param init_size Počáteční velikost v bitech
 */
 #define bitset_create(bitset, init_size)                                               \
    static_assert((init_size) > 0, "bitset_create: Pole musí být větší než 0");         \
    bitset_index_t array_size = ((init_size % ELEMENT_SIZE) == 0) ?                     \
            (init_size / ELEMENT_SIZE + 1) : (init_size / ELEMENT_SIZE + 2);            \
    unsigned long bitset[array_size];                                                   \
    for (bitset_index_t i = 1; i < array_size; i++) {                                   \
        bitset[i] = 0;                                                                  \
    }                                                                                   \
    bitset[0] = init_size;                                                              \
    alloc_used = 0;

/**
 * @brief Alokuje a vynuluje paměť pro pole bitů
 * 
 * @param bitset Jméno pole
 * @param init_size Počáteční velikost v bitech
 */
#define bitset_alloc(bitset, init_size)                                                 \
    assert((init_size) > 0 && "bitset_create: Pole musí být větší než 0");              \
    bitset_index_t array_size = ((init_size % ELEMENT_SIZE) == 0) ?                     \
            (init_size / ELEMENT_SIZE + 1) : (init_size / ELEMENT_SIZE + 2);            \
    assert(array_size <= MAX_ALLOC_SIZE);                                               \
    bitset_t (bitset) = calloc(array_size, sizeof(unsigned long));                      \
    if ((bitset) == NULL)                                                               \
        error_exit("bitset_alloc: Chyba alokace paměti");                               \
    (bitset)[0] = init_size;                                                            \
    alloc_used = 1;

#ifdef USE_INLINE
/*******************************************************************************
 * Inline funkce pro práci s polem bitů
 ******************************************************************************/
/**
 * @brief Uvolní dynamicky alokované pole
 * 
 * @param bitset Pole bitů
 */
inline void bitset_free(bitset_t bitset) {
    free(bitset);
}

/**
 * @brief Vrací velikost pole v bitech
 * 
 * @param bitset Pole bitů
 * 
 * @return Velikost pole v bitech
 */
inline bitset_index_t bitset_size(bitset_t bitset) {
    return bitset[0];
}

/**
 * @brief Vynuluje nebo nastaví na 1 celý obsah pole
 * 
 * @param bitset Pole bitů
 * @param value Hodnota true/false
 */
inline void bitset_fill(bitset_t bitset, bool value) {
    bitset_index_t size_in_bits = bitset_size(bitset);
    unsigned long filler = value ? ~0UL : 0UL;

    bitset_index_t array_size = ((size_in_bits % ELEMENT_SIZE) == 0) ?
            (size_in_bits / ELEMENT_SIZE) : (size_in_bits / ELEMENT_SIZE + 1);

    for (bitset_index_t i = 1; i <= array_size; i++) {
        bitset[i] = filler;
    }
}

/**
 * @brief Nastaví zadaný bit na zadanou hodnotu
 * 
 * @param bitset Pole bitů
 * @param index Index v @p bitset
 * @param value Hodnota true/false
 */
inline void bitset_setbit(bitset_t bitset, bitset_index_t index, bool value) {
    index_out_of_range_check(bitset, index);
    bitset_index_t UL_index = index / ELEMENT_SIZE + 1;
    bitset_index_t shift = index % ELEMENT_SIZE;
    if (value)
        bitset[UL_index] |= (1UL << shift);  
    else
        bitset[UL_index] &= ~(1UL << shift);
}

/**
 * @brief Získá hodnotu zadaného bitu
 * 
 * @param bitset Pole ukazatelů
 * @param index Index v @p bitset
 * 
 * @return 0 nebo 1
 */
inline bitset_index_t bitset_getbit(bitset_t bitset, bitset_index_t index) {
    index_out_of_range_check(bitset, index);
    bitset_index_t UL_index = index / ELEMENT_SIZE + 1;
    bitset_index_t shift = index % ELEMENT_SIZE;
    bitset_index_t bit_value = (bitset[UL_index] >> shift) & 1;

    return bit_value;
}

#else
/*******************************************************************************
 * Makra pro práci s polem bitů
 ******************************************************************************/
/**
 * @brief Uvolní dynamicky alokované pole
 * 
 * @param bitset Pole bitů
 */
#define bitset_free(bitset) free(bitset);

/**
 * @brief Vrací velikost pole v bitech
 * 
 * @param bitset Pole bitů
 */
#define bitset_size(bitset) ((bitset)[0])

/**
 * @brief Vynuluje nebo nastaví na 1 celý obsah pole
 * 
 * @param bitset Pole bitů
 * @param value Hodnota true/false
 */
#define bitset_fill(bitset, value) {                                                    \
    bitset_index_t size_in_bits = bitset_size(bitset);                                  \
    unsigned long filler = (value) ? ~0UL : 0UL;                                        \
    bitset_index_t array_size = ((size_in_bits % ELEMENT_SIZE) == 0) ?                  \
            (size_in_bits / ELEMENT_SIZE) : (size_in_bits / ELEMENT_SIZE + 1);          \
    for (bitset_index_t i = 1; i <= array_size; i++) {                                  \
        bitset[i] = filler;                                                             \
    }                                                                                   \
}

/**
 * @brief Nastaví zadaný bit na zadanou hodnotu
 * 
 * @param bitset Pole ukazatelů
 * @param index Index v @p bitset
 * @param value Hodnota true/false
 */
#define bitset_setbit(bitset, index, value) {                                           \
    index_out_of_range_check(bitset, index);                                            \
    bitset_index_t UL_index = (index) / ELEMENT_SIZE + 1;                               \
    bitset_index_t shift = (index) % ELEMENT_SIZE;                                      \
    if (value)                                                                          \
        bitset[UL_index] |= (1UL << shift);                                             \
    else                                                                                \
        bitset[UL_index] &= ~(1UL << shift);                                            \
}

/**
 * @brief Získá hodnotu zadaného bitu
 * 
 * @param bitset Pole ukazatelů
 * @param index Index v @p bitset
 */
#define bitset_getbit(bitset, index) (                                                  \
    index_out_of_range_check(bitset, index),                                            \
    (((bitset)[(index) / ELEMENT_SIZE + 1] >> ((index) % ELEMENT_SIZE)) & 1)            \
)

#endif  // USE_INLINE

#endif  // BITSET_H
