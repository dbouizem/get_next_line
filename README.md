# get\_next\_line

**get\_next\_line** est une fonction permettant de lire un fichier ou une entrée ligne par ligne, quelle que soit la taille de la ligne ou du buffer, dans le cadre du cursus 42.

---

## Table des matières

* [Description](#description)
* [Fonctionnalités](#fonctionnalités)
* [Compilation](#compilation)

  * [Exemples de compilation](#exemples-de-compilation)
  * [Vérification mémoire et débogage](#vérification-mémoire-et-débogage)
* [Utilisation](#utilisation)
* [Structure du projet](#structure-du-projet)
* [Principales fonctions](#principales-fonctions)
* [Gestion des erreurs](#gestion-des-erreurs)
* [Notions importantes](#notions-importantes)
* [Schéma global](#schéma-global)
* [Tests](#tests)

---

## Description

**get\_next\_line** permet de lire un fichier, ou l’entrée standard, **ligne par ligne**, sans limite de longueur de ligne et indépendamment de la taille du buffer.
Ce projet forme à la manipulation de la mémoire dynamique, aux pointeurs et à la gestion fine de la lecture de fichiers en C.

---

## Fonctionnalités

* Lecture ligne à ligne pour n’importe quel descripteur de fichier (`fd`)
* Lecture de lignes de taille arbitraire
* Aucune dépendance à la libft
* Gestion robuste des erreurs et de la mémoire
* Compatible Linux & MacOS

---

## Compilation 

---

### Exemples de compilation

Compiler avec différents `BUFFER_SIZE` :

```bash
# Test avec BUFFER_SIZE = 0 (test d’erreur)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=0 \
    get_next_line.c get_next_line_utils.c main.c -o test_gnl_zero
./test_gnl_zero

# Test avec BUFFER_SIZE = 1 (lecture caractère par caractère)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
    get_next_line.c get_next_line_utils.c main.c -o test_gnl_1
./test_gnl_1

# Test avec BUFFER_SIZE = 42 (lecture efficace)
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 \
    get_next_line.c get_next_line_utils.c main.c -o test_gnl_42
./test_gnl_42
```

> **Conseil** : Teste toujours avec plusieurs tailles de buffer pour valider la robustesse de ton code !

---

### Vérification mémoire et débogage

#### Sous **Linux** (avec Valgrind) :

```bash
valgrind --leak-check=full --show-leak-kinds=all ./test_gnl_42
```

Pour détecter les double free/invalide read :

```bash
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all ./test_gnl_42
```

#### Sous **MacOS** (outil leaks) :

```bash
leaks --atExit -- ./test_gnl_42
```

#### Compilation avec AddressSanitizer (tous OS, pour debug avancé) :

```bash
gcc -g -fsanitize=address -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o test_gnl_asan
./test_gnl_asan
```

---

## Utilisation

Inclure le header dans ton code :

```c
#include "get_next_line.h"
```

Exemple d’utilisation :

```c
int fd = open("monfichier.txt", O_RDONLY);
char *line;
while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

* Fonctionne aussi sur l’entrée standard (`fd = 0`).

---

## Structure du projet

```
get_next_line/
├── get_next_line.c          # Fonction principale et logique associée
├── get_next_line_utils.c    # Fonctions utilitaires (mini-libft)
├── get_next_line.h          # Prototypes
├── Makefile                 # Compilation
└── main.c                   # Exemple d’utilisation / tests
```

---

## Principales fonctions

### get\_next\_line

Fonction principale : orchestre la lecture, l’extraction de la ligne, la gestion d’erreur, et la mise à jour du buffer.

### read\_file

Lit le fichier par morceaux de taille BUFFER\_SIZE jusqu’à trouver une ligne complète ou EOF. Permet de supporter des lignes très longues.

### ft\_line

Extrait et retourne la prochaine ligne complète du stock (jusqu’au \n inclus si présent).

### ft\_next

Met à jour le stock : ne garde que ce qu’il reste après la ligne extraite, libère le reste.

### clean\_stock

Libère la mémoire du buffer "stock" et sécurise le pointeur pour éviter les fuites.

### Fonctions utilitaires

* **ft\_strlen** : Calcule la longueur d'une chaîne de caractères.
* **ft\_strdup** : Duplique une chaîne.
* **ft\_strchr** : Cherche la première occurrence d’un caractère dans une chaîne.
* **ft\_strlcpy** : Copie une chaîne en toute sécurité, évitant les dépassements de buffer.
* **ft\_strjoin\_free** : Concatène deux chaînes, libère la première pour éviter toute fuite mémoire.

---

## Gestion des erreurs

* Contrôle systématique de la validité du descripteur, de la valeur de BUFFER\_SIZE, et du succès des allocations mémoire.
* Nettoyage de toute mémoire allouée en cas d’erreur.
* Retour de `NULL` en cas d’erreur, ou à la fin du fichier.

---

## Notions importantes

* **Gestion dynamique de la mémoire** : aucune fuite tolérée.
* **Variable statique pour le buffer** : permet de garder le "reste" entre les appels.
* **Lecture en plusieurs morceaux** : gestion automatique de la taille de ligne.
* **Robustesse** : chaque appel doit être fiable, même avec des conditions limites (BUFFER\_SIZE 0, fd invalide, fichier vide, ...).

---

## Schéma global (mindmap)

![Organigramme mindmap get\_next\_line](![image](https://github.com/user-attachments/assets/d7a583ea-304a-41f5-aaf7-93df942a57f9)
)

---

## Tests

Un fichier **main.c** est fourni avec plusieurs cas de test :

* Fichiers textes classiques
* Fichiers très longs
* Cas de EOF, fichier vide, ou sans \n final
* Gestion des erreurs (fichier inexistant, fd invalide)

Pour tester :

```bash
make
./test_gnl_42         # Ou ./test_gnl_1 etc.
```

Pour ajouter tes propres cas de test, modifie `main.c`.

