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

#ifndef GET_CALENDAR_H_
#define GET_CALENDAR_H_

#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <stdint.h>
#include "../util/split_string.h"
#include "../VCS/VCS.h"

#define URL_VCS			"https://www.gpu-lr.fr/gpu/gpu2vcs.php?semaine=&prof_etu=ETU&etudiant="
#define URL_VCS_ARGS	"https://www.gpu-lr.fr/gpu/gpu2vcs.php?semaine=%d&prof_etu=ETU&etudiant=%s"

CURLcode get_calendar(char* dept, char* annee, char* phpsessid, char* user_id, char* week, uint8_t number_week, char * file_name);

#endif /* GET_CALENDAR_H_ */
