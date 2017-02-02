/* Copyright 2017 Romain LETANG <rl@r0l.fr>

   This file is part of GPU-iCalendar.

   GPU-iCalendar is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   GPU-iCalendar is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GPU-iCalendar.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef SPLIT_STRING_H_
#define SPLIT_STRING_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Sépare une chaîne de caractères en un tableau de chaines de caractères
 *
 * @param in_str chaîne de caractères en entrée
 * @param separator le caractères de séparation
 * @param str_arr un pointeur vers un tableau de chaînes de caractères
 * @return le nombre d'éléments dans str_arr
 */
size_t split_str(char *in_str, const char separator, char *** str_arr);

/**
 * Libère la mémoire allouée a tableau de chaînes de caractères
 *
 * @param str_arr le tableau de chaines de caractères
 * @param number_elements le nombre d'élements dans le tableau
 */
void free_splited_string(char ** str_arr, size_t number_elements);

#endif /* SPLIT_STRING_H_ */
