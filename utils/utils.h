
#include "./../modules/crimen.h"

#ifndef UTILS_H
#define UTILS_H

void menu();
void seleccion(int opcion);
void printMenuRegistro();
void menuRegistro(int *);
void printMenuBD();
void bdMenuRegistro(int *opcion);
Crimen registrarCrimen();
void opcionEstadisticas(int *);

#endif