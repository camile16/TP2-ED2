#include "box.h"
#include "intercala2f.h"
#include "intercalaf+1.h"

int main(int argc, char *argv[]) {
    int metodo, qntdItens, situacao, p = 0;

    clock_t tempoIni, tempoFim;
    double tempoDeExecucao;
    long nTransferenciaPre = 0, nComparacoesPre = 0, nTransferencia = 0, nComparacoes = 0;

    // Verificação da chamada do programa
    if ((argc < 4) || (argc > 5)) {
        printf("Formato esperado: ordena <método> <quantidade> <situação> [-P]\n");
        return 0;
    }

    // Transformação de string para inteiro
    metodo = atoi(argv[1]);
    qntdItens = atoi(argv[2]);
    situacao = atoi(argv[3]);

    if (argc == 5) {
        // Trata o caso de último argumento com 2 caracteres, para evitar erro no tratamento de caracter minúsculo
        if (strlen(argv[4]) < 2) {
            printf("Formato esperado: pesquisa <método> <quantidade> <situação> [-P]\n");
            return 0;
        }

        // Tolera o uso de -p (minúsculo)
        char *argP = argv[4];
        argP[1] = toupper(argP[1]);

        if (!strcmp(argP, "-P"))
            p = 1;
        else {
            printf("Formato esperado: pesquisa <método> <quantidade> <situação> <chave> [-P]\n");
            return 0;
        }
    }

    // Começa a contar o tempo de execução
    tempoIni = clock();

    // Caso tenha o [-P] como argumento
    if (p) {
        FILE *arq = fopen("out.bin", "rb");
        if (arq == NULL) {
            printf("Arquivo inexistente!\n");
            return 0;
        }
        printf("\nArquivo completo: \n\n");
        TRegistro item;
        for (int j = 0; j < qntdItens; j++) {
            if (!fread(&item, sizeof(TRegistro), 1, arq)) break;
            printf("['%ld', '%.2f', '%s', '%s', '%s']\n", item.inscricao, item.nota, item.estado, item.cidade, item.curso);
        }
        fclose(arq);
    }

    // Escolha do método que será usado no programa
    switch (metodo) {
        // Intercalação Balanceada 2f
        case 1:
            break;

        // Intercalação Balanceada f + 1
        case 2:
            
            break;

        // Quicksort Externo
        case 3:
            
            break;

        default:
            printf("Método inválido!\n");
            return 0;
    }

    // Calcula o tempo de execução
    tempoFim = clock();
    tempoDeExecucao = ((double)(tempoFim - tempoIni)) / CLOCKS_PER_SEC;

    // Exibe o resumo da execução
    char metString[60];
    switch (metodo) {
        case 1:
            strcpy(metString, "Intercalação Balanceada 2f");
            break;

        case 2:
            strcpy(metString, "Intercalação Balanceada f + 1");
            break;

        case 3:
            strcpy(metString, "Quicksort Externo");
            break;

        default:
            strcpy(metString, "Erro!");
            break;
    }

    printf("\n\nFim da execução\n\n---------------------------------------\n");
    printf("Método utilizado: %s\n", metString);
    printf("Tempo de execução: %lf segundos\n", tempoDeExecucao);
    printf("Transferência no pré-processamento: %ld\n", nTransferenciaPre);
    printf("Comparações no pré-processamento: %ld\n", nComparacoesPre);
    printf("Transferência na ordenação: %ld\n", nTransferencia);
    printf("Comparações na ordenação: %ld\n", nComparacoes);
    printf("---------------------------------------\n");

    return 0;
}