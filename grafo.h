//Bárbara Fernandes Madera      nUSP: 11915032
//Viktor Sérgio Ferreira        nUSP: 11800570
#ifndef GRAFO_H_INCLUDED   
#define GRAFO_H_INCLUDED

#include "lista.h"

#define infinito 1000

typedef struct {
    char nomeTecnologia[128]; // = '\0';
    int grupo;  // = 0;
    int grauEntrada;
    int grauSaida;
    int grau;
} tipoDado;

typedef struct{
    tipoDado info;
    Lista lista;
} elementoVetor;

typedef elementoVetor* Grafo;


// elementoVetor vetor[cabecalho.nroTec];

int funcionalidade8(char *Dados);
int funcionalidade9(char *Dados);
int funcionalidade10(char *Dados);
int funcionalidade11(char* Dados);
int funcionalidade12(char *Dados);
int inicializaGrafo(Grafo grafo, int TAMANHO_MAX_DO_VETOR);
void RegistroParaGrafo(Registro reg, elementoVetor* grafo);
void imprimeGrafo(Grafo grafo, int TAMANHO_MAX_DO_VETOR);
void liberaGrafo(Grafo grafo, int TAMANHO_MAX_DO_VETOR);
void listarOrigens(elementoVetor* vetor, int nroTecnologias, char* tecnologiaDestino);
int contaVertices(Grafo grafo, Cabecalho cabecalho);
int inserirVertice(Grafo grafo, char* nomeTecnologia);
void RegistroParaGrafoTransposto(Grafo grafo, Registro registro);
int dijkstra(Grafo grafo, int qtdDeVertices, char * origem, char* destino);
int acharIndiceDeVertice(Grafo grafo, int qtdDeVertices, char* vertice);
int kosaraju(Grafo grafo, Grafo grafoTransposto, int qtdDeVertices);
void dfs1(Grafo grafo, int qtdDeVertices, elementoVetor vertice, int* verticeVisitado, char** listaDoDFS1);
void dfs2(Grafo grafo, int qtdDeVertices, char* vertice, int* verticeVisitado, char** listaDoDFS1);
int acharIndiceDeVerticeNaLista(char** listaDoDFS1, int qtdDeVertices, char* vertice);


#endif
