#include "common.h"
#include "utils.h"
#include <sys/ipc.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/shm.h>

int main(){

    int id = shmget(IPC_KEY,20,IPC_CREAT | 0600);

    printf("%d\n", id); 

    void *p = shmat(id,0,0);
    exit_on_null(p,"não conseguiu ligar");

    char* s;
    s = (char*) p;

    int i;
    for(i = 0; i < 20; i++){
        s[i] = 'x';
    }

    printf("%c\n", s[0]);


}
