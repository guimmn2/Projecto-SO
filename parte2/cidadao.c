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


Cidadao novo_cidadao(){
    Cidadao n;

    printf("Nome: ");
    my_fgets(n.nome,100,stdin);
    printf("Nº de utente: ");
    scanf("%d", &n.num_utente); //!!tenho que limitar este buffer de alguma forma para o nº de dígitos certo
    printf("Idade: ");
    scanf("%d", &n.idade); //!!tenho que limitar este buffer de alguma forma para o nº de dígitos certo
    printf("Nº de telemóvel: ");
    my_fgets(n.nr_telemovel, 10, stdin);
    printf("Localidade: ");
    my_fgets(n.localidade,100, stdin);
    n.PID_cidadao = getpid();

    return n;
}
    void signal_cancel(int sig){
        printf("\nO cidadão cancelou a vacinação, o pedido nº %d foi cancelado\n", getpid());
        remove("pedidovacina.txt");
        exit(0);
    }

    void handle_sigusr1(int sig){
        printf("Vacinação do cidadão com o PID nº %d em curso.\n", getpid());
        remove("pedidovacina.txt");
    }

    void handle_sigusr2(int sig){
        printf("Vacinação do cidadão com o PID Nº %d concluída.\n", getpid());
        exit(0);
    }

    void handle_sigterm(int sig){
        printf("Não é possível vacinar o cidadão com o PID nº %d\n", getpid());
        remove("pedidovacina.txt");
        exit(1);
    }

int main (){
    
    char sv_pid[5]; //PID do servidor
    

    signal(SIGINT, signal_cancel);//ctrl-c
    signal(SIGUSR1, handle_sigusr1);//caso exista enfermeiro disponível
    signal(SIGUSR2, handle_sigusr2);//quando a vacinação terminar
    signal(SIGTERM, handle_sigterm);//caso não seja possível realizar a vacinação
    
    //para verificar se está tudo a funcionar minimamente bem por aqui...
//   printf("%s %d %d %s %s %d\n",n.nome, n.num_utente,n.idade, n.nr_telemovel, n.localidade, n.PID_cidadao);


    FILE *f;
    f = fopen("pedidovacina.txt", "r");

    //fazer a EXTRA-POINTS C10) !!!
    if ( f != NULL ){
        printf("Não é possível iniciar o processo de vacinação neste momento.\n");
        fclose(f);
        exit(1);
    }
    else {
        
        Cidadao n = novo_cidadao();
        f = fopen("pedidovacina.txt", "w");
        fprintf(f,"%d:%s:%d:%s:%s:%d:%d\n",n.num_utente, n.nome,n.idade, n.localidade, n.nr_telemovel, 0, n.PID_cidadao);
        fclose(f);

        FILE *sp; //servidor.pid
        sp = fopen("servidor.pid", "r");

        if( sp == NULL ){
            printf("Não é possível saber o PID do servidor!\n");
            exit(1);

        } else {

            //por alguma razão aqui espera que eu carregue no enter para tentar abrir o servidor.pid ???
            my_fgets(sv_pid, 5, sp);
            //printf("%s\n", sv_pid);
            int sv_pid_value = atoi(sv_pid); //converter de string para int
            //printf("%d\n", sv_pid_value);
            fclose(sp);
            kill(SIGUSR1, sv_pid_value);

        }

    }

}
