#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUTOS 100
//===============================================
// Programadores: Jose Cristovao e Neuria Helena
//===============================================

/* Este Projecto foi desenvolvido para o exame de programacao no IMETRO
 Aonde fomos desafiados pelo Professor Macaba Nobre a solucionar um problema que as pessoas enfrentam no dia-a-dia
 E um dos problemas que encontramos foi a falta de historicos nos sisetmas de vendas dos Supermercadoos
 Os supermercados em Angola dao faturas para os seus clientes e as mesmas faturas devem ser usadas para comprovar uma determinada compra
 E muitas pessoas que querem reclamar ou fazer a devolucao de um produto por defeito muitas das vezes extraviam ou mesmo perdem a fatura
 E isso resulta em descontentamento e frustacao por parte do cliente e com isso surgiu a ideia deste projecto que facilitara nas reclamcoes
 E dara mais seguranca aos consumidores.*/


typedef struct Produto {
    char nome[50];
    float preco;
    int quantidade;
} Produto;


typedef struct Cliente {
    char nome[50];
    int id;
} Cliente;


void salvar_historico(Cliente cliente, Produto produto, int qtd, float total, float valor_pago, float troco) {
    FILE *arq = fopen("historico.txt", "a"); // Salva hist�rico geral
    time_t t = time(NULL);
    struct tm *data = localtime(&t);

    if(arq == NULL) {
        printf("Erro ao salvar historico!\n");
        return;
    }

    fprintf(arq,
        "Data: %02d/%02d/%d %02d:%02d\n"
        "Cliente: %s\n"
        "ID: %d\n"
        "Produto: %s\n"
        "Quantidade: %d\n"
        "Preco Unitario: %.2f Kz\n"
        "Total: %.2f Kz\n"
        "Valor Pago: %.2f Kz\n"
        "Troco: %.2f Kz\n\n",
        data->tm_mday, data->tm_mon+1, data->tm_year+1900,
        data->tm_hour, data->tm_min,
        cliente.nome, cliente.id,
        produto.nome, qtd,
        produto.preco, total, valor_pago, troco
    );

    fclose(arq);
}

void gerar_comprovativo(Cliente cliente, Produto produto, int qtd, float total, float valor_pago, float troco) {
    FILE *arq = fopen("comprovativo.txt", "a"); // Gera comprovativo autom�tico
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);

    fprintf(arq,
        "=========== COMPROVATIVO ===========\n"
        "Data: %02d/%02d/%d %02d:%02d\n"
        "Cliente: %s\n"
        "ID: %d\n"
        "Produto: %s\n"
        "Quantidade: %d\n"
        "Preco Unitario: %.2f Kz\n"
        "Total: %.2f Kz\n"
        "Valor Pago: %.2f Kz\n"
        "Troco: %.2f Kz\n"
        "===================================\n\n",
        tm->tm_mday, tm->tm_mon+1, tm->tm_year+1900,
        tm->tm_hour, tm->tm_min,
        cliente.nome, cliente.id,
        produto.nome, qtd,
        produto.preco, total, valor_pago, troco
    );

    fclose(arq);
}

void mostrar_historico() {
    FILE *arq = fopen("historico.txt", "r"); // Mostrar todo o hist�rico
    char linha[200];

    if(arq == NULL) {
        printf("Historico inexistente!\n");
        return;
    }

    printf("\n====== HISTORICO DE COMPRAS ======\n");
    while(fgets(linha, sizeof(linha), arq)) {
        printf("%s", linha);
    }

    fclose(arq);
}

void pesquisar_historico_cliente(int id) {
    FILE *arq = fopen("historico.txt", "r"); // Pesquisar hist�rico do cliente (ID)
    char linha[200];
    int encontrado = 0;

    if(arq == NULL) {
        printf("Historico inexistente!\n");
        return;
    }

    printf("\n====== HISTORICO DO CLIENTE (ID %d) ======\n", id);

    while(fgets(linha, sizeof(linha), arq)) {
        if(strncmp(linha, "ID: ", 4) == 0 && atoi(linha + 4) == id) {
            encontrado = 1;
            printf("%s", linha);

            while(fgets(linha, sizeof(linha), arq) && linha[0] != '\n') {
                printf("%s", linha);
            }
            printf("\n");
        }
    }

    if(!encontrado) {
        printf("Nenhum registro encontrado para este cliente.\n");
    }

    fclose(arq);
}

int carregar_produtos(Produto produtos[]) {
    FILE *arq = fopen("C:\\Users\\LENOVO\\Saved Games\\Documents\\Projeto LCC1M\\produtos.txt", "r"); // Carregar produtos do arquivo
    if(arq == NULL) {
        printf("Arquivo de produtos nao encontrado!\n");
        return 0;
    }

    int i = 0;
    char linha[100];

    while(fgets(linha, sizeof(linha), arq)) {
        if(i >= MAX_PRODUTOS) break;

        char *token = strtok(linha, ";");
        if(token) strcpy(produtos[i].nome, token);

        token = strtok(NULL, ";");
        if(token) produtos[i].preco = atof(token);

        token = strtok(NULL, ";");
        if(token) produtos[i].quantidade = atoi(token);

        i++;
    }

    fclose(arq);
    return i;
}


int buscar_produto(Produto produtos[], int total, char nome[]) {
    int i;
    for(i = 0; i < total; i++) {
        if(strcmp(produtos[i].nome, nome) == 0)
            return i;
    }
    return -1;
}


int main() {
    Cliente cliente;
    Produto produtos[MAX_PRODUTOS];

    int opcao = -1;
    int quantidade;
    float total, valor_pago, troco;
    int cliente_cadastrado = 0;

    while(opcao != 0) {
        system("cls");
        printf("=========== SISTEMA DE ATENDIMENTO ===========\n");
        printf("1 - Registrar Cliente\n");
        printf("2 - Cadastrar Compra\n");
        printf("3 - Historico de Compras (Geral)\n");
        printf("4 - Historico de Cliente (Por ID)\n");
        printf("5 - Listar Produtos (Stock)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        if(opcao == 1) {
            printf("Nome do cliente: ");
            fgets(cliente.nome, 50, stdin);
            cliente.nome[strcspn(cliente.nome, "\n")] = 0;
            cliente.id = rand() % 9000 + 1000;
            cliente_cadastrado = 1;
            cliente_cadastrado = 1++;
            printf("Cliente registrado! ID: %d\n", cliente.id);
        }

        else if(opcao == 2) {
            if(!cliente_cadastrado) {
                printf("Registre um cliente primeiro!\n");
            } else {
                int total_produtos = carregar_produtos(produtos);
                char nome_produto[50];

                printf("Produto: ");
                fgets(nome_produto, 50, stdin);
                nome_produto[strcspn(nome_produto, "\n")] = 0;

                int idx = buscar_produto(produtos, total_produtos, nome_produto);

                if(idx == -1) {
                    printf("Produto nao encontrado!\n");
                }
                else if(produtos[idx].quantidade <= 0) {
                    printf("STOCK ESGOTADO!\n");
                }
                else {
                    printf("Preco: %.2f Kz\n", produtos[idx].preco);
                    printf("Quantidade: ");
                    scanf("%d", &quantidade);
                    getchar();

                    total = produtos[idx].preco * quantidade;

                    printf("Valor pago: ");
                    scanf("%f", &valor_pago);
                    getchar();

                    troco = valor_pago - total;

                    salvar_historico(cliente, produtos[idx], quantidade, total, valor_pago, troco);
                    gerar_comprovativo(cliente, produtos[idx], quantidade, total, valor_pago, troco);

                    printf("Compra finalizada! Troco: %.2f Kz\n", troco);
                }
            }
        }

        else if(opcao == 3) {
            mostrar_historico();
        }

        else if(opcao == 4) {
            int id;
            printf("Digite o ID do cliente: ");
            scanf("%d", &id);
            getchar();
            pesquisar_historico_cliente(id);
        }

        else if(opcao == 5) {
            int i, total_produtos = carregar_produtos(produtos);
            printf("\n--- PRODUTOS EM STOCK ---\n");
            for(i = 0; i < total_produtos; i++) {
                printf("%s | %.2f Kz | Qtd: %d",
                       produtos[i].nome,
                       produtos[i].preco,
                       produtos[i].quantidade);
                if(produtos[i].quantidade == 0)
                    printf(" <-- ESGOTADO");
                printf("\n");
            }
        }

        printf("\nPressione ENTER para continuar...");
        getchar();
    }

    return 0;
}

