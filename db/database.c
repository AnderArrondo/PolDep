
#include <stdio.h>
#include "sqlite3.h"
#include "./../modules/crimen.h"
#include <string.h>

#define BUFFER_SIZE 1024

int insert_data(sqlite3 *db, char *csv_line, int id) {
	int i, result, value;
	sqlite3_stmt *stmt;
	char *sql;

	if(id == 0) {
	    sql = "INSERT INTO Encarcelamiento VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, NULL, ?, ?, ?, ?, ?, ?);";
	} else {
		sql = "INSERT INTO Prision VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";
	}

	result = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if(result != SQLITE_OK) {
        fprintf(stderr, "Error preparando el statement: %s\n", sqlite3_errmsg(db));
        return result;
    }

    char *token = strtok((char *)csv_line, ",");
    for(i = 1; token != NULL; i++) {
		if(i == 1) {
			// jurisdiccion
			sqlite3_bind_text(stmt, i, token, -1, SQLITE_TRANSIENT);
		} else {
			sscanf(token, "%d", &value);
			sqlite3_bind_int(stmt, i, value);
		}
        token = strtok(NULL, ",");
    }

	result = sqlite3_step(stmt);
    if(result != SQLITE_DONE) {
        fprintf(stderr, "Error de ejecución al insertar datos: %s\n", sqlite3_errmsg(db));
		return result;
    }

    result = sqlite3_finalize(stmt);
	if(result != SQLITE_OK) {
		printf("Error finalizando el statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int csv_to_db(char **filenames, int size, sqlite3 *db) {
	int i;
	FILE *f;
	char line[BUFFER_SIZE];

	for(i = 0; i < size; i++) {
		f = fopen(filenames[i], "r");
		if (f == NULL) {
			fprintf(stderr, "No se pudo abrir el archivo: %s\n", filenames[i]);
			return -1;
		}

		// omitir header
		fgets(line, BUFFER_SIZE, f);

		while (fgets(line, BUFFER_SIZE, f)) {
			// eliminar salto de linea
			line[strcspn(line, "\n")] = 0;
			insert_data(db, line, i);
		}
		fclose(f);
	}
	return 0;
}

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