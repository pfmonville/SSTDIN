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
int readStr(char *input, unsigned long size);
void readInt(int *nb);
void readNumber(void *nb, Type t, void* quit);
unsigned long readNumbers(void* tab, Type t, unsigned long limit);
void debugList(void* list, Type t, unsigned long size);


#endif
