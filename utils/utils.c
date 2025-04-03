#include "utils.h"
#include <stdio.h>
#include <stdbool.h>
#include "crimen.h"


void menu(int opcion){
    printf("----------------------\n");
    printf("ADMINISTRAR USUARIOS\n");
    printf("----------------------\n");
    printf("1. Ver todos los usuarios\n");
    printf("2. Agregar nuevo usuario\n");
    printf("3. Eliminar usuario\n");
    printf("4. Modificar usuario\n");
    printf("----------------------\n");
    printf("Selecione una opcion: ");
    scanf("%i", &opcion);
}

void seleccion(opcion){
    int opciones={1,2,3,4};
    
    if (opcion==opciones){
        if (opcion==1){
            
        }else if (opcion==2){

        }else if (opcion==3){

        }else if (opcion==4){
            
        }
    }else{
        printf("Selecciona una opcion valida");
    }
    
}

void printMenu(){

    printf("1- Administrar datos policia.\n");
    printf("2- Añadir crimen.\n");
    printf("3- Visualizar estadisticas.\n");
    printf("4- Salir.\n");
}

void menuRegistro(int *opcion){

    bool seguir = true;
    printf("Seleccione una opcion: \n");

    printMenu();

    scanf("%i", &opcion);

    while(seguir){

        if(opcion == 1){


        }
        else if(opcion == 2){


        }
        else if(opcion == 3){


        }
        else if(opcion == 4){

            seguir = false;
            break;
        }

        printMenu();
        printf("Seleccione una opcion: \n");
        scanf("%i", &opcion);
    }
    
}
void registrarCrimen() {
    
    printf("=========================================================\n");
    printf("                   REGISTRO DE CRIMINAL                  \n");
    printf("=========================================================\n");
    
    char *nombre;
    char *apellido;
    int *edad;
    char *genero;
    char *estadoCivil;

   
    char *DNI;
    char *descripcion;
    char *anio;  

  
    nombre = (char *)malloc(100 * sizeof(char));
    apellido = (char *)malloc(100 * sizeof(char));
    edad = (int *)malloc(sizeof(int));
    genero = (char *)malloc(20 * sizeof(char));
    estadoCivil = (char *)malloc(20 * sizeof(char));
    DNI = (char *)malloc(20 * sizeof(char));
    descripcion = (char *)malloc(200 * sizeof(char));
    anio = (char *)malloc(5 * sizeof(char));  

    

    
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

   
    printf("Ingrese el DNI: ");
    scanf("%s", DNI);

    printf("Ingrese la descripción del crimen: ");
    scanf("%s", descripcion);

    printf("Ingrese el anio del crimen: ");
    scanf("%s", anio);  

    
    printf("\n=== Datos Ingresados De Criminal ===\n");
    printf("Nombre: %s\n", nombre);
    printf("Apellido: %s\n", apellido);
    printf("Edad: %d\n", *edad);
    printf("Género: %s\n", genero);
    printf("Estado Civil: %s\n", estadoCivil);
    printf("DNI: %s\n", DNI);
    printf("Descripción: %s\n", descripcion);
    printf("Anio del crimen: %s\n", anio);  

    
    free(nombre);
    free(apellido);
    free(edad);
    free(genero);
    free(estadoCivil);
    free(DNI);
    free(descripcion);
    free(anio); 
}
