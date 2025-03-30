#include "utils.h"
#include <stdio.h>

int opcion;
void menu(){
    printf("----------------------\n");
    printf("ADMINISTRAR USUARIOS\n");
    printf("----------------------\n");
    printf("1. Ver todos los usuarios\n");
    printf("2. Agregar nuevo usuario\n");
    printf("3. Eliminar usuario\n");
    printf("4. Modificar usuario\n");
    printf("----------------------\n");
    printf("Selecione una opcion: ");
    scanf("%i", opcion);
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