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

#include "get_cookie_value.h"

CURLcode get_cookie_value(const char *name, CURL *handler, char ** cookie){
	CURLcode retCode;

	struct curl_slist *cookies;
	struct curl_slist *nc;

	retCode = curl_easy_getinfo(handler, CURLINFO_COOKIELIST, &cookies);
	if(retCode != CURLE_OK)
		return retCode;

	nc = cookies;
	char **out_str = NULL;
	size_t num_fields;

	while(nc){

		num_fields = split_str(nc->data, '\t', &out_str);

		/* cookie format : domain  tailmatch  path  secure  expiretCode  name  value */

		if(num_fields != 0 && strcmp(out_str[5], name) == 0){

			*cookie = malloc(strlen(out_str[6]) + 1);
			strcpy(*cookie, out_str[6]);
			nc = NULL;

		}else{
			nc = nc->next;
		}

		free_splited_string(out_str, num_fields);
	}


	curl_slist_free_all(cookies);
	curl_slist_free_all(nc);

	return retCode;
}


void print_cookies(CURL *curl)
{
    CURLcode retCode;
    struct curl_slist *cookies;
    struct curl_slist *nc;
    int i;

    retCode = curl_easy_getinfo(curl, CURLINFO_COOKIELIST, &cookies);

    if(retCode != CURLE_OK) {
		fprintf(stderr, "Curl curl_easy_getinfo failed: %s\n", curl_easy_strerror(retCode));
			exit(1);
	}

    nc = cookies, i = 1;


      while(nc) {
    	  fprintf(stderr, "[%d]: %s\n", i, nc->data);

    	  nc = nc->next;
    	  i++;
      }

      if(i == 1) {
    	  fprintf(stderr, "(none)\n");
      }
      curl_slist_free_all(cookies);
}
