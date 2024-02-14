#include <stdio.h>
#include <stdlib.h>

#include "lista.h" //inclui os Protótipos


Lista* criaLista()
{
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void liberaLista(Lista* li)
{
    if (li != NULL)
	{
        Elem* no;
        while ((*li) != NULL)
		{
            no = *li;
            *li = (*li)->prox;
            //free(no->dado);
            free(no);
        }
        free(li);
    }
}

int insereListaFinal(Lista* li, char *dt)
{
    Elem *no;

    if (li == NULL) return ERRO;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)  return ERRO;

    strcpy(no->dado, dt);
    no->prox = NULL;

	if ((*li) == NULL)
	{   //lista vazia: insere início
        no->ant = NULL;
        *li = no;
    }else
	{
        Elem *aux;
        aux = *li;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return OK;
}

int insereListaInicio(Lista* li, char* dt)
{
    if (li == NULL)
        return ERRO;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return ERRO;

    strcpy(no->dado,dt);
    no->prox = (*li);
    no->ant = NULL;

	if (*li != NULL) //lista não vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return OK;
}

int tamanhoLista(Lista* li)
{
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int listaVazia(Lista* li)
{
    if (li == NULL)
        return OK;
    if (*li == NULL)
        return OK;
    return FALSO;
}

int dadoExisteLista(Lista* li, char* dadoString) {
    if (li == NULL || *li == NULL) {
        return FALSO;  // Lista vazia, dado não existe
    }

    Elem* no = *li;

    while (no != NULL) {
       
        if (strcmp(no->dado, dadoString) == 0) {
            return VERDADEIRO;  // Dado encontrado na lista
        }
        
        no = no->prox;
    }

    return FALSO;  // Dado não encontrado na lista
}

int imprimeLista(Lista* li) {
    if (li == NULL || *li == NULL) {
        return FALSO;  // Lista vazia, dado não existe
    }

    Elem* no = *li;

    while (no != NULL) {
       printf("%s\n",no->dado);
        no = no->prox;
    }

    return FALSO;  // Dado não encontrado na lista
}
