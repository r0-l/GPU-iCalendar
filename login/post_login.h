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

#ifndef POST_LOGIN_H_
#define POST_LOGIN_H_

#include <stdlib.h>
#include <curl/curl.h>

#define URL_INDEX		"https://www.gpu-lr.fr/sat/index.php?page_param=accueilsatellys.php&cat=0&numpage=1&niv=0&clef=/"

/**
 * Une requête POST afin d'authentifier l'utilisateur
 *
 * @param user_id l'ID de l'utilisateur
 * @param user_pass le mot de passe hashé
 * @param login_handler un pointeur dans lequel les cookies seront stockés
 * @return un code de retour
 */

CURLcode post_login(char* user_id, char* user_pass, CURL** login_handler);

#endif /* POST_LOGIN_H_ */
