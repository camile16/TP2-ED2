#include "box.h"

int main(int argc, char *argv[static argc]) {  
    int metodo, qntdItens, situacao, chave, p = 0;

    //clock_t tempoIni, tempoFim;
    //double tempoDeExecucao;
    //long nTransferenciaPre = 0, nComparacoesPre = 0, nTransferencia = 0, nComparacoes = 0;

    //Verificação da chamada do programa
    if((argc < 4) || (argc > 5)) {
        printf("Formato esperado: ordena <método> <quantidade> <situação> [-P]\n");
        return 0;
    }

    //Transformação de string para inteiro
    metodo = atoi(argv[1]);
    qntdItens = atoi(argv[2]);
    situacao = atoi(argv[3]);

    if(argc == 5) {

        // Trata o caso de último argumento com de 2 caracteres, para evitar erro no tratamento de caracter minúsculo
        if (strlen(argv[4]) < 2) {
            printf("Formato esperado: pesquisa <método> <quantidade> <situação> [-P]\n");
            return 0;
        }

        // Tolera o uso de -p (minúsculo)
        char * argP = argv[4];
        argP[1] = toupper(argP[1]);

        if(!strcmp(argP, "-P")) 
            p = 1;
        else {
            printf("Formato esperado: pesquisa <método> <quantidade> <situação> <chave> [-P]\n");
            return 0;
        }
    }

    //COMECA A CONTAR O TEMPO DE EXECUCAO
    tempoIni = clock();

    //CASO TENHA O [-P] COMO ARGUMENTO
    if(p){
        FILE* arq = fopen("out.bin", "rb");
        if(arq == NULL) {
            printf("Arquivo inexistente!\n");
            return 0;
        }
        printf("\nArquivo completo: \n\n");
        for (int j = 0; j < qntdItens; j++) {

            if(!fread(&item, sizeof(item), 1, arq)) break;
            printf("['%d', '%ld', '%s', '%s']\n", item.key, item.dado_1, item.dado_2, item.dado_3);
        }
        fclose(arq);
    }

    //ESCOLHA DO MÉTODO QUE IRÁ USAR NO PROGRAMA
    switch (metodo) {

        // BUSCA DE ACESSO SEQUENCIAL INDEXADO
        case 1:

            //CASO ARQUIVO ESTEJA DESORDENADO
            if(situacao == 3) {
                printf("Não foi possível, arquivo desordenado!\n");
                return -1;
            }
            sequencial(qntdItens, situacao, chave, &nTransferenciaPre, &nTransferencia, &nComparacoes);
            break;

        //ÁRVORE BINÁRIA DE PESQUISA ADEQUADA À MEMÓRIA EXTERNA
        case 2:

            //DECLARAÇÕES
            binary(&nTransferenciaPre, &nComparacoesPre);
            FILE* arqBinary = fopen("binaryTree.bin", "rb");
            Node node; 

            //VERIFICAÇÃO SE EXISTE O ARQUIVO
            if(arqBinary == NULL){
                printf("O arquivo com a árvore estruturada ainda não foi criado!\n");
                return -1;
            }
            fread(&node, sizeof(node), 1, arqBinary);

            if(binaryResearch(chave, arqBinary, node, &nTransferencia, &nComparacoes) != 1) {
                printf("\nNão há uma chave correspondente no arquivo!\n\n");
            }

            fclose(arqBinary);
            break;

        //ÁRVORE B
        case 3:
            //DECLARAÇÕES
            b(&nTransferenciaPre, &nComparacoesPre);
            FILE* arqBTree = fopen("BTree.bin", "rb");
            if(arqBTree == NULL) {
                printf("O arquivo da árvore B ainda não foi gerado, por favor gere!\n");
                return -1;
            }
            bResearch(arqBTree, chave, &nTransferencia, &nComparacoes);
            fclose(arqBTree);
            break;

        //ÁRVORE B*
        case 4:
            //DECLARAÇÕES
            bstar(&nTransferenciaPre, &nComparacoesPre);
            ArqBstar arqBstar;
            arqBstar.Leaf = fopen("Leaf.bin", "rb");
            if(arqBstar.Leaf == NULL) {
                printf("O arquivo da árvore B* ainda não foi gerado, por favor gere!!\n");
                return -1;
            }

            arqBstar.Internal = fopen("Internal.bin", "rb");
            if(arqBstar.Internal == NULL) {
                printf("Arquivo não foi encontrado!\n");
                return -1;
            }
            bStarResearch(& arqBstar, chave, &nTransferencia, &nComparacoes);
            fclose(arqBstar.Leaf);
            fclose(arqBstar.Internal);
            break;

        default:
            break;
    }

    // CALCULA O TEMPO DE EXECUCAO  
    tempoFim = clock();
    tempoDeExecucao = ((double) (tempoFim - tempoIni)) / CLOCKS_PER_SEC;

    char metString[60];
    switch (metodo)
    {
    case 1:
        strcpy(metString, "Acesso sequencial indexado");
        break;

    case 2:
        strcpy(metString, "Árvore binária de pesquisa adequada à memória externa");
        break;

    case 3:
        strcpy(metString, "Árvore B");
        break;

    case 4:
        strcpy(metString, "Árvore B*");
        break;

    default:
        strcpy(metString, "Erro!");
        break;
    }

    printf("\n\nFim da execução\n\n---------------------------------------\nMetodo utilizado: %s\nTempo de execução: %lf\nTransferência no pré processamento: %ld\nComparações no pré processamento: %ld\nTransferência na pesquisa: %ld\nComparações na pesquisa: %ld\n---------------------------------------\n",metString, tempoDeExecucao, nTransferenciaPre, nComparacoesPre, nTransferencia, nComparacoes);

    return 0;
}

