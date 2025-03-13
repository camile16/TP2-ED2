#include "intercalaf+1.h"

// Função para intercalar blocos ordenados das fitas de entrada na fita de saída
void intercalar_fitas(FILE *fitas_entrada[FITAS_ENTRADA], FILE *fita_saida, long *nTransferencia, long *nComparacoes) {
    TRegistro blocos[FITAS_ENTRADA]; // Blocos de registros
    int indices[FITAS_ENTRADA] = {0}; // Índices para cada bloco

    // Ler um registro de cada fita de entrada
    for (int i = 0; i < FITAS_ENTRADA; i++) {
        if (fread(&blocos[i], sizeof(TRegistro), 1, fitas_entrada[i])) {
            indices[i] = 1; // Indica que há um registro disponível
            (*nTransferencia)++; // Contabiliza transferências
        }
    }

    while (1) {
        int todos_vazios = 1;
        for (int i = 0; i < FITAS_ENTRADA; i++) {
            if (indices[i] > 0) {
                todos_vazios = 0;
                break;
            }
        }
        if (todos_vazios) break; // Todas as fitas de entrada estão vazias

        // Encontrar o menor registro entre os blocos
        int menor_idx = -1;
        float menor_nota = 101.0; // Notas vão até 100.0
        for (int i = 0; i < FITAS_ENTRADA; i++) {
            if (indices[i] > 0 && blocos[i].nota < menor_nota) {
                menor_nota = blocos[i].nota;
                menor_idx = i;
                (*nComparacoes)++; // Contabiliza comparações
            }
        }

        // Escrever o menor registro na fita de saída
        fwrite(&blocos[menor_idx], sizeof(TRegistro), 1, fita_saida);
        (*nTransferencia)++; // Contabiliza transferências

        // Ler o próximo registro da fita de entrada correspondente
        if (!fread(&blocos[menor_idx], sizeof(TRegistro), 1, fitas_entrada[menor_idx])) {
            indices[menor_idx] = 0; // Fita de entrada esgotada
        } else {
            (*nTransferencia)++; // Contabiliza transferências
        }
    }
}

// Função principal da intercalação balanceada f + 1
void intercalacao_balanceada_f1(const char *nome_arquivo_bin, int qntdItens, long *nTransferencia, long *nComparacoes) {
    FILE *fitas_entrada[FITAS_ENTRADA];
    FILE *fita_saida;

    // Abrir as fitas de entrada
    for (int i = 0; i < FITAS_ENTRADA; i++) {
        char nome_fita[20];
        sprintf(nome_fita, "fita_entrada_%d.bin", i);
        fitas_entrada[i] = fopen(nome_fita, "rb");
        if (!fitas_entrada[i]) {
            perror("Erro ao abrir fita de entrada");
            return;
        }
    }

    // Abrir a fita de saída
    fita_saida = fopen("fita_saida.bin", "wb");
    if (!fita_saida) {
        perror("Erro ao abrir fita de saída");
        return;
    }

    // Intercalar as fitas
    intercalar_fitas(fitas_entrada, fita_saida, nTransferencia, nComparacoes);

    // Fechar as fitas
    for (int i = 0; i < FITAS_ENTRADA; i++) {
        fclose(fitas_entrada[i]);
    }
    fclose(fita_saida);
}