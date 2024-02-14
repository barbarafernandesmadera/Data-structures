//Bárbara Fernandes Madera      nUSP: 11915032
//Viktor Sérgio Ferreira        nUSP: 11800570
#ifndef LISTA_H_INCLUDED   
#define LISTA_H_INCLUDED

#include "arquivoDeDados.h"

#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0



struct elemento{    
    char nomeTecnologia[128];
    int peso;
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista;

Lista cria_lista();
void libera_lista(Lista* li);
int insere_lista_ordenada(Lista* li, Registro reg);
int tamanhoLista(Lista* li);
int listaVazia(Lista* li);

#endif
