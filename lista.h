//Bárbara Fernandes Madera      nUSP: 11915032
//Viktor Sérgio Ferreira        nUSP: 11800570
#ifndef LISTA_H_INCLUDED   // guardas de cabeçalho, impedem inclusões cíclicas
#define LISTA_H_INCLUDED

#include "todasfuncoes.h"

#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0


typedef Registro Tipo_Dado;

struct elemento{
    struct elemento *ant;
    char dado[128];
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista;

Lista* criaLista();
void liberaLista(Lista* li);
int insereListaFinal(Lista* li, char *dt);
int insereListaInicio(Lista* li, char *dt);
int tamanhoLista(Lista* li);
int listaVazia(Lista* li);
int dadoExisteLista(Lista* li, char* dadoString);
int imprimeLista(Lista* li);

#endif
