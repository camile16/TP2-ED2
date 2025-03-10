#ifndef BOX_H
#define BOX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_METODO1 10
#define MAX_METODO2 19

// Estrutura para armazenar os dados de cada aluno
typedef struct {
  long inscricao;
  float nota;
  char estado[3];
  char cidade[51];
  char curso[31];
} Aluno;

typedef struct {
    int chave;
    int ativo; // 1: ativo (pode ser usado na run atual), 0: congelado (para próxima run)
} HeapItem;

typedef struct {
    HeapItem *itens;
    int tamanho;
    int capacidade;
} FilaPrioridade;

void ler_provao(FILE *file, Aluno alunos[], int n);

//void metodo1

//void metodo2

//void metodo3

#endif // BOX_H