/** 
 * @file ppm.h
 * 
 * Řešení IJC-DU1, příklad b), 19.3.2025
 * Autor: Radim Kopunec (xkopunr00), FIT
 * Přeloženo: gcc 13.3
 * 
 * @brief Deklarace struktury a funkcí pro práci s .ppm obrázkem
 */

#ifndef PPM_H
#define PPM_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Datová struktura pro .ppm obrázek */
struct ppm {
    unsigned xsize;
    unsigned ysize;
    char data[];
 };

struct ppm *ppm_read(const char * filename);

void ppm_free(struct ppm *p);

#endif
