#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <float.h>
#include <ctype.h>
#include "sstdin.h"


/*fonction qui vide le buffer*/
void clearBuffer()	
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

/*prend un pointeur de string et récupère l'entrée utilisateur et renvoie 1 si réussi 0 sinon*/
int readStr(char *str, int longueur)
{
    char *positionEntree = NULL;
    
    if(fgets(str, longueur, stdin) != NULL)	// fgets renvoie null si il y a une erreur, donc si il n'y a pas d'erreur ...
    {
        positionEntree = strchr(str, '\n'); //	... strchr fonction qui permet de chercher un caractère dans une chaine
        if(positionEntree != NULL)	// si on a trouver un caractère entrée...
        {
            *positionEntree = '\0';	//... on évite d'écrire le caractère entrée car fgets le lit et l'affiche
        }
        else	// si on a pas trouver le caractère entrée ...
        {
            clearBuffer();	// ... c'est qu'il y a trop de texte tapé donc on affiche ce qui est prévu et on vide le buffer
        }
        return 1;
    }
    else
    {
        clearBuffer();  //erreur non prévu du fgets l'utilisateur aura tapé un truc mais problème alors on vide le buffer et on renvoie un code d'erreur
        return 0;
    }
}


/*transforme une chaine récupérée en Int*/
void readInt(int *nb)
{
    char *endStr, str[50];
    long l;
    
    while (1)   //boucle infini tant que l'utilisateur n'a pas rentré un nombre valide
    {
        if (readStr (str, 50))  // si la fonction lire renvoie 1 cad ça a bien marché
        {
            errno = 0;    //restera à zero si pas d'erreur
            l = strtol(str,&endStr, 10);
            if ((errno == ERANGE && (l == LONG_MAX || l == LONG_MIN)) || (errno != 0 && l == 0)){ //ERANGE est récupéré depuis strtol si on sort du domaine d'un long
                printf("Wrong entry, please try again\n");}   //on boucle
            else if (endStr == str){ 
                printf("Wrong entry, please try again\n");}    //on boucle si charactères au début de chaine
            
            else if (l > INT_MAX || l < INT_MIN){ 
                printf("Wrong entry, please try again\n");}    // si l trop grand ou trop petit pour etre stocké dans un int
            else {
                *nb = (int)l; 
                return;
            }
        }
        else{
            printf("Error : unable to get the buffer, please try again\n");
        }
        printf(">>");
    }
}


/*transforme une chaine récupérée en un nombre non signé*/
void readNumber(void *nb, Type t, void* quit)
{
    char *endStr, str[320];
    double l;
    
    printf(">>");
    while (1)  
    {
        if (readStr (str, 320))	
        {
            if (quit && tolower(str[0]) == 'q'){ //si l'utilisateur veut arreter une boucle d'entrée de donnée
                    *(char*)quit = 1;
                    return;
            }
            else if (tolower(str[0]) == 'q'){
                printf("You must choose a number\n");
                continue;
            }
            errno = 0;    
            l = strtod(str, &endStr);	
            
            if ((errno == ERANGE && (l == DBL_MAX || l == DBL_MIN)) || (errno != 0 && l == 0)) {
                printf("Wrong entry, please try again\n");}   
            else if (endStr == str) {
                printf("Wrong entry, please try again\n");}    //on boucle
            else{
                if (quit)  
                    *(long long*)quit = 0;
                switch (t){
                    case CHAR:
                        if (l > 127 || l < -128){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(long long*)nb = (char)l;  
                            return;
                        }
                        break;
                    case UCHAR:
                        if (l > 255 || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(unsigned char*)nb = (unsigned char)l;  
                            return;
                        }
                        break;
                    case SHRT: 
                        if (l > SHRT_MAX || l < SHRT_MIN){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(short*)nb = (short)l;  
                            return;
                        }
                        break;
                   
                    case INT:
                        if (l > INT_MAX || l < INT_MIN){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(int*)nb = (int)l;  
                            return;
                        }
                        break;
                    case LONG:
                        if (l > LONG_MAX || l < LONG_MIN){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(long*)nb = (long)l;  
                            return;
                        }
                        break;
                    case LLONG:
                        if (l > LLONG_MAX || l < LLONG_MIN){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(long long*)nb = (long long)l;  
                            return;
                        }
                        break;
                    case FLT:   //il y a la précision à prendre en compte, les nombres trop petits sont traités
                        if (l > FLT_MAX || (l < FLT_MIN && l > -FLT_MIN) || l < -FLT_MAX){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(float*)nb = (float)l;  
                            return;
                        }
                        break;
                    case DBL:   //il ne peut y avoir d'erreur puisqu'on utilise strtod
                        *(double*)nb = (double)l;  
                        return;
                        break;
                    case USHRT:
                        if (l > USHRT_MAX || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(unsigned short*)nb = (unsigned short)l;  
                            return;
                        }
                        break;
                    case UINT:
                        if (l > UINT_MAX || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(unsigned int*)nb = (unsigned int)l;  
                            return;
                        }
                        break;
                    case ULONG:
                        if (l > ULONG_MAX || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(unsigned long*)nb = (unsigned long)l;  
                            return;
                        }
                        break;
                    case ULLONG:
                        if (l > ULLONG_MAX || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            *(unsigned long long*)nb = (unsigned long long)l;  
                            return;
                        }
                        break;
                    default:
                        printf("Wrong type, please try again\n");
                        break;
                }
            }	
        }
        else{
            printf("Error : unable to get the buffer, please try again\n");
        }
        printf(">>");
    }
}

//lit une certaine quantité de nombres 
//si limit vaut 0 alors c'est à l'utilisateur d'arreter la saisie en tapant sur q ou Q
//renvoi la quantité de nombres stockée
//le pointeur fourni est alloué dynamiquement. penser à le libérer.
unsigned long readNumbers(void *tab, Type t, unsigned long limit)
{
    if (tab == NULL)
    {
        printf("Error : null pointer. You have to give a dynamicaly allocated pointer\n");
        return 0;
    }
    void* transition = NULL;
    unsigned long numberOfCycle = 0;
    char *endStr, str[320];
    double l;

    limit = abs(limit); //si on met -5 on lira quand même 5 nombres
    printf(">>");
    while (1)  
    {
        if (readStr (str, 320)) 
        {
            if (limit == 0 && tolower(str[0]) == 'q'){ //si l'utilisateur veut arreter une boucle d'entrée de donnée
                return numberOfCycle;
            }
            else if (tolower(str[0]) == 'q'){
                printf("You must choose a number\n");
                continue;
            }
            errno = 0;    
            l = strtod(str, &endStr);   
            
            if ((errno == ERANGE && (l == DBL_MAX || l == DBL_MIN)) || (errno != 0 && l == 0)) {
                printf("Wrong entry, please try again\n");}   
            else if (endStr == str) {
                printf("Wrong entry, please try again\n");}    //on boucle
            else{
                switch (t){
                    case CHAR:
                        if (l > 127 || l < -128){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((char*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((char*)tab + numberOfCycle++) = (char)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    case UCHAR:
                        if (l > 255 || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((unsigned char*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((unsigned char*)tab + numberOfCycle++) = (unsigned char)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    case SHRT: 
                        if (l > SHRT_MAX || l < SHRT_MIN){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((short*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((short*)tab + numberOfCycle++) = (short)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                   
                    case INT:
                        if (l > INT_MAX || l < INT_MIN){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((int*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((int*)tab + numberOfCycle++) = (int)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    case LONG:
                        if (l > LONG_MAX || l < LONG_MIN){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((long*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((long*)tab + numberOfCycle++) = (long)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    case LLONG:
                        if (l > LLONG_MAX || l < LLONG_MIN){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((long long*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((long long*)tab + numberOfCycle++) = (long long)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    case FLT:   //il y a la précision à prendre en compte, les nombres trop petits ne sont pas traités
                        if (l > FLT_MAX || (l < FLT_MIN && l > -FLT_MIN) || l < -FLT_MAX){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((float*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((float*)tab + numberOfCycle++) = (float)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    case DBL:   //il ne peut y avoir d'erreur puisqu'on utilise strtod
                        transition = realloc((double*)tab, numberOfCycle+1);
                        if(transition != NULL){
                            tab = transition;
                            *((double*)tab + numberOfCycle++) = (double)l;
                        }
                        else{
                            printf("Error : cannot allocate more space for the pointer\n");
                            return 0;                                    
                        }
                        break;
                    case USHRT:
                        if (l > USHRT_MAX || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((unsigned short*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((unsigned short*)tab + numberOfCycle++) = (unsigned short)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    case UINT:
                        if (l > UINT_MAX || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((unsigned int*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((unsigned int*)tab + numberOfCycle++) = (unsigned int)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    case ULONG:
                        if (l > ULONG_MAX || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((unsigned long*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((unsigned long*)tab + numberOfCycle++) = (unsigned long)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    case ULLONG:
                        if (l > ULLONG_MAX || l < 0){
                            printf("Wrong entry, please try again\n");}
                        else{
                            transition = realloc((unsigned long long*)tab, numberOfCycle+1);
                            if(transition != NULL){
                                tab = transition;
                                *((unsigned long long*)tab + numberOfCycle++) = (unsigned long long)l;
                            }
                            else{
                                printf("Error : cannot allocate more space for the pointer\n");
                                return 0;                                    
                            }
                        }
                        break;
                    default:
                        printf("Wrong type, please try again\n");
                        break; 
                } 
                if(limit != 0){
                    if(--limit == 0)
                        return numberOfCycle;
                }
            }   
        }
        else{
            printf("Error : unable to get the buffer, please try again\n");
        }
        printf(">>");
    }
}

void debugPtr(void* ptr, Type t, unsigned long size){
    for (unsigned int i = 0; i < size; ++i)
    {
        switch (t){
            case CHAR:
                printf("%hhd ", *((char*)ptr+i));
                break;
            case UCHAR:
                printf("%hhu ", *((unsigned char*)ptr+i));
                break;
            case SHRT:
                printf("%hd ", *((short*)ptr+i));
                break;
            case USHRT:
                printf("%hu ", *((unsigned short*)(ptr+i)));
                break;
            case INT:
                printf("%d ", *((int*)ptr+i));
                break;
            case UINT:
                printf("%u ", *((unsigned int*)ptr+i));
                break;
            case LONG:
                printf("%ld ", *((long*)ptr+i));
                break;
            case ULONG:
                printf("%lu ", *((unsigned long*)ptr + i));
                break;
            case LLONG:
                printf("%lld ", *((long long*)ptr + i));
                break;
            case ULLONG:
                printf("%llu ", *((unsigned long long*)ptr + i));
                break;
            case FLT:   
                printf("%.2f ", *((float*)ptr + i));
                break;
            case DBL:   
                printf("%.2lf ", *((double*)ptr + i));
                break;
            default:
                printf("Wrong type given\n");
        }
    }
    printf("\n");
}