#include <stdio.h>
#include <stdlib.h>
#include "lista.h" //inclui os Protótipos
#include "arquivoDeDados.h"

Lista cria_lista() {
    Lista li = (Lista)malloc(sizeof(Elem)); // Allocating memory for struct elemento
    if (li != NULL) {
        li->nomeTecnologia[0] = '\0';
        li->prox = NULL; // Initializing the prox pointer to NULL
        li->peso = 0;    // Or initialize any other members if needed
        // Initialize other members of struct elemento if necessary
    }
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        //free(li);
    }
}

// void libera_lista(Lista* li) {
//     if(li == NULL || *li == NULL ) return;
//     libera_lista(&(*li)->prox);
//     free(*li);
    
// }

// void libera_lista(Lista li) {
//     if (li != NULL) {
//         Elem* current = li;
//         while (current != NULL) {
//             Elem* next = current->prox; // Store the next node reference
//             free(current); // Free the current node
//             current = next; // Move to the next node
//         }
//     }
// }



int insere_lista_ordenada(Lista* li, Registro reg){
    if(li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->peso = reg.peso;
    strcpy(no->nomeTecnologia, reg.nomeTecnologiaDestino.string);
    if((*li) == NULL){//lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else{
        Elem *ant, *atual = *li;
        
        while(atual != NULL && (strcmp(atual->nomeTecnologia, reg.nomeTecnologiaDestino.string) < 0) ){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == *li){//insere início
            no->prox = (*li);
            *li = no;
        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}







int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}


//imprime De acordo com a funcionalidade 8 e a 9


// imprimir de acordo com a funcionalidade 10

