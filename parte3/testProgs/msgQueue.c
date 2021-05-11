#include "defs.h"
#include "common.h"
main() {
int id = msgget ( IPC_KEY, IPC_CREAT | 0666 );

if ( id < 0 ) {
printf ("Erro na criação da fila de mensagens\n" );
exit(1);
}
printf ("Criada fila de mensagens com id %d\n", id);
}

