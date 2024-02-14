//Bárbara Fernandes Madera      nUSP: 11915032
//Viktor Sérgio Ferreira        nUSP: 11800570
#ifndef BTREE_H_INCLUDED   // guardas de cabeçalho, impedem inclusões cíclicas
#define BTREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "todasfuncoes.h"

#define NO 0
#define YES 1
#define NIL (-1)

#define TAMANHO_CHAVE_BUSCA 55// Definção o tamanho máximo para os campos e registros
#define TAMANHO_LIXO_CABECALHO 196

#define PREENCHIMENTO '$'// Defina o caractere de preenchimento

//Define dos registros
#define ORDEM 4
#define TAMANHO_CHAVE 55

#define TAMANHO_PAGINA 205




typedef struct {
    char C[TAMANHO_CHAVE+1];
    int PR;
} duplaChaveRRN;


// Definição a estrutura do nó da árvore-B
typedef struct {
    int nroChavesNo;
    int alturaNo;
    int RRNdoNo;
    duplaChaveRRN duplaChaveRRN[3];
    int P[4];
} NoArvoreB;



// Estrutura do Registro de Cabeçalho
typedef struct {
    char status;
    int noRaiz;
    int RRNproxNo;
} B_Cabecalho;



//.h da Árvore B
// search_node(char key, NoArvoreB *p_page, int *pos);
void lerCabecalho(FILE *binarioIndice, duplaChaveRRN *chave);
void criarNoRaiz(FILE *binarioIndice, duplaChaveRRN *chave, B_Cabecalho *cab);
void recuperaDadosComIndiceArvoreB(char *arquivoDados, char *arquivoIndice, int n);
int buscarRRNNoIndice(FILE *binarioIndice, NoArvoreB *indice, char *chaveBusca, int condicaoDeParada, int *RRN, int *pos, int P);
int procuraDados(FILE *binario, char *nomeDoCampo, char *valorDoCampo, int valorCampo);
void drive(char *Dados,char *Arvore);
int inserirChaveNoIndice(FILE *binarioIndice, NoArvoreB *page, NoArvoreB *newpage, int RRN, duplaChaveRRN chave, int *promo_r_child, duplaChaveRRN* promo_key, B_Cabecalho *cabecalho, int pos);
void split(duplaChaveRRN key, int r_child, NoArvoreB *p_oldpage, duplaChaveRRN *promo_key, int *promo_r_child, NoArvoreB *p_newpage, B_Cabecalho *cabecalho);
void ins_in_page(duplaChaveRRN key, int r_child, NoArvoreB *p_page);
void escreverPaginaNoBinarioIndice(NoArvoreB page, FILE *binarioIndice, int RRN);
void lerPaginaNoBinarioIndice(NoArvoreB *page, FILE *binarioIndice, int RRN);
int acharPosicaoDaChaveNaPagina(char *chave, NoArvoreB pagina);
void create_root(FILE* binarioIndice, duplaChaveRRN key, int left, int right);
void pageinit(NoArvoreB *page);
void inserirNoNo(FILE *binarioIndice, NoArvoreB *page, duplaChaveRRN *promo_key, int p_b_rrn);
void printaNo(NoArvoreB page);

//func7
void realizarInsercoes(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroInsercoes);
B_Cabecalho lerCabecalhoArvore(FILE* arquivoIndice, B_Cabecalho cab_B);
void BinarioDadosParaRegistro(FILE* binario, int RRN, Registro *regTemp);
void atualizaNroTecnologiasEPares(FILE* binario);
//funcoesFornecidas

#endif
