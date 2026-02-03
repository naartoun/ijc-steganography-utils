/** 
 * @file steg-decode.c
 * 
 * Řešení IJC-DU1, příklad b), 22.3.2025
 * Autor: Radim Kopunec (xkopunr00), FIT
 * Přeloženo: gcc 13.3
 * 
 * @brief Dešifrování zprávy z .ppm obrázku
 */

#include "ppm.h"
#include "bitset.h"
#include "error.h"
#include "eratosthenes.h"
#include "utf8_check.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

/** Index, od kterého začneme dešifrovat zprávu */
#define START_PRIME 101

/** Proměnná pro kontrolu alokace */
int alloc_used = 1;

/**
 * @brief Dešifruje a uloží zprávu do řetězce
 * 
 * @param picture Struktura obrázku
 */
unsigned char *decode_message(struct ppm *pic) {
    /** Vytvoření pole prvočísel */
    bitset_alloc(prime_numbers, 3 * pic->xsize * pic->ysize);
    Eratosthenes(prime_numbers);
    
    /** Alokace řetězce pro zápis */
    unsigned alloc_size = 50;
    unsigned char *message = malloc(alloc_size * sizeof(char));
    if (message == NULL) {
        bitset_free(prime_numbers);
        return NULL;
    }
    unsigned long m_index = 0;

    /** Prohledání pole prvočísel a dešifrování znaků */
    double n = 0;
    unsigned ctonum = 0;
    for (unsigned long i = START_PRIME; i < 3 * pic->xsize * pic->ysize; i++) {
        if (bitset_getbit(prime_numbers, i) == 1) {
            /** Převod bitu do desítkové soustavy podle pozice a přičtení */
            ctonum += (unsigned)pow(2, n) * (pic->data[i] & 1);
            n += 1;

            /** Uložení znaku do řetězce */
            if (n == 8) {
                message[m_index++] = ctonum;
                if (ctonum == '\0') {
                    bitset_free(prime_numbers);
                    return message;
                }
                n = 0;
                ctonum = 0;

                /** Realokace řetězce */
                if (m_index == alloc_size) {
                    message = realloc(message, (m_index + alloc_size) * sizeof(char));
                    if (message == NULL) {
                        bitset_free(prime_numbers);
                        return NULL;
                    }
                }
            }
        }
    }

    bitset_free(prime_numbers);

    return message;
}

/**
 * @brief Hlavní funkce programu
 * 
 * Načte obrázek, dešifruje a zobrazí zprávu
 * 
 * @param argc Počet argumentů
 * @param argv Pole argumentů
 */
int main (int argc, char *argv[]) {
    if (argc != 2) {
        error_exit("main: Špatný počet argumentů");
    }

    struct ppm *picture = ppm_read(argv[1]);
    if (picture == NULL) {
        error_exit("main: Chybný formát souboru");
    }

    unsigned char *message = decode_message(picture);
    ppm_free(picture);
    if (message == NULL) {
        error_exit("main: Chyba při alokaci paměti pro řetězec");
    }

    if (message[strlen((const char*)message)] != '\0') {
        free(message);
        error_exit("main: Chybný formát řetězce, zpráva musí být ukončena '\\0'");
    }

    if (utf8_check(message) != NULL) {
        free(message);
        warning("main: Zpráva není v UTF-8 formátu");
    }

    fprintf(stdout, "%s\n", message);

    free(message);

    return 0;
}