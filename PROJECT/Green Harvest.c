#include <stdio.h>   // Inclui a biblioteca padrão de entrada e saída
#include <locale.h>  // Inclui a biblioteca para configurações de localização (usada para definir a localidade do programa)
#include <string.h>  // Inclui a biblioteca para manipulação de strings

#define MAX_PRODUTOS 100  // Define o número máximo de produtos que podem ser cadastrados

// Definição da estrutura Produto
typedef struct {
    int codProduto;           // Código do produto
    char nomeProduto[30];     // Nome do produto, com até 30 caracteres
    float valorProduto;       // Valor unitário do produto
} Produto;

// Variáveis globais
Produto produtos[MAX_PRODUTOS];  // Array que armazena todos os produtos cadastrados
int numProdutos = 0;             // Contador para o número de produtos cadastrados
int caixaAberto = 0;             // Flag para indicar se o caixa está aberto (0 = fechado, 1 = aberto)
float saldoInicial = 0.0;        // Saldo inicial do caixa
float saldoAtual = 0.0;          // Saldo atual do caixa

// Função para gravar produtos em um arquivo
void gravarProdutos() {
    FILE *file = fopen("produtos.txt", "w");  // Abre o arquivo "produtos.txt" no modo escrita ("w")
    if (file == NULL) {  // Verifica se houve erro ao abrir o arquivo
        printf("Erro ao abrir o arquivo para gravar.\n");  // Exibe mensagem de erro
        return;  // Retorna se o arquivo não pôde ser aberto
    }

    // Grava os produtos no arquivo
    for (int i = 0; i < numProdutos; i++) {
        fprintf(file, "%d %s %.2f\n", produtos[i].codProduto, produtos[i].nomeProduto, produtos[i].valorProduto);
        // Escreve o código, nome e valor do produto no arquivo
    }

    fclose(file);  // Fecha o arquivo
    printf("Produtos gravados com sucesso!\n");  // Informa que os produtos foram gravados
}

// Função para exibir os produtos cadastrados
void mostrarProdutos() {
    if (numProdutos == 0) {  // Verifica se não há produtos cadastrados
        printf("Nenhum produto cadastrado.\n");  // Exibe mensagem se não houver produtos
        return;  // Retorna se não houver produtos
    }

    // Exibe os produtos cadastrados
    printf("\nProdutos Cadastrados:\n");
    printf("---------------------------------------\n");
    for (int i = 0; i < numProdutos; i++) {  // Loop para percorrer e exibir os produtos
        printf("CÓDIGO: %d\n", produtos[i].codProduto);
        printf("NOME: %s\n", produtos[i].nomeProduto);
        printf("VALOR: %.2f\n", produtos[i].valorProduto);
        printf("---------------------------------------\n");
    }
}

// Função para cadastrar novos produtos
void cadastrarProdutos() {
    printf("\nDIGITE A QUANTIDADE DE PRODUTOS QUE SERÃO CADASTRADOS: ");
    int x;

    // Verifica se a entrada é válida
    while (scanf("%d", &x) != 1 || x <= 0) {
        printf("Entrada inválida. Tente novamente.\n");
        while(getchar() != '\n');  // Limpa o buffer de entrada
    }

    // Loop para cadastrar os produtos
    for (int i = 0; i < x && numProdutos < MAX_PRODUTOS; i++) {
        printf("---------------------------------------\n");
        printf("********CADASTRO DE PRODUTOS***********\n");
        printf("---------------------------------------\n");

        // Lê o código do produto
        printf("\nCÓDIGO DO PRODUTO:                   \n");
        scanf("%d", &produtos[numProdutos].codProduto);

        // Lê o nome do produto
        printf("\nNOME DO PRODUTO:                     \n");
        getchar();  // Limpa o newline que ficou no buffer
        fgets(produtos[numProdutos].nomeProduto, sizeof(produtos[numProdutos].nomeProduto), stdin);  // Lê o nome do produto
        produtos[numProdutos].nomeProduto[strcspn(produtos[numProdutos].nomeProduto, "\n")] = 0;  // Remove o newline no final da string

        // Lê o valor unitário do produto
        printf("\nVALOR UNITÁRIO DO PRODUTO:           \n");
        while (scanf("%f", &produtos[numProdutos].valorProduto) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while(getchar() != '\n');  // Limpa o buffer de entrada
        }

        // Exibe o resumo do produto cadastrado
        printf("\n-------------------------------------\n");
        printf("\nCÓDIGO DO PRODUTO: %d\n", produtos[numProdutos].codProduto);
        printf("\nNOME DO PRODUTO:   %s\n", produtos[numProdutos].nomeProduto);
        printf("\nVALOR UNITÁRIO DO PRODUTO:   %.2f\n", produtos[numProdutos].valorProduto);
        printf("\nPRODUTO CADASTRADO COM SUCESSO!!! \n\n");

        numProdutos++;  // Incrementa o número de produtos cadastrados
    }

    gravarProdutos();  // Chama a função para gravar os produtos cadastrados em um arquivo
}

// Função para abrir o caixa
void abrirCaixa() {
    if (caixaAberto) {  // Verifica se o caixa já está aberto
        printf("O caixa já está aberto.\n");
        return;
    }

    // Lê o saldo inicial do caixa
    printf("Digite o saldo inicial para abrir o caixa: ");
    while (scanf("%f", &saldoInicial) != 1 || saldoInicial < 0) {
        printf("Entrada inválida. Tente novamente.\n");
        while(getchar() != '\n');  // Limpa o buffer de entrada
    }

    saldoAtual = saldoInicial;  // Define o saldo atual como o saldo inicial
    caixaAberto = 1;  // Marca o caixa como aberto
    printf("Caixa aberto com sucesso! Saldo inicial: R$ %.2f\n", saldoInicial);
}

// Função para fechar o caixa
void fecharCaixa() {
    if (!caixaAberto) {  // Verifica se o caixa está fechado
        printf("O caixa não está aberto.\n");
        return;
    }

    // Exibe o saldo final e fecha o caixa
    printf("Fechando caixa...\n");
    printf("Saldo final: R$ %.2f\n", saldoAtual);
    caixaAberto = 0;  // Marca o caixa como fechado
}

// Função para exibir o saldo atual do caixa
void exibirSaldoCaixa() {
    if (!caixaAberto) {  // Verifica se o caixa está fechado
        printf("O caixa está fechado.\n");
        return;
    }

    printf("Saldo atual do caixa: R$ %.2f\n", saldoAtual);  // Exibe o saldo atual
}

// Função para autenticar o funcionário
int autenticarFuncionario() {
    const int idGabriela = 1234;  // ID da funcionária Gabriela
    const int idGabriel = 12345;  // ID do funcionário Gabriel
    int tentativas = 3;  // Número de tentativas para autenticação
    int idFuncionario;

    // Loop para autenticação com 3 tentativas
    for (int i = 0; i < tentativas; i++) {
        printf("\nDigite seu ID de funcionário: ");
        scanf("%d", &idFuncionario);

        // Verifica se o ID é de Gabriela ou Gabriel
        if (idFuncionario == idGabriela) {
            printf("\nAcesso concedido, Gabriela. Função: operadora de caixa\n");
            return 1;  // Autenticação bem-sucedida
        } else if (idFuncionario == idGabriel) {
            printf("\nAcesso concedido, Gabriel. Função: diretor\n");
            return 1;  // Autenticação bem-sucedida
        } else {
            printf("\nAcesso negado. ID inválido.\n");
            printf("Você tem mais %d tentativa(s).\n", tentativas - i - 1);
        }
    }

    printf("\nNúmero máximo de tentativas atingido. Acesso bloqueado.\n");
    return 0;  // Falha na autenticação
}

int main() {
    setlocale(LC_ALL, "Portuguese");  // Define a localidade para o idioma português

    while (1) {  // Loop principal do programa
        int firstOption;

        // Exibe o menu principal
        printf("---------------------------------------\n");
        printf("*******HORTIFRUIT GREEN HARVEST********\n");
        printf("---------------------------------------\n");
        printf("\n      DIGITE SOMENTE NÚMEROS         \n");
        printf("\n\nSELECIONE A OPÇÃO REQUERIDA:       \n");
        printf("\n(1) - PRODUTOS                       \n");
        printf("\n(2) - OPERAÇÃO DE CAIXA              \n");
        printf("\n(3) - SERVIÇOS DO SERVIDOR           \n");
        printf("---------------------------------------\n");

        scanf("%d", &firstOption);  // Lê a opção selecionada

        if (firstOption < 1 || firstOption > 3) {  // Verifica se a opção é inválida
            printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
            continue;  // Volta para o início do loop
        }

        if (firstOption == 1) {  // Se a opção for "PRODUTOS"
            while (1) {
                int selectNumber;

                // Exibe o menu de produtos
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

                if (selectNumber < 0 || selectNumber > 3) {  // Verifica se a opção é inválida
                    printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
                    continue;
                }

                if (selectNumber == 0) {  // Se a opção for "VOLTAR"
                    break;  // Sai do loop de produtos
                }

                switch (selectNumber) {
                    case 1:
                        cadastrarProdutos();  // Chama a função para cadastrar produtos
                        break;

                    case 2:
                        mostrarProdutos();  // Chama a função para exibir os produtos cadastrados
                        break;

                    case 3:
                        printf("\nFUNÇÃO NÃO HABILITADA\n");  // Caso não implementado
                        break;
                }
            }

        } else if (firstOption == 2) {  // Se a opção for "OPERAÇÃO DE CAIXA"
            if (autenticarFuncionario()) {  // Chama a função de autenticação
                while (1) {  // Loop para as opções de operação de caixa
                    int opcaoCaixa;

                    // Exibe o menu de operação de caixa
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

                    if (opcaoCaixa < 0 || opcaoCaixa > 3) {  // Verifica se a opção é inválida
                        printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
                        continue;
                    }

                    if (opcaoCaixa == 0) {  // Se a opção for "VOLTAR"
                        break;  // Sai do loop de operação de caixa
                    }

                    switch (opcaoCaixa) {
                        case 1:
                            abrirCaixa();  // Chama a função para abrir o caixa
                            break;

                        case 2:
                            fecharCaixa();  // Chama a função para fechar o caixa
                            break;

                        case 3:
                            exibirSaldoCaixa();  // Chama a função para exibir o saldo atual
                            break;
                    }
                }
            }
        }
        else{
            printf("\nFUNÇÃO NÃO HABILITADA\n\n");
        }




    }

    return 0;  // Retorna 0 para indicar que o programa foi executado com sucesso
}
