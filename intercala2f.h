#ifndef INTERCALA2F_H
#define INTERCALA2F_H

#include "box.h"

//Número de fitas de entrada e saída
#define FITAS_ENTRADA 10
#define FITAS_SAIDA 10

#define MAX_MEMORIA 10

void gerar_blocos(const char *nome_arquivo_bin, int qntdItens, long *nTransferencia, long *nComparacoes);

void intercalar_fitas(FILE *fitas_entrada[FITAS_ENTRADA], FILE *fitas_saida[FITAS_SAIDA], long *nTransferencia, long *nComparacoes);

void intercalacao_balanceada_2f(const char *nome_arquivo_bin, int qntdItens, long *nTransferencia, long *nComparacoes);

#endif INTERCALA2F_H