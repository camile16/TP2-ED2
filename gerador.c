#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 500000
#define MAX_LINE_LENGTH 200

// Função para extrair a nota de uma linha
float extract_grade(const char *line) {
    float grade;
    sscanf(line, "%*d %f", &grade); // Ignora o código e lê a nota
    return grade;
}

// Função para comparar duas linhas por nota (crescente)
int compare_asc(const void *a, const void *b) {
    float grade_a = extract_grade(*(const char **)a);
    float grade_b = extract_grade(*(const char **)b);
    if (grade_a < grade_b) return -1;
    if (grade_a > grade_b) return 1;
    return 0;
}

// Função para comparar duas linhas por nota (decrescente)
int compare_desc(const void *a, const void *b) {
    float grade_a = extract_grade(*(const char **)a);
    float grade_b = extract_grade(*(const char **)b);
    if (grade_a > grade_b) return -1;
    if (grade_a < grade_b) return 1;
    return 0;
}

int main() {
    char *lines[MAX_LINES];
    char buffer[MAX_LINE_LENGTH];
    int line_count = 0;

    // Abrir o arquivo para leitura
    FILE *input_file = fopen("PROVAO_ALEATORIO.TXT", "r");
    if (input_file == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Ler todas as linhas do arquivo
    while (fgets(buffer, MAX_LINE_LENGTH, input_file) != NULL) {
        lines[line_count] = malloc(strlen(buffer) + 1);
        strcpy(lines[line_count], buffer);
        line_count++;
    }
    fclose(input_file);

    // Ordenar crescente por nota
    qsort(lines, line_count, sizeof(char *), compare_asc);
    FILE *asc_file = fopen("PROVAO_CRESCENTE.TXT", "w");
    for (int i = 0; i < line_count; i++) {
        fprintf(asc_file, "%s", lines[i]);
    }
    fclose(asc_file);

    // Ordenar decrescente por nota
    qsort(lines, line_count, sizeof(char *), compare_desc);
    FILE *desc_file = fopen("PROVAO_DECRESCENTE.TXT", "w");
    for (int i = 0; i < line_count; i++) {
        fprintf(desc_file, "%s", lines[i]);
    }
    fclose(desc_file);

    // Liberar memória alocada
    for (int i = 0; i < line_count; i++) {
        free(lines[i]);
    }

    printf("Arquivos ordenados por nota gerados com sucesso!\n");
    return 0;
}