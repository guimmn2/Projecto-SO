#include "common.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>

int msg_id;
MsgCliente msg;
char ped[100];

int main(){


    msg.tipo = 1;
    msg.dados.pedido = PEDIDO;
    msg.dados.num_utente = 100275;
    strcpy(msg.dados.nome, "Tiago Faria");
    msg.dados.PID_cidadao = getpid();
    
    printf("enviada mensagem com:\n tipo: %ld\n num_utente: %d\n nome: %s\n PID: %d\n",msg.tipo, msg.dados.num_utente, msg.dados.nome,msg.dados.PID_cidadao);

    msg_id = msgget(IPC_KEY, 0666);

    int status = msgsnd(msg_id, &msg, sizeof(msg),0);
    exit_on_error(status,"n funcionou");

    printf("\nfuncionou!\n");
}
