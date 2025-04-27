
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "./../utils/utils.h"
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

int mostrarPrisionesPorEstado(sqlite3 *db, char estado[]){

	sqlite3_stmt *stmt;

	char sqlPrision[] = "select * from Prision where jurisdiccion = ?";

	int result = sqlite3_prepare_v2(db, sqlPrision, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (SELECT)\n");

	result = sqlite3_bind_text(stmt, 1, estado, strlen(estado), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	char jurisdiccion[100];
	int incluyeCarcel;
	int ainos[16];

	printf("\n");
	printf("\n");
	printf("Mostrando prisiones:\n");

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy(jurisdiccion, (char *) sqlite3_column_text(stmt, 0));
			incluyeCarcel = sqlite3_column_int(stmt, 1);

			for (int i = 0; i < 16; i++) {
                ainos[i] = sqlite3_column_int(stmt, i + 2);
            }

			printf("Jurisdiccion: %s, IncluyeCarcel: %i,\n", jurisdiccion, incluyeCarcel);
			for(int i = 0; i < 16; i++){

				printf("Año %i", ainos[i]);
			}
			
		}
	} while (result == SQLITE_ROW);

	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

	return SQLITE_OK;

}

int mostrarPrisionesPorAino(sqlite3 *db, int aino){

	sqlite3_stmt *stmt;

	char sqlPrision[256];

    if (aino < 2001 || aino > 2016) {
        printf("Año fuera de rango (2001-2016)\n");
        return SQLITE_ERROR;
    }

	sprintf(sqlPrision, "select jurisdiccion, incluyeCarcel, \"%d\" from Prision where \"%d\" > 0;", aino, aino);

	int result = sqlite3_prepare_v2(db, sqlPrision, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("SQL query prepared (SELECT)\n");

	char jurisdiccion[100];
	int incluyeCarcel;
	int valorAino;

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy(jurisdiccion, (char *) sqlite3_column_text(stmt, 0));
			incluyeCarcel = sqlite3_column_int(stmt, 1);
			valorAino =  sqlite3_column_int(stmt, 2);

			printf("Jurisdiccion: %s, IncluyeCarcel: %i, Año: %i\n", jurisdiccion, incluyeCarcel, valorAino);
		}
	} while (result == SQLITE_ROW);

	printf("\n");
	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Prepared statement finalized (SELECT)\n");

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

int mostrarDelincuenciaPorAnyo(sqlite3 *db, int anyo) {
	int result;
	sqlite3_stmt *stmt;

	char *jurisdiccion = malloc(10 * sizeof(char));
	int poblacion, nPrisionero, nCrimenViolento, nAsesinato, nViolacion, nRobo, nCrimenPropiedad;

	char *sql = "SELECT * FROM Encarcelamiento WHERE anyo = ?;";

	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(result != SQLITE_OK) {
		printf("Error preparando statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, anyo);
	if(result != SQLITE_OK) {
		printf("Error añadiendo parametros al statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	printf("%15s %15s %15s %15s %15s %15s %15s %15s\n", "JURISDICCIÓN", "POBLACIÓN",
		"PRISIONEROS", "CRIM.VIOLENTOS", "ASESINATOS", "VIOLACIONES", "ROBOS", "CRIM.PROPIEDAD");
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			strcpy(jurisdiccion, (char *) sqlite3_column_text(stmt, 0));
			nPrisionero = sqlite3_column_int(stmt, 3);
			poblacion = sqlite3_column_int(stmt, 6);
			nCrimenViolento = sqlite3_column_int(stmt, 7);
			nAsesinato = sqlite3_column_int(stmt, 8);
			nViolacion = sqlite3_column_int(stmt, 9);
			nRobo = sqlite3_column_int(stmt, 11);
			nCrimenPropiedad = sqlite3_column_int(stmt, 13);

			printf("%15s %15d %15d %15d %15d %15d %15d %15d\n", jurisdiccion, poblacion,
				nPrisionero, nCrimenViolento, nAsesinato, nViolacion, nRobo, nCrimenPropiedad);
			printf("\n");
		}
	} while(result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	free(jurisdiccion);
	jurisdiccion = NULL;

	return SQLITE_OK;
}

int mostrarDelincuenciaPorEstado(sqlite3 *db, char *estado) {
	int result;
	sqlite3_stmt *stmt;

	int anyo, poblacion, nPrisionero, nCrimenViolento, nAsesinato, nViolacion, nRobo, nCrimenPropiedad;

	char *sql = "SELECT * FROM Encarcelamiento WHERE UPPER(jurisdiccion) = UPPER(?);";

	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(result != SQLITE_OK) {
		printf("Error preparando statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, estado, -1, SQLITE_TRANSIENT);
	if(result != SQLITE_OK) {
		printf("Error añadiendo parametros al statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	printf("%5s %15s %15s %15s %15s %15s %15s %15s\n", "AÑO", "POBLACIÓN",
		"PRISIONEROS", "CRIM.VIOLENTOS", "ASESINATOS", "VIOLACIONES", "ROBOS", "CRIM.PROPIEDAD");
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			anyo = sqlite3_column_int(stmt, 2);
			nPrisionero = sqlite3_column_int(stmt, 3);
			poblacion = sqlite3_column_int(stmt, 6);
			nCrimenViolento = sqlite3_column_int(stmt, 7);
			nAsesinato = sqlite3_column_int(stmt, 8);
			nViolacion = sqlite3_column_int(stmt, 9);
			nRobo = sqlite3_column_int(stmt, 11);
			nCrimenPropiedad = sqlite3_column_int(stmt, 13);

			printf("%5d %15d %15d %15d %15d %15d %15d %15d\n", anyo, poblacion,
				nPrisionero, nCrimenViolento, nAsesinato, nViolacion, nRobo, nCrimenPropiedad);
			printf("\n");
		}
	} while(result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizando statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int informeDelincuencia(sqlite3 *db, char *estado, int anyo) {
	FILE *f;
	sqlite3_stmt *stmt;
	int result, estimacionCrimen, poblacion, nPrisionero, nAsesinato, nViolacion, nRobo, nAsalto;
	char *strAsesinato, *strViolacion, *strRobo, *strAsalto;
	char c = '#';
	char destfile[30];
	sprintf(destfile, "Inf-%s-%d.txt", estado, anyo);
	char *sql = "SELECT * FROM Encarcelamiento WHERE (UPPER(jurisdiccion) = UPPER(?)) AND (anyo = ?);";
	
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(result != SQLITE_OK) {
		printf("Error preparando statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, estado, -1, SQLITE_TRANSIENT);
	if(result != SQLITE_OK) {
		printf("Error añadiendo parametros al statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	f = fopen(destfile, "w");

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			nPrisionero = sqlite3_column_int(stmt, 3);
			estimacionCrimen = sqlite3_column_int(stmt, 5);
			poblacion = sqlite3_column_int(stmt, 6);
			nAsesinato = sqlite3_column_int(stmt, 8) / 1000;
			nViolacion = sqlite3_column_int(stmt, 9) / 1000;
			nRobo = sqlite3_column_int(stmt, 11) / 1000;
			nAsalto = sqlite3_column_int(stmt, 12) / 1000;

			strAsesinato = histStr(nAsesinato, c);
			strViolacion = histStr(nViolacion, c);
			strRobo = histStr(nRobo, c);
			strAsalto = histStr(nAsalto, c);

			fprintf(f, "===================================\n");
			fprintf(f, "      INFORME DE DELINCUENCIA      \n");
			fprintf(f, "===================================\n\n");

			fprintf(f, "DATOS GENERALES\n");
			fprintf(f, "Jurisdicción: %s\n", estado);
			fprintf(f, "Año: %d\n\n", anyo);
			fprintf(f, "Población: %d\n", poblacion);
			fprintf(f, "Estimación de crímenes: %d\n", estimacionCrimen);
			fprintf(f, "Número de prisioneros %d\n\n", nPrisionero);

			fprintf(f, "HISTOGRAMA POR TIPO DE CRIMEN\n");
			fprintf(f, "Cada '#' representan 1000 unidades.\n");
			fprintf(f, "%15s: %s\n", "ASESINATOS", strAsesinato);
			fprintf(f, "%15s: %s\n", "VIOLACIONES", strViolacion);
			fprintf(f, "%15s: %s\n", "ROBOS", strRobo);
			fprintf(f, "%15s: %s\n", "ASALTO.AGRAV", strAsalto);

			free(strAsesinato);
			strAsesinato = NULL;
			free(strViolacion);
			strViolacion = NULL;
			free(strRobo);
			strRobo = NULL;
			free(strAsalto);
			strAsalto = NULL;
		}
	} while(result == SQLITE_ROW);

	fclose(f);

	printf("Informe creado: %s\n", destfile);

	return SQLITE_OK;
}