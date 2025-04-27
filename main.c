#include <stdlib.h>
#include "./utils/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "./utils/utils.h"
#include "./db/database.h"
#include "../db/sqlite3.h"
#include <stdbool.h>

int main(void) {
    sqlite3 *db;
    bool dbcargada = false;

    int result = sqlite3_open("./db/data.sqlite3", &db);
    if (result != SQLITE_OK) {
        printf("Error opening database\n");
        return result;
    } else {
        dbcargada = true;
    }

    if (dbcargada == true) {
        char *filenames[2] = {
            "./data/crime_and_incarceration_by_state.csv",
            "./data/prison_custody_by_state.csv"
        };

        csv_to_db(filenames, 2, db);
    }

    // Aquí puedes poner el menú principal

    result = sqlite3_close(db);
    if (result != SQLITE_OK) {
        printf("Error closing database\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }

    return 0;
}

