#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include "./../modules/crimen.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "./../db/database.h"

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


//MENU CREADO ABAJO PARA PODER AÑADIR LAS FUNCIONES QUE ESTEN YA DECLARADAS!!!!!!!!
void printMenuRegistro(){

    printf("=========================================================\n");
    printf("                   DEPARTAMENTO DE POLICIA                   \n");
    printf("=========================================================\n");
    printf("1- Administrar datos policia.\n");
    printf("2- Añadir crimen.\n");
    printf("3- Visualizar estadisticas.\n");
    printf("4- Salir.\n");
    printf("----------------------\n");
}

void menuRegistro(int *opcion){

    bool seguir = false;
    int maxValue = 4;
    printf("Seleccione una opcion: \n");

    while(seguir == false){

        printMenuRegistro();
        scanf("%i", opcion);
        validarInputMenu(maxValue, opcion, &seguir);
    }
    

    while(seguir == true){

        if(*opcion == 1){


        }
        else if(*opcion == 2){


        }
        else if(*opcion == 3){


        }
        else if(*opcion == 4){

            seguir = false;
        }

        printMenuRegistro();
        scanf("%i", opcion);
        validarInputMenu(maxValue, opcion, &seguir);
    }
}

void printMenuBD(){

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
        while(!isValid) {
            printMenuDelincuencia();
            validarInputMenu(maxVal, opcionElegida, &isValid);
        }

        if(*opcionElegida == 1) {
            // Datos por estado
            mostrarListaCriminales(db);
        } else if(*opcionElegida == 2) {
            // Datos por año
        } else if(*opcionElegida == 3) {
            // Informe de delincuencia
        } else {
            // salir
            salir = true;
        }
    }
}

/**
 * Inicia un bucle que acaba cuando opcionElegida tenga un valor válido.
 */
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
        } else {
            // salir
            salir = true;
        }
    }
}

void menu() {
    int opcion = 0;
    bool opcionValida = false;
    int maxValor = 4;

    while (opcion != 4) {
        opcionValida = false;

        while (!opcionValida) {
            printf("=========================================================\n");
            printf("                    POLICIA DEUSTO                       \n");
            printf("=========================================================\n");
            printf("Selecione una de esta opciones:\n");
            printf("1- Administrar datos policia\n");
            printf("2- Añadir crimen\n");
            printf("3- Visualizar estadisticas\n");
            printf("4- Salir\n");
            printf("----------------------\n");
            scanf("%d", &opcion);

            if (opcion >= 1 && opcion <= maxValor) {
                opcionValida = true;
            } else {
                printf("Opcion no valida. Intentelo de nuevo\n");
            }
        }
    //meter vuestrats fucniones aqui
        if (opcion == 1) {
            printf("Administratcion de datos\n");
        } else if (opcion == 2) {
            printf("Agregar crimen\n");
            Crimen registrarCrimen();
        } else if (opcion == 3) {
            printf("Visualizacion de Estadisticas\n");
        } else if (opcion == 4) {
            printf("Salir\n");
    }
}
}