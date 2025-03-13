#include "box.h"

// Função para ler os dados do arquivo "PROVAO.TXT"
void ler_provao(FILE *file, Aluno alunos[], int n) {
  // Passa pelo arquivo completo
  for (int i = 0; i < n; i++)
    // Lê e armazena os dados nas variáveis correspondentes
    fscanf(file, "%ld %f %s %s %s", &alunos->inscricao, &alunos->nota,
           alunos->estado, alunos->cidade, alunos->curso);
}

// Função para escrever os registros no arquivo binário temp.bin
void escrever_temp_bin(const char *nome_arquivo_txt, const char *nome_arquivo_bin, int quantidade) {
    FILE *arquivo_txt = fopen(nome_arquivo_txt, "r");
    if (!arquivo_txt) {
        perror("Erro ao abrir o arquivo PROVAO.TXT");
        return;
    }

    FILE *arquivo_bin = fopen(nome_arquivo_bin, "wb");
    if (!arquivo_bin) {
        perror("Erro ao criar o arquivo temp.bin");
        fclose(arquivo_txt);
        return;
    }

    TRegistro reg;
    int contador = 0;

    // Ler os registros do arquivo texto e escrever no arquivo binário
    while(contador < quantidade && fscanf(arquivo_txt, "%d %f %2s %50s %30s",
                                          &reg.inscricao, &reg.nota,
                                          reg.estado, reg.cidade, reg.curso) == 5) {
        fwrite(&reg, sizeof(TRegistro), 1, arquivo_bin);
        contador++;
    }

    fclose(arquivo_txt);
    fclose(arquivo_bin);
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

void metodo1(Aluno alunos[], int n) {

}

void metodo2(Aluno alunos[], int n) {

}

void metodo3(Aluno alunos[], int n) {

}

