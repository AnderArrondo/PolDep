
#include <stdio.h>
#include "criminal.h"

void printCriminal(int id, Criminal *c) {
    printf("  %d) %s %s [%d, %s] %s (%s)\n",
        id, c->nombre, c->apellido, c->edad, c->genero,
        c->ciudadNacimiento, c->estadoCivil);
}