SSTDIN
======

secured standart input


bibliothèque permettant de récupérer des entrées utilisateurs de façon sécurisée (pas d'overflow, pas de crash)

## Liste des types acceptés

*  CHAR  : char
*  UCHAR : unsigned char
*  SHRT  : short
*  USHRT : unsigned shortINT   : int
*  UINT  : unsigned int
*  LONG  : long
*  ULONG : unsigned long
*  LLONG : long long
*  ULLONG: unsigned long long
*  FLT   : float
*  DBL   : double

## liste des fonctions

##### void clearBuffer
*  nettoie le buffer


##### void readStr(char input, unsigned long size)
*  récupère une chaine de caractère en nettoyant le buffer automatiquement si besoin
*  input : la chaine à récupérer
*  size : la quantité de caractère à lire


##### void readInt(int* number) 
*  lit un entier passé en paramètre


##### void readNumber(void* number, Type t, void* quit) 
*  permet de lire un nombre de n'importe quel type et de laisser le choix à l'utilisateur de ne pas rentrer de nombres
*  number prend n'importe quel type
*  t est un type de la liste Type
*  quit = 1 si l'utilisateur appuie sur 'q' ou 'Q', 0 sinon
*  On peut mettre NULL dans ce cas l'utilisateur doit obligatoirement rentrer un nombre valide


##### unsigned long readNumbers(void* number, Type t, unsigned long limit)
*  permet de récupérer un tableau de nombres 
*  number prend n'importe quel type de pointeur alloué dynamiquement
*  t est un type de la liste Type
*  limit indique la quantité de nombres souhaitée. 
*  Si 0 alors l'utilisateur est libre de rentrer autant de nombres qu'il souhaite puis de rentrer 'q' ou 'Q' pour quitter.
*  la taille de la liste de nombre est renvoyée (nécessaire si limit = 0)


##### void debugList(void* list, Type t, unsigned long size)
*  permet d'afficher en console les éléments de la liste fournie
*  list est une liste créée avec readNumbers ou tout tableau  de nombre
*  t est un type de la liste Type
*  size indique le nombre d'élément de la liste à afficher


## Exemple

exemple d'utilisation pour readNumbers:
```C
int* list = (int*)malloc(sizeof(int));
int size;
size = readNumbers(list, INT, 0);
```
