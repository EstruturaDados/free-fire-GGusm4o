#include "funcoes.h"

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.

int main() {
    // A estrutura switch trata cada opção chamando a função correspondente.
    // A ordenação e busca binária exigem que os dados estejam bem organizados.
    Item mochila[10]; // Vetor de structs com capacidade para 10 itens
    int totalItens = 0; // Contador de itens atuais
    int ordenadaPorNome = 0;
    int opcao;

    // Menu principal com opções:
    do {
        limparTela();
        exibirMenu(totalItens, ordenadaPorNome);
        scanf("%d", &opcao);
        limparBuffer();

        switch(opcao) {
            // 1. Adicionar um item
            case 1:
                inserirItem(mochila, &totalItens, &ordenadaPorNome);
                break;
            // 2. Remover um item
            case 2:
                removerItem(mochila, &totalItens);
                break;
            // 3. Listar todos os itens
            case 3:
                listarItens(mochila, totalItens);
                break;
                // 4. Ordenar os itens por critério (nome, tipo, prioridade)
            case 4: { // Bloco criado por causa da declaração da variável interna
                menuDeOrdenacao(mochila, totalItens, &ordenadaPorNome);
                break;
            }
            // 5. Realizar busca binária por nome
            case 5:{
                buscaBinariaPorNome(mochila, totalItens, ordenadaPorNome);
                break;
            }
            // 0. Sair
            case 0:
                printf("\nFechando a mochila...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar(); // Pausa a tela até o jogador apertar Enter
        }

    } while(opcao != 0);

    return 0;
}
