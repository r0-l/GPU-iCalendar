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

#include "get_index.h"

static size_t body_callback(void *contents, size_t size, size_t nmemb, void *userp){
	return size * nmemb;
}

// we don't need to use any handler, it' just a post request to trigger something on the sever

CURLcode get_index(char* dept, char* annee, char* phpsessid){

	CURLcode ret;
	CURL *hnd;
	struct curl_slist *slist1;

	char *cookie = malloc( sizeof(char) * (strlen("dept=; annee=; PHPSESSID=") + strlen(dept) + strlen(annee) + strlen(phpsessid)) + 1);

	sprintf(cookie, "dept=%s; annee=%s; PHPSESSID=%s", dept, annee, phpsessid);

	slist1 = NULL;
	slist1 = curl_slist_append(slist1, "Host: www.gpu-lr.fr");
	slist1 = curl_slist_append(slist1, "User-Agent: Mozilla/5.0");
	slist1 = curl_slist_append(slist1, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
	slist1 = curl_slist_append(slist1, "Accept-Language: en-US,en;q=0.5");
	slist1 = curl_slist_append(slist1, "Accept-Encoding: utf8");
	slist1 = curl_slist_append(slist1, "DNT: 1");

	hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_URL, "https://www.gpu-lr.fr/gpu/index.php");
	curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
	curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
	curl_easy_setopt(hnd, CURLOPT_COOKIE, cookie);
	curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);
	curl_easy_setopt(hnd, CURLOPT_COOKIEFILE, ""); /* start cookie engine */
	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, body_callback);

	ret = curl_easy_perform(hnd);

	free(cookie);

	curl_easy_cleanup(hnd);
	hnd = NULL;
	curl_slist_free_all(slist1);
	slist1 = NULL;

	return ret;
}
