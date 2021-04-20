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

}





