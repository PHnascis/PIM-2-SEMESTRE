#include <stdio.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese");

    while(1){
int selectNumber;
printf("---------------------------------------\n");
printf("*******HORTIFRUIT GREEN HARVEST********\n");
printf("---------------------------------------\n");
printf("\n      DIGITE SOMENTE NÚMEROS         \n");
printf("\n\nSELECIONE A OPÇÃO REQUERIDA:       \n");
printf("\n(1) - CADASTRO DE PRODUTOS           \n");
printf("\n(2) - CALCULAR PREÇO                 \n");
printf("\n(3) - CONFERIR PRODUTOS              \n");
printf("---------------------------------------\n");

scanf("%d", &selectNumber);

switch("%d", selectNumber){


    if (selectNumber > 3){
        printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");

    }


   case 1:



    printf("---------------------------------------\n");
    printf("********CADASTRO DE PRODUTOS***********\n");
    printf("---------------------------------------\n");
       int codProduto, qtdProduto;
      char nomeProduto[30];
      float valorProduto;

    printf("\nCÓDIGO DO PRODUTO:                   \n");
        scanf("%d", &codProduto);
    printf("\nNOME DO PRODUTO:                     \n");
        scanf("%s", &nomeProduto);
    printf("\nQUANTIDADE DO PRODUTO:               \n");
        scanf("%d", &qtdProduto);
    printf("\nVALOR UNITÁRIO DO PRODUTO:           \n");
        scanf("%f", &valorProduto);
    printf("\n-------------------------------------\n");

    printf("\nCÓDIGO DO PRODUTO: %d", codProduto);
    printf("\nNOME DO PRODUTO:   %s", nomeProduto);
    printf("\nQUANTIDADE DO PRODUTO:  %d", qtdProduto);
    printf("\nVALOR UNITÁRIO DO PRODUTO:   %.2f", valorProduto);


break;

    case 2:








break;

    case 3:


break;

    }
break;
}







return 0;
}
