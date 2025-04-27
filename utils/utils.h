
#include "./../modules/crimen.h"
#include "./../db/sqlite3.h"

#ifndef UTILS_H
#define UTILS_H

void menu();
void seleccion(int opcion);
void printMenuRegistro();
void menuRegistro(int *);
void printMenuBD();
void bdMenuRegistro(int *opcion);
Crimen registrarCrimen();
void opcionEstadisticas(int *, sqlite3 *db);
char *histStr(int, char);

#endif