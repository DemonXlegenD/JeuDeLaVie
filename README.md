# Jeu de la Vie en C avec SDL

## Description

Le Jeu de la Vie est un automate cellulaire, un jeu de zéro joueur inventé par le mathématicien John Conway en 1970. Dans ce jeu, chaque cellule d'une grille bidimensionnelle peut être dans l'un des deux états possibles : vivante ou morte. L'évolution d'une génération à l'autre est déterminée uniquement par l'état des cellules voisines selon certaines règles simples.

## Règles du Jeu de la Vie

1. Toute cellule vivante ayant moins de deux voisins vivants meurt, faute de solitude.
2. Toute cellule vivante ayant deux ou trois voisins vivants survit pour la prochaine génération.
3. Toute cellule vivante ayant plus de trois voisins vivants meurt, faute de surpopulation.
4. Toute cellule morte ayant exactement trois voisins vivants devient une cellule vivante, par reproduction.

## Fonctionnalités

- Implémentation du Jeu de la Vie en C avec utilisation de l'allocation mémoire et des pointeurs.
- Utilisation de la librairie SDL pour la gestion de la fenêtre et l'affichage graphique du jeu.
- Affichage de la grille bidimensionnelle avec des cellules vivantes et mortes.
- Évolution automatique des cellules selon les règles du Jeu de la Vie.
- Interface utilisateur simple pour contrôler la vitesse de l'évolution et quitter le jeu `Échap` ou mettre en pause le jeu avec `Espace`.

## Installation

1. Clonez ce dépôt sur votre machine locale.
2. Assurez-vous d'avoir installé la librairie SDL sur votre système. Vous pouvez télécharger SDL depuis [le site officiel](https://www.libsdl.org/download-2.0.php) ou l'installer via un gestionnaire de paquets.
3. Compilez le programme en exécutant la commande suivante dans votre terminal :
   ```bash
   gcc -o jeu_de_la_vie jeu_de_la_vie.c -lSDL2
