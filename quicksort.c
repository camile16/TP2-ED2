#include <stdio.h>
#include <stdlib.h> 
#include <limits.h>
#include <stdbool.h>
#include "box.c"

#define TAM 10 // Tamanho da memória interna disponível

FILE *ArqLE; // Arquivo de Leitura Superior e Escrita Superior
FILE *ArqLi; // Arquivo de Leitura Inferior
FILE *ArqEi; // Arquivo de Escrita Inferior

// Cria um registro (aluno)
TRegistro aluno;

// Estrutura do pivõ
typedef struct {
  TRegistro pivo[TAM];
  int num_cel_ocupadas;
} TPivo;

// Inicialização do pivô
void InicializaPivo(TPivo *pivo) {
    pivo->num_cel_ocupadas = 0;
}

// Leitura na parte superior do arquivo
void LeSup(FILE **ArqLE, TRegistro *ult_lido, int *Ls, short *onde_ler) {
  fseek(*ArqLE, (*Ls - 1) * sizeof (TRegistro), SEEK_SET);
  fread (ult_lido, sizeof(TRegistro), 1, *ArqLE);
  (*Ls)--;  
  *onde_ler = false;
}

// Leitura na parte inferior do arquivo
void Leinf(FILE **ArqLi, TRegistro *ult_lido, int *Li, short *onde_ler) { 
  fread(ult_lido, sizeof (TRegistro), 1, *ArqLi);
  (*Li)++; 
  *onde_ler = true;
}

// Inserção de um elemento no pivo
void InserePivo(TPivo *pivo, TRegistro *ult_lido) {
    // Insere ult_lido de forma ordenada no pivo
    InsereItem (*ult_lido, pivo); 
    pivo->num_cel_ocupadas++;
}

// Escrita de um elemento na parte superior do arquivo
void EscreveMax(FILE **ArqLE, TRegistro R, int *Es)
{
  fseek(*ArqLE, (*Es-1) *sizeof(TRegistro), SEEK_SET);
  fwrite(&R, sizeof(TRegistro), 1, *ArqLE); (*Es)--;
}

// Escrita de um elemento na parte inferior do arquivo
void EscreveMin (FILE **ArqEi, TRegistro R, int *Ei) { 
    fwrite (&R, sizeof (TRegistro), 1, *ArqEi); (*Ei)++; 
}

void RetiraMax(TPivo *pivo, TRegistro *R, int *cel_ocupadas)
{ 
    RetiraUltimo (pivo, R); 
    *cel_ocupadas = pivo->num_cel_ocupadas; 
}

void RetiraMin (TPivo *pivo, TRegistro *R, int *cel_ocupadas)
{ 
    RetiraPrimeiro(pivo, R); 
    *cel_ocupadas = pivo->num_cel_ocupadas;
}

// Partição do arquivo
void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLE, TPivo pivo, int esq, int dir, int *i, int *j) {
    int Ls = dir, Es = dir, Li = esq, Ei = esq, // começa com os ponteiros de leitura e escrita no início e no final do arquivo
        Linf = INT_MIN, Lsup = INT_MAX; // inicializa os limites inferior e superior do pivô
    short onde_ler = true; // controla se o registro é lido da parte inferior ('false') ou superior ('true') do arquivo
    TRegistro ult_lido, R; // registros auxiliares
    
    int cel_ocupadas = pivo.num_cel_ocupadas; // ALTERAR 

    // Posiciona os ponteiros de leitura e escrita
    fseek(*ArqLi, (Li - 1) * sizeof(TRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(TRegistro), SEEK_SET);

    // Inicializa os valores de i e j, que indicam os limites dos subarquivos
    *i = esq - 1;
    *j = dir + 1;

    // Faz partições enquanto Ls e Li não se cruzam
    while(Ls >= Li) {
        // Há espaço no pivô
            if(pivo.num_cel_ocupadas < TAM - 1) {
                // lê o próximo registro do arquivo
                if(onde_ler)
                    LeSup(ArqLE, &ult_lido, &Ls, &onde_ler);
                else
                    LeInf(ArqLi, &ult_lido, &Li, &onde_ler);
                // insere o registro lido no pivô
                InserePivo(&pivo, &ult_lido);
                continue;
            }
        // Pivô está cheio
            // Quebra da alternancia de leitura, caso os ponteiros de leitura e escrita se encontrem
            if (Ls == Es)
                LeSup(ArqLE, &ult_lido, &Ls, &onde_ler);
            else if (Li == Ei)
                LeInf(ArqLi, &ult_lido, &Li, &onde_ler);
            // Leitura normal, seguindo a alternância
            else if (onde_ler)
                LeSup(ArqLE, &ult_lido, &Ls, &onde_ler);
            else
                LeInf(ArqLi, &ult_lido, &Li, &onde_ler);
            // Escreve elementos nos subarquivos
            if (ult_lido.nota >= Lsup) {
                *j = Es;
                EscreveMax(ArqLE, ult_lido, &Es);
                continue;
            }
            if (ult_lido.nota < Linf) {
                *i = Ei;
                EscreveMin(ArqEi, ult_lido, &Ei);
                continue;
            }

            InserePivo(&pivo, &ult_lido);

            if (Ei - esq < dir - Es) {
                RetiraMin(&pivo, &R, &cel_ocupadas);
                EscreveMin(ArqEi, R, &Ei);
                Linf = R.nota;
            } else {
                RetiraMax(&pivo, &R, &cel_ocupadas);
                EscreveMax(ArqLE, R, &Es);
                Lsup = R.nota;
            }
    }
    
    while (Ei <= Es) {
        RetiraMin(&pivo, &R, &cel_ocupadas);
        EscreveMin(ArqEi, R, &Ei);
    }
}

// Ordenação externa pelo método QuickSort
void QuicksortExterno (FILE **ArqLi, FILE **ArqEi, FILE **ArqLE, int esq, int dir) { 
    int i, j; // variáveis auxiliares
  
    // Cria e inicializa o pivô
    TPivo pivo;
    InicializaPivo(&pivo);

    // Condição de parada da recursão
    if (dir - esq < 1) return;

    // Realiza a partição do pivo
    Particao(ArqLi, ArqEi, ArqLE, pivo, esq, dir, &i, &j);

    // Ordena primeiro o subarquivo menor
    if (i - esq < dir - j) { // subarquivo da esquerda é menor
        QuicksortExterno (ArqLi, ArqEi, ArqLE, esq, i);
        QuicksortExterno (ArqLi, ArqEi, ArqLE, j, dir);
    }
    else { // subarquivo da direita é menor
        QuicksortExterno (ArqLi, ArqEi, ArqLE, j, dir);
        QuicksortExterno (ArqLi, ArqEi, ArqLE, esq, i);
    }
}

int main(int argc, char *argv[]) {
    
    ArqLi = fopen("teste.dat", "wb");
        if (ArqLi == NULL) {
            printf("Arquivo nao pode ser aberto\n");
            exit(1);
        }

    aluno.nota = 5; fwrite(&aluno, sizeof (TRegistro), 1, ArqLi);
    aluno.nota = 3; fwrite(&aluno, sizeof (TRegistro), 1, ArqLi);
    aluno.nota = 10;fwrite(&aluno, sizeof (TRegistro), 1, ArqLi);
    aluno.nota = 6; fwrite(&aluno, sizeof (TRegistro), 1, ArqLi);
    aluno.nota = 1; fwrite(&aluno, sizeof (TRegistro), 1, ArqLi);
    aluno.nota = 7; fwrite(&aluno, sizeof (TRegistro), 1, ArqLi);
    aluno.nota = 4; fwrite(&aluno, sizeof (TRegistro), 1, ArqLi);

    fclose(ArqLi);
    
    ArqLi = fopen("teste.dat", "r+b");
        if (ArqLi == NULL) {
            printf("Arquivo não pode ser aberto!\n");
            exit(1);
        }
        ArqEi = fopen("teste.dat", "r+b");
        if (ArqEi == NULL) {
            printf("Arquivo nao pode ser aberto\n");
            exit(1);
        }
        ArqLE = fopen("teste.dat", "r+b");
        if (ArqLE == NULL) {
            printf("Arquivo nao pode ser aberto\n");
            exit(1);
        }
       
        QuicksortExterno(&ArqLi, &ArqEi, &ArqLE, 1, 7);
        
        fflush(ArqLi);
        fclose(ArqEi);
        fclose(ArqLE);

        fseek(ArqLi, 0, SEEK_SET);
        while (fread(&R, sizeof(TRegistro), 1, ArqLi)) {
            printf("aluno-%d\n", R.nota);
        }
        
    fclose(ArqLi);
    
    return 0;
}
