#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_REGISTROS_1 10
#define MAX_REGISTROS_2 19
#define MAX_FITAS 20

// Estrutura para armazenar um registro
typedef struct {
    long inscricao;
    float nota;
    char estado[3];
    char cidade[51];
    char curso[31];
} Registro;

// Função auxiliar para comparar registros
int comparar_registros(const void *a, const void *b) {
    Registro *regA = (Registro *)a;
    Registro *regB = (Registro *)b;
    return (regA->nota > regB->nota) - (regA->nota < regB->nota);
}

// Função para realizar a intercalação balanceada de vários caminhos (2f fitas)
void intercalacao_balanceada_2f() {
    printf("Executando intercalação balanceada de vários caminhos (2f fitas)\n");
    // Implementação do método 1
}

// Função para realizar a intercalação balanceada de vários caminhos (f+1 fitas)
void intercalacao_balanceada_f1() {
    printf("Executando intercalação balanceada de vários caminhos (f+1 fitas)\n");
    // Implementação do método 2
}

// Função para realizar o quicksort externo
void quicksort_externo() {
    printf("Executando quicksort externo\n");

    FILE *arquivo = fopen("PROVAO.TXT", "r+");
    if (!arquivo) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    
    // Ler registros do arquivo
    Registro *registros = malloc(MAX_REGISTROS_1 * sizeof(Registro));
    if (!registros) {
        printf("Erro ao alocar memória\n");
        fclose(arquivo);
        exit(1);
    }
    
    int n = 0;
    while (fscanf(arquivo, "%ld %f %2s %50s %30s", &registros[n].inscricao, &registros[n].nota, registros[n].estado, registros[n].cidade, registros[n].curso) == 5) {
        n++;
        if (n >= MAX_REGISTROS_1) {
            qsort(registros, n, sizeof(Registro), comparar_registros);
            fwrite(registros, sizeof(Registro), n, arquivo);
            n = 0;
        }
    }
    
    if (n > 0) {
        qsort(registros, n, sizeof(Registro), comparar_registros);
        fwrite(registros, sizeof(Registro), n, arquivo);
    }
    
    free(registros);
    fclose(arquivo);
    printf("Quicksort externo concluído com sucesso.\n");
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: ordena <método> <quantidade> <situação> [-P]\n");
        return 1;
    }

    int metodo = atoi(argv[1]);
    int quantidade = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    int imprimir = (argc == 5 && strcmp(argv[4], "-P") == 0);

    switch (metodo) {
        case 1:
            intercalacao_balanceada_2f();
            break;
        case 2:
            intercalacao_balanceada_f1();
            break;
        case 3:
            quicksort_externo();
            break;
        default:
            printf("Método inválido. Escolha 1, 2 ou 3.\n");
            return 1;
    }
    
    return 0;
}
