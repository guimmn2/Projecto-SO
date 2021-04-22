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
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handle_sigusr1(int sig){
    sucesso("S4) Servidor espera pedidos");
    FILE *f;
    f = fopen(FILE_PEDIDO_VACINA, "r");

    if(f == NULL){
        erro("S5.1) Não foi possível ler o ficheiro FILE_PEDIDO_VACINA");
    }
    
    fseek(f,0,SEEK_END);    //para determinar o tamanho do ficheiro, ou seja da string. 
    int sz = ftell(f);
    fseek(f,0,SEEK_SET);
    
    char str[sz];
    my_fgets(str, sz, f); //guarda a string em str.
    
    char* delim; 
    delim = strtok(str, ":"); //define um delimitador ":"

    char str_arr[7][20]; //cria array de strings para guardar campos
    int i = 0; //iterador

    while(delim != NULL){
        //printf("%s\n", delim);
        strcpy(str_arr[i], delim);
        delim = strtok(NULL, ":");
        i++;
    }

    printf("Chegou o cidadão com o pedido no %s, com nº utente %s, para ser vacinado no Centro de Saúde CS%s\n", str_arr[6], str_arr[0], str_arr[3]);
    sucesso("S5.1) Dados Cidadão: %s; %s; %s; %s; %s; %s", str_arr[0],str_arr[1],str_arr[2], str_arr[3],str_arr[4],str_arr[5], str_arr[6]);
    



}


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
    Enfermeiro e, *p;
    int file_size, nr_enfs;
    fp = fopen(FILE_ENFERMEIROS, "r");
    if(fp == NULL){
        erro("S2) Não consegui ler o ficheiro FILE_ENFERMEIROS!");
    }
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp); //obtém o tamanho do ficheiro
    fseek(fp, 0, SEEK_SET);
    //printf("file_size is %d\n", file_size);
    nr_enfs = file_size/sizeof(e);
    //printf("nº de enfs: %d\n", nr_enfs);
    sucesso("S2) Ficheiro FILE_ENFERMEIROS tem %d bytes, ou seja, %d enfermeiros", file_size, nr_enfs);
    p = (Enfermeiro *)malloc(sizeof(e) * nr_enfs); //***
    if(p == NULL){
        printf("Null Pointer\n");
        exit(1);
    }
    fread(p, sizeof(e), nr_enfs, fp);
    fclose(fp);

    Vaga v[NUM_VAGAS];
    for(int i = 0; i < NUM_VAGAS; i++){
        v[i].index_enfermeiro = -1;
    }
    sucesso("S3) Iniciei a lista de %d vagas",NUM_VAGAS);
    
    signal(SIGUSR1, handle_sigusr1);
    pause();


}




