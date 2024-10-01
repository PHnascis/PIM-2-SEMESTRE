#include <stdio.h>

int main(){

int tamanho = 0;
int valor;
printf("digite quantidade a ser cadastrada: ");
scanf("%d", &tamanho);

int gui[tamanho], i;


for(i = 0; i < tamanho; i++){
    printf("\ndigite o valor do item %d: ", i+1 );
    scanf("%d", &valor);
    gui[i] = valor;
}

for(i = 0; i< tamanho; i++){
        printf("\n item %d: -> %d", i+1, gui[i]);

        }
return 0;
}
