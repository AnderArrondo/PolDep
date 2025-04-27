#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include "./../modules/crimen.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "./db/database.h"
#include "../db/sqlite3.h"

/**
 * Vacía el buffer de entrada
 */
void liberarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Pide un entrada al usuario:
 * 
 * - Si no es válida, borra la pantalla, e informa mediante un Warning.
 * - Sino cambia el valor de isValid a true.
 * 
 * Finalmente, es libera la memoria del buffer.
 */
void validarInputMenu(int maxValue, int *opcionElegida, bool *isValid) {
    printf("Elija una opción: ");
    if(scanf("%i", opcionElegida) != 1) {
        system("cls");
        printf("\n[ WARNING ] Tipo de dato inválido:\nDebes introducir un entero entre [1, %i]\n\n", maxValue);
    } else if(maxValue < *opcionElegida || *opcionElegida < 1) {
        system("cls");
        printf("\n[ WARNING ] Valor fuera de límites.\nDebes introducir un entero entre [1, %i]\n\n", maxValue);
    } else {
        printf("\n");
        *isValid = true;
    }
    liberarBuffer();
}

void menuadministrar(int opcion){ //CAMBIAR EL FORMATO AL FORMTAO 2 DE WASSAP
    printf("----------------------\n");
    printf("ADMINISTRAR USUARIOS\n");
    printf("----------------------\n");
    printf("1) Ver todos los usuarios\n");
    printf("2) Agregar nuevo usuario\n");
    printf("3) Eliminar usuario\n");
    printf("4) Modificar usuario\n");
    printf("----------------------\n");
    printf("Selecione una opcion: ");
}

void seleccion(int opcion) { // INT OPCION UN PUNTERO, ANTES DE LOS IF HAYQ UE PONER UN BUCLE PARA PEDIRLE LOS DATOS HASTA QUE SEAN CORRECTOS,
                            // EN MENU REGUSTRO EJEMPLO DE ESO Y OPCION ESTADISTICAS EL COMO HACERLO, 
    if (opcion == 1) {
        
    } else if (opcion == 2) {

    } else if (opcion == 3) {
        
    } else if (opcion == 4) {
        
    } else {
        printf("Selecciona una opción válida\n");
    }
}


void menuRegistro(){
    //Creada la funcion de la base de datos pero no la tabala de la base de datos
   char username[100];
    char password[100];

    printf("Ingrese su nombre de usuario: ");
    scanf("%s", username);

    printf("Ingrese su contraseña: ");
    scanf("%s", password);

 

    
}

Crimen registrarCrimen() {
    printf("=========================================================\n");
    printf("                   REGISTRO DE CRIMEN                   \n");
    printf("=========================================================\n");

   
    char *nombre = (char *)malloc(100);
    char *apellido = (char *)malloc(100);
    int *edad = (int *)malloc(sizeof(int));
    char *genero = (char *)malloc(20);
    char *estadoCivil = (char *)malloc(20);
    char *ciudadNacimiento = (char *)malloc(100);
    char *dni = (char *)malloc(20);
    char *descripcion = (char *)malloc(200);
    char *anioStr = (char *)malloc(5);

    
    printf("Ingrese el nombre: ");
    scanf("%s", nombre);

    printf("Ingrese el apellido: ");
    scanf("%s", apellido);

    printf("Ingrese la edad: ");
    scanf("%d", edad);

    printf("Ingrese el género: ");
    scanf("%s", genero);

    printf("Ingrese el estado civil: ");
    scanf("%s", estadoCivil);

    printf("Ingrese la ciudad de nacimiento: ");
    scanf("%s", ciudadNacimiento);

    printf("Ingrese el DNI: ");
    scanf("%s", dni);

    printf("Ingrese la descripción del crimen: ");
    scanf("%s", descripcion);

    printf("Ingrese el año del crimen: ");
    scanf("%s", anioStr);

   
    Criminal *c = malloc(sizeof(Criminal));
    c->nombre = strdup(nombre);
    c->apelido = strdup(apellido);
    c->edad = *edad;
    c->genero = strdup(genero);
    c->estadoCivil = strdup(estadoCivil);
    c->ciudadNacimiento = strdup(ciudadNacimiento);

    Crimen crimen;
    crimen.autor = c;
    crimen.dni = strdup(dni);
    crimen.descripcion = strdup(descripcion);
    crimen.aino = atoi(anioStr);

    
    free(nombre);
    free(apellido);
    free(edad);
    free(genero);
    free(estadoCivil);
    free(ciudadNacimiento);
    free(dni);
    free(descripcion);
    free(anioStr);
    

    return crimen;
}
 


/**
 * Imprime el título y las opciones a elegir sobre estadísticas de criminalidad
 */
void printMenuEstadisticas() {
    printf("==================================\n");
    printf("#  ESTADÍSTICAS DE CRIMINALIDAD  #\n");
    printf("==================================\n");
    printf("1) Lista de criminales\n");
    printf("2) Información sobre prisiones\n");
    printf("3) Información sobre delincuencia\n");
    printf("4) Salir\n");
}

/**
 * Inicia un bucle que acaba cuando opcionElegida tenga un valor válido.
 */
void opcionEstadisticas(int *opcionElegida) {
    bool isValid = false;
    int maxVal = 4;

    while(!isValid) {
        printMenuEstadisticas();
        validarInputMenu(maxVal, opcionElegida, &isValid);
    }

    if(*opcionElegida == 1) {
        // Lista de criminales
    } else if(*opcionElegida == 2) {
        // Información sobre prisioneros
    } else if(*opcionElegida == 3) {
        // Información sobre delincuencia
    } else {
        // salir
    }
}

void menu() {
    sqlite3 *db;
    bool dbcargada = false;

    int result = sqlite3_open("./db/data.sqlite3", &db);
    if (result != SQLITE_OK) {
        printf("Error opening database\n");
        return result;
    } else {
        dbcargada = true;
    }

    if (dbcargada) {
        char *filenames[2] = {
            "./data/crime_and_incarceration_by_state.csv",
            "./data/prison_custody_by_state.csv"
        };
        csv_to_db(filenames, 2, db);
    }
    menuRegistro();
    int opcion = 0;
    bool opcionValida = false;
    int maxValor = 4;

    while (opcion != 4) {
        opcionValida = false;

        while (!opcionValida) {
            printf("=========================================================\n");
            printf("                    POLICIA DEUSTO                       \n");
            printf("=========================================================\n");
            printf("Seleccione una de estas opciones:\n");
            printf("1 - Administrar datos policia\n");
            printf("2 - Añadir crimen\n");
            printf("3 - Visualizar estadisticas\n");
            printf("4 - Salir\n");
            printf("----------------------\n");
            scanf("%d", &opcion);

            if (opcion >= 1 && opcion <= maxValor) {
                opcionValida = true;
            } else {
                printf("Opcion no valida. Intentelo de nuevo\n");
            }
        }

        if (opcion == 1) {
            printf("Administración de datos\n");
            

        } else if (opcion == 2) {
            printf("Agregar crimen\n");
            Crimen crimenInsertar = registrarCrimen();
            insertNewCrime(db, crimenInsertar);

        } else if (opcion == 3) {
            printf("Visualización de estadísticas\n");

        } else if (opcion == 4) {
            printf("Salir\n");
            
        }
    }

    result = sqlite3_close(db);
    if (result != SQLITE_OK) {
        printf("Error closing database\n");
        printf("%s\n", sqlite3_errmsg(db));
    }

    return;
}
