
#include "./../modules/crimen.h"
#include "./../db/sqlite3.h"

#ifndef UTILS_H
#define UTILS_H

void menu();
void seleccion(int opcion);
void printMenuRegistro();
void menuRegistro();
void printMenuBD();
void bdMenuRegistro(int *opcion, sqlite3 *db);
void opcionEstadisticas(int *, sqlite3 *db);
char *histStr(int, char);
void menuRegistro();
void registrarCrimen(sqlite3 *db);
void opcionEstadisticas(int *, sqlite3 db);
void menuRegistro(db);

#endif