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

// INT OPCION UN PUNTERO, ANTES DE LOS IF HAYQ UE PONER UN BUCLE PARA PEDIRLE LOS DATOS HASTA QUE SEAN CORRECTOS,
// EN MENU REGUSTRO EJEMPLO DE ESO Y OPCION ESTADISTICAS EL COMO HACERLO, 
void seleccion(sqlite3 *db) {
    int opcion = 0;
    bool opcionValida = false;
    int maxValor = 4;

    while (!opcionValida) {
        printf("=========================================================\n");
        printf("                 ADMINISTRAR USUARIOS                    \n");
        printf("=========================================================\n");
        printf("1. Ver todos los usuarios\n");
        printf("2. Agregar nuevo usuario\n");
        printf("3. Eliminar usuario\n");
        printf("4. Modificar usuario\n");
        printf("----------------------\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        validarInputMenu(maxValor, &opcion, &opcionValida);
    }

    if (opcion == 1) {
        printf("Mostrando todos los usuarios...\n");
        mostrarUsuarios(db); //ESTA FUNCION HAY QUE HACERLA
    } 
    else if (opcion == 2) {
        printf("Agregando nuevo usuario...\n");
        menuRegistro(db); 
    } 
    else if (opcion == 3) {
        printf("Eliminando un usuario...\n");
        eliminarUsuario(db); //ESTA FUNCION HAY QUE HACERLA
    } 
    else if (opcion == 4) {
        printf("Modificando un usuario...\n");
        modificarUsuario(db); //ESTA FUNCION HAY QUE HACERLA
    } 
    else {
        printf("Selecciona una opción válida.\n");
    }
}

void mostrarUsuarios(sqlite3 *db) {

}

void eliminarUsuario(sqlite3 *db) {

}

void modificarUsuario(sqlite3 *db) {

}


void menuRegistro(db){
    //Creada la funcion de la base de datos pero no la tabala de la base de datos
    char username[100];
    char password[100];
    printf("Ingrese su nombre de usuario: ");
    scanf("%s", username);

    printf("Ingrese su contraseña: ");
    scanf("%s", password);

    insertUsuario( db, username, password);
}




void printMenuBD(){ //no estiendo esto para que es

    printf("=========================================================\n");
    printf("                   ESTADISTICAS DE PRISIONEROS                   \n");
    printf("=========================================================\n");
    printf("1- Mostrar prisiones por estado.\n");
    printf("2- Mostrar prisiones por año.\n");
    printf("3. Salir.\n");
}

void bdMenuRegistro(int *opcion){

    bool seguir = false;
    int maxValue = 3;
    printf("Seleccione una opcion: \n");

    while(seguir == false){

        printMenuRegistro();
        scanf("%i", opcion);
        validarInputMenu(maxValue, opcion, &seguir);
    }


    while(seguir == true){

        if(*opcion == 1){

            //metodo de mostrar prisiones por estado
        }
        else if(*opcion == 2){

            //metodo de mostrar prisiones por año
        }
        else if(*opcion == 3){

            seguir = false;
        }

        printMenuRegistro();
        scanf("%i", opcion);
        validarInputMenu(maxValue, opcion, &seguir);
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
    if (crimen.autor != NULL) {
        if (crimen.autor->nombre) free(crimen.autor->nombre);
        if (crimen.autor->apellido) free(crimen.autor->apellido);
        if (crimen.autor->genero) free(crimen.autor->genero);
        if (crimen.autor->estadoCivil) free(crimen.autor->estadoCivil);
        if (crimen.autor->ciudadNacimiento) free(crimen.autor->ciudadNacimiento);
        free(crimen.autor);
    }

    if (crimen.dni) free(crimen.dni);
    if (crimen.descripcion) free(crimen.descripcion);
    free(edad);
    free(anio);
}




int printMenuEstadisticas() {
    int opcion;
    printf("=========================================================\n");
    printf("              ESTADÍSTICAS DE CRIMINALIDAD               \n");
    printf("=========================================================\n");
    printf("1- Lista de criminales\n");
    printf("2- Información sobre prisiones\n");
    printf("3- Información sobre delincuencia\n");
    printf("4- Salir\n");
    printf("----------------------\n");
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);  

    return opcion;         
}


int printMenuDelincuencia() {
    int opcion;
    printf("=========================================================\n");
    printf("              ESTADÍSTICAS DE DELINCUENCIA               \n");
    printf("=========================================================\n");
    printf("1- Datos por estado\n");
    printf("2- Datos por año\n");
    printf("3- Informe de delincuencia\n");
    printf("4- Salir\n");
    printf("----------------------\n");
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);

    return opcion;
}

void opcionDelincuencia(int *opcionElegida, sqlite3 *db) {
    bool isValid = false;
    bool salir = false;
    int maxVal = 4;

    while(!salir) {
        while(!isValid) {
            printMenuDelincuencia();
            validarInputMenu(maxVal, opcionElegida, &isValid);
        }

        if(*opcionElegida == 1) {
            char *estado = malloc(15 * sizeof(char));

            printf("Introduzca una jurisdicción: ");
            fgets(estado, 15, stdin);
            printf("\n");

            mostrarDelincuenciaPorEstado(db, estado);

            free(estado);
            estado = NULL;
        } else if(*opcionElegida == 2) {
            // Datos por año
            mostrarDelincuenciaPorAnyo(db, 0);
        } else if(*opcionElegida == 3) {
            // Informe de delincuencia
            // informeDelincuencia();
        } else {
            // salir
            salir = true;
        }
    }
}


void opcionEstadisticas(int *opcionElegida, sqlite3 *db) {
    bool isValid = false;
    bool salir = false;
    int maxVal = 4;

    while(!salir) {
        while(!isValid) {
            printMenuEstadisticas();
            validarInputMenu(maxVal, opcionElegida, &isValid);
        }
    
        if(*opcionElegida == 1) {
            // Lista de criminales
            mostrarListaCriminales(db);
        } else if(*opcionElegida == 2) {
            // Información sobre prisioneros
        } else if(*opcionElegida == 3) {
            // Información sobre delincuencia
            opcionDelincuencia(opcionElegida, db);
        } else {
            // salir
            salir = true;
        }
    }
}



void menu() {
    sqlite3 *db;
    bool dbcargada = false;

    int result = sqlite3_open("./db/data.sqlite3", &db);
    if (result != SQLITE_OK) {
        printf("Error opening database\n");
        return;  
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

    menuRegistro(db);

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
            printf("3 - Visualizar estadísticas\n");
            printf("4 - Salir\n");
            printf("----------------------\n");
            scanf("%d", &opcion);

            if (opcion >= 1 && opcion <= maxValor) {
                opcionValida = true;
            } else {
                printf("Opción no válida. Inténtelo de nuevo\n");
            }
        }

        if (opcion == 1) {
            printf("Administración de datos\n");
            menuadministrar();

        } else if (opcion == 2) {
            printf("Agregar crimen\n");
            registrarCrimen(db);
           

        } else if (opcion == 3) {
            printf("Visualización de estadísticas\n");
            int opciondelasestadisticas = printMenuEstadisticas();

            if (opciondelasestadisticas == 3) {
                int opcion3 = printMenuDelincuencia();
                opcionDelincuencia(opcion3, db);
            }
            opcionEstadisticas(opciondelasestadisticas, db);

        } else if (opcion == 4) {
            printf("Salir\n");
            //no tenemos todavia metodo  de salir
        }
    }

    result = sqlite3_close(db);
    if (result != SQLITE_OK) {
        printf("Error cerrando la base de datos\n");
        printf("%s\n", sqlite3_errmsg(db));
    }

    liberarBuffer();  
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
