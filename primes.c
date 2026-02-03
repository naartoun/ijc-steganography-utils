/** 
 * @file primes.c
 * 
 * Řešení IJC-DU1, příklad a), 21.3.2025
 * Autor: Radim Kopunec (xkopunr00), FIT
 * Přeloženo: gcc 13.3
 * 
 * @brief Nalezení a zobrazení prvočísel
 */

#include "bitset.h"
#include "eratosthenes.h"
#include <stdio.h>
#include <time.h>

/** Makro určující počet prvočísel k vypsání */
#define N 10

/** Počáteční velikost pole bitů */
enum { INIT_SIZE = 333000000 };

/** Proměnná pro kontrolu alokace */
int alloc_used = 0;

/**
 * @brief Vypíše @c N největších prvočísel v pořadí vzestupném
 * 
 * @param prime_numbers Bitové pole prvočísel
 */
void print_N_biggest_primes(bitset_t prime_numbers) {
    bitset_index_t count = 0;
    unsigned long big_primes[N];

    for (bitset_index_t i = INIT_SIZE - 1; i > 0; i--) {
        if (bitset_getbit(prime_numbers, i) == 1) {
            big_primes[count] = i;
            count++;
            if (count == N)
                break;
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        fprintf(stdout, "%lu\n", big_primes[i]);
    }
}

/**
 * @brief Hlavní funkce programu
 * 
 * Vytvoří lokální pole bitů, nalezne prvočísla
 * pomocí @c Eratosthenes a vypíše @c N největších.
 */
int main() {
    clock_t start = clock();

    bitset_create(prime_numbers, INIT_SIZE);
    Eratosthenes(prime_numbers);

    print_N_biggest_primes(prime_numbers);

    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    return 0;
}
