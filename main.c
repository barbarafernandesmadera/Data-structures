//Bárbara Fernandes Madera      nUSP: 11915032
//Viktor Sérgio Ferreira        nUSP: 11800570
#include <stdio.h>
#include "todasfuncoes.h"


int main()
{
    int funcionalidade;
    int n, RRN;
    char entrada[50];
    char saida[50];
    Cabecalho novoCabecalho;
    scanf("%d ", &funcionalidade);
    switch(funcionalidade){
        case 1:
            scanf("%s %s", entrada, saida);
            FILE* entradaCsv = abreCsv(entrada); //entrada
            FILE* binario = criarBinario(saida);
            csvParaBinario(entradaCsv, binario);
            fclose(entradaCsv);
            binarioNaTela(saida);
            break;
        case 2:
            scanf("%s", saida);
            listarRegistros(saida);
            break;
        case 3:
            scanf("%s %d",entrada, &n);
            recuperaDadosBuscados(entrada, n);
            break;
        case 4:
            scanf("%s %d", entrada, &RRN);
            FILE* binario1;
            abrirArquivo(&binario1, entrada, "rb");
            recuperacaoDoRegistro(binario1, RRN);
            fclose(binario1);
            break;
        default:
            return -1;
    } 
    return 0;
}