#include "common.h"
#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void trata(int sinal){
    printf("Recebi o sinal nº %d\n", sinal);
    exit(0);
}


int main(){
    printf("%d\n", getpid());
    signal(SIGUSR1, trata);
    while(1){
        printf(">\n");
        sleep(3);
    }
}
