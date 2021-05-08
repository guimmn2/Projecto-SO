#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define exit_on_error(s,m) if ( s < 0 ) { perror(m); exit(1); }

