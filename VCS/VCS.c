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

#include "VCS.h"

const char * VCS_HEADER[] = {
		"BEGIN:VCALENDAR\r\n",
		"PRODID: Gpu2vcs modified by Dynamisoft and edited by Romain LÉTANG <rl@r0l.fr>\r\n",
		"VERSION:2.0\r\n",
		"METHOD:PUBLISH\r\n"
		};


const char * VCS_FOOTER[] = {
		"END:VCALENDAR\n"
		};


typedef struct vcalendar_chunk{
	char * begin;
	char * end;
} vcalendar_chunk;


void convertCalendar(MemoryStruct * chunk, FILE * file){

	vcalendar_chunk calendar;
	calendar.begin = NULL;
	calendar.end = NULL;

	calendar.begin = strstr(chunk->memory, "BEGIN:VCALENDAR");
	calendar.end = strstr(calendar.begin, "END:VCALENDAR");

	//calendar.end += sizeof("END:VEVENT");

	vcalendar_chunk event;
	event.begin = NULL;
	event.end = NULL;

	char* i;
	char* o;

	fprintf(file, VCS_HEADER[0]);
	fprintf(file, VCS_HEADER[1]);
	fprintf(file, VCS_HEADER[2]);
	fprintf(file, VCS_HEADER[3]);


	// iterate through each event block
	for(i = calendar.begin; i != calendar.end; i++){

		event.begin = strstr(i, "BEGIN:VEVENT");

		if(event.begin == NULL)
			break;

		event.end = strstr(event.begin, "END:VEVENT");
		event.end += sizeof("END:VEVENT"); // to get full VEVENT block

		// for each event
		for(o = event.begin; o != event.end; o++, i++){
				fputc(*o, file);
		}

	}

	fprintf(file, VCS_FOOTER[0]);

}
