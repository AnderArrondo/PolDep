#ifndef DATABASE_H
#define DATABASE_H
#include <sqlite3.h>
#include <modules\crimen.h>


int insertNewCrime(sqlite3 *db, Crimen crimen);

#endif