#include "common.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>

int msg_id;
MsgServidor msg;

int main(){


    msg_id = msgget(IPC_KEY, 0666);
    msg.dados.status = NAOHAENFERMEIRO;

    printf("insere pid do cidado para testar: ");
    scanf("%ld", &msg.tipo);
    printf("%ld",msg.tipo);

    int status = msgsnd(msg_id, &msg, sizeof(msg),0);
    exit_on_error(status, "n funcionou");

    printf("\nfuncionou!\n");


    
}
