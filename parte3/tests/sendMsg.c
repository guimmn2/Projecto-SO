#include"defs.h"
#include<string.h>

typedef struct {
long tipo;
char texto[250];
} MsgStruct;

main() {
int msg_id;
int status;

MsgStruct msg; //declara estrutura de dados MsgStruct com o nome msg

// ligar à fila de mensagens
msg_id = msgget ( 1000, 0600 | IPC_CREAT ); //obtem o id do ipcsq, ou seja da mensagem
exit_on_error (msg_id, "Criação/Ligação");

// enviar ums mensagem
msg.tipo = 1;
strcpy( msg.texto, "Hello");
status = msgsnd( msg_id, &msg, sizeof(msg.texto), 0);
exit_on_error (status, "Envio");

printf ("Mensagem enviada!\n");
}

