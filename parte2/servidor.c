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

int index_enf;
int vaga_index;
Vaga vagas[NUM_VAGAS];
Enfermeiro *e;
int n_children = 0; 
int children[100]; //limite para processos filhos = 100;
int *vaga_filho_pointer;

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
    Enfermeiro *enfermeiros;
    int nr_enfs = get_nr_enfs();
    enfermeiros = (Enfermeiro *)malloc(sizeof(Enfermeiro) * nr_enfs); //***
    if(enfermeiros == NULL){
        printf("Null Pointer\n");
        exit(1);
    }
    fread(enfermeiros, sizeof(Enfermeiro), nr_enfs, fp);
    fclose(fp);

    return enfermeiros;
}

Cidadao get_cidadao_data(){

    Cidadao temp;
    FILE *f;
    f = fopen(FILE_PEDIDO_VACINA, "r");

    if(f == NULL){
        erro("S5.1) Não foi possível ler o ficheiro FILE_PEDIDO_VACINA");
        exit(1);
    }
    
    fseek(f,0,SEEK_END);    //para determinar o tamanho do ficheiro, ou seja da string. 
    int sz = ftell(f);
    fseek(f,0,SEEK_SET);
    
    char str[sz];
    my_fgets(str, sz, f); //guarda a string em str.
    
    char* delim; 
    delim = strtok(str, ":"); //define um delimitador ":"

    char str_arr[7][100]; //cria array de strings para guardar campos
    int i = 0; //iterador

    //guarda os campos no string de arrays str_arr
    while(delim != NULL){
        strcpy(str_arr[i], delim);
        delim = strtok(NULL, ":");
        i++;
    }
    temp.num_utente = atoi(str_arr[0]); //passa as informações guardadas no array para o cidadao temporário
    strcpy(temp.nome,str_arr[1]);
    temp.idade = atoi(str_arr[2]);
    strcpy(temp.localidade, str_arr[3]);
    strcpy(temp.nr_telemovel, str_arr[4]);
    temp.estado_vacinacao = atoi(str_arr[5]);
    temp.PID_cidadao = atoi(str_arr[6]);
    
    fclose(f);

    return temp;
}

int verifica_localidade(){

    Cidadao temp = get_cidadao_data(); //obtem dados acerca do cidadão
    e = define_enfermeiros();
    int nr_enfs = get_nr_enfs(); //obtem o nº de cidadãos
    int is_available = 0; //parte do princípio que não existe = 0
    char cs_temp[20] = "CS"; //adicionar CS para comparar strings com CS_enfmermeiro

    strcat(cs_temp, temp.localidade);

    for(int i = 0; i < nr_enfs; i++){
        //debug("%s\n",e[i].CS_enfermeiro);
        debug("index: %d nome: %s disp: %d local: %s\n", i,e[i].nome,e[i].disponibilidade, e[i].CS_enfermeiro);
        debug("%s\n", cs_temp);
        debug("%s\n",e[i].CS_enfermeiro);
            debug("%d\n", index_enf);
            index_enf = i;
        if(!strcmp(cs_temp,e[i].CS_enfermeiro)){
            if(e[i].disponibilidade == 1){
            is_available = 1;
            break;
            } 
        }
    }
        //debug("%d\n", is_available);
        is_available = 0;
        return is_available;
    
}

void handle_sigusr1(int sig){
    Cidadao temp = get_cidadao_data();
    printf("Chegou o cidadão com o pedido nº %d, com nº utente %d, para ser vacinado no Centro de Saúde CS%s\n",temp.PID_cidadao, temp.num_utente, temp.localidade);
}

void handle_sigchld(int sig){
    int temp_index = vagas[vaga_index].index_enfermeiro;
    vagas[vaga_index].index_enfermeiro = -1;
    sucesso("S5.5.3.1) Vaga %d que era do servidor dedicado %d libertada", vaga_index, vagas[vaga_index].PID_filho);
    e[temp_index].disponibilidade = 1;
    sucesso("S5.5.3.2)Enfermeiro %d atualizado para disponível", temp_index);
    e[temp_index].num_vac_dadas += 1;
    sucesso("S5.5.3.3) Enfermeiro %d atualizado para %d vacinas dadas", temp_index, e[temp_index].num_vac_dadas);
    FILE *f;
    f = fopen(FILE_ENFERMEIROS, "wb");
    if (f == NULL){
        printf("Null Pointer!\n");
        exit(1);
    }
    fseek(f, sizeof(Enfermeiro)*temp_index, SEEK_SET); //coloca ponteiro na linha do enfermeiro certo
    fwrite(&e[temp_index], sizeof(Enfermeiro),1,f);
    fseek(f,0,SEEK_SET); //pra voltar ao início
    fclose(f);
    sucesso("S5.5.3.4) Ficheiro FILE_ENFERMEIROS %d atualizado para %d vacinas dadas", temp_index, e[temp_index].num_vac_dadas);
    sucesso("S5.5.3.5) Retorna");
}

void handle_sigterm(int sig){
    kill(get_cidadao_data().PID_cidadao, SIGTERM);
    sucesso("S5.6.1) SIGTERM recebido, servidor dedicado termina Cidadão");
    exit(0);
}

void handle_sigint(int sig){
    for(int i = 0; i < n_children; i++){
        kill(children[i], SIGTERM);
        exit(0);
    }
}


int main(){

    FILE *svp;
    svp=fopen(FILE_PID_SERVIDOR,"w"); //n adicionei condição if NULL, pois à partida não existem problemas de permissões

    if(svp == NULL){
        erro("S1) Não consegui registar o servidor!");
        exit(1);
    }
     
    fprintf(svp,"%d",getpid());
    fclose(svp);
    sucesso("S1) Escrevi no ficheiro FILE_PID_SERVIDOR o PID: %d", getpid());
    
    e = define_enfermeiros(); //Muda var global Enfermeiro *e

    Vaga vagas[NUM_VAGAS];
    for(int i = 0; i < NUM_VAGAS; i++){
        vagas[i].index_enfermeiro = -1;
    }
    sucesso("S3) Iniciei a lista de %d vagas",NUM_VAGAS);
    
    signal(SIGUSR1, handle_sigusr1);
    waitsignal: sucesso("S4) Servidor espera pedidos");
    pause();

    //verificar a disponibilidade de enfermeiro, se existir na localidade
    if ( verifica_localidade() != 1 ){ 
        //!= 1, significa que não está disps")
        erro("S5.2.1) Enfermeiro %d indisponível para o pedido %d para o Centro de Saúde %s", index_enf, get_cidadao_data().PID_cidadao, get_cidadao_data().localidade);
        kill(get_cidadao_data().PID_cidadao,SIGTERM);
    } else {   
        sucesso("S5.2.1) Enfermeiro %d disponível para o pedido %d", index_enf,get_cidadao_data().PID_cidadao);
        for(int i = 0; i < NUM_VAGAS; i++){
            debug("%d\n", vaga_index);  
            vaga_index = i;
            if(vagas[vaga_index].index_enfermeiro != -1){
                kill(get_cidadao_data().PID_cidadao,SIGTERM); 
                erro("S5.2.2) Não há vaga para vacinação para o pedido %d", get_cidadao_data().PID_cidadao);
                goto waitsignal;
            } else {
                sucesso("S5.2.2) Há vaga para vacinação para o pedido %d", get_cidadao_data().PID_cidadao);
                vagas[i].index_enfermeiro = index_enf; //preenche com o indice da lista de enfs
                vagas[i].cidadao = get_cidadao_data(); //preenche com info do cidadão
                e[i].disponibilidade = 0;
                sucesso("Vaga nº %d preenchida para o pedido %d", i,get_cidadao_data().PID_cidadao);
                break;
            }
        }
    }

        children[n_children] = fork();
        if(children[n_children] < 0){
            erro("S5.4) Não foi possível criar o servidor dedicado");
            exit(1);
        } 
        if(children[n_children] == 0) {
            //código do filho
            sucesso("S5.4) Servidor dedicado %d criado para o pedido %d", getpid(), get_cidadao_data().PID_cidadao);
            signal(SIGTERM, handle_sigterm);
            kill(vagas[vaga_index].cidadao.PID_cidadao, SIGUSR1);
            sucesso("S5.6.2) Servidor dedicado inicia consulta de vacinação");
            sleep(TEMPO_CONSULTA);
            sucesso("S5.6.3) Vacinação terminada para o cidadão com o pedido nº %d", get_cidadao_data().PID_cidadao);
            kill(vagas[vaga_index].cidadao.PID_cidadao, SIGUSR2);
            vaga_filho_pointer = &vaga_index;
            exit(0);

        } else {
            //código do pai
        n_children ++;
        vagas[vaga_index].PID_filho = children[n_children]; 
        sucesso("S5.5.1) Servidor dedicado %d na vaga %d", children[n_children], vaga_index);

        signal(SIGCHLD, handle_sigchld);
        sucesso("S5.5.2) Servidor aguarda fim do servidor dedicado %d", children[n_children]); 

        signal(SIGINT, handle_sigint);

        }
        
        
    goto waitsignal; 



}