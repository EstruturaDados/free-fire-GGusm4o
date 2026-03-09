#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
typedef enum {
    NOME = 1,
    TIPO,
    PRIORIDADE
} CriterioOrdenacao;

int contadorComparacoes = 0; // Variável global para contar comparações durante a ordenação

void limparTela();
void limparBuffer();
void exibirMenu(int totalItens, int ordenadaPorNome);
void inserirItem(Item mochila[], int *total, int *ordenado);
void listarItens(Item mochila[], int total);
int buscarItemAuxiliar(Item mochila[], int total, char nomeBusca[]);
void removerItem(Item mochila[], int *total);
void menuDeOrdenacao(Item mochila[], int total, int *ordenadaPorNome);
void insertionSort(Item mochila[], int n, int criterio, int *comparacao);
void buscaBinariaPorNome(Item mochila[], int tamanho, int ordenadaPorNome);

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}   

// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu(int totalItens, int ordenadaPorNome) {
    printf("\n==================================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("==================================================\n");
    printf("Itens na Mochila: %d/10\n\n", totalItens);
    printf("Status da Ordenacao por Nome: %s\n", ordenadaPorNome ? "ORDENADO" : "NAO ORDENADO");
    printf("1. Adicionar Componentes (Loot)\n");
    printf("2. Remover Componentes\n");
    printf("3. Listar Componentes (Inventario)\n");
    printf("4. Organizar Itens (Ordenar Componentes)\n");
    printf("5. Busca Binaria por Componente-Chave (por nome)\n");
    printf("0. Sair\n");
    printf("--------------------------------------------------\n");
    printf("Escolha uma opcao: ");

}

// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem(Item mochila[], int *total, int *ordenado) {
    if (*total >= 10) {
        printf("\nA mochila está cheia! Remova algum item primeiro.\n");
        return;
    }

    printf("\n--- Coletando Novo Componente ---\n");
    printf("Nome do item: ");
    // Lê a string permitindo espaços, até 29 caracteres
    scanf(" %29[^\n]", mochila[*total].nome); 
    limparBuffer();
    
    printf("Tipo do item (Estrutural, Eletronico, Energia): ");
    scanf(" %19[^\n]", mochila[*total].tipo);
    limparBuffer();
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    limparBuffer();

    printf("Prioridade de Montagem (1-5): ");
    scanf("%d", &mochila[*total].prioridade); // [MUDANÇA] Adicionado campo prioridade
    limparBuffer();

    printf("\nComponente '%s' adicionado com sucesso!\n", mochila[*total].nome);
    
    (*total)++; // Incrementa a quantidade total de itens na mochila
    
    *ordenado = 0;
    // Lista os itens logo após adicionar, conforme requisito
    listarItens(mochila, *total);
}

// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens(Item mochila[], int total) {
    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", total);
    printf("-----------------------------------------------------------------\n");
    printf("%-20s | %-15s | %-10s | %s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("-----------------------------------------------------------------\n");
    
    for (int i = 0; i < total; i++) {
        // O %-20s alinha a string à esquerda com 20 espaços para manter a tabela reta
        printf("%-20s | %-15s | %-10d | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("-----------------------------------------------------------------\n");
}

int buscarItemAuxiliar(Item mochila[], int total, char nomeBusca[]) {
    for (int i = 0; i < total; i++){
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Retorna o índice
        }
    }
    return -1; // Não encontrou o item
}

// Permite remover um componente da mochila pelo nome.
// Se encontrado, reorganiza o vetor para preencher a lacuna.
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeRemover[30];
    printf("\n--- Remover Item ---\n");
    printf("Digite o nome do item a ser removido: ");
    scanf(" %29[^\n]", nomeRemover);
    limparBuffer();

    int indice = buscarItemAuxiliar(mochila, *total, nomeRemover);

    if (indice != -1) {
        // Desloca os itens uma posição para trás para sobrescrever o item removido
        for (int i = indice; i < *total - 1; i++) {
            mochila[i] = mochila[i + 1];
        }
        (*total)--; // Reduz o total de itens
        printf("\nItem '%s' removido com sucesso!\n", nomeRemover);
        
        // Lista os itens após remover
        listarItens(mochila, *total);
    } else {
        printf("\nItem '%s' não encontrado na mochila.\n", nomeRemover);
    }
}


// --- Algoritmos de Ordenação ---

// Permite ao jogador escolher como deseja ordenar os itens.
// Utiliza a função insertionSort() com o critério selecionado.
// Exibe a quantidade de comparações feitas (análise de desempenho).
void menuDeOrdenacao(Item mochila[], int total, int *ordenadaPorNome) {
    if (total < 2) {
        printf("\nItens insuficientes para ordenar.\n");
        return;
    }

    int criterio, comparacao = 0;
    printf("\n--- Estrategia de Organizacao ---\n");
    printf("Como deseja ordenar os componetes?\n");
    printf("1. Por nome (Ordem Alfabética)\n");
    printf("2. Por tipo\n");
    printf("3. Por prrioridade de Montagem\n");
    printf("0. Cancelar\n");
    printf("Escolha o criterio: ");
    scanf("%d", &criterio);
    limparBuffer();

    if (criterio == 0) return;

    clock_t inicio = clock();

    insertionSort(mochila, total, criterio, &comparacao);

    clock_t fim = clock(); // [MUDANÇA] Fim da medição de tempo
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    *ordenadaPorNome = (criterio == NOME);
    printf("\nOrdenado! Comparacoes: %d | Tempo: %.5fs\n", comparacao, tempo);
    printf("\nMochila organizada! Comparacoes realizadas: %d\n", comparacao);
    listarItens(mochila, total);

}

// Implementação do algoritmo de ordenação por inserção.
// Funciona com diferentes critérios de ordenação:
// - Por nome (ordem alfabética)
// - Por tipo (ordem alfabética)
// - Por prioridade (da mais alta para a mais baixa)
void insertionSort(Item mochila[], int n, int criterio, int *comparacao) {
    for (int i = 1; i < n; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacao)++;
            int troca = 0;

            if (criterio == NOME) {
                troca = strcmp(mochila[j].nome, chave.nome) > 0;
            } else if (criterio == TIPO) {
                troca = strcmp(mochila[j].tipo, chave.tipo) > 0;
            } else if (criterio == PRIORIDADE) {
                troca = mochila[j].prioridade < chave.prioridade; // Prioridade mais alta vem primeiro
            }

            if (troca) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }
}

// Realiza busca binária por nome, desde que a mochila esteja ordenada por nome.
// Se encontrar, exibe os dados do item buscado.
// Caso contrário, informa que não encontrou o item.
void buscaBinariaPorNome(Item mochila[], int tamanho, int ordenadaPorNome) {
    if (!ordenadaPorNome) {
        printf("\nALERTA: A busca binaria requer que a mochila esteja ordenada por NOME.\n");
        printf("Use a Opcao 4 para organizar a mochila primeiro.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n--- Busca Binaria (Componente-Chave) ---\n");
    printf("Digite o nome do componente a buscar: ");
    scanf(" %29[^\n]", nomeBusca);
    limparBuffer();


    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        // int meio = (inicio + fim) / 2; // Forma comum, mas pode dar overflow com números muito grandes.

        // Forma mais segura para calcular o meio, evitando overflow:
        int meio = inicio + (fim - inicio) / 2;
        int chute = strcmp(mochila[meio].nome, nomeBusca);
        // 1. Se o valor estiver exatamente no meio, encontramos!
        if (chute == 0) {
            printf("\nItem Localizado na Torre de Fuga!\n");
            printf("Nome: %s | Tipo: %s | Qtd: %d | Prio: %d\n", mochila[meio].nome, mochila[meio].tipo, mochila[meio].quantidade, mochila[meio].prioridade);
            return;
        }
        if (chute < 0) {
            inicio = meio + 1; // O item buscado é maior que o do meio, então ignoramos a metade inferior
        } else {
            fim = meio - 1; // O item buscado é menor que o do meio, então ignoramos a metade superior
        }
    }
    printf("\nComponente '%s' nao encontrado.\n", nomeBusca);
}