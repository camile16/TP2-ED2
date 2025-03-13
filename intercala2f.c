#include "intercala2f.h"

// Função para gerar blocos ordenados e gravá-los nas fitas de entrada
void gerar_blocos(const char *nome_arquivo_bin, int qntdItens, long *nTransferencia, long *nComparacoes) {
    FILE *arquivo_bin = fopen(nome_arquivo_bin, "rb");
    if (!arquivo_bin) {
        perror("Erro ao abrir o arquivo binário");
        return;
    }

    TRegistro bloco[MAX_MEMORIA];
    int contador_blocos = 0;

    while (1) {
        // Ler um bloco de registros do arquivo binário
        int registros_lidos = fread(bloco, sizeof(TRegistro), MAX_MEMORIA, arquivo_bin);
        if (registros_lidos == 0) break; // Fim do arquivo

        // Ordenar o bloco na memória interna
        selecao_por_substituicao(bloco, registros_lidos);
        (*nComparacoes) += registros_lidos * (long)log2(registros_lidos); // Contabiliza comparações

        // Gravar o bloco ordenado em uma fita de entrada
        char nome_fita[20];
        sprintf(nome_fita, "fita_entrada_%d.bin", contador_blocos);
        FILE *fita = fopen(nome_fita, "wb");
        if (!fita) {
            perror("Erro ao criar fita de entrada");
            fclose(arquivo_bin);
            return;
        }

        fwrite(bloco, sizeof(TRegistro), registros_lidos, fita);
        (*nTransferencia) += registros_lidos; // Contabiliza transferências

        fclose(fita);
        contador_blocos++;
    }

    fclose(arquivo_bin);
    printf("%d blocos ordenados foram gerados e gravados nas fitas de entrada.\n", contador_blocos);
}

// Função para intercalar blocos ordenados das fitas de entrada nas fitas de saída
void intercalar_fitas(FILE *fitas_entrada[FITAS_ENTRADA], FILE *fitas_saida[FITAS_SAIDA], long *nTransferencia, long *nComparacoes) {
    TRegistro blocos[FITAS_ENTRADA][FITAS_ENTRADA]; // Blocos de registros
    int indices[FITAS_ENTRADA] = {0}; // Índices para cada bloco

    // Ler um bloco de cada fita de entrada
    for (int i = 0; i < FITAS_ENTRADA; i++) {
        indices[i] = fread(blocos[i], sizeof(TRegistro), FITAS_ENTRADA, fitas_entrada[i]);
        (*nTransferencia) += indices[i]; // Contabiliza transferências
    }

    int fita_saida_atual = 0;
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
            if (indices[i] > 0 && blocos[i][0].nota < menor_nota) {
                menor_nota = blocos[i][0].nota;
                menor_idx = i;
                (*nComparacoes)++; // Contabiliza comparações
            }
        }

        // Escrever o menor registro na fita de saída atual
        fwrite(&blocos[menor_idx][0], sizeof(TRegistro), 1, fitas_saida[fita_saida_atual]);
        (*nTransferencia)++; // Contabiliza transferências

        // Remover o registro do bloco
        for (int i = 1; i < indices[menor_idx]; i++) {
            blocos[menor_idx][i - 1] = blocos[menor_idx][i];
        }
        indices[menor_idx]--;

        // Avançar para a próxima fita de saída
        fita_saida_atual = (fita_saida_atual + 1) % FITAS_SAIDA;
    }
}

// Função principal da intercalação balanceada 2f
void intercalacao_balanceada_2f(const char *nome_arquivo_bin, int qntdItens, long *nTransferencia, long *nComparacoes) {
    FILE *fitas_entrada[FITAS_ENTRADA];
    FILE *fitas_saida[FITAS_SAIDA];

    // Abrir as fitas de entrada e saída
    for (int i = 0; i < FITAS_ENTRADA; i++) {
        char nome_fita[20];
        sprintf(nome_fita, "fita_entrada_%d.bin", i);
        fitas_entrada[i] = fopen(nome_fita, "rb");
        if (!fitas_entrada[i]) {
            perror("Erro ao abrir fita de entrada");
            return;
        }
    }
    for (int i = 0; i < FITAS_SAIDA; i++) {
        char nome_fita[20];
        sprintf(nome_fita, "fita_saida_%d.bin", i);
        fitas_saida[i] = fopen(nome_fita, "wb");
        if (!fitas_saida[i]) {
            perror("Erro ao abrir fita de saída");
            return;
        }
    }

    // Intercalar as fitas
    intercalar_fitas(fitas_entrada, fitas_saida, nTransferencia, nComparacoes);

    // Fechar as fitas
    for (int i = 0; i < FITAS_ENTRADA; i++) {
        fclose(fitas_entrada[i]);
    }
    for (int i = 0; i < FITAS_SAIDA; i++) {
        fclose(fitas_saida[i]);
    }
}
