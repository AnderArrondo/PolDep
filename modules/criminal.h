
#ifndef CRIMINAL_H
#define CRIMINAL_H
typedef struct{
    char *nombre;
    char *apellido;
    int edad;
    char *genero;
    char *ciudadNacimiento;
    char *estadoCivil;
} Criminal;

void printCriminal(int id, Criminal *);

#endif