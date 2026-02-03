/** 
 * @file ppm.c
 * 
 * Řešení IJC-DU1, příklad b), 21.3.2025
 * Autor: Radim Kopunec (xkopunr00), FIT
 * Přeloženo: gcc 13.3
 * 
 * @brief Definice funkcí pro práci s .ppm obrázkem
 */

#include "ppm.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * @brief Načte obrázek do struktury ppm
 * 
 * @param filename Jméno souboru obrázku
 */
struct ppm *ppm_read(const char *filename) {
    FILE* file;

    char ppm_type[3];
    unsigned width;
    unsigned height;
    unsigned max_value;

    if ((file = fopen(filename, "rb")) == NULL) {
        error_exit("ppm_read: Soubor se nepodařilo otevřít");
    }

    if (strcmp(strrchr(filename, '.'), ".ppm") != 0) {
        warning("ppm_read: Chybná přípona souboru");
    }

    if (fscanf(file, "%2s %u %u %u", ppm_type, &width, &height, &max_value) != 4) {
        fclose(file);
        warning("ppm_read: Chybná hlavička obrázku");
        return NULL;
    }

    if (strcmp(ppm_type, "P6") != 0) {
        fclose(file);
        warning("ppm_read: Chybná varianta PPM, má být P6");
        return NULL;
    }

    if (max_value != 255) {
        fclose(file);
        warning("ppm_read: Chybná maximální barevná hodnota, má být 255");
        return NULL;
    }

    struct ppm *pic = malloc(sizeof(struct ppm) + 3 * width * height * sizeof(char));
    if (pic == NULL) {
        fclose(file);
        error_exit("ppm_read: Chyba alokace struktury");
    }

    pic->xsize = width;
    pic->ysize = height;
    
    int c = fgetc(file);

    unsigned long i = 0;
    while (((c = fgetc(file)) != EOF) && (i < 3 * width * height)) {
        pic->data[i++] = c;
    }

    if (i != 3 * width * height) {
        fclose(file);
        free(pic);
        error_exit("ppm_read: Nedostatek dat v souboru");
    }

    fclose(file);
    return pic;
}

/**
 * @brief Uvolní dynamicky alokované pole
 * 
 * @param pic Struktura obrázku
 */
void ppm_free(struct ppm *pic) {
    free(pic);
}
