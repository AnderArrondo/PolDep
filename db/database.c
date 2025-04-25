#include <stdio.h>
#include <sqlite3.h>
#include <modules\crimen.h>

int insertNewCrime(sqlite3 *db, Crimen crimen){

    sqlite3_stmt *stmt;

    char sql[] = "Insert into crime (id, nombre, apellido, edad, genero, estadoCivil, ciudadNacimiento, dni, descripcion, anioStr) values (NULL, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

    int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    printf("SQL query prepared (INSERT)\n");

    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into country table\n");
		return result;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (INSERT)\n");

	return SQLITE_OK;
}