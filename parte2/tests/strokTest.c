#include<stdio.h>
#include<string.h>


int main (){

    FILE *f;
    f = fopen("../pedidovacina.txt", "r");
    fseek(f,0,SEEK_END);

    int sz = ftell(f);
    char str[sz];
    fseek(f,0,SEEK_SET);
    fgets(str, sz, f);

    char * delim;

    delim = strtok(str,":");

    while(delim != NULL){
        printf("%s\n", delim);
        delim = strtok(NULL, ":");
    }
}
