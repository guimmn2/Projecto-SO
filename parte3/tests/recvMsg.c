#include "defs.h"
#include <string.h>

typedef struct {
long tipo;
char texto[250];
} MsgStruct;

main() {
int msg_id;
int status;

MsgStruct msg;

// ligar à fila de mensagens
// notar que não foi usado IPC_CREAT, pois fila já existe
msg_id = msgget ( 1000, 0 );
exit_on_error (msg_id, "Criação/Ligação");

// receber uma mensagem (bloqueia se não houver)
status = msgrcv( msg_id, &msg, sizeof(msg.texto), 1, 0);
exit_on_error (status, "Recepção");

printf ("MENSAGEM <%s>\n", msg.texto);

}

