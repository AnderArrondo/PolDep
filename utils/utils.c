#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include "./../modules/crimen.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "./../db/database.h"
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


// void menuadministrar(int opcion){ //CAMBIAR EL FORMATO AL FORMTAO 2 DE WASSAP
//     printf("=========================================================\n");
//     printf("                    ADMINISTRAR USUARIOS                 \n");
//     printf("=========================================================\n");
//     printf("1. Ver todos los usuarios\n");
//     printf("2. Agregar nuevo usuario\n");
//     printf("3. Eliminar usuario\n");
//     printf("4. Modificar usuario\n");
//     printf("----------------------\n");
//     printf("Selecione una opcion: ");
// }

void seleccion(sqlite3 *db) {
    int opcion = 0;
    bool salir = false;
    int maxValor = 4;

    while (!salir) {
        bool opcionValida = false;
        while (!opcionValida) {
            printf("=========================================================\n");
            printf("                 ADMINISTRAR USUARIOS                    \n");
            printf("=========================================================\n");
            printf("1. Ver todos los usuarios\n");
            printf("2. Agregar nuevo usuario\n");
            printf("3. Eliminar usuario\n");
            printf("4. Salir del menú\n");
            printf("---------------------------------------------------------\n");
            validarInputMenu(maxValor, &opcion, &opcionValida);
        }

        system("cls");

        switch (opcion) {
            case 1:
                mostrarUsuarios(db);
                break;
            case 2:
                menuRegistro(db);
                break;
            case 3:
                eliminarUsuario(db);
                break;
            default:
                salir = true;
                break;
        }

        if (!salir) {
            printf("\nPresione Enter para continuar...");
            liberarBuffer();
            system("cls");
        }
    }
}





void menuRegistro(sqlite3 *db){
    //Creada la funcion de la base de datos pero no la tabala de la base de datos
    char dni[100];
    char username[100];
    char password[100];

    printf("Ingrese su dni: ");
    scanf("%s", dni);

    printf("Ingrese su nombre de usuario: ");
    scanf("%s", username);

    printf("Ingrese su contraseña: ");
    scanf("%s", password);

    insertUsuario(db, dni, username, password);
}




void printMenuPrisioneros(){ //no estiendo esto para que es

    printf("=========================================================\n");
    printf("                   ESTADISTICAS DE PRISIONEROS                   \n");
    printf("=========================================================\n");
    printf("1- Mostrar prisiones por estado.\n");
    printf("2- Mostrar prisiones por año.\n");
    printf("3. Salir.\n");
}

void opcionPrisioneros(int *opcion, sqlite3 *db){

    bool isValid = false;
    bool salir = false;
    int maxValue = 3;
    printf("Seleccione una opcion: \n");


    while(!salir){
        isValid = false;
        while(!isValid){
            printMenuPrisioneros();
            validarInputMenu(maxValue, opcion, &isValid);
        }

        system("cls");

        if(*opcion == 1){
            printf("Inserta un estado: ");
            char estado[100];
            fgets(estado, 100, stdin);
            system("cls");
            mostrarPrisionesPorEstado(db, estado);
        } else if(*opcion == 2){

            printf("Inserta un año: ");
            int aino;
            scanf("%i", &aino);
            system("cls");
            mostrarPrisionesPorAino(db, aino);
            liberarBuffer();
        } else {
            salir = true;
        }

        if(!salir) {
            printf("\nPresione Enter para continuar...");
            liberarBuffer();
            system("cls");
        }
    }
}

void registrarCrimen(sqlite3 *db) {
    printf("=========================================================\n");
    printf("                   REGISTRO DE CRIMEN                   \n");
    printf("=========================================================\n");

   
    char *nombre = (char *)malloc(100 * sizeof(char));
    char *apellido = (char *)malloc(100 * sizeof(char));
    int *edad = (int *)malloc(sizeof(int));
    char *genero = (char *)malloc(20 * sizeof(char));
    char *estadoCivil = (char *)malloc(20 * sizeof(char));
    char *ciudadNacimiento = (char *)malloc(100 * sizeof(char));
    char *dni = (char *)malloc(20 * sizeof(char));
    char *descripcion = (char *)malloc(200 * sizeof(char));
    int *anio = (int *)malloc(sizeof(int));

   
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
    scanf("%d", anio);

    
    Criminal *c = (Criminal *)malloc(sizeof(Criminal));
    if (!c) {
        printf("Error reservando memoria para el Criminal.\n");
        exit(EXIT_FAILURE);
    }

    c->nombre = nombre;
    c->apellido = apellido;
    c->edad = *edad;
    c->genero = genero;
    c->estadoCivil = estadoCivil;
    c->ciudadNacimiento = ciudadNacimiento;

    Crimen crimen;
    crimen.autor = c;
    crimen.dni = dni;
    crimen.descripcion = descripcion;
    crimen.aino = *anio;

    
    insertNewCrime(db, crimen); //lo meto mejor directamente en la base de datos que desde el main


   
   //libero la memoria 
    free(nombre);
    free(apellido);
    free(apellido);
    free(genero);
    free(estadoCivil);
    free(ciudadNacimiento);
    free(dni);
    free(descripcion);
    free(edad);
    free(anio);
    free(c);

    printf("\nPresione Enter para continuar...");
    liberarBuffer();
}




void printMenuEstadisticas() {
    
    printf("=========================================================\n");
    printf("              ESTADÍSTICAS DE CRIMINALIDAD               \n");
    printf("=========================================================\n");
    printf("1- Lista de criminales\n");
    printf("2- Información sobre prisiones\n");
    printf("3- Información sobre delincuencia\n");
    printf("4- Salir\n");
    printf("----------------------\n");
}


void printMenuDelincuencia() {
    
    printf("=========================================================\n");
    printf("              ESTADÍSTICAS DE DELINCUENCIA               \n");
    printf("=========================================================\n");
    printf("1- Datos por estado\n");
    printf("2- Datos por año\n");
    printf("3- Informe de delincuencia\n");
    printf("4- Salir\n");
    printf("----------------------\n");
}

void opcionDelincuencia(int *opcionElegida, sqlite3 *db) {
    bool isValid = false;
    bool salir = false;
    int maxVal = 4;

    while(!salir) {
        isValid = false;
        while(!isValid) {
            printMenuDelincuencia();
            validarInputMenu(maxVal, opcionElegida, &isValid);
        }

        system("cls");

        if(*opcionElegida == 1) {
            // Datos por estado
            char estado[100];

            printf("Introduzca un estado: ");
            fgets(estado, 100, stdin);
            printf("\n");
            mostrarDelincuenciaPorEstado(db, estado);
        } else if(*opcionElegida == 2) {
            // Datos por año
            int anyo;
            printf("Introduzca un año: ");
            scanf("%i", &anyo);
            printf("\n");
            mostrarDelincuenciaPorAnyo(db, anyo);
            liberarBuffer();
        } else if(*opcionElegida == 3) {
            // Informe de delincuencia
            int anyo;
            char estado[100];

            printf("Introduzca un estado: ");
            fgets(estado, 100, stdin);
            printf("\n");

            printf("Introduzca un año: ");
            scanf("%i", &anyo);
            printf("\n");
            liberarBuffer();

            informeDelincuencia(db, estado, anyo);
        } else {
            // salir
            salir = true;
        }

        if(!salir) {
            printf("\nPresione Enter para continuar...");
            liberarBuffer();
            system("cls");
        }
    }
}


void opcionEstadisticas(int *opcionElegida, sqlite3 *db) {
    bool isValid;
    bool salir = false;
    int maxVal = 4;

    while(!salir) {
        isValid = false;
        while(!isValid) {
            printMenuEstadisticas();
            validarInputMenu(maxVal, opcionElegida, &isValid);
        }

        system("cls");
    
        if(*opcionElegida == 1) {
            // Lista de criminales
            mostrarListaCriminales(db);

            printf("\nPresione Enter para continuar...");
            liberarBuffer();
            system("cls");
        } else if(*opcionElegida == 2) {
            // Información sobre prisioneros
            opcionPrisioneros(opcionElegida, db);
        } else if(*opcionElegida == 3) {
            // Información sobre delincuencia
            opcionDelincuencia(opcionElegida, db);
        } else {
            // salir
            salir = true;
        }
    }
}

void iniciarsesion(sqlite3 *db){
    bool encontrado = false;
    char username[100];
    char password[100];

    while (encontrado == false) {
        printf("=========================================================\n");
        printf("                    POLICIA DEUSTO                       \n");
        printf("=========================================================\n");

        printf("Ingrese su nombre de usuario: ");
        scanf("%s", username);

        printf("Ingrese su contraseña: ");
        scanf("%s", password);

        if (verificarPolicia(db, username, password) == true) {
            encontrado = true; 
        } else {
            printf("Usuario no existente, vuelva a intentarlo.\n");
        }

        system("cls");
    }

   printf("Usuario existente.\n\n");
}


void menu() {
    sqlite3 *db;
    bool dbcargada = false;

    system("cls");

    int result = sqlite3_open("./db/data.sqlite3", &db);
    if (result != SQLITE_OK) {
        printf("Error opening database\n");
        return;  
    } 

    if (dbcargada) {
        char *filenames[2] = {
            "./data/crime_and_incarceration_by_state.csv",
            "./data/prison_custody_by_state.csv"
        };
        csv_to_db(filenames, 2, db);
    }

    iniciarsesion(db); // no dejara avanzar hasta que salga del bucle

    int opcion = 0;
    bool opcionValida = false;
    bool salir = false;
    int maxValor = 4;

    while (!salir) {
        opcionValida = false;

        while (!opcionValida) {
            printf("=========================================================\n");
            printf("                    POLICIA DEUSTO                       \n");
            printf("=========================================================\n");
            printf("Seleccione una de estas opciones:\n");
            printf("1 - Administrar datos policia\n");
            printf("2 - Añadir crimen\n");
            printf("3 - Visualizar estadísticas\n");
            printf("4 - Salir\n");
            printf("----------------------\n");

            validarInputMenu(maxValor, &opcion, &opcionValida);
        }

        system("cls");

        if (opcion == 1) {
            printf("Administración de datos\n");
            seleccion(db);

        } else if (opcion == 2) {
            printf("Agregar crimen\n");
            registrarCrimen(db);
           

        } else if (opcion == 3) {
            printf("Visualización de estadísticas\n");
            opcionEstadisticas(&opcion,db);
        } else {
            salir = true;
        }
    }

    result = sqlite3_close(db);
    if (result != SQLITE_OK) {
        printf("Error cerrando la base de datos\n");
        printf("%s\n", sqlite3_errmsg(db));
    }

    system("cls");
    return;
}

char *histStr(int n, char c) {
    int i;
    char *result;

    if(n <= 0) {
        result = malloc(sizeof(char));
        result[0] = '\0';
        return result;
    }

    result = malloc((n + 1) * sizeof(char));
    for(i = 0; i < n; i++) {
        result[i] = c;
    }
    result[n] = '\0';

    return result;
}

