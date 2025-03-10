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
