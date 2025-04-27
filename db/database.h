
#include "./sqlite3.h"
#include "./../modules/crimen.h"

#ifndef DATABASE_H
#define DATABASE_H

int get_last_inserted_id(sqlite3 *db);
int insertNewCrime(sqlite3 *, Crimen);

int mostrarPrisionesPorEstado(sqlite3 *db, char *estado);
int mostrarPrisionesPorAino(sqlite3 *db, int aino);

int csv_to_db(char **, int, sqlite3 *);

int mostrarListaCriminales(sqlite3 *);
int mostrarDelincuenciaPorAnyo(sqlite3 *, int);
int mostrarDelincuenciaPorEstado(sqlite3 *, char *);
int informeDelincuencia(sqlite3 *, char *, int);


#endif
