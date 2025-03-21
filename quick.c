#include "box.h"
#include "box.c"
#include "quicksort.c"

void FAVazia(TPivo *Area) {
    int i;
    pivo->num_cel_ocupadas = 0;
    pivo->Primeiro = -1;
    pivo->Ultimo = -1;
    pivo->CelulasDisp = 0;
    for (i = 0; i < TAM; i++) {
        pivo->Itens[i].Ant = -1;
        pivo->Itens[i].Prox = i + 1;
    }
}

int ObtemNumCelOcupadas(TPivo* pivo) {
    return (pivo->num_cel_ocupadas);
}

void InsereItem(TRegistro Item, TPivo *pivo, int* comp) {
    int pos, disp, IndiceInsercao;
    (*comp)++;
    if (pivo->num_cel_ocupadas == TAM) {
        printf("Tentativa de inserção em memoria cheia.\n");
        return;
    }
    disp = pivo->CelulasDisp;
    pivo->CelulasDisp = pivo->Itens[pivo->CelulasDisp].Prox;
    pivo->Itens[disp].Item = Item;
    pivo->num_cel_ocupadas++;
    (*comp)++;
    if (pivo->num_cel_ocupadas == 1) {
        /*Inserção do primeiro item*/
        pivo->Primeiro = disp;
        pivo->Ultimo = pivo->Primeiro;
        pivo->Itens[pivo->Primeiro].Prox = -1;
        pivo->Itens[pivo->Primeiro].Ant = -1;
        return;
    }
    pos = pivo->Primeiro;
    (*comp)++;
    if (Item.nota < pivo->Itens[pos].Item.nota) {
        /*Inserção na primeira posição*/
        pivo->Itens[disp].Ant = -1;
        pivo->Itens[disp].Prox = pos;
        pivo->Itens[pos].Ant = disp;
        pivo->Primeiro = disp;
        return;
    }
    IndiceInsercao = pivo->Itens[pos].Prox;
    while (IndiceInsercao != -1 && pivo->Itens[IndiceInsercao].Item.nota < Item.nota) {
        (*comp)++;
        pos = IndiceInsercao;
        IndiceInsercao = pivo->Itens[pos].Prox;
    }
    (*comp)++;
    if (IndiceInsercao == -1) {
        /*Inserção realizada na ultima posição*/
        pivo->Itens[disp].Ant = pos;
        pivo->Itens[disp].Prox = -1;
        pivo->Itens[pos].Prox = disp;
        pivo->Ultimo = disp;
        return;
    }
    pivo->Itens[disp].Ant = pos;
    pivo->Itens[disp].Prox = pivo->Itens[pos].Prox;
    pivo->Itens[pos].Prox = disp;
    pos = pivo->Itens[disp].Prox;
    pivo->Itens[pos].Ant = disp;
    /*Inserção realizada no meio da área*/
}

void RetiraPrimeiro(TPivo *pivo, TRegistro* Item, int* comp) {

    Apontador ProxTmp;
    (*comp)++;
    if (pivo->num_cel_ocupadas == 0) {
        /*Área Vazia*/
        //printf("Erro. Memoria vazia\n");
        return;
    }
    *Item = pivo->Itens[pivo->Primeiro].Item;
    ProxTmp = pivo->Itens[pivo->Primeiro].Prox;
    pivo->Itens[pivo->Primeiro].Prox = pivo->CelulasDisp;
    pivo->CelulasDisp = pivo->Primeiro;
    pivo->Primeiro = ProxTmp;
    (*comp)++;
    if ((unsigned int) pivo->Primeiro < TAM)
        pivo->Itens[pivo->Primeiro].Ant = -1;
    pivo->num_cel_ocupadas--;
}

void RetiraUltimo(TPivo* pivo, TRegistro *Item, int *comp) {
    Apontador AntTmp;
    (*comp)++;
    if (pivo->num_cel_ocupadas == 0) {
        /*pivo vazia*/
        printf("Erro. Memoria vazia\n");
        return;
    }
    *Item = pivo->Itens[pivo->Ultimo].Item;
    AntTmp = pivo->Itens[pivo->Ultimo].Ant;
    pivo->Itens[pivo->Ultimo].Prox = pivo->CelulasDisp;
    pivo->CelulasDisp = pivo->Ultimo;
    pivo->Ultimo = AntTmp;
    (*comp)++;
    if ((unsigned int) pivo->Ultimo < TAM)
        pivo->Itens[pivo->Ultimo].Prox = -1;
    pivo->num_cel_ocupadas--;

}

void ImprimePivo(TPivo* pivo) {
    int pos;
    if (pivo->num_cel_ocupadas <= 0) {
        printf("Memoria vazia\n");
        return;
    }
    printf("Memoria\n");
    printf("Numero de celulas ocupadas: %d\n", pivo->num_cel_ocupadas);
    pos = pivo->Primeiro;
    while (pos != -1) {
        printf("%f ", pivo->Itens[pos].Item.nota);
        pos = pivo->Itens[pos].Prox;
    }
}

// Funções utilizadas na partição do QuickSort

void LeSup(FILE **ArqLEs, TRegistro* UltLido, int* Ls, short *OndeLer, int* transf) {
    //assert(ArqLEs);
    fseek(*ArqLEs, (*Ls - 1) * sizeof (TRegistro), SEEK_SET);
    fread(UltLido, sizeof (TRegistro), 1, *ArqLEs);
    (*transf)++;
    (*Ls)--;
    *OndeLer = false;
}

void LeInf(FILE** ArqLi, TRegistro* UltLido, int* Li, short* OndeLer, int* transf) {
    //assert(LeInf);
    fread(UltLido, sizeof (TRegistro), 1, *ArqLi);
    (*transf)++;
    (*Li)++;
    *OndeLer = true;
}

void InsereNoPivo(TPivo* pivo, TRegistro* UltLido, int* NRpivo, int* comp) {
    /*Insere UltLido de forma ordenada na área*/
    InsereItem(*UltLido, pivo, comp);
    *NRpivo = ObtemNumCelOcupadas(pivo);
}

void EscreveMax(FILE **ArqLEs, TRegistro R, int *Es, int* transf) {
    //assert(ArqLEs);
    fseek(*ArqLEs, (*Es - 1) * sizeof (TRegistro), SEEK_SET);
    fwrite(&R, sizeof (TRegistro), 1, *ArqLEs);
    (*transf)++;
    (*Es)--;
}

void EscreveMin(FILE **ArqEi, TRegistro R, int *Ei, int* transf) {
    fwrite(&R, sizeof (TRegistro), 1, *ArqEi);
    (*transf)++;
    (*Ei)++;
}

void RetiraMax(TPivo* pivo, TRegistro *R, int *NRpivo, int* comp) {
    RetiraUltimo(pivo, R, comp);
    *NRpivo = ObtemNumCelOcupadas(pivo);
}

void RetiraMin(TPivo* pivo, TRegistro* R, int *NRpivo, int* comp) {
    RetiraPrimeiro(pivo, R, comp);
    *NRpivo = ObtemNumCelOcupadas(pivo);
}

void Particao(FILE** ArqLi, FILE** ArqEi, FILE** ArqLEs, TPivo pivo, int Esq, int Dir, int*i, int*j, int* transf, int* comp) {
    assert(ArqLi);
    assert(ArqEi);
    assert(ArqLEs);
    int Ls = Dir;
    int Es = Dir;
    int Li = Esq;
    int Ei = Esq;
    int NRpivo = 0;
    int Linf = INT_MIN;
    int Lsup = INT_MAX;
    short OndeLer = true;
    TRegistro UltLido, R;

    fseek(*ArqLi, (Li - 1) * sizeof (TRegistro), SEEK_SET);
    fseek(*ArqEi, (Ei - 1) * sizeof (TRegistro), SEEK_SET);
    *i = Esq - 1;
    *j = Dir + 1;
    while (Ls >= Li) {
        (*comp)++;
        if (NRpivo < TAM - 1) {
            if (OndeLer)
                LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, transf);
            else
                LeInf(ArqLi, &UltLido, &Li, &OndeLer, transf);

            InsereNoPivo(&pivo, &UltLido, &NRpivo, comp);
            continue;
        }
        (*comp)++;
        if (Ls == Es)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, transf);
        else
        (*comp)++;
        if (Li == Ei)
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, transf);
        else
            if (OndeLer)
            LeSup(ArqLEs, &UltLido, &Ls, &OndeLer, transf);
        else
            LeInf(ArqLi, &UltLido, &Li, &OndeLer, transf);
        (*comp)++;
        if (UltLido.nota > Lsup) {
            *j = Es;
            EscreveMax(ArqLEs, UltLido, &Es, transf);
            continue;
        }
        (*comp)++;
        if (UltLido.nota < Linf) {
            *i = Ei;
            EscreveMin(ArqEi, UltLido, &Ei, transf);
            continue;
        }
        InsereNoPivo(&pivo, &UltLido, &NRpivo, comp);
        (*comp)++;
        if (Ei - Esq < Dir - Es) {
            RetiraMin(&pivo, &R, &NRpivo, comp);
            EscreveMin(ArqEi, R, &Ei, transf);
            Linf = R.nota;
        } else {
            RetiraMax(&pivo, &R, &NRpivo, comp);
            EscreveMax(ArqLEs, R, &Es, comp);
            Lsup = R.nota;
        }
    }
    while (Ei <= Es) {
        (*comp)++;
        RetiraMin(&pivo, &R, &NRpivo, comp);
        EscreveMin(ArqEi, R, &Ei, comp);
    }
}

void QuickSortExterno(FILE** ArqLi, FILE** ArqEi, FILE** ArqLEs, int Esq, int Dir, int* transf, int* comp) {
    assert(ArqLi);
    assert(ArqEi);
    assert(ArqLEs);
    int i, j;
    TPivo pivo; /*Área de armazenamento interna*/
    if (Dir - Esq < 1)
        return;
    InicializaPivo(&pivo);
    Particao(ArqLi, ArqEi, ArqLEs, pivo, Esq, Dir, &i, &j, transf, comp);
    if (i - Esq < Dir - j) {
        /*Ordena primeiro o subarquivo menor */
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, transf, comp);
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, transf, comp);
    } else {

        QuickSortExterno(ArqLi, ArqEi, ArqLEs, j, Dir, transf, comp);
        QuickSortExterno(ArqLi, ArqEi, ArqLEs, Esq, i, transf, comp);
    }
}
