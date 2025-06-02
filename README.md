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
* [Schéma global](#schéma-global-mindmap)
* [Tests](#tests)
* [Bonus](#bonus)

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

![Organigramme mindmap get\_next\_line](https://github.com/user-attachments/assets/93f76eda-ef78-44c5-aaf9-a5f888c56a43)

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

---

# Bonus

La partie **Bonus** de **get_next_line** ajoute la capacité à lire en parallèle plusieurs fichiers (ou entrées standard) en appelant successivement :
```c
char *get_next_line(int fd);
```
pour chaque descripteur de fichier. Chaque `fd` conserve son propre “stock” (buffer statique ou structure dédiée) afin que les lectures n’interfèrent pas entre elles. On reste capable de lire des lignes de longueur arbitraire, sans contrainte liée à `BUFFER_SIZE`, et de gérer correctement les erreurs (notamment `read() < 0`) et la fin de fichier (EOF).

---

## Fonctionnalités Bonus

1. **Lecture simultanée de plusieurs descripteurs**
    - Chaque appel `get_next_line(fd1)`, `get_next_line(fd2)`, … avance indépendamment dans chaque fichier.
    - Les buffers intermédiaires (stocks) sont isolés par `fd`.
2. **Gestion des erreurs de lecture**
    - Si `read(fd, buff, BUFFER_SIZE)` renvoie `1`, on doit :
        1. Libérer immédiatement le buffer statique associé au `fd` (stock).
        2. Supprimer l’entrée `fd` de la structure (liste chaînée).
        3. Retourner `NULL` pour ce seul appel.
    - Lorsqu’on réouvre le même fichier plus tard (même valeur de `fd`), on repart de zéro, sans reste d’anciennes données.
3. **Support des mêmes cas que pour la partie obligatoire**
    - Lignes de longueur arbitraire (plus grandes que `BUFFER_SIZE`).
    - Lecture depuis `stdin` (`fd = 0`).
    - Retour `NULL` quand EOF est atteint (après avoir renvoyé la dernière ligne).
    - Prise en compte de `BUFFER_SIZE = 0` comme cas d’erreur (retour `NULL` immédiat).
4. **Pas de fuite mémoire**
    - À chaque fin de lecture (EOF ou erreur), la mémoire allouée pour ce `fd` est libérée.
    - Chaque appel à `get_next_line` qui retourne une chaîne dynamique doit être `free()`ée par l’utilisateur.

---
```
get_next_line_bonus/
├── get_next_line_bonus.c         # Implémentation principale (gestion multi‐fd)
├── get_next_line_bonus.h         # Prototypes et structure t_fdlist
├── get_next_line_utils_bonus.c   # Fonctions utilitaires (ft_strdup, ft_strchr, ft_strlcpy, ft_strjoin_free, etc.)
├── Makefile                      # Compilation (cibles : all, bonus, clean, fclean, re)
```
---

## Principales fonctions

### get_next_line (bonus)

```c
char *get_next_line(int fd);

```

- Valide `fd` (`fd < 0` ou `BUFFER_SIZE <= 0` renvoient immédiatement `NULL`).
- Récupère (ou crée) le nœud `t_fdlist` pour ce `fd` via `get_fdnode()`.
- Teste `read(fd, NULL, 0)` : si `< 0`, on sait que le prochain `read()` va échouer.
    - On appelle `move_fdnode()` pour libérer le buffer, on supprime le nœud, on retourne `NULL`.
- Sinon, appelle `gnl_handle_node()` pour lire réellement la prochaine ligne.

### get_fdnode

```c
t_fdlist *get_fdnode(t_fdlist **lst, int fd);

```

- Parcourt la liste `lst`. Si un nœud avec `nœud->fd == fd` existe, on le retourne.
- Sinon, crée un nouveau nœud `malloc(sizeof(t_fdlist))`, initialise `fd`, `stock = NULL`, l’insère en tête de la liste, puis le retourne.

### read_file (statique)

```c
static char *read_file(int fd, char *stock);

```

- Si `stock` existe et contient déjà un `'\n'`, on le retourne tel quel (rien à relire).
- Sinon, on effectue une boucle `read(fd, buff, BUFFER_SIZE)` :
    1. Si `bytes_read < 0` (erreur), faire `free(stock); return NULL`.
    2. Terminer la chaîne `buff[bytes_read] = '\0'`.
    3. Concaténer `stock = ft_strjoin_free(stock, buff)`.
    4. Si `buff` contient `'\n'`, on sort de la boucle (ligne complète trouvée).
- `free(buff)` à la sortie de la boucle.
- Si `bytes_read < 0`, on retourne `NULL`. Sinon, on retourne `stock` (mis à jour).

### ft_line (statique)

```c
static char *ft_line(char *stock);

```

- Si `stock` est NULL ou vide, retourne `NULL`.
- Parcourt `stock` jusqu’au premier `'\n'` (inclus).
- Alloue `line = malloc(len + 1)`, copie `len` caractères (via `ft_strlcpy`), retourne `line`.
- Toute la ligne (avec `'\n'`, s’il existe).

### ft_next (statique)

```c
static char *ft_next(char *stock);

```

- Cherche le premier `'\n'` dans `stock`.
- Si aucun `'\n'`, libère `stock` et retourne `NULL`.
- Sinon, fait `rest = ft_strdup(newline + 1)`, `free(stock)`.
- Si `rest[0] == '\0'` (reste vide), `free(rest); return NULL`.
- Sinon, retourne `rest`.

### gnl_handle_node (statique)

```c
static char *gnl_handle_node(t_fdlist **lst, t_fdlist *node, int fd);

```

- Appelle `node->stock = read_file(fd, node->stock)`.
    - Si `node->stock` devient `NULL` ou vide, alors `move_fdnode(lst, fd); return NULL`.
- Extrait la ligne à renvoyer : `line = ft_line(node->stock)`.
    - Si `line == NULL`, `move_fdnode(lst, fd); return NULL`.
- Met à jour le reste : `node->stock = ft_next(node->stock)`.
    - Si après `ft_next`, `node->stock == NULL`, on appelle `move_fdnode(lst, fd)`.
- Retourne `line`.

### Fonctions utilitaires (get_next_line_utils_bonus.c)

- *fre*move_fdnode
    
    ```c
    void remove_fdnode(t_fdlist **lst, int fd);
    
    ```
    
    - Parcourt la liste `lst`.
    - Si `nœud->fd == fd`, on :
        1. Libère `nœud->stock` (s’il est non‐NULL).
        2. Met à jour le chaînage pour retirer le nœud.
        3. `free(nœud)` et retourne.

---

## Notions importantes

- **Liste chaînée par `fd`**
    - La structure `t_fdlist` permet de gérer plusieurs buffers indépendants :
        
        ```c
        typedef struct s_fdlist
        {
            int             fd;
            char            *stock;   // Contenu en attente pour ce fd
            struct s_fdlist *next;
        } t_fdlist;
        
        ```
        
    - À chaque appel, on retrouve ou crée un nœud pour le `fd` passé en argument.
- **Buffer statique par `fd`**
    - `stock` est la chaîne cumulée entre plusieurs appels `get_next_line(fd)`.
    - Elle contient le texte lu mais non encore renvoyé (tout ce qui se trouve après la dernière ligne renvoyée).
- **Lecture fragmentée**
    - On peut lire un fichier dont la longueur totale dépasse `BUFFER_SIZE`.
    - À chaque itération, on lit `BUFFER_SIZE` octets, on concatène à `stock`.
    - Dès qu’on rencontre un `'\n'`, on peut découper `stock` en deux parties :
        - **ligne à renvoyer** (avec `'\n'`)
        - **reste** (après le `'\n'`), qui devient le nouveau `stock`.
- **Gestion de l’erreur de `read()`**
    - La fonction `read(fd, NULL, 0)` vérifie qu’on peut toujours lire (pour le bonus). Si cette vérification échoue, on supprime tout de suite le buffer et le nœud.
    - Lors d’une lecture “réelle” (`read(fd, buff, BUFFER_SIZE)`), si le retour `< 0`, on libère immédiatement la mémoire, puis on supprime le nœud.
- **Aucune fuite tolérée**
    - Chaque appel à `get_next_line()` renvoie une chaîne `malloc`ée que l’utilisateur doit `free()`.
    - Quand on atteint EOF ou une erreur, `move_fdnode()` libère systématiquement `stock` et le nœud, empêchant toute perte de mémoire.
 
  ---

  ### Cas particulier : erreur de lecture simulée

1. Après avoir lu deux lignes, le test met `next_read_error = 1`.
2. Dans la boucle “drain” (pour BUFFER_SIZE > 100), on appelle `get_next_line(fd)` jusqu’à ce qu’il retourne `NULL` :
    - Au premier appel, `read_file()` détecte `read() < 0` → `free(stock)` → `return NULL`.
    - `gnl_handle_node()` appelle alors `move_fdnode()`, supprimant le nœud et libérant le buffer.
3. Le test fait `test_gnl(fd, NULL)`. Il doit obtenir exactement `NULL`.
4. Après, il ferme `fd` et le réouvre ; la fonction doit repartir sur une nouvelle lecture de la ligne 1 (sans ancien stock). Si votre code n’avait pas supprimé le nœud, il renverrait des données superflues ou planterait.
