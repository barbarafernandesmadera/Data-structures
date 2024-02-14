//Bárbara Fernandes Madera      nUSP: 11915032
//Viktor Sérgio Ferreira        nUSP: 11800570
#ifndef ARQUIVODEDADOS_H_INCLUDED  
#define ARQUIVODEDADOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_REGISTRO 76
#define TAMANHO_CABECALHO 13

// Defina a estrutura de dados para representar um registro
typedef struct {
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
} Cabecalho;

typedef struct{
    int tamanho;
    char* string;
} structVariavel;


typedef struct {
    char removido; 
    int grupo;
    int popularidade;
    int peso;
    structVariavel nomeTecnologiaOrigem;
    structVariavel nomeTecnologiaDestino;
} Registro;


Cabecalho* alocaNovoCabecalho();
Registro* alocaNovoRegistro();
FILE* criarBinario( char *nomeTabela);
void liberaRegistro(Registro *registro);
void registroParaBinario(FILE *arquivo, Registro *registro);
void printaConsiderandoNulo(int campo);
void printaString(char* string, int tamanhoString);
void stringParaBinario(char* string, FILE* arquivo, int tamanho);
void imprimeLinha(Registro* r);


int comparaCampo(Registro *registro, char *nomeCampo, char *valorCampo, int valorCampo2);
char* getfield(char* line, int num);
void cabecalhoParaBinario(FILE* arquivo, Cabecalho* cabecalho);
void linhaParaRegistro(char* tmp, Registro *registroTemp);
void listarRegistros(char *nomeTabela);
void recuperaDadosBuscados(char *arquivoEntrada, char* arquivoEntradaIndice, int n);
int contaRegistros(FILE* binario);
void recuperacaoDoRegistro(FILE* binario, int RRN); 
void binarioParaRegistro(FILE *arquivo, Registro *registro);
int procuraDados(FILE *binario, char *nomeDoCampo, char *valorDoCampo, int valorCampo);

void validarArquivo(FILE* binario);
void abrirArquivo(FILE **arquivo,  char *nomeArquivo,  char *modo);
void fecharArquivo(FILE *arquivo);
Cabecalho lerCabecalhoDados(FILE* arquivoDados, Cabecalho cabecalho);



#endif
