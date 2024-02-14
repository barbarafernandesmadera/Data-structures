#include "grafo.h"
#include "arquivoDeDados.h"
#include "funcoesFornecidas.h"



int main()
{
    int funcionalidade;
    //int n; //RRN;
    char entrada[50];
    //char arvoreBinaria[50];
    //char saida[50];
    //Cabecalho novoCabecalho;
    scanf("%d ", &funcionalidade);
    switch(funcionalidade){
        case 1:
            printf("Funcionalidade usada no trabalho passado.");
            break;
        case 2:
            printf("Funcionalidade usada no trabalho passado.");
            break;
        case 3:
            printf("Funcionalidade usada no trabalho passado.");
            break;
        case 4:
            printf("Funcionalidade usada no trabalho passado.");
            break;
        case 5:
            printf("Funcionalidade usada no trabalho passado.");
            //drive(entrada, arvoreBinaria);
             // fazer com que n chame essa função para o caso 4
            //criarIndiceArvoreB(entrada, arvoreBinaria);
            break;
        case 6:
            printf("Funcionalidade usada no trabalho passado.");
            
            //recuperaDadosComIndiceArvoreB(entrada, arvoreBinaria, n);
            break;
        case 7:
            printf("Funcionalidade usada no trabalho passado.");
            //realizarInsercoes(entrada, arvoreBinaria, n);
          
            //binarioNaTela(arvoreBinaria);
            break;
        case 8:
            scanf("%s", entrada);
            funcionalidade8(entrada);
            break;
        case 9:
            scanf("%s", entrada);
            funcionalidade9(entrada);
            break;
        case 10:
            scanf("%s", entrada);
            funcionalidade10(entrada);
            break;
        case 11:
            scanf("%s", entrada);
            funcionalidade11(entrada);
            break;
        case 12:
            scanf("%s", entrada);
            funcionalidade12(entrada);
            break;
        default:
            return -1;
    } 
    return 0;
}
