#include "common.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>


int size_of_enfermeiros(){
    
    //quero criar um malloc em função do tamanho do ficheiro enfermeiros.dat, de forma a que comporte todos os enfs.
    
    FILE *f;
    f = fopen(FILE_ENFERMEIROS,"r");

    int size = sizeof(*f);
    printf("size of f is: %d\n", size);

}

int main(){
    size_of_enfermeiros();

}

