
#include "./../modules/crimen.h"
#include "./../db/sqlite3.h"
#include <stdbool.h>

#ifndef UTILS_H
#define UTILS_H

void menu();
void seleccion(sqlite3 *db);
void printMenuRegistro();
void printMenuBD();
void opcionPrisioneros(int *opcion, sqlite3 *db);
char *histStr(int, char);
void menuRegistro();
void registrarCrimen(sqlite3 *db);
void opcionEstadisticas(int *, sqlite3 *db);
void menuRegistro(sqlite3 *db);
void printMenuDelincuencia() ;
void printMenuEstadisticas();
void iniciarsesion(sqlite3 *db);
#endif