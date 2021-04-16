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
    svp = fopen("servidor.pid","w"); //n adicionei condição if NULL, pois à paritda não existem problemas de permissões
    fprintf(svp,"%d", getpid());

}



