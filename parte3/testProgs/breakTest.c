#include<stdio.h>

int main(){

    int a = 5, b = 10;

    for(int i = 0; i < 10; i++){
        printf("%d\n", i);

        if(i < 5) printf("ainda não...\n");
        else if(i > 5){
            printf("agora! i > 5, deverá ser 6...\n");
            break;
        }
    }

    printf("saí do for!\n");
}
