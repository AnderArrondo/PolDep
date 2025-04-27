
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "./../modules/criminal.h"
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

int get_last_inserted_id(sqlite3 *db) {
    return (int)sqlite3_last_insert_rowid(db);
}

int insertNewCrime(sqlite3 *db, Crimen crimen){

    sqlite3_stmt *stmt;

	char sqlCriminal[] = "Insert into Criminal (id, nombre, apellido, edad, genero, ciudadNacimiento, estadoCivil) values (?, ?, ?, ?, ?, ?, ?, ?)";

    int result = sqlite3_prepare_v2(db, sqlCriminal, -1, &stmt, NULL) ;

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

	//////
	int idCriminal = get_last_inserted_id(db);
    char sqlCrimen[] = "Insert into Crimen (id, anyo, descripcion, idCriminal) values (NULL, ?, ?, ?, ?)";

    result = sqlite3_prepare_v2(db, sqlCrimen, -1, &stmt, NULL) ;

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

int mostrarListaCriminales(sqlite3 *db) {
	int id, result;
	Criminal c;
	c.nombre = malloc(20 * sizeof(char));
	c.apelido = malloc(20 * sizeof(char));
	c.genero = malloc(sizeof(char));
	c.ciudadNacimiento = malloc(25 * sizeof(char));
	c.estadoCivil = malloc(15 * sizeof(char));
	sqlite3_stmt *stmt;
	
	char *sql = "SELECT * FROM Criminal;";

	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparando statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			id = sqlite3_column_int(stmt, 0);
			strcpy(c.nombre, (char *) sqlite3_column_text(stmt, 1));
			strcpy(c.apelido, (char *) sqlite3_column_text(stmt, 2));
			c.edad = sqlite3_column_int(stmt, 3);
			strcpy(c.genero, (char *) sqlite3_column_text(stmt, 4));
			strcpy(c.ciudadNacimiento, (char *) sqlite3_column_text(stmt, 5));
			strcpy(c.estadoCivil, (char *) sqlite3_column_text(stmt, 6));

			printCriminal(id, &c);
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	free(c.nombre);
	free(c.apelido);
	free(c.genero);
	free(c.ciudadNacimiento);
	free(c.estadoCivil);

	return SQLITE_OK;
}
#include <stdio.h>
#include <sqlite3.h>

int insertUsuario(sqlite3 *db, char *username, char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Usuarios (username, password) VALUES (?, ?);";
    int result;

    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando el statement: %s\n", sqlite3_errmsg(db));
        return result;
    }

    // Vincular los valores a las interrogantes (?)
    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error ejecutando el statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_finalize(stmt);

    printf("Usuario registrado correctamente en la base de datos.\n");
    return SQLITE_OK;
}
