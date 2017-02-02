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

#include "get_calendar.h"

CURLcode content_typeVCAL = CURL_LAST;

static size_t body_callback(void *contents, size_t size, size_t nmemb, void *userp){

	size_t realsize = size * nmemb;
	MemoryStruct * mem = (MemoryStruct *)userp;

	mem->memory = realloc(mem->memory, mem->size + realsize + 1);
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return size * nmemb;
}

static size_t header_callback(char *buffer,   size_t size,   size_t nitems,   void *userdata){

	int i;

	char **str_arr = NULL;
	size_t size_arr = 0;

	for(i = 0; i < size; i++){
		#ifdef DEBUG
			fprintf(stderr, "%s", buffer);
		#endif

		size_arr = split_str(buffer, ' ', &str_arr);

		const char raw_cmp_string[] = {
				't', 'e', 'x', 't', '/', 'x', '-',
				'v', 'c', 'a', 'l', 'e', 'n', 'd', 'a', 'r',
				0x0D, 0x0A, 0x00
		};

		if(size_arr > 1 && strcmp(str_arr[0], "Content-Type:") == 0){

			if(strcmp(str_arr[1], raw_cmp_string) == 0){
				#ifdef DEBUG
					fprintf(stderr, "Content type is OK\n");
				#endif
				content_typeVCAL = CURLE_OK;
			}else{
				#ifdef DEBUG
					fprintf(stderr, "Content type is not OK : %s\n", str_arr[1]);
				#endif
					content_typeVCAL = CURL_LAST;
			}


		}
	}
	free_splited_string(str_arr, size_arr);
	return nitems * size;
}

CURLcode get_calendar(char* dept, char* annee, char* phpsessid, char* user_id, char* week, uint8_t number_week, char * file_name){

	MemoryStruct chunk;
	chunk.memory = malloc(1);
	chunk.size = 0;

	CURLcode retcode;
	CURL * hnd;
	struct curl_slist *slist1;

	#ifdef DEBUG
		fprintf(stderr, "Get calendar from week %d to %d\n", atoi(week), atoi(week)+number_week);
	#endif

	char * cookie = malloc( sizeof(char) * (strlen("dept=; annee=; PHPSESSID=") + strlen(dept) + strlen(annee) + strlen(phpsessid) + 1));
	sprintf(cookie, "dept=%s; annee=%s; PHPSESSID=%s", dept, annee, phpsessid);

	char * url = NULL;

	int i = 0;


	for(i = 0; i < number_week; i++){

		uint8_t week_number = atoi(week) + i;

		url = malloc( sizeof(char) * (strlen(URL_VCS) + 2 + strlen(user_id) + 1));
		sprintf(url, URL_VCS_ARGS, week_number, user_id);

		slist1 = NULL;
		slist1 = curl_slist_append(slist1, "Host: www.gpu-lr.fr");
		slist1 = curl_slist_append(slist1, "User-Agent: Mozilla/5.0");
		slist1 = curl_slist_append(slist1, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
		slist1 = curl_slist_append(slist1, "Accept-Language: en-US,en;q=0.5");
		slist1 = curl_slist_append(slist1, "Accept-Encoding: utf8");

		curl_global_init(CURL_GLOBAL_ALL );
		hnd = curl_easy_init();

		curl_easy_setopt(hnd, CURLOPT_URL, url);
		curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
		curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
		curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
		curl_easy_setopt(hnd, CURLOPT_COOKIE, cookie);
		curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
		curl_easy_setopt(hnd, CURLOPT_COOKIEFILE, ""); /* start cookie engine */
		curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, body_callback);
		curl_easy_setopt(hnd, CURLOPT_WRITEDATA, (void *)&chunk);

		curl_easy_setopt(hnd, CURLOPT_HEADERFUNCTION, header_callback);

		retcode = curl_easy_perform(hnd);

		if(content_typeVCAL != CURLE_OK){
			fprintf(stderr, "Error : bad content-type\n");
			exit(1);
		}

		free(url);
		url = NULL;

		curl_easy_cleanup(hnd);
		curl_slist_free_all(slist1);
		curl_global_cleanup();

	}


	FILE * file = fopen(file_name, "w+");

	convertCalendar(&chunk, file);

	fprintf(stdout, "Calendrier sauvegardé dans le fichier %s\n", file_name);

	fclose(file);

	free(chunk.memory);
	free(cookie);
	free(url);


	return retcode;
}
