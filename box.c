#include "box.h"

// Função para ler os dados do arquivo "PROVAO.TXT"
void ler_provao(FILE *file, Aluno alunos[], int n) {
  for (int i = 0; i < n; i++)
    fscanf(file, "%ld %f %s %s %s", &alunos->inscricao, &alunos->nota,
           alunos->estado, alunos->cidade, alunos->curso);
}

// Função para a técnica de seleção por substituição
void selecao(Aluno alunos[], int n) {
  FILE *ent1 = fopen("ent1", "w");
  FILE *ent2 = fopen("ent1", "w");
  FILE *ent3 = fopen("ent1", "w");
  FILE *ent4 = fopen("ent1", "w");
  FILE *ent5 = fopen("ent1", "w");
  FILE *ent6 = fopen("ent1", "w");
  FILE *ent7 = fopen("ent1", "w");
  FILE *ent8 = fopen("ent1", "w");
  FILE *ent9 = fopen("ent1", "w");
  FILE *ent10 = fopen("ent1", "w");
}

void metodo1(Aluno alunos[], int n) {}
