#ifndef INTERCALAF+1_H
#define INTERCALAF+1_H

#include "box.h"

//Número de fitas de entrada e saída
#define FITAS_ENTRADA 19
#define FITAS_SAIDA 1

#define MAX_MEMORIA 19

void gerar_blocos(const char *nome_arquivo_bin, int qntdItens, long *nTransferencia, long *nComparacoes);

void intercalar_fitas(FILE *fitas_entrada[FITAS_ENTRADA], FILE *fita_saida, long *nTransferencia, long *nComparacoes);

void intercalacao_balanceada_f1(const char *nome_arquivo_bin, int qntdItens, long *nTransferencia, long *nComparacoes);

#endif INTERCALAF+1_H