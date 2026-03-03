#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

// Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
// A prioridade indica a importância do item na montagem do plano de fuga.
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Função que limpa a tela do console, simulando uma nova interface para o jogador a cada ação.
void limparTela();

// Função para exibir o menu principal, mostrando as opção diponiveis para selecionar 
void exibirMenu(int totalItens);

// Função auxiliar para limpar o buffer do teclado
void limparBuffer();

// 2. Busca sequencial: Localiza o item pelo nome e retorna o índice (ou -1 se não achar)
int buscarItem(Item mochila[], int total);

// 3. Listagem dos itens: Mostra tudo o que está registrado formatado como tabela
void listarItens(Item mochila[], int total);

// 4. Cadastro de itens: Adiciona um novo item no final do vetor
void inserirItem(Item mochila[], int *total);

// 5. Remoção de itens: Busca o item pelo nome e o remove, reorganizando o vetor
void removerItem(Item mochila[], int *total);

int buscarItemAuxiliar(Item mochila[], int total, char nomeBusca[]);

int main() {

    // 4. Ordenar os itens por critério (nome, tipo, prioridade)
    // 5. Realizar busca binária por nome
    // 0. Sair

    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    Item mochila[10]; // Vetor de structs com capacidade para 10 itens
    int totalItens = 0; // Contador de itens atuais
    int opcao;

    // Menu principal com opções:
    do {
        limparTela();
        exibirMenu(totalItens);
        scanf("%d", &opcao);

        switch(opcao) {
            // 1. Adicionar um item
            case 1:
                inserirItem(mochila, &totalItens);
                break;
            // 2. Remover um item
            case 2:
                removerItem(mochila, &totalItens);
                break;
            // 3. Listar todos os itens
            case 3:
                listarItens(mochila, totalItens);
                break;
            
            case 4: { // Bloco criado por causa da declaração da variável interna
                buscarItem(mochila, totalItens);
                break;
            }
            case 0:
                printf("\nFechando a mochila...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        if (opcao != 0) {
            limparBuffer(); // Limpa o "Enter" que sobra do scanf
            printf("\nPressione Enter para continuar...");
            getchar(); // Pausa a tela até o jogador apertar Enter
        }

    } while(opcao != 0);

    return 0;
}

// Enum CriterioOrdenacao:
// Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).

// Vetor mochila:
// Armazena até 10 itens coletados.
// Variáveis de controle: numItens (quantidade atual), comparacoes (análise de desempenho), ordenadaPorNome (para controle da busca binária).
int buscarItemAuxiliar(Item mochila[], int total, char nomeBusca[]) {
    for (int i = 0; i < total; i++){
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            return i; // Retorna o índice
        }
    }
    return -1; // Não encontrou o item
}

int buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\nA mochila está vazia!\n");
        return -1 ; // Retona -1 para indicar que não encontrou nada.
    }

    char nomeBusca[30];
    
    printf("--- Buscar Item na Mochila ---\n");
    printf("\nDigite o nome do item que deseja buscar: ");
    scanf(" %29[^\n]", nomeBusca); // Lê a string permitindo espaços, até 29 caracteres

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n--- Item Encontrado! ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("------------------------\n");           

            // O return faz a função acabar IMEDIATAMENTE aqui.
            return i; // Retorna o índice do item encontrado
        }
    }
    // Se o código chegou até essa linha, é porque o return ali de cima nunca foi chamado.
    // Ou seja, não achou nada!
    printf("\nResultado: Item '%s' NAO foi encontrado na mochila.\n", nomeBusca);
    return -1; // Retorna -1 para indicar que não encontrou nada.
}

// Simula a limpeza da tela imprimindo várias linhas em branco.
void limparTela() {
    for (int i = 0; i < 50; i++) {
        printf("\n");
    }
}   

// Apresenta o menu principal ao jogador, com destaque para status da ordenação.
void exibirMenu(int totalItens){
    printf("\n==================================================\n");
    printf(" MOCHILA DE SOBREVIVENCIA - CODIGO DA ILHA\n");
    printf("==================================================\n");
    printf("Itens na Mochila: %d/10\n\n", totalItens);
    printf("1. Adicionar Item (Loot)\n");
    printf("2. Remover Item\n");
    printf("3. Listar Itens na Mochila\n");
    printf("4. Buscar Item por Nome\n");
    printf("0. Sair\n");
    printf("--------------------------------------------------\n");
    printf("Escolha uma opcao: ");

}

// Adiciona um novo componente à mochila se houver espaço.
// Solicita nome, tipo, quantidade e prioridade.
// Após inserir, marca a mochila como "não ordenada por nome".
void inserirItem(Item mochila[], int *total) {
    if (*total >= 10) {
        printf("\nA mochila está cheia! Remova algum item primeiro.\n");
        return;
    }

    printf("\n--- Adicionar Novo Item ---\n");
    printf("Nome do item: ");
    // Lê a string permitindo espaços, até 29 caracteres
    scanf(" %29[^\n]", mochila[*total].nome); 
    
    printf("Tipo do item (arma, municao, cura, etc.): ");
    scanf(" %19[^\n]", mochila[*total].tipo);
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    printf("\nItem '%s' adicionado com sucesso!\n", mochila[*total].nome);
    
    (*total)++; // Incrementa a quantidade total de itens na mochila

    // Lista os itens logo após adicionar, conforme requisito
    listarItens(mochila, *total);
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


// Exibe uma tabela formatada com todos os componentes presentes na mochila.
void listarItens(Item mochila[], int total) {
    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", total);
    printf("--------------------------------------------------\n");
    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "QUANTIDADE");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < total; i++) {
        // O %-20s alinha a string à esquerda com 20 espaços para manter a tabela reta
        printf("%-20s | %-15s | %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
    printf("--------------------------------------------------\n");
}

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

// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}