
#include "./../modules/crimen.h"
#include "./../db/sqlite3.h"
#include <stdbool.h>

#ifndef UTILS_H
#define UTILS_H

void menu();
void seleccion(sqlite3 *db);
void printMenuRegistro();
void printMenuBD();
<<<<<<< HEAD
void bdMenuRegistro(int *opcion, sqlite3 *db);
void opcionEstadisticas(int *, sqlite3 *db);
=======
void bdMenuRegistro(int *opcion);
>>>>>>> 2db39bcf79dd0e5abf2b4ea109e7b4d837b53bfc
char *histStr(int, char);
void menuRegistro();
void registrarCrimen(sqlite3 *db);
void opcionEstadisticas(int *, sqlite3 *db);
void menuRegistro(sqlite3 *db);
void printMenuDelincuencia() ;
void printMenuEstadisticas();
bool iniciarsesion(sqlite3 *db);
#endif