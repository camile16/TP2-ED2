void QuicksortExterno (FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir) { 
  int i, J;
  TipoArea Area; // Pivô
  if (Dir - Esq < 1) return;
  FAVazia(&Area);
  Particao (ArqLi, ArqEi, ArgLEs, Area, Esq, Dir, &i, &j);
  if (i - Esq < Dir - i) { 
  /* ordene primeiro o subarquivo menor */
    QuicksortExterno (ArqLi, ArqEi, ArgLEs, Esq, i);
    QuicksortExterno (ArqLi, ArqEi, ArgLEs, j, Dir);
  }
  else { 
    QuicksortExterno (ArqLi, ArgEi, ArgLEs, j, Dir);
    QuicksortExterno (ArqLi, ArqEi, ArqLEs, Esq, i);
  }
}

void LeSup(FILE **ArqLEs, TipoRegistro * UltLido, int *Ls, short *OndeLer) {
  fseek(*ArqLEs, (#Ls - 1) * sizeof (TipoRegistro), SEEK_SET);
  fread (UltLido, sizeof(TipoRegistro), 1, *ArqLEs);
  (*Ls)--;  
  *OndeLer = FALSE;
}

void Leinf(FILE **ArqLi, TipoRegistro *UitLido, int *Li, short *OndeLer) { 
  fread(UltLido, sizeof (TipoRegistro), 1, *ArqLi);
  (*Li)++; 
  *OndeLer = TRUE;
}

void InserirArea (TipoArea *Area, TipoRegistro *UltLido, int *NRArea) {
  /*Insere UltLido de forma ordenada na Area*/
  Insereltem (*UItLido, Area); *NRArea = ObterNumCelOcupadas (Area);
}

void EscreveMax(FILE **ArqLEs, TipoRegistro R, int *Es)
{
  fseek(*ArqLEs, (*Es-1) *sizeof(TipoRegistro), SEEK_SET);
  fwrite(&R, sizeof(TipoRegistro), 1, *ArqLEs); (*Es)--;
}

void RetiraMax(TipoArea *Area, TipoRegistro *R, int *NRArea)
{ 
    RetiraUltimo (Area, R); 
    *NRArea = ObterNumCelOcupadas (Area); 
}

void RetiraMin (TipoArea *Area, TipoRegistro *R, int *NRArea)
{ 
    RetiraPrimeiro(Area, R); 
    *NRArea = ObterNumCelOcupadas (Area); 
}

void Particao(FILE **ArqLi, FILE **ArqEi, FILE **ArqLES,
              TipoArea Area, int Esq, int Dir, int *i, int *j) {
    int Ls = Dir, Es = Dir, Li = Esq, Ei = Esq,
        NRArea = 0, Linf = INT_MIN, Lsup = INT_MAX;
    short OndeLer = TRUE;
    TipoRegistro UltLido, R;
    fseek(*ArqLi, (Li - 1) * sizeof(TipoRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof(TipoRegistro), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;
    while (Ls >= Li) {
        if (NRArea < TAMAREA - 1) {
            if (OndeLer)
                LeSup(ArqLES, &UltLido, &Ls, &OndeLer);
            else
                LeInf(ArqLi, &UltLido, &Li, &OndeLer);
            InserirArea(&Area, &UltLido, &NRArea);
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
    }
    if (UltLido.Chave >= Lsup) {
        *j = Es;
        EscreveMax(ArqLES, UltLido, &Es);
        continue;
    }
    if (UltLido.Chave < Linf) {
        *i = Ei;
        EscreveMin(ArqEi, UltLido, &Ei);
        continue;
    }
    InserirArea(&Area, &UltLido, &NRArea);
    if (Ei - Esq < Dir - Es) {
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei);
        Linf = R.Chave;
    } else {
        RetiraMax(&Area, &R, &NRArea);
        EscreveMax(ArqLES, R, &Es);
        Lsup = R.Chave;
    }
    while (Ei <= Es) {
        RetiraMin(&Area, &R, &NRArea);
        EscreveMin(ArqEi, R, &Ei);
    }
}

typedef int TipoApontador;
typedef TipoItem TipoRegistro;
FILE *ArqLES;
FILE *ArqLi;  
FILE *ArqEi;  
TipoItem R;

int main(int argc, char *argv[]) {
    ArqLi = fopen("teste.dat", "w");
    if (ArqLi == NULL) {
        printf("Arquivo nao pode ser aberto\n");
        exit(1);
    }
    R.Chave = 5; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 3; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 10; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 6; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 1; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 7; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
    R.Chave = 4; fwrite(&R, sizeof(TipoRegistro), 1, ArqLi);
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
        printf("Registro-%d\n", R.Chave);
    }
    fclose(ArqLi);
    return 0;
}
