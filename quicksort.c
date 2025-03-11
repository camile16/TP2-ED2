#include <stdio.h>
#include <stdlib.h> 
#include <limits.h>
#include <stdbool.h>

#define TAM_PIVO 10

typedef int TipoApontador;
FILE *ArqLES;
FILE *ArqLi;  
FILE *ArqEi;  

typedef struct {
  long inscricao;
  float nota;
  char estado[3];
  char cidade[51];
  char curso[31];
} TipoRegistro;

// Cria o pivô
TipoRegistro R;

typedef struct {
  TipoRegistro pivo[TAM_PIVO];
} TipoPivo;

void QuicksortExterno (FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir) { 
  int i, j;
  TipoPivo pivo; // Pivô
  if (Dir - Esq < 1) return;
  PivoVazio(&pivo);
  Particao (ArqLi, ArqEi, ArqLEs, pivo, Esq, Dir, &i, &j);
  if (i - Esq < Dir - i) { 
    // Ordena primeiro o subarquivo menor
    QuicksortExterno (ArqLi, ArqEi, ArqLEs, Esq, i);
    QuicksortExterno (ArqLi, ArqEi, ArqLEs, j, Dir);
  }
  else { 
    QuicksortExterno (ArqLi, ArqEi, ArqLEs, j, Dir);
    QuicksortExterno (ArqLi, ArqEi, ArqLEs, Esq, i);
  }
}

// Lê na parte superior do arquivo
void LeSup(FILE **ArqLEs, TipoRegistro * UltLido, int *Ls, short *OndeLer) {
  fseek(*ArqLEs, (*Ls - 1) * sizeof (TipoRegistro), SEEK_SET);
  fread (UltLido, sizeof(TipoRegistro), 1, *ArqLEs);
  (*Ls)--;  
  *OndeLer = false;
}

// Lê na parte inferior do arquivo
void Leinf(FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer) { 
  fread(UltLido, sizeof (TipoRegistro), 1, *ArqLi);
  (*Li)++; 
  *OndeLer = true;
}

// Insere elemento no pivo
void InserirPivo (TipoPivo *pivo, TipoRegistro *UltLido, int *NRpivo) {
  /*Insere UltLido de forma ordenada na pivo*/
  InsereItem (*UltLido, pivo); *NRpivo = ObterNumCelOcupadas (pivo);
}

// Escreve um elemento na parte superior do arquivo
void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es)
{
  fseek(*ArqLEs, (*Es-1) *sizeof(TipoRegistro), SEEK_SET);
  fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEs); (*Es)--;
}

// EscreveMin

void RetiraMax(TipoPivo *pivo, TipoRegistro *R, int *NRpivo)
{ 
    RetiraUltimo (pivo, R); 
    *NRpivo = ObterNumCelOcupadas(pivo); 
}

void RetiraMin (TipoPivo *pivo, TipoRegistro *R, int *NRpivo)
{ 
    RetiraPrimeiro(pivo, R); 
    *NRpivo = ObterNumCelOcupadas(pivo);
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLES,
              TipoPivo pivo, int Esq, int Dir, int *i, int *j) {
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq,
        NRpivo = 0, Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = true;
    TipoRegistro UltLido, R;
    fseek(*ArqLi, (Li - 1) * sizeof(TipoRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(TipoRegistro), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;
    while (Ls >= Li) {
        if (NRpivo < TAM_PIVO - 1) {
            if (OndeLer)
                LeSup(ArqLES, &UltLido, &Ls, &OndeLer);
            else
                LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            InserirPivo(&pivo, &UltLido, &NRpivo);
            continue;
        }
        if (Ls == Es)
            LeSup(ArqLES, &UltLido, &Ls, &OndeLer);
        else if (Li == Ei)
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);
        else if (OndeLer)
            LeSup(ArqLES, &UltLido, &Ls, &OndeLer);
        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer);

        if (UltLido.nota >= Lsup) {
            *j = Es;
            EscreveMax(ArqLES, UltLido, &Es);
            continue;
        }
        if (UltLido.nota < Linf) {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei);
            continue;
        }
        InserirPivo(&pivo, &UltLido, &NRpivo);
        if (Ei - Esq < Dir - Es) {
            RetiraMin(&pivo, &R, &NRpivo);
            EscreveMin(ArqEi, R, &Ei);
            Linf = R.nota;
        } else {
            RetiraMax(&pivo, &R, &NRpivo);
            EscreveMax(ArqLES, R, &Es);
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
    R.nota = 5; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.nota = 3; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.nota = 10; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.nota = 6; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.nota = 1; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.nota = 7; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.nota = 4; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
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
    ArqLES = fopen("teste.dat", "r+b");
    if (ArqLES == NULL) {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }
    QuicksortExterno(&ArqLi, &ArqEi, &ArqLES, 1, 7);
    fflush(ArqLi);
    fclose(ArqEi);
    fclose(ArqLES);
    fseek(ArqLi, 0, SEEK_SET);
    while (fread(&R, sizeof(TipoRegistro), 1, ArqLi)) {
        printf("Registro-%d\n", R.nota);
    }
    fclose(ArqLi);
    return 0;
}
