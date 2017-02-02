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

#ifndef GET_COOKIE_VALUE_H_
#define GET_COOKIE_VALUE_H_

#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "../util/split_string.h"

CURLcode get_cookie_value(const char* name, CURL *handler, char ** cookie);

void print_cookies(CURL *curl);

#endif /* GET_COOKIE_VALUE_H_ */
