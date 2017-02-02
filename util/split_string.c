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

#include "split_string.h"

size_t split_str(char *in_str, const char separator, char *** str_arr){

	size_t out_str_SIZE = 0;
	char **out_str = NULL;

	size_t input_length = 1; // size for '\0' (null) chararcter
	char *cursor = in_str;

    while(*++cursor != 0)
    	input_length++;

    char *start_str = in_str;
    char **tmp_out_str;
    char* str;

    cursor = in_str;;

    while(*cursor != 0){

    	cursor++;

        if(*cursor == separator || *cursor == '\0'){

            /* string is between |input_str ... cursor| */
        	size_t length = sizeof(char) * (cursor - start_str + 1); // string size + 1 for \0 character

        	str = malloc(length);

			memcpy(str, start_str, length);
			str[length-1] = '\0';

			out_str_SIZE += 1;

			tmp_out_str = realloc(out_str, (out_str_SIZE) * sizeof(char *));

			if(!tmp_out_str){
				fprintf(stderr, "Erreur : 0x01");
				exit(1);
			}

			out_str = tmp_out_str;

			tmp_out_str = NULL;

			/* append str to out_str */
			out_str[out_str_SIZE - 1] = str;
			start_str = cursor + 1;
        }

    }

    *str_arr = out_str;
    free(tmp_out_str);

    return out_str_SIZE;

}

void free_splited_string(char ** str_arr, size_t number_elements){
	int i;
	for(i = 0; i < number_elements; i++){
		free(str_arr[i]);
	}

	free(str_arr);
}
