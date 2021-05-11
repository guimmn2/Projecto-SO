#include "common.h"
#include "utils.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>

int msg_id;

MsgCliente msg;

int main(){

    msg.tipo = 1;
    msg.dados.PID_cidadao = getpid();
    
    printf("debug -> msg.tipo = %d; msg.dados.PID_cidadao = %d", msg.tipo, msg.dados.PID_cidadao);

    msg_id = msgget(IPC_KEY, 0666);

    int status = msgsnd(msg_id, &msg, sizeof(msg),0);
    exit_on_error(status,"n funcionou");

    printf("\nfuncionou!\n");
}
