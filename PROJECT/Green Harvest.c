#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    int codProduto;
    char nomeProduto[30];
    float valorProduto;
} Produto;
/*                          
                
                */


Produto produtos[MAX_PRODUTOS];
int numProdutos = 0;
int caixaAberto = 0;  // Flag to check if the cash register is open
float saldoInicial = 0.0;
float saldoAtual = 0.0;

/*

*/



void gravarProdutos() {
    FILE *file = fopen("produtos.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para gravar.\n");
        return;
    }
    
    

    for (int i = 0; i < numProdutos; i++) {
        fprintf(file, "%d %s %.2f\n", produtos[i].codProduto, produtos[i].nomeProduto, produtos[i].valorProduto);
    }
    
    

    fclose(file);
    printf("Produtos gravados com sucesso!\n");
}



void mostrarProdutos() {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    
    

    printf("\nProdutos Cadastrados:\n");
    printf("---------------------------------------\n");
    for (int i = 0; i < numProdutos; i++) {
        printf("CÓDIGO: %d\n", produtos[i].codProduto);
        printf("NOME: %s\n", produtos[i].nomeProduto);
        printf("VALOR: %.2f\n", produtos[i].valorProduto);
        printf("---------------------------------------\n");
    }
}



void cadastrarProdutos() {
    printf("\nDIGITE A QUANTIDADE DE PRODUTOS QUE SERÃO CADASTRADOS: ");
    int x;

    
    
    while (scanf("%d", &x) != 1 || x <= 0) {
        printf("Entrada inválida. Tente novamente.\n");
        while(getchar() != '\n'); // Limpa o buffer
    }
    
    

    for (int i = 0; i < x && numProdutos < MAX_PRODUTOS; i++) {
        printf("---------------------------------------\n");
        printf("********CADASTRO DE PRODUTOS***********\n");
        printf("---------------------------------------\n");

        printf("\nCÓDIGO DO PRODUTO:                   \n");
        scanf("%d", &produtos[numProdutos].codProduto);

        printf("\nNOME DO PRODUTO:                     \n");
        getchar(); // Limpa o newline
        fgets(produtos[numProdutos].nomeProduto, sizeof(produtos[numProdutos].nomeProduto), stdin);
        produtos[numProdutos].nomeProduto[strcspn(produtos[numProdutos].nomeProduto, "\n")] = 0;

        printf("\nVALOR UNITÁRIO DO PRODUTO:           \n");
        while (scanf("%f", &produtos[numProdutos].valorProduto) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while(getchar() != '\n'); // Limpa o buffer
        }
        
        
        

        printf("\n-------------------------------------\n");
        printf("\nCÓDIGO DO PRODUTO: %d\n", produtos[numProdutos].codProduto);
        printf("\nNOME DO PRODUTO:   %s\n", produtos[numProdutos].nomeProduto);
        printf("\nVALOR UNITÁRIO DO PRODUTO:   %.2f\n", produtos[numProdutos].valorProduto);
        printf("\nPRODUTO CADASTRADO COM SUCESSO!!! \n\n");

        numProdutos++;
    }
    
    

    gravarProdutos();
}



void abrirCaixa() {
    if (caixaAberto) {
        printf("O caixa já está aberto.\n");
        return;
    }
    
    

    printf("Digite o saldo inicial para abrir o caixa: ");
    while (scanf("%f", &saldoInicial) != 1 || saldoInicial < 0) {
        printf("Entrada inválida. Tente novamente.\n");
        while(getchar() != '\n'); // Limpa o buffer
    }
    
    

    saldoAtual = saldoInicial;
    caixaAberto = 1;
    printf("Caixa aberto com sucesso! Saldo inicial: R$ %.2f\n", saldoInicial);
}



void fecharCaixa() {
    if (!caixaAberto) {
        printf("O caixa não está aberto.\n");
        return;
    }
    
    

    printf("Fechando caixa...\n");
    printf("Saldo final: R$ %.2f\n", saldoAtual);
    caixaAberto = 0;
}



void exibirSaldoCaixa() {
    if (!caixaAberto) {
        printf("O caixa está fechado.\n");
        return;
    }
    
    

    printf("Saldo atual do caixa: R$ %.2f\n", saldoAtual);
}



int main() {
    setlocale(LC_ALL, "Portuguese");

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

        if (firstOption < 1 || firstOption > 3) {
            printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
            continue;
        }
        
        
        

        if (firstOption == 1) {
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
                printf("\n(0) - VOLTAR                         \n");
                printf("---------------------------------------\n");
                scanf("%d", &selectNumber);

                if (selectNumber < 0 || selectNumber > 3) {
                    printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
                    continue;
                }
                
                

                if (selectNumber == 0) {
                    break;
                }
                
                

                switch (selectNumber) {
                    case 1:
                        cadastrarProdutos();
                        break;
                        
                        

                    case 2:
                        mostrarProdutos();
                        break;
                        
                        

                    case 3:
                        printf("\nFUNÇÃO NÃO HABILITADA\n");
                        break;
                        
                }
            }
            
            
            
        } else if (firstOption == 2) {
            
            
            
            while (1) {
                    
                    
                    
                int opcaoCaixa;
                printf("\n\n---------------------------------------\n");
                printf("*******HORTIFRUIT GREEN HARVEST********\n");
                printf("**********OPERAÇÃO DE CAIXA************\n");
                printf("---------------------------------------\n");
                printf("\n(1) - ABRIR CAIXA                    \n");
                printf("\n(2) - FECHAR CAIXA                   \n");
                printf("\n(3) - MOSTRAR SALDO DO CAIXA         \n");
                printf("\n(0) - VOLTAR                         \n");
                printf("---------------------------------------\n");

                scanf("%d", &opcaoCaixa);
                
                
                

                if (opcaoCaixa < 0 || opcaoCaixa > 3) {
                    printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
                    continue;
                }
                
                
                

                if (opcaoCaixa == 0) {
                    break;
                }
                
                
                

                switch (opcaoCaixa) {
                    
                    
                    
                    case 1:
                        abrirCaixa();
                        break;
                        
                        
                        

                    case 2:
                        fecharCaixa();
                        break;
                        
                        
                        

                    case 3:
                        exibirSaldoCaixa();
                        break;


                }
            }
        }
    }

    
    
    
    
    return 0;
}
