
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int chave;
    int ativo; // 1: ativo (pode ser usado na run atual), 0: congelado (para próxima run)
} HeapItem;

typedef struct {
    HeapItem *itens;
    int tamanho;
    int capacidade;
} FilaPrioridade;

// Cria a fila (heap) com capacidade definida
FilaPrioridade* criarFila(int capacidade) {
    FilaPrioridade *fila = (FilaPrioridade*) malloc(sizeof(FilaPrioridade));
    fila->capacidade = capacidade;
    fila->tamanho = 0;
    fila->itens = (HeapItem*) malloc(capacidade * sizeof(HeapItem));
    return fila;
}

// Troca dois itens do heap
void trocar(HeapItem *a, HeapItem *b) {
    HeapItem temp = *a;
    *a = *b;
    *b = temp;
}

// Função de comparação:
// Itens ativos são sempre considerados "menores" que itens congelados,
// independentemente do valor. Se ambos tiverem o mesmo status, compara-se pela chave.
int compare(HeapItem a, HeapItem b) {
    if(a.ativo != b.ativo) {
        return (a.ativo ? -1 : 1);
    } else {
        if(a.chave < b.chave) return -1;
        else if(a.chave > b.chave) return 1;
        else return 0;
    }
}

// Heapify up: ajusta a posição do item recém-inserido
void heapifyUp(FilaPrioridade *fila, int indice) {
    while(indice > 0) {
        int pai = (indice - 1) / 2;
        if(compare(fila->itens[pai], fila->itens[indice]) > 0) {
            trocar(&fila->itens[pai], &fila->itens[indice]);
            indice = pai;
        } else {
            break;
        }
    }
}

// Heapify down: ajusta a posição do item após remoção
void heapifyDown(FilaPrioridade *fila, int indice) {
    while (1) {
        int esquerda = 2 * indice + 1;
        int direita = 2 * indice + 2;
        int menor = indice;

        if (esquerda < fila->tamanho && compare(fila->itens[esquerda], fila->itens[menor]) < 0)
            menor = esquerda;
        if (direita < fila->tamanho && compare(fila->itens[direita], fila->itens[menor]) < 0)
            menor = direita;

        if (menor != indice) {
            trocar(&fila->itens[indice], &fila->itens[menor]);
            indice = menor;
        } else {
            break;
        }
    }
}

// Insere um novo item no heap, com a indicação se ele está ativo ou congelado
void inserir(FilaPrioridade *fila, int chave, int ativo) {
    if (fila->tamanho < fila->capacidade) {
        HeapItem novo;
        novo.chave = chave;
        novo.ativo = ativo;
        fila->itens[fila->tamanho] = novo;
        heapifyUp(fila, fila->tamanho);
        fila->tamanho++;
    }
}

// Remove e retorna o menor item do heap
HeapItem removerMinimo(FilaPrioridade *fila) {
    HeapItem vazio;
    vazio.chave = INT_MAX;
    vazio.ativo = 1;
    if (fila->tamanho == 0) return vazio;
    HeapItem minItem = fila->itens[0];
    fila->itens[0] = fila->itens[fila->tamanho - 1];
    fila->tamanho--;
    heapifyDown(fila, 0);
    return minItem;
}

// Reconstrói o heap "descongelando" todos os itens, para iniciar uma nova run
void reconstruirHeap(FilaPrioridade *fila) {
    for (int i = 0; i < fila->tamanho; i++) {
        fila->itens[i].ativo = 1; // desmarca todos os itens (torna-os ativos)
    }
    // Reconstrói o heap (bottom-up)
    for (int i = (fila->tamanho / 2) - 1; i >= 0; i--) {
        heapifyDown(fila, i);
    }
}

// Função que implementa a seleção por substituição
// 'entrada' contém os dados, 'n' é o número total de itens e 'm' o tamanho do buffer (heap)
void processarItensSubstituicao(int *entrada, int n, int m) {
    FilaPrioridade *fila = criarFila(m);
    int lastOutput = INT_MIN; // Último item escrito na run atual
    int index = 0;

    // Inicializa o heap com os primeiros m itens, todos ativos
    for (; index < m && index < n; index++) {
        inserir(fila, entrada[index], 1);
    }

    printf("Run atual:\n");

    // Processa o heap enquanto houver itens
    while (fila->tamanho > 0) {
        // Se o menor item estiver congelado, significa que não há mais itens ativos
        // para a run atual; assim, finalizamos a run e reconstruímos o heap para a próxima run.
        if (fila->itens[0].ativo == 0) {
            printf("\nFim da run.\n");
            reconstruirHeap(fila);
            lastOutput = INT_MIN; // Reinicia o lastOutput para a nova run
            printf("Nova run:\n");
            continue;
        }

        // Remove o menor item (ativo) e o escreve na run atual
        HeapItem minItem = removerMinimo(fila);
        printf("%d ", minItem.chave);
        lastOutput = minItem.chave;

        // Se houver mais itens na entrada, processa o próximo
        if (index < n) {
            int novo = entrada[index++];
            // Se o novo item é maior ou igual ao último item escrito, ele pode entrar na run atual
            if (novo >= lastOutput) {
                inserir(fila, novo, 1);
            } else {
                // Caso contrário, o item é congelado para ser usado na próxima run
                inserir(fila, novo, 0);
            }
        }
    }
    printf("\n");

    free(fila->itens);
    free(fila);
}

int main() {
    int entrada[] = {5, 1, 9, 3, 4, 6, 8, 2, 7, 0};
    int n = sizeof(entrada) / sizeof(entrada[0]);
    int m = 4; // Tamanho do buffer (heap)

    processarItensSubstituicao(entrada, n, m);

    return 0;
}
