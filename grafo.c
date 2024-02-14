#include "grafo.h"
#include "arquivoDeDados.h"
#include "funcoesFornecidas.h"
#include "lista.h"


int funcionalidade8(char *Dados){
    int qtdRegistros, RRN = 0;
    FILE *binarioDados;
    Registro *registro = alocaNovoRegistro();
    Cabecalho cabDados;
    abrirArquivo(&binarioDados, Dados, "rb");

    
    if(binarioDados == NULL){
        return 0;
    }
    cabDados = lerCabecalhoDados(binarioDados, cabDados);
    //elementoVetor grafo[cabDados.nroTecnologias];

    Grafo grafo = malloc(cabDados.nroTecnologias * sizeof(elementoVetor));
    if (grafo == NULL) {
        // Handle allocation failure
        fprintf(stderr, "Error: Memory allocation failed for grafo.\n");
        exit(1);
    }

    inicializaGrafo(grafo, cabDados.nroTecnologias);


    qtdRegistros =  contaRegistros(binarioDados);

    fseek(binarioDados, TAMANHO_CABECALHO,SEEK_SET);
    while (RRN < qtdRegistros){ 


        binarioParaRegistro(binarioDados, registro);
        fseek(binarioDados, 76 - 21 - (registro->nomeTecnologiaOrigem.tamanho + registro->nomeTecnologiaDestino.tamanho), SEEK_CUR);
        if(registro->removido == '1' || registro->nomeTecnologiaDestino.string[0] =='\0')
        {
            RRN++;
            continue;
        }
        //printf("reg.peso: %d\n", registro->peso);
        RegistroParaGrafo(*registro, grafo);

        RRN++;
    }

    imprimeGrafo(grafo,cabDados.nroTecnologias);
    liberaGrafo(grafo, cabDados.nroTecnologias);
    return 0;
}







int funcionalidade9(char *Dados){
    int qtdRegistros, RRN = 0;
    FILE *binarioDados;
    Cabecalho cabDados;
    Registro *registro = alocaNovoRegistro();
    
    abrirArquivo(&binarioDados, Dados, "rb");

    
    if(binarioDados == NULL){
        return 0;
    }

    cabDados = lerCabecalhoDados(binarioDados, cabDados);
    Grafo grafo = malloc(cabDados.nroTecnologias * sizeof(elementoVetor));
    if (grafo == NULL) {
      // Handle allocation failure
        fprintf(stderr, "Error: Memory allocation failed for grafo.\n");
        exit(1);
    }
     inicializaGrafo(grafo, cabDados.nroTecnologias);
    //elementoVetor grafo[cabDados.nroTecnologias];

    qtdRegistros =  contaRegistros(binarioDados);

    fseek(binarioDados, TAMANHO_CABECALHO,SEEK_SET);
    while (RRN < qtdRegistros){ 


        binarioParaRegistro(binarioDados, registro);
        fseek(binarioDados, 76 - 21 - (registro->nomeTecnologiaOrigem.tamanho + registro->nomeTecnologiaDestino.tamanho), SEEK_CUR); //pular lixo
        if(registro->removido == '1' || registro->nomeTecnologiaDestino.string[0] =='\0')
        {
            RRN++;
            continue;
        }

        RegistroParaGrafoTransposto(grafo, *registro);

        RRN++;
    }

    imprimeGrafo(grafo,cabDados.nroTecnologias);
    liberaGrafo(grafo, cabDados.nroTecnologias);
    return 0;
}



 int funcionalidade10(char *Dados){
    int qtdRegistros, RRN = 0;
    FILE *binarioDados;
    Cabecalho cabDados;
    Registro *registro = alocaNovoRegistro();
    
    abrirArquivo(&binarioDados, Dados, "rb");

    
    if(binarioDados == NULL){
        return 0;
    }

    cabDados = lerCabecalhoDados(binarioDados, cabDados);
    Grafo grafoTranposto = malloc(cabDados.nroTecnologias * sizeof(elementoVetor));
    if (grafoTranposto == NULL) {
      // Handle allocation failure
        printf("Error: Memory allocation failed for grafo.\n");
        return 1;
    }
     inicializaGrafo(grafoTranposto, cabDados.nroTecnologias);
    //elementoVetor grafo[cabDados.nroTecnologias];

    qtdRegistros =  contaRegistros(binarioDados);

    fseek(binarioDados, TAMANHO_CABECALHO,SEEK_SET);

    // criando grafo transposto
    while (RRN < qtdRegistros){ 


        binarioParaRegistro(binarioDados, registro);
        fseek(binarioDados, 76 - 21 - (registro->nomeTecnologiaOrigem.tamanho + registro->nomeTecnologiaDestino.tamanho), SEEK_CUR);
        if(registro->removido == '1' || registro->nomeTecnologiaDestino.string[0] =='\0')
        {
            RRN++;
            continue;
        }

        RegistroParaGrafoTransposto(grafoTranposto, *registro);

        RRN++;
    }


    // agora que o grafo transposto esta montado, iremos para o que a funcionalidade 10 propoe
    int n;
    scanf("%d", &n);
    char destinosAseremBuscados[n][128];
    int qtdDeVertices = contaVertices(grafoTranposto, cabDados);
    for(int i = 0; i < n; i++){
        scan_quote_string(destinosAseremBuscados[i]);
        int j = 0;
        while( strcmp(grafoTranposto[j].info.nomeTecnologia, destinosAseremBuscados[i]) != 0){
            if( (j == qtdDeVertices ) )
            {
                printf("Registro inexistente.");
                
                break;
            }
            if(j == 500){
                break;
            }
            j++;
        }
        if(j != qtdDeVertices){

            printf("%s: ",grafoTranposto[j].info.nomeTecnologia);
            Elem* current = grafoTranposto[j].lista;
            while (current->prox != NULL) {
                printf("%s, ",current->nomeTecnologia);
                current = current->prox;
            }
            printf("%s\n\n", current->nomeTecnologia);
        }
    }


    // liberar o grafo
    liberaGrafo(grafoTranposto, cabDados.nroTecnologias);
    return 0;
 }




int inicializaGrafo(Grafo grafo, int TAMANHO_MAX_DO_VETOR){
    for(int i = 0; i < TAMANHO_MAX_DO_VETOR; i++) {
        grafo[i].info.nomeTecnologia[0] ='\0';
        grafo[i].info.grauEntrada = 0;
        grafo[i].info.grauSaida = 0;
        grafo[i].info.grau = 0;
        grafo[i].info.grupo = 0;
        grafo[i].lista = cria_lista();

    }
    return 0;
}

void RegistroParaGrafo(Registro reg, elementoVetor* grafo){
    
    // elementoVetor atual, proximo;
    int i = 0;
    int j = 0;

  
    
    
    j = inserirVertice(grafo, reg.nomeTecnologiaDestino.string);
    grafo[j].info.grauEntrada++;
    grafo[j].info.grau++;
    
    i = inserirVertice(grafo,reg.nomeTecnologiaOrigem.string);
    if(grafo[i].info.grupo == -1){
        grafo[i].info.grupo = reg.grupo;
    }
    grafo[i].info.grauSaida++;
    grafo[i].info.grau++;

    //     // atualiza os graus
    insere_lista_ordenada(&(grafo[i].lista) , reg);




}

void RegistroParaGrafoTransposto(Grafo grafo, Registro reg){

    structVariavel aux;
    aux = reg.nomeTecnologiaDestino;
    reg.nomeTecnologiaDestino = reg.nomeTecnologiaOrigem;
    reg.nomeTecnologiaOrigem = aux;

    // char* aux = (char*) malloc(128*sizeof(char));
    // strcpy(aux,reg.nomeTecnologiaDestino.string);
    // strcpy(reg.nomeTecnologiaDestino.string,reg.nomeTecnologiaOrigem.string);
    // strcpy(reg.nomeTecnologiaOrigem.string,aux);
    
    // RegistroParaGrafo(reg, grafo);
    int i = 0;
    int j = 0;

  
    
    
    j = inserirVertice(grafo, reg.nomeTecnologiaDestino.string);
    if(grafo[j].info.grupo == -1){
        grafo[j].info.grupo = reg.grupo;
        
    }
    grafo[j].info.grauEntrada++;
    grafo[j].info.grau++;
    
    i = inserirVertice(grafo,reg.nomeTecnologiaOrigem.string);

    grafo[i].info.grauSaida++;
    grafo[i].info.grau++;

    //     // atualiza os graus
    insere_lista_ordenada(&(grafo[i].lista) , reg);



}

// Função para imprimir o grafo conforme especificado das funcionalidade 8 e 9
void imprimeGrafo(Grafo grafo, int TAMANHO_MAX_DO_VETOR) {
    //comentei o if abaixo pq ainda n fiz a funcao confereGrafoExiste
    // if (!confereGrafoExiste(grafo))
    //     return;

    // Percorre cada elemento do vetor
    for (int i = 0; i < TAMANHO_MAX_DO_VETOR && grafo[i].info.nomeTecnologia[0] != '\0' ; i++) {
        Lista aux;
        aux = grafo[i].lista;
        while(aux != NULL){
            printf("%s %d %d %d %d ",grafo[i].info.nomeTecnologia, grafo[i].info.grupo, grafo[i].info.grauEntrada, grafo[i].info.grauSaida, grafo[i].info.grau);
            printf("%s %d\n", aux->nomeTecnologia , aux->peso);
            aux = aux -> prox;
        }
    }
}



void liberaGrafo(Grafo grafo, int TAMANHO_MAX_DO_VETOR) {

    for (int i = 0; i < TAMANHO_MAX_DO_VETOR ; i++) {
        //printf("tecOrigem: %s tecDestino: ", grafo[i].info.nomeTecnologia);
        libera_lista(&(grafo[i].lista));
        //printf("\n");
        
    }
    free(grafo);
}


int inserirVertice(Grafo grafo, char* nomeTecnologia) {
    int i = 0;
    elementoVetor atual, proximo;
    while((strcmp(grafo[i].info.nomeTecnologia, nomeTecnologia) < 0) && (grafo[i].info.nomeTecnologia[0] != '\0')){
        i++;
    }

    if(strcmp(nomeTecnologia, grafo[i].info.nomeTecnologia) == 0){
        return i;

    } else{
        if(grafo[i].info.nomeTecnologia[0] == '\0'){
            strcpy(grafo[i].info.nomeTecnologia, nomeTecnologia);
            grafo[i].info.grupo = -1;
            grafo[i].info.grauSaida = 0;
            grafo[i].info.grauEntrada = 0;
            grafo[i].info.grau = 0;
            grafo[i].lista = NULL;
            return i;

        }else{
            atual = grafo[i];
            atual.lista = grafo[i].lista;
            proximo = grafo[i+1];
            proximo.lista = grafo[i+1].lista;

            strcpy(grafo[i].info.nomeTecnologia, nomeTecnologia);
            grafo[i].info.grupo = -1;
            grafo[i].info.grauSaida = 0;
            grafo[i].info.grauEntrada = 0;
            grafo[i].info.grau = 0;
            grafo[i].lista = NULL;
            int res = i;

            i++;
            while(grafo[i].info.nomeTecnologia[0] != '\0') {
                grafo[i] = atual;
                grafo[i].lista = atual.lista;
                atual = proximo;
                atual.lista = proximo.lista;
                proximo = grafo[i+1];
                proximo.lista = grafo[i+1].lista;
                i++;
            }
            grafo[i] = atual;
            grafo[i].lista = atual.lista;
            return res;
            
        }
    }

}


int funcionalidade11(char* Dados){
    int qtdRegistros, RRN = 0;
    FILE *binarioDados;
    Registro *registro = alocaNovoRegistro();
    Cabecalho cabDados;
    abrirArquivo(&binarioDados, Dados, "rb");

    
    if(binarioDados == NULL){
        return 0;
    }
    cabDados = lerCabecalhoDados(binarioDados, cabDados);
    //elementoVetor grafo[cabDados.nroTecnologias];

    Grafo grafo = malloc(cabDados.nroTecnologias * sizeof(elementoVetor));
    Grafo grafoTransposto = malloc(cabDados.nroTecnologias * sizeof(elementoVetor));
    if (grafo == NULL) {
        // Handle allocation failure
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    inicializaGrafo(grafo, cabDados.nroTecnologias);
    inicializaGrafo(grafoTransposto, cabDados.nroTecnologias);


    qtdRegistros =  contaRegistros(binarioDados);

    fseek(binarioDados, TAMANHO_CABECALHO,SEEK_SET);
    while (RRN < qtdRegistros){ 


        binarioParaRegistro(binarioDados, registro);
        fseek(binarioDados, 76 - 21 - (registro->nomeTecnologiaOrigem.tamanho + registro->nomeTecnologiaDestino.tamanho), SEEK_CUR);
        if(registro->removido == '1' || registro->nomeTecnologiaDestino.string[0] =='\0')
        {
            RRN++;
            continue;
        }
        RegistroParaGrafo(*registro, grafo);
        RegistroParaGrafoTransposto(grafoTransposto, *registro);

        RRN++;
    }

    int qtdDeVertices = contaVertices(grafo, cabDados);
    int qtdComponentes = kosaraju(grafo, grafoTransposto, qtdDeVertices);
    if(qtdComponentes == 1){
        printf("Sim, o grafo é fortemente conexo e possui 1 componente.");
    }else {
        printf("Não, o grafo não é fortemente conexo e possui %d componentes.", qtdComponentes);
    } 

    liberaGrafo(grafo, cabDados.nroTecnologias);
    liberaGrafo(grafoTransposto, cabDados.nroTecnologias);
    return 0;

}

int kosaraju(Grafo grafo, Grafo grafoTransposto, int qtdDeVertices) {
    int verticeVisitado[qtdDeVertices];
    int numeroDeComponentes = 0;
    char** listaDoDFS1 = (char**) malloc(qtdDeVertices * sizeof(char *));

    // Alocação dinâmica de memória para o vetor de strings
    if (listaDoDFS1 == NULL) {
        printf("Erro na alocação de memória.\n");
        return 1;
    }

    // Alocação dinâmica de memória para cada string
    for (int i = 0; i < qtdDeVertices; i++) {
        listaDoDFS1[i] = (char*) malloc(128 * sizeof(char));
        if (listaDoDFS1[i] == NULL) {
            printf("Erro na alocação de memória.\n");
            return 1;
        }
        listaDoDFS1[i][0] = '\0';
    }

    for(int i = 0; i < qtdDeVertices; i++){
        verticeVisitado[i] = FALSO;
    }

    for( int i = 0; i < qtdDeVertices; i++){
        if(verticeVisitado[i] == FALSO){
            dfs1(grafo, qtdDeVertices, grafo[i], verticeVisitado, listaDoDFS1);
        }
    }



    for(int i = 0; i < qtdDeVertices; i++){
        verticeVisitado[i] = FALSO;
    }

    
    for(int i = qtdDeVertices - 1; i >= 0; i--){
        if(verticeVisitado[i] == FALSO){
            dfs2(grafoTransposto, qtdDeVertices, listaDoDFS1[i], verticeVisitado, listaDoDFS1);
    
            numeroDeComponentes++;
        }
    }
    
    for (int i = 0; i < qtdDeVertices; i++) {
        free(listaDoDFS1[i]);
    }
    free(listaDoDFS1);
    return numeroDeComponentes;
}



void dfs1(Grafo grafo, int qtdDeVertices, elementoVetor vertice, int* verticeVisitado, char** listaDoDFS1) {
   
    int idVerticeVisitado = acharIndiceDeVertice(grafo, qtdDeVertices, vertice.info.nomeTecnologia);
    if(verticeVisitado[idVerticeVisitado] == VERDADEIRO) {

        return;
    }

    verticeVisitado[idVerticeVisitado] = VERDADEIRO;

    Elem* vizinho = grafo[idVerticeVisitado].lista;
    //printf("%d || ", qtdDeRelaxados);
    while(vizinho != NULL){
        //printf("%s xxx ", vizinho->nomeTecnologia);
        int idVizinho = acharIndiceDeVertice(grafo, qtdDeVertices, vizinho->nomeTecnologia);
        dfs1(grafo, qtdDeVertices, grafo[idVizinho], verticeVisitado, listaDoDFS1);
        vizinho = vizinho->prox;
    }
    


    
    char aux[128];
    strcpy(aux, listaDoDFS1[0]);
    int j = 0;
    while(aux[0] != '\0'){
        j++;
        strcpy(aux, listaDoDFS1[j]);
    }
    strcpy(listaDoDFS1[j], vertice.info.nomeTecnologia);


    return;
}



void dfs2(Grafo grafoTransposto, int qtdDeVertices, char* vertice, int* verticeVisitado, char** listaDoDFS1) {
    
    
    //posicao na lista:
    int idVerticeVisitado = acharIndiceDeVerticeNaLista(listaDoDFS1, qtdDeVertices, vertice);
    
    
    if(verticeVisitado[idVerticeVisitado] == VERDADEIRO) {
        return;
    }

    verticeVisitado[idVerticeVisitado] = VERDADEIRO;

   // passa o id da lista para o id do grafo
    int idVerticeVisitadoNoGrafo = acharIndiceDeVertice(grafoTransposto, qtdDeVertices, listaDoDFS1[idVerticeVisitado]);
    Elem* vizinho = grafoTransposto[idVerticeVisitadoNoGrafo].lista;
    
    while(vizinho != NULL){
        dfs2(grafoTransposto, qtdDeVertices, vizinho->nomeTecnologia, verticeVisitado, listaDoDFS1);
        vizinho = vizinho->prox;
    }

    return;
}



int contaVertices(Grafo grafo, Cabecalho cabecalho) {
    int countVertice;

    for (countVertice = 0; countVertice < cabecalho.nroTecnologias; countVertice++) {
        // Verifica se o nomeTecnologia do elemento atual é '\0'
        if (grafo[countVertice].info.nomeTecnologia[0] == '\0') {
            break;
        }
    }
    return countVertice;
}

int funcionalidade12(char *Dados){

    FILE *binarioDados;
    Registro *registro = alocaNovoRegistro();
    Cabecalho cabDados;
    abrirArquivo(&binarioDados, Dados, "rb");

    
    if(binarioDados == NULL){
        return 0;
    }
    cabDados = lerCabecalhoDados(binarioDados, cabDados);
    //elementoVetor grafo[cabDados.nroTecnologias];

    Grafo grafo = (Grafo) malloc(cabDados.nroTecnologias * sizeof(elementoVetor));
    if (grafo == NULL) {
        // Handle allocation failure
        fprintf(stderr, "Error: Memory allocation failed for grafo.\n");
        exit(1);
    }

    inicializaGrafo(grafo, cabDados.nroTecnologias);

    int qtdRegistros =  contaRegistros(binarioDados);
    int RRN = 0;

    fseek(binarioDados, TAMANHO_CABECALHO,SEEK_SET);
    while (RRN < qtdRegistros){ 


        binarioParaRegistro(binarioDados, registro);
        fseek(binarioDados, 76 - 21 - (registro->nomeTecnologiaOrigem.tamanho + registro->nomeTecnologiaDestino.tamanho), SEEK_CUR);
        if(registro->removido == '1' || registro->nomeTecnologiaDestino.string[0] =='\0')
        {
            RRN++;
            continue;
        }
        //printf("reg.peso: %d\n", registro->peso);
        RegistroParaGrafo(*registro, grafo);

        RRN++;
    }




    int n;
    scanf("%d", &n);
    char origem[n][128];
    char destino[n][128];
    int qtdVertices = contaVertices(grafo, cabDados);
    for(int i = 0; i < n; i++){
        scan_quote_string(origem[i]);
        scan_quote_string(destino[i]);
        int distancia;

        distancia = dijkstra(grafo, qtdVertices, origem[i], destino[i]);
        if(distancia == infinito){
            printf("%s %s: CAMINHO INEXISTENTE.\n", origem[i], destino[i]);
        } else {
            printf("%s %s: %d\n", origem[i], destino[i], distancia);
        }
    }

    liberaGrafo(grafo, cabDados.nroTecnologias);
    free(registro);
    return 0;
}


int dijkstra(Grafo grafo, int qtdDeVertices, char * origem, char* destino){   
    int distancia[qtdDeVertices], relaxados[qtdDeVertices], qtdDeRelaxados;
    qtdDeRelaxados = 0;
    
    for(int v = 0; v < qtdDeVertices; v++ ) {
        distancia[v] = infinito;
        
        relaxados[v] = FALSO;
    }
    int idOrigem = acharIndiceDeVertice(grafo, qtdDeVertices, origem);
    if(idOrigem == -1){
        return infinito;
    }
    distancia[idOrigem] = 0;
    relaxados[idOrigem] = VERDADEIRO;
    
    int id;
    int idProx;
    id = idOrigem;

    //printf("qtdVertices: %d IdOrigem: %d\n", qtdDeVertices, idOrigem);

    while( qtdDeRelaxados < qtdDeVertices) {
        Elem* atual = grafo[id].lista;
        //printf("%d || ", qtdDeRelaxados);
        while(atual != NULL){
            
            idProx = acharIndiceDeVertice(grafo, qtdDeVertices, atual->nomeTecnologia);
           // printf("%d %d %s ||| ", idProx, id, atual->nomeTecnologia);

            if( (distancia[idProx] > distancia[id] + atual->peso) && relaxados[idProx] == FALSO ){
                distancia[idProx] = distancia[id] + atual->peso;
                //printf(" distancia[%s %d] = %d XXXX", grafo[idProx].info.nomeTecnologia, idProx, distancia[idProx]);
                

            }
            atual = atual->prox;

            // id = indice do que tem a menor distancia
            // 12 binario10.bin 1 ".NET" "ASP.NET" 

        }
        int menor = infinito+1;
        for(int j = 0; j < qtdDeVertices; j++){
            if(distancia[j] < menor && relaxados[j] == FALSO){
                menor = distancia[j];
                id = j;
            }
        }
        relaxados[id] = VERDADEIRO;
        qtdDeRelaxados++;

    }



    int idDestino = acharIndiceDeVertice(grafo, qtdDeVertices, destino);

    //verifica se o id é valido
    if(idDestino == -1) {
        return infinito;
    }
    return distancia[idDestino];
    
}




//modificar para fazer busca binaria
int acharIndiceDeVertice(Grafo grafo, int qtdDeVertices, char* vertice){
    int id;

    for (id = 0; id < qtdDeVertices; id++) {
        if (strcmp(grafo[id].info.nomeTecnologia, vertice) == 0) {
            break;
        }
        
    }
    if(id == qtdDeVertices){
        //printf("nao existe esse vertice no grafo\n");
        // retorna valor invalido para o id
        return -1;
    }
    return id;
}

int acharIndiceDeVerticeNaLista(char** listaDoDFS1, int qtdDeVertices, char* vertice) {
    int id;

    for (id = 0; id < qtdDeVertices; id++) {
        if (strcmp(listaDoDFS1[id], vertice) == 0) {
            break;
        }
        
    }
    if(id == qtdDeVertices){
        printf("n tem esse vertice no grafo\n");
    }
    return id;
}

