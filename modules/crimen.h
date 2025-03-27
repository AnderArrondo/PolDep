#ifndef CRIMEN_H
#define CRIMEN_H
#include "criminal.h"

typedef struct{

    Criminal *autor;
    char *dni;
    char *descripcion;
    int aino;

} Crimen;

#endif