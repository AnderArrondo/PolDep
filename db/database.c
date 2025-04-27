
#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "./../utils/utils.h"
#include "./../modules/criminal.h"
#include "./../modules/crimen.h"
#include <string.h>
#include <stdbool.h>

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

	char sqlCriminal[] = "Insert into Criminal (nombre, apellido, edad, genero, ciudadNacimiento, estadoCivil) values (?, ?, ?, ?, ?, ?)";

    int result = sqlite3_prepare_v2(db, sqlCriminal, -1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	char *nombre = crimen.autor->nombre;
	result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	char *apellido = crimen.autor->apellido;
	result = sqlite3_bind_text(stmt, 2, apellido, strlen(apellido), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int edad = crimen.autor->edad;
	result = sqlite3_bind_int(stmt, 3, edad);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	char *genero = crimen.autor->genero;
	result = sqlite3_bind_text(stmt, 4, genero, strlen(genero), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	char *ciudadDeNacimiento = crimen.autor->ciudadNacimiento;
	result = sqlite3_bind_text(stmt, 5, ciudadDeNacimiento, strlen(ciudadDeNacimiento), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	char *estadoCivil = crimen.autor->estadoCivil;
	result = sqlite3_bind_text(stmt, 6, estadoCivil, strlen(estadoCivil), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into Criminal table\n");
		return result;
	}

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	//////
	
    char sqlCrimen[] = "Insert into Crimen (anyo, descripcion, idCriminal) values (?, ?, ?)";

    result = sqlite3_prepare_v2(db, sqlCrimen, -1, &stmt, NULL) ;

    if (result != SQLITE_OK) {
		printf("Error preparing statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    printf("SQL query prepared (INSERT)\n");

	int aino = crimen.aino;
	result = sqlite3_bind_int(stmt, 1, aino);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	char *descripcion = crimen.descripcion;
	result = sqlite3_bind_text(stmt, 2, descripcion, strlen(descripcion), SQLITE_TRANSIENT);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	int idCriminal = get_last_inserted_id(db);
	result = sqlite3_bind_int(stmt, 3, idCriminal);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error inserting new data into Crimen table\n");
		printf("%s\n", sqlite3_errmsg(db));
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

	char sqlPrision[] = "SELECT * FROM Prision WHERE UPPER(jurisdiccion) = UPPER(?);";

	int result = sqlite3_prepare_v2(db, sqlPrision, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, estado, strlen(estado) - 1, SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	char jurisdiccion[100];
	int incluyeCarcel;
	int ainos[16];

	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy(jurisdiccion, (char *) sqlite3_column_text(stmt, 0));
			incluyeCarcel = sqlite3_column_int(stmt, 1);

			for (int i = 0; i < 16; i++) {
                ainos[i] = sqlite3_column_int(stmt, i + 2);
            }

			printf("JURISDICCIÓN: %s\nINCLUYE CÁRCEL: %i\n\n", jurisdiccion, incluyeCarcel);

			printf("NÚMERO DE PRISIONEROS POR AÑOS:\n");
			for(int i = 2001; i < 2017; i++){
				printf("%7i", i);
			}
			printf("\n");
			for(int i = 0; i < 16; i++){
				printf("%7i", ainos[i]);
			}
			
		}
	} while (result == SQLITE_ROW);

	printf("\n");

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int mostrarPrisionesPorAino(sqlite3 *db, int aino){

	sqlite3_stmt *stmt;

	char sqlPrision[256];

    if (aino < 2001 || aino > 2016) {
        printf("Año fuera de rango (2001-2016)\n");
        return SQLITE_ERROR;
    }

	sprintf(sqlPrision, "select jurisdiccion, incluyeCarcel, \"%d\" from Prision;", aino);

	int result = sqlite3_prepare_v2(db, sqlPrision, -1, &stmt, NULL) ;
	if (result != SQLITE_OK) {
		printf("Error preparing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	char jurisdiccion[100];
	int incluyeCarcel;
	int valorAino;
	printf("%30s %16s %14s\n", "JURISDICCIÓN", "INCLUYE CÁRCEL", "PRISIONEROS");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			strcpy(jurisdiccion, (char *) sqlite3_column_text(stmt, 0));
			incluyeCarcel = sqlite3_column_int(stmt, 1);
			valorAino =  sqlite3_column_int(stmt, 2);

			printf("%30s %16i %14i\n", jurisdiccion, incluyeCarcel, valorAino);
		}
	} while (result == SQLITE_ROW);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	return SQLITE_OK;
}

int mostrarListaCriminales(sqlite3 *db) {
	int id, result;
	Criminal c;
	c.nombre = malloc(20 * sizeof(char));
	c.apellido = malloc(20 * sizeof(char));
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
			strcpy(c.apellido, (char *) sqlite3_column_text(stmt, 2));
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
	free(c.apellido);
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
	printf("%16s %16s %16s %16s %16s %16s %16s %16s\n", "JURISDICCIÓN", "POBLACIÓN",
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

			printf("%16s %16d %16d %16d %16d %16d %16d %16d\n", jurisdiccion, poblacion,
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
	estado[strlen(estado)-1] = '\0';
	printf("%s, %d", estado, strlen(estado));
	sprintf(destfile, "Inf-%s-%d.txt", estado, anyo);
	char *sql = "SELECT * FROM Encarcelamiento WHERE (UPPER(jurisdiccion) = UPPER(?)) AND (anyo = ?);";
	
	result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if(result != SQLITE_OK) {
		printf("Error preparando statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, estado, strlen(estado), SQLITE_STATIC);
	if(result != SQLITE_OK) {
		printf("Error añadiendo parametros al statement 1 (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, anyo);
	if(result != SQLITE_OK) {
		printf("Error añadiendo parametros al statement (SELECT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	printf("Abriendo fichero...\n");
	f = fopen(destfile, "w");
	if(f == NULL) {
		printf("No se pudo abrir el fichero '%s'\n", destfile);
	} else {
		printf("Escribiendo en fichero...\n");

		do {
			result = sqlite3_step(stmt);
			if (result == SQLITE_ROW) {
				printf("Aqui\n");
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
	
		printf("Cerrando fichero...\n");
		fclose(f);
	
		printf("Informe creado: %s\n", destfile);
	}

	return SQLITE_OK;
}

int insertUsuario(sqlite3 *db, char *dni, char *username, char *password) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO Policia (dni, nombre, contraseña) VALUES (?, ?, ?);";
    int result;

    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando el statement: %s\n", sqlite3_errmsg(db));
        return result;
    }

	result = sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
	if(result != SQLITE_OK) {
		printf("Error añadiendo parametros al statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
    sqlite3_bind_text(stmt, 2, username, -1, SQLITE_STATIC);
	if(result != SQLITE_OK) {
		printf("Error añadiendo parametros al statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
    sqlite3_bind_text(stmt, 3, password, -1, SQLITE_STATIC);
	if(result != SQLITE_OK) {
		printf("Error añadiendo parametros al statement (INSERT)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error ejecutando el statement: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
        printf("Error finalizando el statement: %s\n", sqlite3_errmsg(db));
        return result;
    }

    printf("Usuario registrado correctamente en la base de datos.\n");
    return SQLITE_OK;
}


void mostrarUsuarios(sqlite3 *db) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT dni, nombre FROM Policia;";
    int result;

    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando el statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\nLista de usuarios registrados:\n");
    printf("------------------------------\n");

    while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *username = sqlite3_column_text(stmt, 1);

        printf("ID: %d | Usuario: %s\n", id, username);
    }

    if (result != SQLITE_DONE) {
        printf("Error al iterar sobre los resultados: %s\n", sqlite3_errmsg(db));
    }

    result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
        printf("Error finalizando el statement: %s\n", sqlite3_errmsg(db));
        return;
    }
}

void eliminarUsuario(sqlite3 *db) {
    sqlite3_stmt *stmt;
    char username[50];
    const char *sql = "DELETE FROM Policia WHERE nombre = ?;";
    int result;

    printf("Introduce el nombre de usuario que quieres eliminar: ");
    scanf("%s", username);

    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando el statement: %s\n", sqlite3_errmsg(db));
        return;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error ejecutando el statement: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Usuario '%s' eliminado correctamente.\n", username);
    }

    sqlite3_finalize(stmt);
}

void modificarUsuario(sqlite3 *db) {

}

bool verificarPolicia(sqlite3 *db, const char *nombre, const char *contrasena) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT COUNT(*) FROM Policia WHERE nombre = ? AND contraseña = ?;";
    int result;

    result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando statement: %s\n", sqlite3_errmsg(db));
        return false;
    }

    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, contrasena, -1, SQLITE_STATIC);
    result = sqlite3_step(stmt);
    if (result == SQLITE_ROW) {
        int count = sqlite3_column_int(stmt, 0);

        sqlite3_finalize(stmt);

        if (count > 0) {
            return true;   // existe esntoces true
        } else {
            return false;  // sino se encuetra false
        }
    } else {
        printf("Error ejecutando consulta: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    return false; //por si surgue algun erro en la bdd
}
