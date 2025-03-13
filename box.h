#ifndef BOX_H
#define BOX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <time.h>

#define MAX_METODO1 10
#define MAX_METODO2 19

typedef struct {
  long inscricao;
  float nota;
  char estado[3];
  char cidade[51];
  char curso[31];
} TRegistro;

typedef struct {
    int chave;
    int ativo; // 1: ativo pode ser usado na run atual, 0: congelado (para próxima run)
};

typedef struct {
    int alunos[];
} Aluno;

void ler_provao(FILE *file, TRegistro TRegistros[], int n);

void escrever_temp_bin(const char *nome_arquivo_txt, const char *nome_arquivo_bin, int quantidade);

//void metodo1

//void metodo2

//void metodo3

#endif BOX_H