#include <stdio.h>
#include <locale.h>

int main(){
    setlocale(LC_ALL, "Portuguese");

    while(1){

    int firstOption;

    printf("---------------------------------------\n");
    printf("*******HORTIFRUIT GREEN HARVEST********\n");
    printf("---------------------------------------\n");
    printf("\n      DIGITE SOMENTE NÚMEROS         \n");
    printf("\n\nSELECIONE A OPÇÃO REQUERIDA:       \n");
    printf("\n(1) - PRODUTOS                       \n");
    printf("\n(2) - OPERAÇÃO DE CAIXA              \n");
    printf("\n(3) - SERVIÇOS DO SERVIDOR           \n");
    printf("---------------------------------------\n");

        scanf("%d", &firstOption);

        if(firstOption > 3){
            printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
            }

   else if(firstOption == 1){

        while(1){
            int selectNumber;
            printf("\n\n---------------------------------------\n");
            printf("*******HORTIFRUIT GREEN HARVEST********\n");
            printf("**************PRODUTOS*****************\n");
            printf("---------------------------------------\n");
            printf("\n      DIGITE SOMENTE NÚMEROS         \n");
            printf("\n\nSELECIONE A OPÇÃO REQUERIDA:       \n");
            printf("\n(1) - CADASTRAR PRODUTOS             \n");
            printf("\n(2) - CALCULAR PREÇO                 \n");
            printf("\n(3) - CONFERIR PRODUTOS              \n");
            printf("---------------------------------------\n");
                scanf("%d", &selectNumber);

                if (selectNumber > 3){
                printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");

                }
                else if (selectNumber == 0){
                    break;
                }


            switch("%d", selectNumber){


                case 1:

                    int x;

                    printf("\nDIGITE A QUANTIDADE DE PRODUTOS QUE SERÃO CADASTRADOS: ");
                        scanf("%d", &x);

                    for(int i;i <= x; i++ ){

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

                        printf("\nCÓDIGO DO PRODUTO: %d\n", codProduto);
                        printf("\nNOME DO PRODUTO:   %s\n", nomeProduto);
                        printf("\nQUANTIDADE DO PRODUTO:  %d\n", qtdProduto);
                        printf("\nVALOR UNITÁRIO DO PRODUTO:   %.2f\n", valorProduto);
                        printf("\nPRODUTO CADASTRADO COM SUCESSO!!! \n\n" );
                    }

            break;

            case 2:

                
                    






            break;

            case 3:

                printf("%d", codProduto);               


                





            break;

                }

            }

        }

    }




return 0;
}
