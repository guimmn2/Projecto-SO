#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define exit_on_error(s,m) if ( s < 0 ) { perror(m); exit(1); }

main() {
int id = msgget ( 1000, IPC_CREAT | 0666 );
exit_on_error ( id, "Criação da fila de mensagens");
printf ("Criada fila de mensagens com id %d\n", id);
}

