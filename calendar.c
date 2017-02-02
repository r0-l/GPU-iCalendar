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

/* #define DEBUG */

#include "calendar.h"

int main(int argc, char *argv[]){

	CURLcode retCode;

	#ifdef DEBUG
		fprintf(stderr, "Mode de débogage activé\n");
	#endif

	char *user_id = NULL;
	char *password = NULL;
	char *week = NULL;
	char *file_output = "calendar.vcs";

	uint8_t number_weeks = MIN_NUM_WEEKS;

	uint8_t ARGS_MASK = 0;

	int c = 0;
	while( (c = getopt(argc, argv, "vhi:p:w:n:f:")) != -1){

		switch(c){
		case 'i':
			user_id = optarg;
			ARGS_MASK |= I_MASK;
			break;

		case 'p':
			password = optarg;
			ARGS_MASK |= P_MASK;
			break;

		case 'w':
			week = optarg;
			ARGS_MASK |= W_MASK;
			break;

		case 'n':
			number_weeks = atoi(optarg);
			break;

		case 'f':
			file_output = optarg;
			break;

		case 'v':
			print_version();
			exit(0);


		case 'h':
			print_usage(argv[0]);
			exit(0);
			break;

		default:
		case '?':
			fprintf (stdout, "Option inconnue : `-%c'.\n", optopt);
			print_usage(argv[0]);
			exit(1);
		}
	}

	if(ARGS_MASK != CHECK_MASK){
		fprintf(stderr, "Erreur : pas assez d'arguments\n");
		print_usage(argv[0]);
		exit(1);
	}

	/* Checking params */
	if( !( atoi(week) > 0 && atoi(week) < 53 ) ){
		fprintf(stderr, "Erreur : le numéro de semaine est incorrect, il doit être compris en 1 et 53. Numéro de semaine reçu : %s\n", week);
	}

	if( number_weeks < MIN_NUM_WEEKS ){

		fprintf(stdout, "Le nombre de semaines à récupérer était trop bas, il a été fixé à %d\n", MIN_NUM_WEEKS);
		number_weeks = MIN_NUM_WEEKS;

	}else if( number_weeks > MAX_NUM_WEEKS ){

		fprintf(stdout, "Le nombre de semaines à récupérer était trop élevé, il a été fixé à %d\n", MAX_NUM_WEEKS);
		number_weeks = MAX_NUM_WEEKS;
	}

	FILE *a;
	if( (a = fopen(file_output, "w+")) == NULL ){
		fprintf(stderr, "Erreur : impossible d'écrire dans le fichier %s\n", file_output);
		exit(1);
	}
	fclose(a);

	CURL* login_handler;
	retCode = post_login(user_id, password, &login_handler);
	check_CURL_code(retCode);

	#ifdef DEBUG
	print_cookies(login_handler);
	#endif

    LoginCookie login_cookie;
    login_cookie.profil = NULL;
    login_cookie.annee = NULL;
    login_cookie.dept = NULL;
    login_cookie.phpsessid = NULL;


	retCode = get_cookie_value("profil", login_handler, &(login_cookie.profil));
	check_CURL_code(retCode);

	if(login_cookie.profil == NULL){
		fprintf(stdout, "Erreur de connexion\n");
		exit(2);
	}else{
		fprintf(stdout, "Connexion réussie\n");
	}

	retCode = get_cookie_value("dept", login_handler, &(login_cookie.dept));
	check_CURL_code(retCode);


	#ifdef DEBUG
		fprintf(stderr, "dept : %s\n", login_cookie.dept);
	#endif

	retCode = get_cookie_value("PHPSESSID", login_handler, &(login_cookie.phpsessid));
	check_CURL_code(retCode);

	#ifdef DEBUG
		fprintf(stderr, "PHPSESSID : %s\n", login_cookie.phpsessid);
	#endif

	retCode = get_cookie_value("annee", login_handler, &(login_cookie.annee));
	check_CURL_code(retCode);

	#ifdef DEBUG
		fprintf(stderr, "annee : %s\n", login_cookie.annee);
	#endif


	retCode = get_index(login_cookie.dept, login_cookie.annee, login_cookie.phpsessid);
	check_CURL_code(retCode);

	get_calendar(login_cookie.dept, login_cookie.annee, login_cookie.phpsessid, user_id, week, number_weeks, file_output);

	curl_easy_cleanup(login_handler);
	free(login_cookie.dept);
	free(login_cookie.phpsessid);
	free(login_cookie.profil);
	free(login_cookie.annee);

	curl_global_cleanup();

    return 0;
}

void print_usage(char * prog_name){
	printf("Utilisation : %s [-v] [-h] -i id_utilisateur -p mot_de_passe -w numero_semaine [-n nombre_semaines] [-f fichier_sortie] \n"
			"    -v\t\t\t  affiche le numéro de version \n"
			"    -h\t\t\t  affiche cette aide \n"
			"    -i id_utilisateur\t  l'identifiant de connexion de l'utilisateur \n"
			"    -p mot_de_passe\t  le mot de passe de l'utilisateur hashé avec l'algorithme MD5 \n"
			"    -w numero_semaine\t le numéro de la semaine à récupérer \n"
			"    -n nombre_semaines\t  le nombre de semaines à récupérer à partir de <numero_semaine>. Vaut %d par défaut \n"
			"    -f fichier_sortie\t le nom et chemin du fichier dans lequel sera enregistré le calendrier. Vaut par défaut %s \n",

			prog_name, MIN_NUM_WEEKS, FILE_OUTPUT);
}

void print_version(){
	printf("%s %s \n"
			"Copyright (C) %s  %s\n"
			"License GPLv3+ : GNU GPL version 3 ou ultérieure \n"
			"<http://gnu.org/licenses/gpl.html>\n"
			"C'est un logiciel libre, vous êtes libre de le modifier et de le redistribuer.\n"
			"Ce logiciel n'est accompagné d'ABSOLUMENT AUCUNE GARANTIE, dans les limites autorisées par la loi applicable.\n",
			PROG_NAME, VERSION, YEAR, AUTHORS);
}


void check_CURL_code(CURLcode code){
	if(code != CURLE_OK){
		fprintf(stderr, "Erreur : le code retourné montre que quelque chose s'est mal déroulé : %d", (int) code);
		exit(4);
	}
}
