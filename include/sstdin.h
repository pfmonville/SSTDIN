#ifndef SSTDIN
#define SSTDIN

typedef enum { 
    CHAR,
    UCHAR,
    SHRT,
    USHRT,
    INT,
    UINT,
    LONG,
    LLONG,
    ULONG,
    ULLONG,
    FLT,
    DBL
} Type;

void clearBuffer();
int readStr(char *saisie, int longueur);
void readInt(int *nb);
void readNumber(void *nb, Type t, char* quit);
unsigned long readNumbers(void* tab, Type t, unsigned long limit);
void debugPtr(void* ptr, Type t, unsigned long size);


#endif
