#include "box.h"

// Função para trocar dois registros
void trocar(TRegistro *a, TRegistro *b) {
  TRegistro temp = *a;
  *a = *b;
  *b = temp;
}

// Função para ordenar um vetor de registros usando seleção por substituição
void selecao_por_substituicao(TRegistro vetor[], int tamanho) {
  for (int i = 0; i < tamanho - 1; i++) {
      int min_idx = i;
      for (int j = i + 1; j < tamanho; j++) {
          if (vetor[j].nota < vetor[min_idx].nota) {
              min_idx = j;
          }
      }
      trocar(&vetor[i], &vetor[min_idx]);
  }
}

// Função para ler os dados do arquivo "PROVAO.TXT"
void ler_provao(FILE *file, TRegistro reg[], int n) {
  // Passa pelo arquivo completo
  for (int i = 0; i < n; i++)
    // Lê e armazena os dados nas variáveis correspondentes
    fscanf(file, "%ld %f %s %s %s", &reg->inscricao, &reg->nota,
           reg->estado, reg->cidade, reg->curso);
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
    while(contador < quantidade && fscanf(arquivo_txt, "%ld %f %2s %50s %30s",
                                          &reg.inscricao, &reg.nota,
                                          reg.estado, reg.cidade, reg.curso) == 5) {
        fwrite(&reg, sizeof(TRegistro), 1, arquivo_bin);
        contador++;
    }

    fclose(arquivo_txt);
    fclose(arquivo_bin);
}

// Função para a técnica de seleção por substituição
void selecao(TRegistro reg[], int n) {
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

void metodo1(TRegistro reg[], int n) {

}

void metodo2(TRegistro reg[], int n) {

}

void metodo3(TRegistro reg[], int n) {

}

