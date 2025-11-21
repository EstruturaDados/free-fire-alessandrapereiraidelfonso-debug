#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Estrutura No para Lista Encadeada
typedef struct No {
    Item dados;
    struct No *proximo;
} No;

// --- CONFIGURAÇÃO GLOBAL ---

// 1. Configuração para Vetor
#define CAPACIDADE_MAXIMA 10
Item mochilaVetor[CAPACIDADE_MAXIMA];
int totalItensVetor = 0;

// 2. Configuração para Lista Encadeada
No *cabecaLista = NULL;

// 3. Contadores
long long contadorComparacoes = 0; // Usado para ambas as buscas no Vetor
long long contadorComparacoesLista = 0; // Usado para a busca na Lista

// --- PROTÓTIPOS DE FUNÇÕES ---
// Necessário para que o main e os menus possam chamar as funções
void menuVetor();
void inserirItemVetor();
void removerItemVetor(const char *nomeItem);
void listarItensVetor();
void ordenarVetor();
void buscarSequencialVetor(const char *nomeItem);
void buscarBinariaVetor(const char *nomeItem);

void menuLista();
void inserirItemLista();
void removerItemLista(const char *nomeItem);
void listarItensLista();
void buscarSequencialLista(const char *nomeItem);
void liberarLista();

int main() {
 int escolhaPrincipal;

    do {
        printf("\n===================================\n");
        printf(" MOCHILA DO JOGADOR - ESCOLHA A ESTRUTURA\n");
        printf("===================================\n");
        printf("1. MOCHILA usando VETOR (Lista Sequencial)\n");
        printf("2. MOCHILA usando LISTA ENCADEDADA (Estrutura Dinâmica)\n");
        printf("0. Sair do Jogo\n");
        printf("Escolha uma opção: ");

        if (scanf("%d", &escolhaPrincipal) != 1) {
            // Limpa o buffer em caso de entrada não numérica
            while(getchar() != '\n');
            escolhaPrincipal = -1;
        }

        switch (escolhaPrincipal) {
            case 1:
                menuVetor();
                break;
            case 2:
                menuLista();
                break;
            case 0:
                liberarLista(); // Limpeza de memória
                printf("\n Encerrando o sistema de mochila. Até logo!\n");
                break;
            default:
                printf("\nOpção inválida. Por favor, escolha 1, 2 ou 0.\n");
        }
    } while (escolhaPrincipal != 0);

    return 0;
}

void exibirItemVetor(Item item) {
    printf("  [ %s ] | Tipo: %s | Qtd: %d\n", item.nome, item.tipo, item.quantidade);
}

void inserirItemVetor() {
    if (totalItensVetor >= CAPACIDADE_MAXIMA) {
        printf("\n Mochila Cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("\n--- INSERIR ITEM ---\n");
    printf("Nome do Item: ");
    scanf(" %[^\n]", novoItem.nome);
    printf("Tipo do Item: ");
    scanf(" %[^\n]", novoItem.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochilaVetor[totalItensVetor] = novoItem;
    totalItensVetor++;
    printf(" Item '%s' adicionado com sucesso na mochila.\n", novoItem.nome);
}

void listarItensVetor() {
    printf("\n--- MOCHILA (VETOR) - %d/%d ITENS ---\n", totalItensVetor, CAPACIDADE_MAXIMA);
    if (totalItensVetor == 0) {
        printf(" A mochila está vazia.\n");
        return;
    }

    for (int i = 0; i < totalItensVetor; i++) {
        printf("%02d. ", i + 1);
        exibirItemVetor(mochilaVetor[i]);
    }
}

void removerItemVetor(const char *nomeItem) {
    if (totalItensVetor == 0) {
        printf(" A mochila está vazia. Nada a remover.\n");
        return;
    }

    int indiceRemover = -1;

    for (int i = 0; i < totalItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nomeItem) == 0) {
            indiceRemover = i;
            break;
        }
    }

    if (indiceRemover != -1) {
        for (int i = indiceRemover; i < totalItensVetor - 1; i++) {
            mochilaVetor[i] = mochilaVetor[i + 1];
        }
        totalItensVetor--;
        printf("Item '%s' removido com sucesso.\n", nomeItem);
    } else {
        printf("Item '%s' não encontrado na mochila.\n", nomeItem);
    }
}

void ordenarVetor() {
    if (totalItensVetor <= 1) {
        printf("A mochila precisa de pelo menos 2 itens para ordenar.\n");
        return;
    }

    // Bubble Sort
    int trocado;
    for (int i = 0; i < totalItensVetor - 1; i++) {
        trocado = 0;
        for (int j = 0; j < totalItensVetor - i - 1; j++) {
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[j + 1].nome) > 0) {
                Item temp = mochilaVetor[j];
                mochilaVetor[j] = mochilaVetor[j + 1];
                mochilaVetor[j + 1] = temp;
                trocado = 1;
            }
        }
        if (trocado == 0) break;
    }
    printf("\n Mochila ordenada por nome (Bubble Sort) com sucesso.\n");
}

void buscarSequencialVetor(const char *nomeItem) {
    contadorComparacoes = 0;
    int encontrado = 0;

    printf("\n--- BUSCA SEQUENCIAL (VETOR) ---\n");

    for (int i = 0; i < totalItensVetor; i++) {
        contadorComparacoes++;
        if (strcmp(mochilaVetor[i].nome, nomeItem) == 0) {
            printf(" Item encontrado na posição %d (índice %d):\n", i + 1, i);
            exibirItemVetor(mochilaVetor[i]);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf(" Item '%s' não encontrado.\n", nomeItem);
    }

    printf("\n Comparações realizadas: %lld\n", contadorComparacoes);
}

void buscarBinariaVetor(const char *nomeItem) {
    contadorComparacoes = 0;
    int inicio = 0;
    int fim = totalItensVetor - 1;
    int encontrado = 0;

    printf("\n--- BUSCA BINÁRIA (VETOR ORDENADO) ---\n");

    if (totalItensVetor == 0) {
        printf(" A mochila está vazia. Impossível buscar.\n");
        return;
    }

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        contadorComparacoes++;

        int comparacao = strcmp(mochilaVetor[meio].nome, nomeItem);

        if (comparacao == 0) {
            printf(" Item encontrado na posição %d (índice %d):\n", meio + 1, meio);
            exibirItemVetor(mochilaVetor[meio]);
            encontrado = 1;
            break;
        } else if (comparacao < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    if (!encontrado) {
        printf(" Item '%s' não encontrado.\n", nomeItem);
    }

    printf("\n Comparações realizadas: %lld\n", contadorComparacoes);
}

void menuVetor() {
    int escolha;
    char nomeBusca[30];
    char nomeRemover[30];

    do {
        printf("\n===================================\n");
        printf(" MOCHILA (VETOR - LISTA SEQUENCIAL)\n");
        // ... (Menu de opções)
        printf("1. Inserir Novo Item\n");
        printf("2. Remover Item por Nome\n");
        printf("3. Listar Itens\n");
        printf("4. Ordenar Mochila por Nome\n");
        printf("5. Buscar Item (Sequencial)\n");
        printf("6. Buscar Item (Binária - REQUER ORDENAÇÃO)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &escolha) != 1) {
            while(getchar() != '\n');
            escolha = -1;
        }

        switch (escolha) {
            case 1: inserirItemVetor(); break;
            case 2:
                printf("\nNome do Item a remover: ");
                scanf(" %[^\n]", nomeRemover);
                removerItemVetor(nomeRemover);
                break;
            case 3: listarItensVetor(); break;
            case 4: ordenarVetor(); break;
            case 5:
                printf("\nNome do Item para BUSCA SEQUENCIAL: ");
                scanf(" %[^\n]", nomeBusca);
                buscarSequencialVetor(nomeBusca);
                break;
            case 6:
                printf("\nNome do Item para BUSCA BINÁRIA (Vetor deve estar ordenado!): ");
                scanf(" %[^\n]", nomeBusca);
                buscarBinariaVetor(nomeBusca);
                break;
            case 0: printf("\nRetornando ao Menu Principal...\n"); break;
            default: printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);
}

// -------------------------------------------------------------------
// Funções da Lista Encadeada
// -------------------------------------------------------------------

No *criarNo(Item item) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf(" Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dados = item;
    novoNo->proximo = NULL;
    return novoNo;
}

void inserirItemLista() {
    Item novoItem;
    printf("\n--- INSERIR ITEM (LISTA ENCADEDADA) ---\n");
    printf("Nome do Item: ");
    scanf(" %[^\n]", novoItem.nome);
    printf("Tipo do Item: ");
    scanf(" %[^\n]", novoItem.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    No *novoNo = criarNo(novoItem);
    novoNo->proximo = cabecaLista;
    cabecaLista = novoNo;

    printf(" Item '%s' adicionado com sucesso na mochila (início da lista).\n", novoItem.nome);
}

void listarItensLista() {
    printf("\n--- MOCHILA (LISTA ENCADEDADA) ---\n");
    if (cabecaLista == NULL) {
        printf(" A mochila está vazia.\n");
        return;
    }

    No *atual = cabecaLista;
    int indice = 1;
    while (atual != NULL) {
        printf("%02d. [ %s ] | Tipo: %s | Qtd: %d\n", indice++, atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
        atual = atual->proximo;
    }
}

void removerItemLista(const char *nomeItem) {
    if (cabecaLista == NULL) {
        printf(" A mochila está vazia. Nada a remover.\n");
        return;
    }

    No *atual = cabecaLista;
    No *anterior = NULL;

    while (atual != NULL && strcmp(atual->dados.nome, nomeItem) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf(" Item '%s' não encontrado na mochila.\n", nomeItem);
        return;
    }

    if (anterior == NULL) {
        cabecaLista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    printf(" Item '%s' removido com sucesso.\n", nomeItem);
}

void buscarSequencialLista(const char *nomeItem) {
    contadorComparacoesLista = 0;
    No *atual = cabecaLista;
    int encontrado = 0;

    printf("\n--- BUSCA SEQUENCIAL (LISTA ENCADEDADA) ---\n");

    while (atual != NULL) {
        contadorComparacoesLista++;
        if (strcmp(atual->dados.nome, nomeItem) == 0) {
            printf(" Item encontrado:\n");
            printf("  [ %s ] | Tipo: %s | Qtd: %d\n", atual->dados.nome, atual->dados.tipo, atual->dados.quantidade);
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado) {
        printf(" Item '%s' não encontrado.\n", nomeItem);
    }

    printf("\n Comparações realizadas: %lld\n", contadorComparacoesLista);
}

void menuLista() {
    int escolha;
    char nomeBusca[30];
    char nomeRemover[30];

    do {
        printf("\n===================================\n");
        printf("MOCHILA (LISTA ENCADEDADA SIMPLES)\n");
        // ... (Menu de opções)
        printf("1. Inserir Novo Item\n");
        printf("2. Remover Item por Nome\n");
        printf("3. Listar Itens\n");
        printf("4. Buscar Item (Sequencial)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        if (scanf("%d", &escolha) != 1) {
            while(getchar() != '\n');
            escolha = -1;
        }

        switch (escolha) {
            case 1: inserirItemLista(); break;
            case 2:
                printf("\nNome do Item a remover: ");
                scanf(" %[^\n]", nomeRemover);
                removerItemLista(nomeRemover);
                break;
            case 3: listarItensLista(); break;
            case 4:
                printf("\nNome do Item para BUSCA SEQUENCIAL: ");
                scanf(" %[^\n]", nomeBusca);
                buscarSequencialLista(nomeBusca);
                break;
            case 0: printf("\nRetornando ao Menu Principal...\n"); break;
            default: printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (escolha != 0);
}

void liberarLista() {
    No *atual = cabecaLista;
    No *proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    cabecaLista = NULL;
}
    // Menu principal com opções:
    // 1. Adicionar um item
    // 2. Remover um item
    // 3. Listar todos os itens
    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.



// Struct Item:
// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).

// limparTela():
// Simula a limpeza da tela imprimindo várias linhas em branco.

// exibirMenu():
// Apresenta o menu principal ao jogador, com destaque para status da ordenação.

// inserirItem():
// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".

// removerItem():
// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.

// listarItens():
// Exibe uma tabela formatada com todos os componentes presentes na mochila.

// menuDeOrdenacao():
// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).

// insertionSort():
// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)

// buscaBinariaPorNome():
// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
