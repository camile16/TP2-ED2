#include <stdio.h>
#include <stdlib.h> 
#include <limits.h>
#include <stdbool.h>
#include "box.c"

#define TAM 10 // Tamanho da memória interna disponível

FILE *ArqLE; // Arquivo de Leitura e Escrita
FILE *ArqLi; // Arquivo de Leitura inferior
FILE *ArqEi; // Arquivo de Escrita inferior

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

// Ordenação externa pelo método QuickSort
void QuicksortExterno (FILE **ArqLi, FILE **ArqEi, FILE **ArqLE, int esq, int dir) { 
    int i, j; // Variáveis auxiliares
  
    // Cria e inicializa o pivô
    TPivo pivo;
    InicializaPivo(&pivo);

    // Condição de parada da recursão (arquivo está ordenado)
    if (dir - esq < 1) return;

    Particao(ArqLi, ArqEi, ArqLE, pivo, esq, dir, &i, &j);

    // Ordena primeiro o subarquivo menor
    if (i - esq < dir - j) { 
        // Subarquivo da esquerda é menor
        QuicksortExterno (ArqLi, ArqEi, ArqLE, esq, i);
        QuicksortExterno (ArqLi, ArqEi, ArqLE, j, dir);
    }
    else { 
        // Subarquivo da direita é menor
        QuicksortExterno (ArqLi, ArqEi, ArqLE, j, dir);
        QuicksortExterno (ArqLi, ArqEi, ArqLE, esq, i);
    }
}

// Lê na parte superior do arquivo
void LeSup(FILE **ArqLE, TRegistro *UltLido, int *Ls, short *OndeLer) {
  fseek(*ArqLE, (*Ls - 1) * sizeof (TRegistro), SEEK_SET);
  fread (UltLido, sizeof(TRegistro), 1, *ArqLE);
  (*Ls)--;  
  *OndeLer = false;
}

// Lê na parte inferior do arquivo
void Leinf(FILE **ArqLi, TRegistro *UltLido, int *Li, short *OndeLer) { 
  fread(UltLido, sizeof (TRegistro), 1, *ArqLi);
  (*Li)++; 
  *OndeLer = true;
}

// Insere elemento no pivo
void InserePivo(TPivo *pivo, TRegistro *UltLido, int *NRpivo) {
  // Insere UltLido de forma ordenada no pivo
  InsereItem (*UltLido, pivo); *NRpivo = pivo->num_cel_ocupadas;
}

// Escreve um elemento na parte superior do arquivo
void EscreveMax(FILE **ArqLE, TRegistro R, int *Es)
{
  fseek(*ArqLE, (*Es-1) *sizeof(TRegistro), SEEK_SET);
  fwrite(&R, sizeof(TRegistro), 1, *ArqLE); (*Es)--;
}

// EscreveMin

void RetiraMax(TPivo *pivo, TRegistro *R, int *NRpivo)
{ 
    RetiraUltimo (pivo, R); 
    *NRpivo = pivo->num_cel_ocupadas; 
}

void RetiraMin (TPivo *pivo, TRegistro *R, int *NRpivo)
{ 
    RetiraPrimeiro(pivo, R); 
    *NRpivo = pivo->num_cel_ocupadas;
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLE, TPivo pivo, int esq, int dir, int *i, int *j) {
    int Ls = dir, Es = dir, Li = esq, Ei = esq, NRpivo = 0, Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = true;
    TRegistro UltLido, R;
    fseek(*ArqLi, (Li - 1) * sizeof(TRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(TRegistro), SEEK_SET);
    *i = esq - 1;
    *j = dir + 1;
    while (Ls >= Li) {
        if (NRpivo < TAM - 1) {
            if (OndeLer)
                LeSup(ArqLE, &UltLido, &Ls, &OndeLer);
            else
                LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            InserePivo(&pivo, &UltLido, &NRpivo);
            continue;
        }
        if (Ls == Es)
            LeSup(ArqLE, &UltLido, &Ls, &OndeLer);
        else if (Li == Ei)
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        else if (OndeLer)
            LeSup(ArqLE, &UltLido, &Ls, &OndeLer);
        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        
        if (UltLido.nota >= Lsup) {
            *j = Es;
            EscreveMax(ArqLE, UltLido, &Es);
            continue;
        }
        if (UltLido.nota < Linf) {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }
        InserePivo(&pivo, &UltLido, &NRpivo);
        if (Ei - esq < dir - Es) {
            RetiraMin(&pivo, &R, &NRpivo);
            EscreveMin(ArqEi, R, &Ei);
            Linf = R.nota;
        } else {
            RetiraMax(&pivo, &R, &NRpivo);
            EscreveMax(ArqLE, R, &Es);
            Lsup = R.nota;
        }
    }
    while (Ei <= Es) {
        RetiraMin(&pivo, &R, &NRpivo);
        EscreveMin(ArqEi, R, &Ei);
    }
}

int main(int argc, char *argv[]) {
    
    ArqLi = fopen("teste.dat", "w");
        if (ArqLi == NULL) {
            printf("Arquivo nao pode ser aberto\n");
            exit(1);
        }
       // ...
    fclose(ArqLi);
    
    ArqLi = fopen("teste.dat", "r+b");
        if (ArqLi == NULL) {
            printf("Arquivo nao pode ser aberto\n");
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
