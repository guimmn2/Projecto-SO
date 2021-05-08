#include "defs.h"
typedef struct {
long tipo;
char texto[250];
} MsgStruct;

main() {

//ligar à fila de mensagens
int msg_id;
msg_id = msgget ( 1000, 0666 | IPC_CREAT );
exit_on_error (msg_id, "Criação/Ligação");
int status;

MsgStruct msg;

while ( 1 ) {
printf ("Esperar pedido...\n");
status = msgrcv( msg_id, &msg, sizeof(msg.texto), 1, 0);
exit_on_error (status, "Recepção");
}

printf ("Recebido pedido <%s>. Executar!\n", msg.texto);
}
