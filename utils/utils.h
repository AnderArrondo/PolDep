
#include "./../modules/crimen.h"

#ifndef UTILS_H
#define UTILS_H

void menu();
void seleccion(int opcion);
void printMenuRegistro();
void menuRegistro();
void printMenuBD();
void bdMenuRegistro(int *opcion);
void menuRegistro();
Crimen registrarCrimen();
void opcionEstadisticas(int *, sqlite3 db);

#endif