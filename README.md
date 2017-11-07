# COUVERTURE CONNEXE MINIMUM DANS LES RESEAUX DE CAPTEURS

Projet de Métaheuristiques dans le cadre du Master 2 de Recherche Opérationnelle (CNAM).

### Participants au projet : <br />

-Alexis Reymann (Télécom ParisTech)<br />
-Madeline Fleury (Ecole des Ponts ParisTech)<br />

### EXECUTER LE PROGRAMME :<br />

Nous n'avons pas implementé le multithread en mode de compatibilité pour Visual Studio. Nous vous conseillons donc de compiler notre programme sur un ordinateur fonctionnant sous Linux ou sous une machine virtuelle Linux.<br />

Pour compiler le code :<br />
`$ make -B`

Pour exécuter le code :<br />
`$ ./mh_fleury_reymann`

### INFORMATIONS :<br />

Vous pouvez retrouver la meilleure solution trouvée par notre algorithme, pour chaque instance, dans le fichier `log.txt` généré automatiquement par notre code. Ce fichier contient des caractères susceptibles d'être mal lus par le Bloc-Notes basique de Windows, nous vous conseillons donc d'utiliser un éditeur plus performant tel que NotePad++ ou Atom. <br />
Le programme affiche également des informations dans la console : Le nombre d'itérations effectuées pour chacune des instances en temps réel ainsi que le nombre de capteurs que contient la meilleure solution actuelle.

### TROUBLESHOOTING :<br />

Si le code ne compile pas : Mettez à jour votre version de g++ (5.4.0)
Si le code s'execute mais ne peut créer tous les threads : Executez le programme sur un ordinateur plus puissant.
Si le problème persiste : Contactez l'un des participants au projet (mad2fleury@gmail.com ou alexis.reymann@telecom-paristech.fr)
