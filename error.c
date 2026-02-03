/** 
 * @file error.c
 * 
 * Řešení IJC-DU1, příklad b), 18.3.2025
 * Autor: Radim Kopunec (xkopunr00), FIT
 * Přeloženo: gcc 13.3
 * 
 * @brief Definice funkcí pro varování a chybové hlášení
 */

#include "error.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Vypíše varovné hlášení na stderr
 * 
 * @param fmt Obsah varovného hlášení
 */
void warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}

/**
 * @brief Vypíše chybové hlášení na stderr a ukončí program
 * 
 * @param fmt Obsah chybového hlášení
 */
void error_exit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
