#include<stdio.h>
#include<string.h>
#include<unistd.h>


int main(){

    FILE *f;
    f = fopen("pedidovacina.txt", "w");

    fprintf(f,"este é o pid: %d\n", getpid());
    fclose(f);
}
