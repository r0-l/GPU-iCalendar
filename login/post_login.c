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

#include "post_login.h"


static size_t body_callback(void *contents, size_t size, size_t nmemb, void *userp){
	return size * nmemb;
}


CURLcode post_login(char* user_id, char* user_pass, CURL** login_handler){

	CURLcode retCode;

	CURL *hnd;

	struct curl_httppost *post1;
	struct curl_httppost *postend;
	struct curl_slist *slist1;

	post1 = NULL;
	postend = NULL;
	curl_formadd(&post1, &postend,
			   CURLFORM_COPYNAME, "modeconnect",
			   CURLFORM_COPYCONTENTS, "connect",
			   CURLFORM_END);
	curl_formadd(&post1, &postend,
			   CURLFORM_COPYNAME, "util",
			   CURLFORM_COPYCONTENTS, user_id,
			   CURLFORM_END);
	curl_formadd(&post1, &postend,
			   CURLFORM_COPYNAME, "acct_pass",
			   CURLFORM_COPYCONTENTS, user_pass,
			   CURLFORM_END);

	slist1 = NULL;
	slist1 = curl_slist_append(slist1, "Host: www.gpu-lr.fr");
	slist1 = curl_slist_append(slist1, "User-Agent: GPU-iCalendar");
	slist1 = curl_slist_append(slist1, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
	slist1 = curl_slist_append(slist1, "Accept-Language: en-US,en;q=0.5");
	slist1 = curl_slist_append(slist1, "Accept-Encoding: utf8");
	slist1 = curl_slist_append(slist1, "DNT: 1");

	curl_global_init(CURL_GLOBAL_ALL );

	hnd = curl_easy_init();

	curl_easy_setopt(hnd, CURLOPT_URL, URL_INDEX);
	curl_easy_setopt(hnd, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(hnd, CURLOPT_HTTPPOST, post1);

	// curl_easy_setopt(hnd, CURLOPT_USERAGENT, "curl/7.38.0");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, slist1);
	curl_easy_setopt(hnd, CURLOPT_MAXREDIRS, 50L);
	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(hnd, CURLOPT_TCP_KEEPALIVE, 1L);

	curl_easy_setopt(hnd, CURLOPT_COOKIEFILE, ""); // start cookie engine

	curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, body_callback);
	curl_easy_setopt(hnd, CURLOPT_TIMEOUT, 10L);

	retCode = curl_easy_perform(hnd);

	curl_slist_free_all(slist1);
	slist1 = NULL;

	curl_formfree(post1);
	post1 = NULL;

	curl_global_cleanup();

	*login_handler = hnd;

	return retCode;
}


