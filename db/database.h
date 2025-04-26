
#include "./sqlite3.h"
#include "./../modules/crimen.h"

#ifndef DATABASE_H
#define DATABASE_H

int insertNewCrime(sqlite3 *, Crimen);
int csv_to_db(char **, int, sqlite3 *);
int mostrarListaCriminales(sqlite3 *);

#endif