#ifndef HEAP_H
#define HEAP_H

typedef struct {
    int chave;
    int ativo; // 1: ativo (pode ser usado na run atual), 0: congelado (para próxima run)
} HeapItem;

typedef struct {
    HeapItem *itens;
    int tamanho;
    int capacidade;
} FilaPrioridade;

//Funções
FilaPrioridade *criarFila(int capacidade);
void trocar(int *a, int *b);
void heapifyUp(FilaPrioridade *fila, int indice);
void heapifyDown(FilaPrioridade *fila, int indice);
void inserir(FilaPrioridade *fila, int item);
int removerMenor(FilaPrioridade *fila);
void processarItens(int *entrada, int n, int m);

#endif HEAP_H