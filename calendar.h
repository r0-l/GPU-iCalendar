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


#ifndef CALENDAR_H_
#define CALENDAR_H_

#include <getopt.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "util/split_string.h"
#include "login/post_login.h"
#include "login/get_index.h"
#include "cookies/get_cookie_value.h"
#include "calendar/get_calendar.h"

#define YEAR 		"2017"
#define PROG_NAME 	"GPU-iCalendar"
#define VERSION 	"0.1"
#define AUTHORS 	"Romain LETANG"

#define MIN_NUM_WEEKS	1
#define MAX_NUM_WEEKS	5
#define FILE_OUTPUT		"./calendar.ics"

#define I_MASK	0x01
#define P_MASK	0x02
#define W_MASK	0x04

#define CHECK_MASK	(I_MASK | P_MASK | W_MASK)


void check_CURL_code(CURLcode code);

void print_version();

void print_usage(char * prog_name);

int main(int argc, char *argv[]);

#endif /* CALENDAR_H_ */
