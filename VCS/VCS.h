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

#ifndef VCS_H_
#define VCS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../mem_struct.h"

extern const char * VCS_HEADER[4];
extern const char * VCS_FOOTER[1];

struct utf8_unicode{
	const char * unicode;
	const char equivalent_char;
};

void convertCalendar(MemoryStruct * chunk, FILE * file);

#endif /* VCS_H_ */
