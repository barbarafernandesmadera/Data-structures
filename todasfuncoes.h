//Bárbara Fernandes Madera      nUSP: 11915032
//Viktor Sérgio Ferreira        nUSP: 11800570
#ifndef TODASFUNCOES_H_INCLUDED   // guardas de cabeçalho, impedem inclusões cíclicas
#define TODASFUNCOES_H_INCLUDED

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
FILE* abreCsv(char* arquivoCsv);
FILE* criarBinario(const char *nomeTabela);
void liberaRegistro(Registro *registro);
void registroParaBinario(FILE *arquivo, Registro *registro);
void printaConsiderandoNulo(int campo);
void printaString(char* string, int tamanhoString);
void stringParaBinario(char* string, FILE* arquivo, int tamanho);
void imprimeLinha(Registro* r);
int comparaCampo(Registro *registro, const char *nomeCampo, const char *valorCampo);
void csvParaBinario(FILE* stream, FILE* binario);
char* getfield(char* line, int num);
void cabecalhoParaBinario(FILE* arquivo, Cabecalho* cabecalho);
void linhaParaRegistro(char* tmp, Registro *registroTemp);
void listarRegistros(char *nomeTabela);
void recuperaDadosBuscados(char *arquivoEntrada, int n);
int contaRegistros(FILE* binario);
void recuperacaoDoRegistro(FILE* binario, int RRN); 
void binarioParaRegistro(FILE *arquivo, Registro *registro);
void abrirArquivo(FILE **arquivo, const char *nomeArquivo, const char *modo);
void fecharArquivo(FILE *arquivo);



//funcoesFornecidas
void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);
void scan_quote_string(char *str);


#endif
