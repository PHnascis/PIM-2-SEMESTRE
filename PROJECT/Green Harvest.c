#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <unistd.h> // Inclui a função sleep()

#define MAX_PRODUTOS 100

typedef struct {
    int codProduto;
    char nomeProduto[30];
    float valorProduto;
} Produto;

Produto produtos[MAX_PRODUTOS];
int numProdutos = 0;
int caixaAberto = 0;
float saldoInicial = 0.0;
float saldoAtual = 0.0;

void exibirEspecificacoesServidor() {
    printf("\n---------------------------------------\n");
    printf("Status: Conectando ao servidor...\n");
    sleep(5); // Pausa de 5 segundos
    printf("Status: Conectado\n");
    printf("---------------------------------------\n");
    printf("*******        SERVIDOR       ********\n");
    printf("---------------------------------------\n");
    printf("Processador: Intel Xeon Silver ou AMD EPYC\n");
    printf("Núcleos: 4 a 8 núcleos\n");
    printf("Frequência: 2.4 GHz ou mais\n");
    printf("Memória RAM: 16 GB DDR4 ou DDR5\n");
    printf("Armazenamento: SSD de 512 GB a 1 TB\n");
    printf("RAID: RAID 1 ou RAID 10\n");
    printf("Sistema Operacional: Linux (Ubuntu Server ou CentOS) ou Windows Server\n");
    printf("Conectividade: Gigabit Ethernet, Wi-Fi opcional\n");
    printf("Portas: USB, Serial para periféricos de PDV\n");
    printf("UPS (Nobreak): Fonte de alimentação com proteção e redundância\n");
    printf("Segurança: Firewall, VPN e backup automático\n");
    printf("Compatibilidade: Suporte para sistema de PDV\n");
    printf("---------------------------------------\n");
}

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
        while(getchar() != '\n');
    }
    for (int i = 0; i < x && numProdutos < MAX_PRODUTOS; i++) {
        printf("---------------------------------------\n");
        printf("********CADASTRO DE PRODUTOS***********\n");
        printf("---------------------------------------\n");

        printf("\nCÓDIGO DO PRODUTO:                   \n");
        scanf("%d", &produtos[numProdutos].codProduto);

        printf("\nNOME DO PRODUTO:                     \n");
        getchar();
        fgets(produtos[numProdutos].nomeProduto, sizeof(produtos[numProdutos].nomeProduto), stdin);
        produtos[numProdutos].nomeProduto[strcspn(produtos[numProdutos].nomeProduto, "\n")] = 0;

        printf("\nVALOR UNITÁRIO DO PRODUTO:           \n");
        while (scanf("%f", &produtos[numProdutos].valorProduto) != 1) {
            printf("Entrada inválida. Tente novamente.\n");
            while(getchar() != '\n');
        }

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
    if (!autenticarFuncionario()) {
        return;
    }
    printf("Digite o saldo inicial para abrir o caixa: ");
    while (scanf("%f", &saldoInicial) != 1 || saldoInicial < 0) {
        printf("Entrada inválida. Tente novamente.\n");
        while(getchar() != '\n');
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

int autenticarFuncionario() {
    const int idGabriela = 1234;
    const int idGabriel = 4321;
    int tentativas = 3;
    int idFuncionario;

    for (int i = 0; i < tentativas; i++) {
        printf("\nDigite seu ID de funcionário: ");
        scanf("%d", &idFuncionario);

        if (idFuncionario == idGabriela) {
            printf("\nAcesso concedido, Gabriela. Função: operadora de caixa\n");
            return 1;
        } else if (idFuncionario == idGabriel) {
            printf("\nAcesso concedido, Gabriel. Função: diretor\n");
            return 1;
        } else {
            printf("\nAcesso negado. ID inválido.\n");
            printf("Você tem mais %d tentativa(s).\n", tentativas - i - 1);
        }
    }
    printf("\nNúmero máximo de tentativas atingido. Acesso bloqueado.\n");
    return 0;
}

void registrarCompra() {
    if (!caixaAberto) {
        printf("O caixa está fechado. Abra o caixa antes de registrar uma compra.\n");
        return;
    }

    int codProduto, quantidade;
    float totalCompra = 0.0;
    char continuarCompra;
    int tipoPagamento;

    printf("Iniciando o registro de compra...\n");

    do {
        printf("Digite o código do produto: ");
        scanf("%d", &codProduto);

        int produtoEncontrado = 0;
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

                float totalProduto = produtos[i].valorProduto * quantidade;
                totalCompra += totalProduto;

                printf("Subtotal para %d x %s: R$ %.2f\n", quantidade, produtos[i].nomeProduto, totalProduto);
                break;
            }
        }

        if (!produtoEncontrado) {
            printf("Produto não encontrado. Tente novamente.\n");
        }

        printf("Deseja registrar outro produto? (S/N): ");
        getchar();
        continuarCompra = getchar();

    } while (continuarCompra == 'S' || continuarCompra == 's');

    printf("\nTotal da compra: R$ %.2f\n", totalCompra);

    printf("\nEscolha a forma de pagamento:\n");
    printf("1 - Dinheiro\n");
    printf("2 - Cartão de Crédito\n");
    printf("3 - Cartão de Débito\n");
    printf("Digite a opção de pagamento: ");
    scanf("%d", &tipoPagamento);

    if (tipoPagamento == 1) {
        float valorPago;
        printf("Digite o valor pago: ");
        while (scanf("%f", &valorPago) != 1 || valorPago < totalCompra) {
            printf("Valor insuficiente. Insira um valor maior ou igual ao total da compra.\n");
            while(getchar() != '\n');
        }
        float troco = valorPago - totalCompra;
        saldoAtual += totalCompra;
        printf("Troco: R$ %.2f\n", troco);
    } else if (tipoPagamento == 2 || tipoPagamento == 3) {
        saldoAtual += totalCompra;
        printf("Pagamento realizado com sucesso.\n");
    } else {
        printf("Opção de pagamento inválida. Compra não registrada.\n");
        return;
    }

    printf("Compra registrada com sucesso!\n");
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
        printf("\n(2) - CAIXA                         \n");
        printf("\n(3) - SERVIDOR                       \n");
        printf("\n(4) - SAIR                           \n");
        printf("---------------------------------------\n");

        scanf("%d", &firstOption);

        if (firstOption == 1) {
            int productOption;
            printf("\n(1) - Cadastrar Produtos\n");
            printf("(2) - Listar Produtos\n");
            printf("Escolha uma opção: ");
            scanf("%d", &productOption);

            if (productOption == 1) {
                cadastrarProdutos();
            } else if (productOption == 2) {
                mostrarProdutos();
            } else {
                printf("Opção inválida.\n");
            }

        } else if (firstOption == 2) {
            int caixaOption;
            printf("\n(1) - Abrir Caixa\n");
            printf("(2) - Fechar Caixa\n");
            printf("(3) - Exibir Saldo do Caixa\n");
            printf("(4) - Registrar Compra\n");
            printf("Escolha uma opção: ");
            scanf("%d", &caixaOption);

            if (caixaOption == 1) {
                abrirCaixa();
            } else if (caixaOption == 2) {
                fecharCaixa();
            } else if (caixaOption == 3) {
                exibirSaldoCaixa();
            } else if (caixaOption == 4) {
                registrarCompra();
            } else {
                printf("Opção inválida.\n");
            }

        } else if (firstOption == 3) {
            exibirEspecificacoesServidor();
        } else if (firstOption == 4) {
            printf("Saindo do sistema...\n");
            break;
        } else {
            printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
