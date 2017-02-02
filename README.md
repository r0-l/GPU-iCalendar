# GPU-iCalendar
GPU-iCalendar est un programme permettant de concaténer plusieurs agendas au format iCalendar en un seul. Ce programme est initialement destiné aux étudiants de l'IUT de La Rochelle utilisant [GPU](https://www.gpu-lr.fr/).

# Compilation
GPU-iCalendar requiert [libcurl](https://curl.haxx.se/libcurl/)

La compilation du programme se fait en utilisant `make` : 
```
make all
```

# Utilisation
Extrait de l'aide du programme : 
```
./GPU-iCalendar [-v] [-h] -i id_utilisateur -p mot_de_passe -w numero_semaine [-n nombre_semaines] [-f fichier_sortie]
			-v 			        affiche le numéro de version
			-h 			        affiche l'aide
			-i id_utilisateur	l'identifiant de connexion de l'utilisateur
			-p mot_de_passe		le mot de passe de l'utilisateur hashé avec l'algorithme MD5
			-w numero_semaine	le numéro de la semaine à récupérer
			-n nombre_semaines	le nombre de semaines à récupérer à partir de <numero_semaine>
			-f fichier_sortie	le nom et chemin du fichier dans lequel sera enregistré le calendrier
```

Afin de se connecter, les mots de passes doivent être renseignés hashés suivant l'algorithm MD5. Par exemple, pour obtenir le hash MD5 de `azerty` : 
```
echo -n azerty | md5sum
```

# Exemple
L'exemple ci-dessous permet à l'utilisateur ayant l'identifiant `1200042` et le mot de passe `azerty` (`ab4f63f9ac65152575886860dde480a1` une fois hashé en md5) de récupérer l'emploi du temps de la semaine `5` ainsi que celui des `3` semaines suivantes et de le stocker dans le fichier `calendar.ics`
```
./GPU-iCalendar -i 1200042 -p ab4f63f9ac65152575886860dde480a1 -w 5 -n 3 -f calendar.ics
```

# Clause de non-responsabilité
Aucun des développeurs du présent programme ne pourra être tenu responsable d'une mauvaise utilisation de GPU-iCalendar pouvant impacter l'utilisation du compte GPU d'un étudiant ou la qualité du service.

[Satellys](http://www.dynamisoft.fr/satellys.html) est un produit [Prisme-services](http://www.dynamisoft.fr/)
