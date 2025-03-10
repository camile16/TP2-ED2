#ifndef HEAP_H
#define HEAP_H

#include "box.h"

//Funções
FilaPrioridade *criarFila(int capacidade);
void trocar(int *a, int *b);
void heapifyUp(FilaPrioridade *fila, int indice);
void heapifyDown(FilaPrioridade *fila, int indice);
void inserir(FilaPrioridade *fila, int item);
int removerMenor(FilaPrioridade *fila);
void processarItens(int *entrada, int n, int m);

#endif // HEAP_H