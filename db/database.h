
#include "./sqlite3.h"
#include "./../modules/crimen.h"

#ifndef DATABASE_H
#define DATABASE_H

int get_last_inserted_id(sqlite3 *db);
int insertNewCrime(sqlite3 *, Crimen);
int csv_to_db(char **, int, sqlite3 *);

#endif