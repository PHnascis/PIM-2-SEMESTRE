#include <stdio.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese");

    int tamanho = 0, i;
    int codProduto[100]; // Define arrays com tamanho máximo
    char nomeProduto[100][30];
    float valorProduto[100];

    while (1) {
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

        if (firstOption > 3) {
            printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
        } else if (firstOption == 1) {

            while (1) {
                int selectNumber;
                printf("\n\n---------------------------------------\n");
                printf("*******HORTIFRUIT GREEN HARVEST********\n");
                printf("**************PRODUTOS*****************\n");
                printf("---------------------------------------\n");
                printf("\n      DIGITE SOMENTE NÚMEROS         \n");
                printf("\n\nSELECIONE A OPÇÃO REQUERIDA:       \n");
                printf("\n(1) - CADASTRAR PRODUTOS             \n");
                printf("\n(2) - CONFERIR PRODUTOS              \n");
                printf("\n(0) - VOLTAR\n");
                printf("---------------------------------------\n");
                scanf("%d", &selectNumber);

                if (selectNumber > 3) {
                    printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
                } else if (selectNumber == 0) {
                    break;
                }

                switch (selectNumber) {
                    case 1:
                        printf("\nDIGITE A QUANTIDADE DE PRODUTOS QUE SERÃO CADASTRADOS: ");
                        scanf("%d", &tamanho); // Define o tamanho correto

                        for (i = 0; i < tamanho; i++) {
                            printf("---------------------------------------\n");
                            printf("********CADASTRO DE PRODUTOS***********\n");
                            printf("---------------------------------------\n");

                            printf("\nCÓDIGO DO PRODUTO %d:                   \n", i + 1);
                            scanf("%d", &codProduto[i]);
                            printf("\nNOME DO PRODUTO:                     \n");
                            scanf("%s", nomeProduto[i]);
                            printf("\nVALOR UNITÁRIO DO PRODUTO:           \n");
                            scanf("%f", &valorProduto[i]);
                            printf("\n-------------------------------------\n");

                            printf("\nCÓDIGO DO PRODUTO: %d\n", codProduto[i]);
                            printf("\nNOME DO PRODUTO:   %s\n", nomeProduto[i]);
                            printf("\nVALOR UNITÁRIO DO PRODUTO:   %.2f\n", valorProduto[i]);
                            printf("\nPRODUTO CADASTRADO COM SUCESSO!!! \n\n");


                            //printf("\nDESEJA CONTINUAR? \n");
                            //printf("\n(1) - SIM\n");
                            //printf("\n(0) - NÃO\n");


                            //int option;
                            //scanf("%d", option);

                            //if(option == 0){
                               // break;

                            }


                        }
                        break;

                    case 2:
                        if (tamanho == 0) {
                            printf("\nNENHUM PRODUTO CADASTRADO!\n");
                        } else {
                            printf("\nLISTA DE PRODUTOS CADASTRADOS:\n");
                            for (i = 0; i < tamanho; i++) {
                                printf("\n-------------------------------------\n");
                                printf("Item %d\n", i + 1);
                                printf("Código: %d\n", codProduto[i]);
                                printf("Nome: %s\n", nomeProduto[i]);
                                printf("Valor: %.2f\n", valorProduto[i]);
                                printf("-------------------------------------\n");
                            }
                        }
                        break;

                    default:
                        printf("\nOPÇÃO INVÁLIDA!\n");
                        break;
                }
            }
        }
    }

    return 0;
}
