/** 
 * @file error.h
 * 
 * Řešení IJC-DU1, příklad b), 18.3.2025
 * Autor: Radim Kopunec (xkopunr00), FIT
 * Přeloženo: gcc 13.3
 * 
 * @brief Deklarace funkcí pro varování a chybové hlášení
 */

#ifndef ERROR_H
#define ERROR_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void warning(const char *fmt, ...);

void error_exit(const char *fmt, ...);

#endif
