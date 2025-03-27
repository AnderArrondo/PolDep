#ifndef CRIMINAL_H
#define CRIMINAL_H
#include "crimen.h"

typedef struct{

    char *nombre;
    char *apelido;
    int edad;
    char *genero;
    char *ciudadNacimiento;
    Crimen *historialCrimenes;
    char *estadoCivil;
} Criminal;

#endif