#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <unistd.h> // Inclui a função sleep() para simular o processamento de pagamento

#define MAX_PRODUTOS 100 // Define o número máximo de produtos que podem ser cadastrados

// Estrutura para armazenar as informações de um produto
typedef struct {
    int codProduto; // Código do produto
    char nomeProduto[30]; // Nome do produto
    float valorProduto; // Valor do produto
} Produto;

// Declaração de variáveis globais
Produto produtos[MAX_PRODUTOS]; // Array para armazenar os produtos
int numProdutos = 0; // Contador de produtos cadastrados
int caixaAberto = 0; // Flag para verificar se o caixa está aberto
float saldoInicial = 0.0; // Saldo inicial do caixa
float saldoAtual = 0.0; // Saldo atual do caixa

// Função para gravar os produtos cadastrados em um arquivo
void gravarProdutos() {
    FILE *file = fopen("produtos.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para gravar.\n");
        return;
    }
    // Grava as informações de cada produto no arquivo
    for (int i = 0; i < numProdutos; i++) {
        fprintf(file, "%d %s %.2f\n", produtos[i].codProduto, produtos[i].nomeProduto, produtos[i].valorProduto);
    }
    fclose(file);
    printf("Produtos gravados com sucesso!\n");
}

// Função para mostrar os produtos cadastrados
void mostrarProdutos() {
    if (numProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }
    printf("\nProdutos Cadastrados:\n");
    printf("---------------------------------------\n");
    // Exibe as informações de cada produto
    for (int i = 0; i < numProdutos; i++) {
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
    while (scanf("%d", &x) != 1 || x <= 0) {
        printf("Entrada inválida. Tente novamente.\n");
        while(getchar() != '\n');
    }
    // Cadastra os produtos conforme a quantidade informada
    for (int i = 0; i < x && numProdutos < MAX_PRODUTOS; i++) {
        printf("---------------------------------------\n");
        printf("********CADASTRO DE PRODUTOS***********\n");
        printf("---------------------------------------\n");

        printf("\nCÓDIGO DO PRODUTO:                   \n");
        scanf("%d", &produtos[numProdutos].codProduto);

        printf("\nNOME DO PRODUTO:                     \n");
        getchar(); // Limpa o buffer do stdin
        fgets(produtos[numProdutos].nomeProduto, sizeof(produtos[numProdutos].nomeProduto), stdin);
        produtos[numProdutos].nomeProduto[strcspn(produtos[numProdutos].nomeProduto, "\n")] = 0; // Remove a nova linha

        printf("\nVALOR UNITÁRIO DO PRODUTO:           \n");
        while (scanf("%f", &produtos[numProdutos].valorProduto) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while(getchar() != '\n');
        }

        printf("\nPRODUTO CADASTRADO COM SUCESSO!!! \n\n");
        numProdutos++;
    }
    gravarProdutos(); // Chama a função para gravar os produtos em um arquivo
}

// Função para abrir o caixa
void abrirCaixa() {
    if (caixaAberto) {
        printf("O caixa já está aberto.\n");
        return;
    }
    if (!autenticarFuncionario()) {
        return; // Se a autenticação falhar, retorna
    }
    printf("Digite o saldo inicial para abrir o caixa: ");
    while (scanf("%f", &saldoInicial) != 1 || saldoInicial < 0) {
        printf("Entrada inválida. Tente novamente.\n");
    }
    saldoAtual = saldoInicial; // Inicializa o saldo atual com o saldo inicial
    caixaAberto = 1; // Marca o caixa como aberto
    printf("Caixa aberto com sucesso! Saldo inicial: R$ %.2f\n", saldoInicial);
}

// Função para fechar o caixa
void fecharCaixa() {
    if (!caixaAberto) {
        printf("O caixa não está aberto.\n");
        return;
    }
    printf("Fechando caixa...\n");
    printf("Saldo final: R$ %.2f\n", saldoAtual);
    caixaAberto = 0; // Marca o caixa como fechado
}

// Função para exibir o saldo do caixa
void exibirSaldoCaixa() {
    if (!caixaAberto) {
        printf("O caixa está fechado.\n");
        return;
    }
    printf("Saldo atual do caixa: R$ %.2f\n", saldoAtual);
}

// Função para autenticar o funcionário
int autenticarFuncionario() {
    const int idGabriela = 1234; // ID da funcionária Gabriela
    const int idGabriel = 12345; // ID do funcionário Gabriel
    int tentativas = 3; // Número de tentativas para autenticação
    int idFuncionario; // Variável para armazenar o ID do funcionário

    // Loop para solicitar o ID do funcionário até que ele seja autenticado ou as tentativas se esgotem
    for (int i = 0; i < tentativas; i++) {
        printf("\nDigite seu ID de funcionário: ");
        scanf("%d", &idFuncionario);

        if (idFuncionario == idGabriela) {
            printf("\nAcesso concedido, Gabriela. Função: operadora de caixa\n");
            return 1; // Acesso concedido
        } else if (idFuncionario == idGabriel) {
            printf("\nAcesso concedido, Gabriel. Função: diretor\n");
            return 1; // Acesso concedido
        } else {
            printf("\nAcesso negado. ID inválido.\n");
            printf("Você tem mais %d tentativa(s).\n", tentativas - i - 1);
        }
    }
    printf("\nNúmero máximo de tentativas atingido. Acesso bloqueado.\n");
    return 0; // Acesso negado
}

// Função para registrar uma compra
void registrarCompra() {
    if (!caixaAberto) {
        printf("O caixa está fechado. Abra o caixa antes de registrar uma compra.\n");
        return;
    }

    int codProduto, quantidade; // Variáveis para o código e quantidade do produto
    float totalCompra = 0.0; // Variável para armazenar o total da compra
    char continuarCompra; // Variável para controle do loop de compra
    int tipoPagamento; // Variável para armazenar o tipo de pagamento

    printf("Iniciando o registro de compra...\n");

    // Loop para registrar produtos até que o usuário decida parar
    do {
        printf("Digite o código do produto: ");
        scanf("%d", &codProduto);

        int produtoEncontrado = 0; // Flag para verificar se o produto foi encontrado
        for (int i = 0; i < numProdutos; i++) {
            if (produtos[i].codProduto == codProduto) {
                produtoEncontrado = 1;

                printf("Produto: %s\n", produtos[i].nomeProduto);
                printf("Valor unitário: R$ %.2f\n", produtos[i].valorProduto);
                
                printf("Digite a quantidade: ");
                while (scanf("%d", &quantidade) != 1 || quantidade <= 0) {
                    printf("Quantidade inválida. Tente novamente.\n");
                    while(getchar() != '\n');
                }

                float totalProduto = produtos[i].valorProduto * quantidade; // Cálculo do subtotal
                totalCompra += totalProduto; // Adiciona o subtotal ao total da compra

                printf("Subtotal para %d x %s: R$ %.2f\n", quantidade, produtos[i].nomeProduto, totalProduto);
                break; // Sai do loop após encontrar o produto
            }
        }

        if (!produtoEncontrado) {
            printf("Produto não encontrado. Tente novamente.\n");
        }

        printf("Deseja registrar outro produto? (S/N): ");
        getchar(); // Limpa o buffer do stdin
        continuarCompra = getchar(); // Lê a opção do usuário

    } while (continuarCompra == 'S' || continuarCompra == 's');

    // Mostrar o total da compra antes de pedir a forma de pagamento
    printf("\nTotal da compra: R$ %.2f\n", totalCompra);

    printf("\nEscolha a forma de pagamento:\n");
    printf("1 - Dinheiro\n");
    printf("2 - Cartão de Crédito\n");
    printf("3 - Cartão de Débito\n");
    printf("Digite sua opção: ");
    scanf("%d", &tipoPagamento);

    // Processa o pagamento de acordo com a forma escolhida
    switch (tipoPagamento) {
        case 1: // Dinheiro
            {
                float valorPago, troco; // Variáveis para o valor pago e o troco
                printf("Digite o valor pago: R$ ");
                while (scanf("%f", &valorPago) != 1 || valorPago < totalCompra) {
                    printf("Valor inválido. Deve ser maior ou igual ao total da compra.\n");
                    while(getchar() != '\n');
                }
                troco = valorPago - totalCompra; // Cálculo do troco
                printf("Troco a devolver: R$ %.2f\n", troco);
                saldoAtual += totalCompra; // Adiciona o total da compra ao saldo do caixa
                printf("Compra registrada com sucesso!\n");
            }
            break;

        case 2: // Cartão de Crédito
            {
                printf("Processando pagamento com cartão de crédito...\n");
                sleep(3); // Simula o tempo de processamento
                saldoAtual += totalCompra; // Adiciona o total da compra ao saldo do caixa
                printf("Pagamento aprovado! Compra registrada com sucesso!\n");
            }
            break;

        case 3: // Cartão de Débito
            {
                printf("Processando pagamento com cartão de débito...\n");
                sleep(3); // Simula o tempo de processamento
                saldoAtual += totalCompra; // Adiciona o total da compra ao saldo do caixa
                printf("Pagamento aprovado! Compra registrada com sucesso!\n");
            }
            break;

        default:
            printf("Opção de pagamento inválida.\n");
            break;
    }
}

// Função principal
int main() {
    setlocale(LC_ALL, "Portuguese"); // Configura a localidade para português
    int firstOption; // Opção principal do menu

    while (1) {
        printf("\n---------------------------------------\n");
        printf("*******HORTIFRUIT GREEN HARVEST********\n");
        printf("**********MENU PRINCIPAL***************\n");
        printf("---------------------------------------\n");
        printf("\n      DIGITE SOMENTE NÚMEROS         \n");
        printf("\n\nSELECIONE A OPÇÃO REQUERIDA:       \n");
        printf("\n(1) - OPERAÇÃO DE PRODUTOS             \n");
        printf("\n(2) - CAIXA                            \n");
        printf("\n(3) - SAIR                             \n");
        printf("---------------------------------------\n");

        scanf("%d", &firstOption);

        // Opção para operações de produtos
        if (firstOption == 1) {
            while (1) {
                int selectNumber; // Número da opção do menu de operações de produtos
                printf("\n\n---------------------------------------\n");
                printf("*******HORTIFRUIT GREEN HARVEST********\n");
                printf("**********OPERAÇÃO DE PRODUTOS*********\n");
                printf("---------------------------------------\n");
                printf("\n      DIGITE SOMENTE NÚMEROS         \n");
                printf("\n\nSELECIONE A OPÇÃO REQUERIDA:       \n");
                printf("\n(1) - CADASTRAR PRODUTOS               \n");
                printf("\n(2) - MOSTRAR PRODUTOS                 \n");
                printf("\n(0) - VOLTAR                           \n");
                printf("---------------------------------------\n");

                scanf("%d", &selectNumber);

                // Verifica se a opção é válida
                if (selectNumber < 0 || selectNumber > 2) {
                    printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
                    continue;
                }

                if (selectNumber == 0) {
                    break; // Sai do loop se a opção for voltar
                }

                // Executa a ação de acordo com a opção selecionada
                switch (selectNumber) {
                    case 1:
                        cadastrarProdutos(); // Chama a função para cadastrar produtos
                        break;
                    case 2:
                        mostrarProdutos(); // Chama a função para mostrar produtos
                        break;
                }
            }
        } 
        // Opção para operações do caixa
        else if (firstOption == 2) {
            while (1) {
                int caixaOption; // Número da opção do menu de operações de caixa
                printf("\n\n---------------------------------------\n");
                printf("*******HORTIFRUIT GREEN HARVEST********\n");
                printf("***********OPERAÇÃO DE CAIXA***********\n");
                printf("---------------------------------------\n");
                printf("\n      DIGITE SOMENTE NÚMEROS         \n");
                printf("\n\nSELECIONE A OPÇÃO REQUERIDA:       \n");
                printf("\n(1) - ABRIR CAIXA                     \n");
                printf("\n(2) - FECHAR CAIXA                    \n");
                printf("\n(3) - EXIBIR SALDO DO CAIXA           \n");
                printf("\n(4) - REGISTRAR COMPRA                \n");
                printf("\n(0) - VOLTAR                          \n");
                printf("---------------------------------------\n");

                scanf("%d", &caixaOption);

                // Verifica se a opção é válida
                if (caixaOption < 0 || caixaOption > 4) {
                    printf("\nERRO: DIGITE O NÚMERO NOVAMENTE\n\n");
                    continue;
                }

                if (caixaOption == 0) {
                    break; // Sai do loop se a opção for voltar
                }

                // Executa a ação de acordo com a opção selecionada
                switch (caixaOption) {
                    case 1:
                        abrirCaixa(); // Chama a função para abrir o caixa
                        break;
                    case 2:
                        fecharCaixa(); // Chama a função para fechar o caixa
                        break;
                    case 3:
                        exibirSaldoCaixa(); // Chama a função para exibir o saldo do caixa
                        break;
                    case 4:
                        registrarCompra(); // Chama a função para registrar uma compra
                        break;
                }
            }
        } else if (firstOption == 3) {
            printf("\nFUNCIONALIDADE INDISPONÍVEL\n\n");
        }
    }

    return 0; // Termina o programa
}
