/******************************************************************************
 ** ISCTE-IUL: Trabalho prático de Sistemas Operativos
 **
 ** Aluno: Nº:98662       Nome:Guilherme Nunes 
 ** Nome do Módulo: servidor.c
 ** Descrição/Explicação do Módulo: 
 **
 **
 ******************************************************************************/
#include "common.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


int main(){

    FILE *svp;
    svp = fopen(FILE_PID_SERVIDOR,"w"); //n adicionei condição if NULL, pois à partida não existem problemas de permissões

    if(svp == NULL){
        erro("S1) Não consegui registar o servidor!");
        exit(1);
    }
    else { 
        fprintf(svp,"%d",getpid());
        sucesso("S1) Escrevi no ficheiro FILE_PID_SERVIDOR o PID: %d", getpid());
    }

    //reservar espaço conforme o tamanho do ficheiro enfermeiros.dat
    // o nº de enfermeiros (nr_enfs) será igual a file_size/sizeof(e)

    FILE *fp;
    Enfermeiro e, *p=NULL;
    int file_size, nr_enfs;
    fp = fopen(FILE_ENFERMEIROS, "r");
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp); //obtém o tamanho do ficheiro
    //printf("file_size is %d\n", file_size);
    nr_enfs = file_size/sizeof(e);
    //printf("nº de enfs: %d\n", nr_enfs);
    p = malloc(sizeof(e) * nr_enfs); //***

    
}





