/******************************************************************************
 ** ISCTE-IUL: Trabalho prático de Sistemas Operativos
 **
 ** Aluno: Nº:98662       Nome:Guilherme Nunes 
 ** Nome do Módulo: cidadao.c
 ** Descrição/Explicação do Módulo: 
 **
 **
 ******************************************************************************/
#include "common.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int exists; //flag para sigalarm

Cidadao novo_cidadao(){
    //Devolve cidadão novo 'n' e grava informações obtidas no input do cliente
    Cidadao n;

    printf("Nº de utente: ");
    scanf("%d", &n.num_utente); 
    printf("Nome: ");
    my_fgets(n.nome,100,stdin);
    printf("Idade: ");
    scanf("%d", &n.idade); 
    printf("Localidade: ");
    my_fgets(n.localidade,100, stdin);
    printf("Nº de telemóvel: ");
    my_fgets(n.nr_telemovel, 10, stdin);
    n.PID_cidadao = getpid();
    n.estado_vacinacao = 0;

    sucesso("C1) Dados Cidadão: %d; %s; %d; %s; %s; %d", n.num_utente, n.nome, n.idade, n.localidade, n.nr_telemovel, n.estado_vacinacao);

    return n;
}
    void signal_cancel(int sig){
        sucesso("C5) O cidadão cancelou a vacinação, o pedido no %d foi cancelado",getpid());
        remove(FILE_PEDIDO_VACINA);
        exit(0);
    }

    void handle_sigusr1(int sig){
        sucesso("C7) Vacinação do cidadão com o pedido no %d em curso", getpid());
        remove(FILE_PEDIDO_VACINA);
    }

    void handle_sigusr2(int sig){
        sucesso("C8) Vacinação do cidadão com o pedido no %d concluída", getpid());
        exit(0);
    }

    void handle_sigterm(int sig){
        sucesso("C9) Não é possível vacinar o cidadão no pedido no %d", getpid());
        remove(FILE_PEDIDO_VACINA);
        exit(0);
    }

    void handle_sigalrm(int sig){
        //se o ficheiro não existir levanta a flag, ou seja muda var global 'exists' para 1
        if(!fopen(FILE_PEDIDO_VACINA, "r")){
            exists = 1;
        }
    }

int main (){
    
    char sv_pid[100]; //PID do servidor
    
    //Sinais armados!
    signal(SIGUSR1, handle_sigusr1);//caso exista enfermeiro disponível
    signal(SIGUSR2, handle_sigusr2);//quando a vacinação terminar
    signal(SIGTERM, handle_sigterm);//caso não seja possível realizar a vacinação
    
    Cidadao n = novo_cidadao(); //cria cidadão com o input do cliente, usando a função novo_cidadão()
    sucesso("C2) PID Cidadão: %d", n.PID_cidadao);

    FILE *f;
    f = fopen(FILE_PEDIDO_VACINA, "r");

    if ( f != NULL ){
        exists = 0;
        erro("C3) Não é possível iniciar o processo de vacinação neste momento");
        signal(SIGALRM, handle_sigalrm);


        while(exists == 0){
            //enquanto o ficheiro existe o cidadao aguarda que o ficheiro deixe de existir
            //para depois correr o handler do sigalrm (quando a var existe = 1)
            alarm(5);
            pause();
        }
    }
        sucesso("C3) Ficheiro FILE_PEDIDO_VACINA pode ser criado");
        f = fopen(FILE_PEDIDO_VACINA, "w");
        if(f == NULL){
        erro("C4) Não é possível criar o ficheiro FILE_PEDIDO_VACINA");
        fclose(f);
        }
        //escrever informações do cidadao no pedidovacina.txt
        fprintf(f,"%d:%s:%d:%s:%s:%d:%d\n",n.num_utente, n.nome,n.idade, n.localidade, n.nr_telemovel, n.estado_vacinacao, n.PID_cidadao);
        fclose(f);
        sucesso("C4) Ficheiro FILE_PEDIDO_VACINA criado e preenchido");

        signal(SIGINT, signal_cancel);//ctrl-c

        FILE *sp; //servidor.pid
        sp = fopen(FILE_PID_SERVIDOR, "r");

        if( sp == NULL ){
            erro("C6) Não existe ficheiro FILE_PID_SERVIDOR!");
            exit(1);

        } else {

            //encontrando o ficheiro servidor.pid lê o pid do servidor e guarda em sv_pid_value
            my_fgets(sv_pid, 100, sp);
            int sv_pid_value = atoi(sv_pid); //converter de string para int
            fclose(sp);
            kill(sv_pid_value,SIGUSR1);
            sucesso("C6) Sinal enviado ao Servidor: %d", sv_pid_value);

        }
        while(1){
            sucesso("aguarda sinais...");
            pause();
        }
}
