//funcionalidade 7
#include "Btree.h"
#include "todasfuncoes.h"
#include "lista.h"

void realizarInsercoes(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroInsercoes) {
    Registro *novoRegistro;
    Cabecalho *cabecalho;
    B_Cabecalho cab_B;
    char grupo[50], popularidade[50], peso[50];
    int RRN;
    //abrir arquivos de dados e de indices
    FILE *arquivoDados = fopen(nomeArquivoDados, "rb+");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "rb+");

    cabecalho = (Cabecalho*) malloc(sizeof(Cabecalho));

    //leia os cabecalhos 
    *cabecalho = lerCabecalhoDados(arquivoDados, *cabecalho);
    novoRegistro = alocaNovoRegistro();
    
    
    cab_B = lerCabecalhoArvore(arquivoIndice, cab_B);



    if (arquivoDados == NULL || arquivoIndice == NULL)
    {
        printf("Falha no processamento do arquivo.");
        return;
    }

    RRN=cabecalho->proxRRN;
    for (int i = 0; i < numeroInsercoes; i++) {
        //chegar até o final do arquivo binario
        fseek(arquivoDados, TAMANHO_CABECALHO + TAMANHO_REGISTRO*RRN, SEEK_SET);

        scanf("%s %s %s %s %s\n",
              novoRegistro->nomeTecnologiaOrigem.string,
              grupo,
              popularidade,
              novoRegistro->nomeTecnologiaDestino.string,
              peso);

      

        // Conversão das strings para inteiros usando a função atoi
        if(strcmp(grupo,"NULO") == 0 ){ 
            novoRegistro->grupo = -1;    
        } else {
            novoRegistro->grupo = atoi(grupo);
        } if(strcmp(popularidade,"NULO")==0) {
            novoRegistro->popularidade = -1;

        } else{
            novoRegistro->popularidade = atoi(popularidade);
        } if(strcmp(peso,"NULO") == 0 ) {
            novoRegistro->peso = -1;
        } else {
             novoRegistro->peso = atoi(peso);
        }
        if(strcmp(novoRegistro->nomeTecnologiaOrigem.string,"NULO") == 0){
            novoRegistro->nomeTecnologiaOrigem.string = NULL;
            novoRegistro->nomeTecnologiaOrigem.tamanho = 0;
        }
        if(strcmp(novoRegistro->nomeTecnologiaDestino.string,"NULO") == 0){
            novoRegistro->nomeTecnologiaDestino.string = NULL;
            novoRegistro->nomeTecnologiaDestino.tamanho = 0;
        }
        fseek(arquivoDados, 0, SEEK_END);
        novoRegistro->nomeTecnologiaOrigem.tamanho = strlen(novoRegistro->nomeTecnologiaOrigem.string) - 1; //tirando a virgula da string
        novoRegistro->nomeTecnologiaDestino.tamanho = strlen(novoRegistro->nomeTecnologiaDestino.string) - 1; //tirando a virgula da string
        novoRegistro->nomeTecnologiaDestino.string[novoRegistro->nomeTecnologiaDestino.tamanho] = '\0';
       novoRegistro->nomeTecnologiaOrigem.string[novoRegistro->nomeTecnologiaOrigem.tamanho] = '\0';
    
        registroParaBinario(arquivoDados, novoRegistro); //Inserção uma por uma
        // Insira o novo registro no arquivo de dados
        //inserirRegistroNoArquivoDados(arquivoDados, novoRegistro);
        cabecalho->proxRRN++;
        

        int novaChave;
        //Verifica caso em que nomeTecnologia Origem ou Destino são nulos ou o registro está removido não deve ocorrer inserção na Árvore B
        if (novoRegistro->nomeTecnologiaOrigem.string == NULL || novoRegistro->nomeTecnologiaDestino.string == NULL || novoRegistro->removido == 1) {
            //printf("Falha: Nome de tecnologia Origem ou Destino nulo, ou registro removido.\n");
            RRN++;
            continue; //nao insere na arvore
        } 
        // Insira a nova chave na árvore-B
        //inserirChaveNoIndice(arquivoIndice, novaChave);//precisa da funcionalidade 5
        //  inserirChaveNoIndice(arquivoIndice, page, newpage, &raiz.RRNdoNo, key, &promo_rrn, promo_key, &cabecalho); 
    }
    atualizaNroTecnologiasEPares(arquivoDados);

    free(novoRegistro);
    free(cabecalho);
    fclose(arquivoDados);
    fclose(arquivoIndice);
}   


B_Cabecalho lerCabecalhoArvore(FILE* arquivoIndice, B_Cabecalho cab_B) {

    fseek(arquivoIndice, 0, SEEK_SET);
    fread(&cab_B.status, sizeof(char), 1, arquivoIndice);
    fread(&cab_B.noRaiz, sizeof(int), 1, arquivoIndice);
    fread(&cab_B.RRNproxNo, sizeof(int), 1, arquivoIndice);
    return cab_B;
}

Cabecalho lerCabecalhoDados(FILE* arquivoDados, Cabecalho cabecalho){
    fseek(arquivoDados, 0 , SEEK_SET);
    fread(&cabecalho.status, sizeof(int), 1, arquivoDados);
    fread(&cabecalho.proxRRN, sizeof(int), 1, arquivoDados);
    fread(&cabecalho.nroTecnologias, sizeof(int), 1, arquivoDados);
    fread(&cabecalho.nroParesTecnologias, sizeof(int), 1, arquivoDados);
}





void atualizaNroTecnologiasEPares(FILE* binario) {
    Lista *li1 = criaLista();
    Lista *li2 = criaLista();
    int nroTecnologias = 0;
    int nroParTecnologias = 0;
    Cabecalho *c1 = alocaNovoCabecalho();
    int RRN = 0;
    int qtdRegistros = contaRegistros(binario);
    while (RRN < qtdRegistros)
    {
        int jaTem1, jaTem2, jaTem3;
        char aux[128];
        jaTem1 = 1;
        jaTem2 = 1;
        jaTem3 = 1;

        for(int i = 0; i < 128; i++){
            aux[i] = '$';
        }
        
        Registro* registroTemp;
        registroTemp = alocaNovoRegistro();
        if(registroTemp->removido == 1){
            RRN++;
            continue;
        }

/*esse sscanf equivale a "registro->grupo = getfield(tmp, 2);" , mas sem problema de conversao de tipos */

        BinarioDadosParaRegistro(binario, RRN, registroTemp);
        
        if(strcmp(registroTemp->nomeTecnologiaOrigem.string,"NULO")){
            jaTem1 = dadoExisteLista(li1,registroTemp->nomeTecnologiaOrigem.string);
            if(!jaTem1){
                insereListaInicio(li1, registroTemp->nomeTecnologiaOrigem.string);
            }
            strcpy(aux,registroTemp->nomeTecnologiaOrigem.string);
        }
        if(strcmp(registroTemp->nomeTecnologiaDestino.string,"NULO")){
            jaTem2 = dadoExisteLista(li1, registroTemp->nomeTecnologiaDestino.string);
            if(!jaTem2){
                insereListaInicio(li1, registroTemp->nomeTecnologiaDestino.string);
            }
            strcat(aux,registroTemp->nomeTecnologiaDestino.string);
        }

        jaTem3 = dadoExisteLista(li2, aux);
        if(!jaTem3){
            c1->proxRRN++;
            if(strcmp(registroTemp->nomeTecnologiaDestino.string,"NULO")){
                insereListaInicio(li2, aux);
            }
        }

        free(registroTemp);
        RRN++;
    }  
        c1->nroTecnologias = tamanhoLista(li1);
        c1->nroParesTecnologias = tamanhoLista(li2); 
        liberaLista(li1);
        liberaLista(li2);
        c1->proxRRN--;
        cabecalhoParaBinario(binario, c1);
}


//Função que recupera o registro pelo RRN 
void BinarioDadosParaRegistro(FILE* binario, int RRN, Registro *regTemp) {
    if( RRN >= contaRegistros(binario) || RRN < 0 ){
        printf("Registro inexistente.\n");
        return;
    }
    validarArquivo(binario);
    if(binario == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    
    fseek(binario, TAMANHO_REGISTRO*RRN + TAMANHO_CABECALHO,SEEK_SET);
    binarioParaRegistro(binario,regTemp); 
    
    if(regTemp->removido == '1'){ // esta logicamente removido
        printf("Registro inexistente.\n");
        return;
    }
    /*
    free(regTemp->nomeTecnologiaOrigem.string);
    free(regTemp->nomeTecnologiaDestino.string);
    free(regTemp);*/
}
