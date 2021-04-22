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

int get_nr_enfs(){

    FILE *fp;
    int file_size, nr_enfs;
    fp = fopen(FILE_ENFERMEIROS, "r");
    if(fp == NULL){
        erro("S2) Não consegui ler o ficheiro FILE_ENFERMEIROS!");
    }
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp); //obtém o tamanho do ficheiro
    fseek(fp, 0, SEEK_SET);
    nr_enfs = file_size/sizeof(Enfermeiro);
    sucesso("S2) Ficheiro FILE_ENFERMEIROS tem %d bytes, ou seja, %d enfermeiros", file_size, nr_enfs);

    fclose(fp);

    return nr_enfs;
}

Enfermeiro* define_enfermeiros(){

    //reservar espaço conforme o tamanho do ficheiro enfermeiros.dat
    // o nº de enfermeiros (nr_enfs) será igual a file_size/sizeof(e)
    FILE *fp;
    fp = fopen(FILE_ENFERMEIROS,"r");
    Enfermeiro e, *enfermeiros;
    int nr_enfs = get_nr_enfs();
    enfermeiros = (Enfermeiro *)malloc(sizeof(e) * nr_enfs); //***
    if(enfermeiros == NULL){
        printf("Null Pointer\n");
        exit(1);
    }
    fread(enfermeiros, sizeof(e), nr_enfs, fp);
    fclose(fp);
    return enfermeiros;
}

void handle_sigusr1(int sig){
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

    //guarda os campos no string de arrays str_arr
    while(delim != NULL){
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
    Enfermeiro *e = define_enfermeiros();

    Vaga v[NUM_VAGAS];
    for(int i = 0; i < NUM_VAGAS; i++){
        v[i].index_enfermeiro = -1;
    }
    sucesso("S3) Iniciei a lista de %d vagas",NUM_VAGAS);
    
    signal(SIGUSR1, handle_sigusr1);
    sucesso("S4) Servidor espera pedidos");
    pause();

}




