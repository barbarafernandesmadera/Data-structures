#include "Btree.h"
#include "todasfuncoes.h"


void lerCabecalho(FILE *binarioIndice, duplaChaveRRN *chave) {
    B_Cabecalho cab;
    fseek(binarioIndice, 0, SEEK_SET);
    //fread(&cab, sizeof(CabecalhoArvoreB), 1, binarioIndice);
    fread(&cab.status, 1, 1, binarioIndice);
    fread(&cab.noRaiz, sizeof(int), 1, binarioIndice);
    fread(&cab.RRNproxNo, sizeof(int), 1, binarioIndice);
     
    if (cab.noRaiz == -1) {
        // Não há raiz, então crie o nó raiz
        criarNoRaiz(binarioIndice, chave, &cab);
    } else {
        // Há uma raiz, apenas insira a chave
        //inserirChaveNoIndice(binarioIndice, chave);
    }
}



void criarNoRaiz(FILE *binarioIndice, duplaChaveRRN *chave, B_Cabecalho *cab) {
    NoArvoreB raiz;
    raiz.nroChavesNo = 1;
    raiz.alturaNo = 1;
    raiz.RRNdoNo = 0;
    raiz.duplaChaveRRN[0] = *chave;

    // Atualizar o cabeçalho
    cab->noRaiz = 0;
    cab->RRNproxNo = 1;
    cab->status = '1'; // Indicar que a árvore foi modificada
    char lixo = '$';
    int menosUm = -1;
    // Escrever o cabeçalho e a raiz no arquivo
    fseek(binarioIndice, 0, SEEK_SET);
    // fwrite(cab, sizeof(B_Cabecalho), 1, binarioIndice);
    fwrite(&cab->status, sizeof(char), 1, binarioIndice);
    fwrite(&cab->noRaiz, sizeof(int), 1, binarioIndice);
    fwrite(&cab->RRNproxNo, sizeof(int), 1, binarioIndice);
    fwrite(&lixo, TAMANHO_LIXO_CABECALHO, 1, binarioIndice);
    

    fseek(binarioIndice, TAMANHO_PAGINA, SEEK_SET);
    // fwrite(&raiz, sizeof(NoArvoreB), 1, binarioIndice);
    fwrite(&raiz.nroChavesNo, sizeof(int), 1, binarioIndice);
    fwrite(&raiz.alturaNo, sizeof(int), 1, binarioIndice);
    fwrite(&raiz.RRNdoNo, sizeof(int), 1, binarioIndice);
    fwrite(&menosUm, sizeof(int), 1, binarioIndice);
    fwrite(&raiz.duplaChaveRRN[0].C, TAMANHO_CHAVE, 1, binarioIndice);
    fwrite(&raiz.duplaChaveRRN[0].PR, sizeof(int), 1, binarioIndice);

}

/*
NoArvoreB* criarNo() {
    NoArvoreB* novoNo = (NoArvoreB*)malloc(sizeof(NoArvoreB));

    // Inicializar os campos do novo nó conforme necessário
    novoNo->nroChavesNo = 0;
    novoNo->alturaNo = 0;
    novoNo->RRNdoNo = -1; 
    novoNo->P[3] = -1;
    // Inicializar os elementos do nó
    for (int i = 0; i < 3; i++) {
        novoNo->P[i] = -1; 
        novoNo->duplaChaveRRN->C[0] = '\0';
        novoNo->duplaChaveRRN[i].PR = -1; 
    }

    // Inicializar os filhos do nó
    for (int i = 0; i < 4; i++) {
        novoNo->P[i] = -1;
    }

    return novoNo;
}
*/

/*
 void inserirNo(NoArvoreB *no, duplaChaveRRN *chave) {
    int posicaoInsercao;

    // Utiliza a busca binária para encontrar a posição correta de inserção
    recuperaDadosComIndiceArvoreB(no, chave, &posicaoInsercao);

    // Move os elementos e filhos para abrir espaço para a nova chave
    for (int i = no->nroChavesNo - 1; i >= posicaoInsercao; i--) {
        no->duplaChaveRRN[i + 1] = no->duplaChaveRRN[i];
        no->P[i + 2] = no->P[i + 1];
    }

    // Insere a nova chave na posição correta
    no->duplaChaveRRN[posicaoInsercao] = *chave;
    no->P[posicaoInsercao + 2] = -1;  // Inicializa o filho à direita como -1
    no->nroChavesNo++;
}

void escreveNoRaiz(FILE *binarioIndice, NoArvoreB *raiz, B_Cabecalho *cabecalho) {
    // Se o nó raiz não existe, não há nada a ser escrito
    if (raiz == NULL) {
        return;
    }

    // Atualizar o cabeçalho da árvore-B com o RRN do novo nó raiz
    cabecalho->noRaiz = raiz->RRNdoNo;

    // Escrever o nó raiz no arquivo de índice
    fseek(binarioIndice, raiz->RRNdoNo * sizeof(NoArvoreB), SEEK_SET);
    fwrite(raiz, sizeof(NoArvoreB), 1, binarioIndice);

    // Atualizar o cabeçalho no arquivo de índice
    fseek(binarioIndice, 0, SEEK_SET);
    fwrite(cabecalho, sizeof(B_Cabecalho), 1, binarioIndice);
}
*/

/*
void inserirChaveNoIndice(FILE* binarioIndice ,B_Cabecalho cab) {
    int rrnDoNoRaiz = cab->rrnNoRaiz;
    duplaChaveRRN chave;
    // Assumindo que 'filho_direita' seja uma variável que será atualizada na função de inserção
    int filhoDireita;

    inserirChaveNoIndice(binarioIndice, cab, rrnDoNoRaiz, &chave, &filhoDireita);

    NoArvoreB raiz;
    // Supondo que 'criar_no()' crie um novo nó da árvore-B
    raiz = criarNo();
    raiz.nroChavesNo = 1;
    raiz.alturaNo = 1;
    raiz.RRNdoNo = cab->noraiz;
    raiz.duplaChaveRRN[0] = chave;
    raiz.P[0] = cab->noraiz;
    raiz.P[1] = filhoDireita;


    // Preencher dados do raiz (implemente essa lógica conforme a estrutura do seu código)
    // Supondo que 'escreveNoRaiz()' escreva os dados da raiz no arquivo binário
    escreveNoRaiz(binarioIndice, &raiz);
}


*/
/*
void dividirNo(FILE *binarioIndice, B_Cabecalho *cabecalho, int RRNdoNo, int posicaoInsercao, duplaChaveRRN *chave, int *posicaoPromocao, duplaChaveRRN *chavePromovida) {
    NoArvoreB no;

    NoArvoreB novoNo;
    novoNo.nroChavesNo = 0;
    novoNo.alturaNo = no.alturaNo;
    novoNo.RRNdoNo = cabecalho->RRNproxNo++;

    int posicaoDivisao = ORDEM - 1;

    // Copia a segunda metade das chaves e filhos para o novo nó
    for (int i = posicaoDivisao + 1; i < 2 * ORDEM - 1; i++) {
        novoNo.elemento[novoNo.nroChavesNo] = no.elemento[i];
        novoNo.filhos[novoNo.nroChavesNo] = no.filhos[i];
        no.elemento[i] = inicializaElemento();  // Limpa a segunda metade do nó original
        no.filhos[i] = -1;
        novoNo.nroChavesNo++;
        no.nroChavesNo--;
    }
    novoNo.filhos[novoNo.nroChavesNo] = no.filhos[2 * ORDEM - 1];
    no.filhos[2 * ORDEM - 1] = -1;

    // Insere a chave na posição correta
    if (posicaoInsercao <= posicaoDivisao) {
        inserirNo(&no, chave);
    } else {
        inserirNo(&novoNo, chave);
    }

    // Atualiza os nós modificados no arquivo
    fseek(binarioIndice, RRNdoNo * sizeof(NoArvoreB), SEEK_SET);
    fwrite(&no, sizeof(NoArvoreB), 1, binarioIndice);

    fseek(binarioIndice, novoNo.RRNdoNo * sizeof(NoArvoreB), SEEK_SET);
    fwrite(&novoNo, sizeof(NoArvoreB), 1, binarioIndice);

    // Promove a chave para o pai
    *chavePromovida = no.elemento[posicaoDivisao];
    *RRNpromovido = novoNo.RRNdoNo;
    no.elemento[posicaoDivisao] = inicializaElemento();  // Limpa a posição da chave promovida
    // no.filhos[posicaoDivisao + 1] = novoNo.RRNdoNo;

    // Atualiza o nó modificado no arquivo
    fseek(binarioIndice, RRNdoNo * sizeof(NoArvoreB), SEEK_SET);
    fwrite(&no, sizeof(NoArvoreB), 1, binarioIndice);

    *posicaoPromocao = posicaoDivisao;

    // Se a raiz foi dividida, cria uma nova raiz
    if (RRNdoNo == cabecalho->noRaiz) {
        criarNovaRaiz(binarioIndice, cabecalho, *chavePromovida, RRNdoNo, novoNo.RRNdoNo);
    }
}
*/

/*
void criarIndiceArvoreB(char *arquivoDados, char *arquivoIndice) { //funcionalidade5

    FILE *binarioDados;
    abrirArquivo(&binarioDados, arquivoDados, "rb");
    if(binarioDados == NULL){
        return;
    }

    FILE *binarioIndice;
    abrirArquivo(&binarioIndice, arquivoIndice, "wb");
    if(binarioDados == NULL){
        return;
    }

    Registro registro;
    B_Cabecalho cabecalho;
    int promoted = 0;

    // Lê o cabeçalho da árvore-B
    //fseek(binarioIndice, 0, SEEK_SET);
    //fread(&cabecalho, sizeof(CabecalhoArvoreB), 1, binarioIndice);
    fread(&cabecalho.status, sizeof(char),1, binarioIndice);
    fread(&cabecalho.noRaiz, sizeof(int), 1, binarioIndice);
    fread(&cabecalho.RRNproxNo, sizeof(int), 1, binarioIndice);
    int qtdRegistros = contaRegistros(binarioDados);
    int RRNx = 0;
    while (RRNx < qtdRegistros) {
        //fread(&registro, sizeof(RegistroDados), 1, binarioDados) == 1
        
        binarioParaRegistro(binarioDados, &registro);
        if (registro.removido != '1') {
            // int RRN = ftell(binarioDados) / sizeof(RegistroDados) - 1; // esse RRN n tem nada a ver
            
            // Concatena as strings de chaves
            char chaveBusca[TAMANHO_CHAVE_BUSCA];
            strcpy(chaveBusca, registro.nomeTecnologiaOrigem.string);
            strcat(chaveBusca, registro.nomeTecnologiaDestino.string);

            // Insere a chave no índice da árvore-B
            promoted = inserirChaveNoIndice(binarioIndice, chaveBusca, &cabecalho);
            if(promoted){
                root = create_root(promo_key, root, promo_rrn);
            }
        }
        RRNx++;
    }

    // Atualiza o cabeçalho da árvore-B após a criação do índice
    fseek(binarioIndice, 0, SEEK_SET);
    //fwrite(&cabecalho, sizeof(CabecalhoArvoreB), 1, binarioIndice);
}
*/




/*
void inserirChaveNoIndiceRecursivo(FILE *binarioIndice, B_Cabecalho *cabecalho, int RRNdoNo, elemento *chave, int *filho_direita) {
    NoArvoreB no;
    fseek(binarioIndice, RRNdoNo * TAMANHO_NO, SEEK_SET);
    fread(&no, sizeof(NoArvoreB), 1, binarioIndice);

    int posicaoInsercao;

    // Utiliza a busca binária para encontrar a posição correta de inserção
    if (buscaBinaria(&no, chave, &posicaoInsercao)) {
        // Chave já existe, não precisa inserir
        return;
    }

    // Se o nó está cheio, faça a divisão e promova a chave
    if (no.nroChavesNo == (2 * ORDEM - 1)) {
        // Faça a divisão e promova a chave
        int posicaoPromocao;
        elemento chavePromovida;
        dividirNo(binarioIndice, cabecalho, RRNdoNo, posicaoInsercao, chave, &posicaoPromocao, &chavePromovida);

        // Se a divisão resultou em uma promoção, ajuste o nó atual
        if (posicaoPromocao == -1) {
            posicaoPromocao = posicaoInsercao;
            no.elemento[posicaoInsercao] = chavePromovida;
            no.nroChavesNo++;
        }
    } else {
        // Inserir a chave na posição correta
        for (int i = no.nroChavesNo; i > posicaoInsercao; i--) {
            no.elemento[i] = no.elemento[i - 1];
        }
        no.elemento[posicaoInsercao] = *chave;
        no.nroChavesNo++;
    }

    fseek(binarioIndice, RRNdoNo * sizeof(NoArvoreB), SEEK_SET);
    fwrite(&no, sizeof(NoArvoreB), 1, binarioIndice);
}

*/

int STACKFRAME;

void recuperaDadosComIndiceArvoreB(char *arquivoDados, char *arquivoIndice, int n) { 
    //funcionalidade6
    FILE *binarioDados = NULL; 
    FILE *binarioIndice = NULL;

    abrirArquivo(&binarioDados, arquivoDados, "rb");
    abrirArquivo(&binarioIndice, arquivoIndice, "rb");

    // Verificar o status do arquivo de dados
    B_Cabecalho *cabecalho;
    cabecalho = (B_Cabecalho*) malloc(sizeof(B_Cabecalho));
    fread(&(cabecalho->status), sizeof(char), 1, binarioIndice);

    if (cabecalho->status == '0') {
        printf("Falha no processamento do arquivo.");
        fecharArquivo(binarioDados);
        fecharArquivo(binarioIndice);
        free(cabecalho);
        return;
    }

    fread(&cabecalho->noRaiz, sizeof(int), 1, binarioIndice);
    NoArvoreB page;

    char campos[n][50], valores[n][50];
    int valorCampo[n];
    int pos;
    int novoN = n; // serve para intercalar esta funcao e a da funcionalidade 3
    // Iterar sobre os campos de busca
    for (int i = 0; i < n; i++) {
        scanf("%s", campos[i]);
        if(!strcmp(campos[i], "popularidade") || !strcmp(campos[i], "grupo") || !strcmp(campos[i], "peso") ){
            scanf("%d", &valorCampo[i]);
        } else{
            scan_quote_string(valores[i]);
        }
        // Verificar se o campo de busca é a chave de busca
        if ((strcmp(campos[i], "nomeTecnologiaOrigemDestino") == 0)) {
            // Utilizar o índice árvore B para encontrar os RRNs correspondentes
            //fseek(binarioIndice, TAMANHO_PAGINA, SEEK_SET);
            //printf("valores: %s\n", valores[i]);
            //fseek(binarioIndice,(cabecalho->noRaiz + 1)*TAMANHO_PAGINA, SEEK_SET);
            int RRN = cabecalho->noRaiz;
            buscarRRNNoIndice(binarioIndice, &page, valores[i], 0, &RRN, &pos, cabecalho->noRaiz);
            if (RRN != NIL) {
                // Recuperar o registro no arquivo de dados usando o RRN
                recuperacaoDoRegistro(binarioDados, RRN); //recuperacaoDoRegistro(binario1, RRN);
                
            } else {
                printf("Registro inexistente.\n");
            }
            novoN--;
        } else {
            // Caso não seja a chave de busca, percorrer o arquivo de dados normalmente
            //recuperaDadosBuscaNormal(binarioDados, campos[i], valores[i]);
            //recuperaDadosBuscados(arquivoDados, arquivoIndice, novoN);
            procuraDados(binarioDados,campos[i],valores[i], valorCampo[i]);
            //void recuperaDadosBuscados(char *arquivoEntrada, int n) 

        }
    }
    if(cabecalho != NULL){
        free(cabecalho);
        cabecalho = NULL;
    }
    fecharArquivo(binarioDados);
    fecharArquivo(binarioIndice);
}



int buscarRRNNoIndice(FILE *binarioIndice, NoArvoreB *indice, char *chaveBusca, int condicaoDeParada, int *RRN, int *pos, int P) {
    if(condicaoDeParada != 0){
        return condicaoDeParada;
    }
    *RRN = -1;
    lerPaginaNoBinarioIndice(indice, binarioIndice, P);
    
    while (condicaoDeParada == 0) {
        int i = 0;
        
        // Percorre as chaves do nó
        i = acharPosicaoDaChaveNaPagina(chaveBusca, *indice);
        *pos = i;
        

        // Se a chave foi encontrada
        ///printf("indiceChave:%s\n", indice.duplaChaveRRN[i].C);
        if (i < indice->nroChavesNo && strcmp(chaveBusca, indice->duplaChaveRRN[i].C) == 0) {
            *RRN = indice->duplaChaveRRN[i].PR;
            condicaoDeParada = 24; // valor diferente de 0 e -1
            
            //return indice.duplaChaveRRN[i].PR; // Retorna o RRN correspondente
        } else {
            // Desce para o próximo nível
            if(indice->alturaNo == 1){
                condicaoDeParada = 24; // valor diferente de 0 e -1
            } else{
                //fseek(binarioIndice, (indice->P[i]+1)*TAMANHO_PAGINA, SEEK_SET); // passar como parametro da função o indiceP e colocar o fseek no começo
                condicaoDeParada = buscarRRNNoIndice(binarioIndice, indice, chaveBusca, condicaoDeParada, RRN, pos, indice->P[i]);
                if(condicaoDeParada != 0){
                    return condicaoDeParada;
                }
            }
        }
    }

    if(condicaoDeParada != 0){
        return condicaoDeParada;
    }
    return NIL; // Chave não encontrada
}


//funcionalidade 5
// ver onde que precisa desalocar memoria
void drive(char *Dados,char *Arvore){
    STACKFRAME = 0;
    int found, pos;
    int x = -1;

    int qtdRegistros, RRN = 0; //esse RRN eh o do binario de dados
    int promoted = -1; // flag para ver se uma chave foi promovida
    int promo_rrn; // RRN do No promovido do binario de indice ??
    duplaChaveRRN *promo_key; // chave promovida
    NoArvoreB raiz;
    NoArvoreB *newpage;
    //page = (NoArvoreB*) malloc(sizeof(NoArvoreB));
    B_Cabecalho cabecalho;
    FILE *binarioDados;
    FILE *binarioIndice;
    abrirArquivo(&binarioDados, Dados, "rb");
    abrirArquivo(&binarioIndice, Arvore, "wb+");

    if(binarioDados == NULL || binarioIndice == NULL){
        return;
    }

    newpage = (NoArvoreB*) malloc(sizeof(NoArvoreB));
    promo_key =(duplaChaveRRN*) malloc(sizeof(duplaChaveRRN));
    

    //chave == tecOrigemDestino junto
    //inicializar cabecalho no arquivoIndice

    cabecalho.status = '0';
    cabecalho.noRaiz = -1;
    cabecalho.RRNproxNo = 0;
    char lixo[TAMANHO_LIXO_CABECALHO];
    for(int j = 0; j < TAMANHO_LIXO_CABECALHO; j++){
        lixo[j] = '$';
    }
    fwrite(&cabecalho.status, sizeof(char), 1, binarioIndice);
    fwrite(&cabecalho.noRaiz, sizeof(int), 1, binarioIndice);
    fwrite(&cabecalho.RRNproxNo, sizeof(int), 1, binarioIndice);
    fwrite(lixo, TAMANHO_LIXO_CABECALHO*sizeof(char), 1, binarioIndice);

    qtdRegistros =  contaRegistros(binarioDados);

    Registro *registro = alocaNovoRegistro();
    duplaChaveRRN key;    

    fseek(binarioDados, TAMANHO_CABECALHO,SEEK_SET);
    while (RRN < qtdRegistros){ 
        STACKFRAME = 0;

        //funcao inicializa raiz 
        if(cabecalho.noRaiz == -1){
            raiz.alturaNo = 1;
            raiz.nroChavesNo = 0;
            raiz.RRNdoNo = 0;
            for(int i = 0; i < ORDEM -1; i++){
                raiz.duplaChaveRRN[i].C[0] = '\0';
                raiz.duplaChaveRRN[i].PR = -1;
                raiz.P[i] = -1;
            }
            raiz.P[3] = -1;
            cabecalho.noRaiz++;
            //funcao escreve no indice
            escreverPaginaNoBinarioIndice(raiz, binarioIndice,cabecalho.noRaiz);
            //fseek(binarioIndice, - TAMANHO_PAGINA, SEEK_CUR);
            cabecalho.noRaiz = 0;
            cabecalho.RRNproxNo = 1;
        }

        //fread(&page, TAMANHO_PAGINA, 1, binarioIndice);
        binarioParaRegistro(binarioDados, registro);
        fseek(binarioDados, 76 - 21 - (registro->nomeTecnologiaOrigem.tamanho + registro->nomeTecnologiaDestino.tamanho), SEEK_CUR);
        if(registro->removido == '1')
        {
            RRN++;
            continue;
        }

        registro->nomeTecnologiaOrigem.string[registro->nomeTecnologiaOrigem.tamanho] = '\0';
        registro->nomeTecnologiaDestino.string[registro->nomeTecnologiaDestino.tamanho] = '\0';
        
        
        strcpy(key.C, registro->nomeTecnologiaOrigem.string);
        strcat(key.C,registro->nomeTecnologiaDestino.string);
         printf("chave a ser inserida: %s \n", key.C);
        key.PR = RRN;
        printf("no raiz :8 -> %d\n", raiz.RRNdoNo);


        // NAO ESQUECER DE TROCAR ESSE Y
        int y = cabecalho.noRaiz;
        NoArvoreB pp;
        lerPaginaNoBinarioIndice(&pp, binarioIndice, y);
        lerPaginaNoBinarioIndice(&raiz, binarioIndice, y);
            
            //found = buscarRRNNoIndice(binarioIndice, &raiz , key.C, 0, &x, &pos, cabecalho.noRaiz);
            //printf("MCposi %d\n", pos);
        printaNo(raiz);
        promoted = inserirChaveNoIndice(binarioIndice, &raiz, newpage, raiz.RRNdoNo, key, &promo_rrn, promo_key, &cabecalho, pos);
        //printf("promotedraiz: %d", promoted); //YES = 1;
        

        if(promoted == (YES) ){
            printf("__________________A__________________\n");
            lerPaginaNoBinarioIndice(&raiz, binarioIndice, cabecalho.noRaiz);
            printaNo(raiz);

/*
            if(raiz.nroChavesNo < ORDEM - 1 ){

                printf("_________________________________________________________________________\n");
                printaNo(raiz);
                inserirNoNo(binarioIndice, &raiz, promo_key, promo_rrn);

            }
        else{*/

            printf("promokey %s\n", promo_key->C);
            
            //create_root(binarioIndeice, raiz.)
            /*
            // root = create_root(promokey, root, promo_rrn);
            fseek(binarioIndice,0, SEEK_END);
            fwrite(1,sizeof(int), 1, binarioIndice);
            fwrite(raiz->alturaNo + 1, sizeof(int), 1, binarioIndice);
            fwrite(cabecalho.RRNproxNo + 1, sizeof(int), 1, binarioIndice);
            // escrever a nova raiz no final do binarioIndice
            */


           strcpy(raiz.duplaChaveRRN[0].C,promo_key->C);
           raiz.duplaChaveRRN[1].C[0] = '\0';
           raiz.duplaChaveRRN[2].C[0] = '\0';
           raiz.duplaChaveRRN[1].PR = -1;
           raiz.duplaChaveRRN[2].PR = -1;
           raiz.duplaChaveRRN[0].PR = promo_key->PR;
           raiz.P[0] = cabecalho.noRaiz;
           raiz.P[1] = promo_rrn;
           raiz.nroChavesNo = 1;
           raiz.alturaNo = raiz.alturaNo + 1;
           raiz.RRNdoNo = cabecalho.RRNproxNo;
           //fseek pro final do arquivo de indice
           //fwrite do aux2
           //atualizar cabecalho
           //fseek começo do arquvio
           //fwrite do cabecalho
            fseek(binarioIndice, 0 , SEEK_END);
            escreverPaginaNoBinarioIndice(raiz, binarioIndice, raiz.RRNdoNo);
            cabecalho.noRaiz = raiz.RRNdoNo;
            cabecalho.RRNproxNo++;
            cabecalho.status = '0';
      //  }
 
        }
        printf("cabecalho NO raiz: %d cabecalho prox rrn: %d\n", cabecalho.noRaiz, cabecalho.RRNproxNo);
        RRN++;

    binarioNaTela(Arvore);
    }

    //criar funcao atualizaCabecalhoDoBinarioIndice
    cabecalho.status = '1';
    fseek(binarioIndice, 0, SEEK_SET);
    fwrite(&cabecalho.status, sizeof(char), 1, binarioIndice);
    fwrite(&cabecalho.noRaiz, sizeof(int), 1, binarioIndice);
    fwrite(&cabecalho.RRNproxNo, sizeof(int), 1, binarioIndice);
    
    free(newpage);
    free(registro->nomeTecnologiaOrigem.string);
    free(registro->nomeTecnologiaDestino.string);
    free(registro);
    free(promo_key);
    fclose(binarioDados);
    fclose(binarioIndice);
    
}

//esse RRN eh do binario indice
int inserirChaveNoIndice(FILE *binarioIndice, NoArvoreB *page, NoArvoreB *newpage, int RRN, duplaChaveRRN chave, int *promo_r_child, duplaChaveRRN* promo_key, B_Cabecalho *cabecalho, int pos2) {
    printf("STACKFRAME: %d - %d <- no atual\n", STACKFRAME++, page -> RRNdoNo);
    int pos;
    //NoArvoreB page2 = *page;
    int found, promoted = -1;  // duas flags
    int p_b_rrn;   // pos eh a posicao onde a chave deveria estar no binarioIndice
    // duplaChaveRRN p_b_key; // eh a chave promovida do no abaixo
    //printf("promo_key no comeco da funcao: %s, promo_r_child no comeco da funcao: %d\n", promo_key->C, *promo_r_child);
    

    if(RRN == NIL) {
        *promo_key = chave;
        *promo_r_child = NIL;
        return (YES);
    }
    //nova função para ler 
    // fseek(binarioIndice, (1 + *RRN)*TAMANHO_PAGINA, SEEK_SET);
    lerPaginaNoBinarioIndice(page, binarioIndice, RRN);
    printf("RRN: %d \n Pagina dps de ner no binarioIndice:\n", RRN);
    printaNo(*page);

    int x = -1; // TROCAR DPS, N ESQUECER!

    // fseek(binarioIndice, (cabecalho->RRNproxNo + 1)*TAMANHO_PAGINA , SEEK_SET);
                             // retorna -1 se nao encontrada e chave.C se encontrada
    // encotnrar pos = posicao onde a chave deveria estar dentro do no
    //pos = acharPosicaoDaChaveNaPagina(chave.C, );

        //oqq eh esse x??
        //found = buscarRRNNoIndice(binarioIndice, page , chave.C, 0, &x, &pos, cabecalho->noRaiz); 
        pos = acharPosicaoDaChaveNaPagina(chave.C, *page);

    printf("found: %d; pos: %d; x: \n", found, pos);
    printaNo(*page);

   /* if( == -1){
        printf("Erro: ja existe a chave que ta tentando inserir.");
        return 0;
    }*/

    // cabecalho->RRNproxNo++;
    //arrumar linha de baixo:

    
    promoted = inserirChaveNoIndice(binarioIndice, page, newpage, page->P[pos], chave, &p_b_rrn, promo_key, cabecalho, pos2);
    //quem é o pos neste caso?
     

    //lerPaginaNoBinarioIndice(page, binarioIndice, RRN);
    printf("RRN aqui :3 -> %d - %d <- promoted aqui B)\n", page->RRNdoNo, promoted);

    if(promoted == NO){
        return NO; // sem promocao
    }

    if(page->nroChavesNo < ORDEM -1)
    {
        printf("esse é o nó %d\n", page->RRNdoNo);
        // printf("preenchimento do no \n");
        // printf("promo_key: %s \n", promo_key->C);
        inserirNoNo(binarioIndice, page, promo_key ,p_b_rrn);
        
        return NO;
    }else {
        //split
        printf("esse é o nó %d e estou dando split\n", page->RRNdoNo);
        printaNo(*page);

        // for(int y = 0; y < ORDEM -1 ; y++) { 
        //     printf("page antes do split: %s", page->duplaChaveRRN[y].C);
        // }
        printf("\n");
        split(chave, p_b_rrn, page, promo_key, promo_r_child, newpage, cabecalho);
        printaNo(*page);
        
        escreverPaginaNoBinarioIndice(*page, binarioIndice, page->RRNdoNo);

        printaNo(*newpage);
        escreverPaginaNoBinarioIndice(*newpage, binarioIndice,newpage->RRNdoNo);
        
        return YES; // teve promocao
    }



}

void split(duplaChaveRRN key, int r_child, NoArvoreB *p_oldpage, duplaChaveRRN *promo_key, int *promo_r_child, NoArvoreB *p_newpage, B_Cabecalho *cabecalho) {
    int i;
    int mid;
    char workkeys[ORDEM][TAMANHO_CHAVE]; //C
    int  workkeysRRN[ORDEM]; //PR
    int workch[ORDEM+1];    //P

// acreditamos que o primeiro for ta certo
    for(i = 0; i < ORDEM-1; i++){
        strcpy(workkeys[i], p_oldpage->duplaChaveRRN[i].C); 
        workkeysRRN[i] = p_oldpage->duplaChaveRRN[i].PR;
        workch[i] = p_oldpage->P[i];

    }
    workch[i] = p_oldpage->P[i];


    for(i = ORDEM-1; strcmp(key.C, workkeys[i-1]) < 0 && i > 0; i--) { // insere nova chave
        strcpy(workkeys[i], workkeys[i-1]);
        workkeysRRN[i] = workkeysRRN[i-1];
        workch[i+1] = workch[i];
    }

    strcpy(workkeys[i], key.C);
    workkeysRRN[i] = key.PR;
    workch[i+1] = r_child;

    char lixo[TAMANHO_CHAVE];
    for(int j = 0; j < TAMANHO_CHAVE; j++){
        lixo[j] = '$';
    }
    //*promo_r_child = getpage();
    
    //pageinit(p_newpage); // eh para dar fwrite
    
    //page_init:
    p_newpage->alturaNo = p_oldpage->alturaNo;

    
    for (int j = 0; j < ORDEM -1; j++)
    {
        p_newpage->duplaChaveRRN[j].C[0] = '\0';
        p_newpage->duplaChaveRRN[j].PR = -1;
        p_newpage->P[j] = -1;
    }
    p_newpage->P[3] = -1;
    p_newpage->nroChavesNo = 0;
    p_newpage->RRNdoNo = 0;

    char aux[100];

    for(int j = 0; j < ORDEM; j++) {
        for(int k = j; k < ORDEM; k++) {
            if(strcmp(workkeys[j], workkeys[k]) > 0) {
                strcpy(aux, workkeys[k]);
                strcpy(workkeys[k], workkeys[j]);
                strcpy(workkeys[j], aux);
            }
        }
    }

    for(i = 0; i < 2; i++){
        strcpy(p_oldpage->duplaChaveRRN[i].C, workkeys[i]);
        p_oldpage->duplaChaveRRN[i].PR = workkeysRRN[i];
        p_oldpage->P[i] = workch[i];
    }

    p_oldpage->P[2] = workch[2];

    strcpy(p_newpage->duplaChaveRRN[0].C,workkeys[3]);
    p_newpage->duplaChaveRRN[0].PR = workkeysRRN[3];


    p_oldpage->duplaChaveRRN[2].C[0] = '\0';
    p_oldpage->duplaChaveRRN[2].PR = NIL;
    p_oldpage->P[3] = NIL;


    p_newpage->P[0] = workch[3];
    p_newpage->P[1] = workch[4];
    p_newpage->nroChavesNo = 1;
    p_oldpage->nroChavesNo = 2;
    strcpy(promo_key->C, workkeys[2]); // ver se tem * no *promo_key
    promo_key->PR = workkeysRRN[2];

    p_newpage->RRNdoNo = cabecalho->RRNproxNo;
    cabecalho->RRNproxNo++;
    *promo_r_child = p_newpage->RRNdoNo;



}

void ins_in_page(duplaChaveRRN key, int r_child, NoArvoreB *p_page) {

    int i;
    for(i = p_page->nroChavesNo; key.C < p_page->duplaChaveRRN[i-1].C && i > 0; i--){
        strcpy(p_page->duplaChaveRRN[i].C, p_page->duplaChaveRRN[i-1].C);
        p_page->duplaChaveRRN[i].PR = p_page->duplaChaveRRN[i].PR;
        p_page->P[i+1] = p_page->P[i];
    }
    p_page->nroChavesNo++;
    strcpy(p_page->duplaChaveRRN[i].C, key.C);
    p_page->duplaChaveRRN[i].PR = key.PR;
    p_page->P[i] = r_child; 
}

void escreverPaginaNoBinarioIndice(NoArvoreB page, FILE *binarioIndice, int RRN) {
    
    char lixo[TAMANHO_CHAVE];
    for(int i = 0; i < TAMANHO_CHAVE; i++){
        lixo[i] = PREENCHIMENTO;
    }
    
    fseek(binarioIndice, (RRN+1)*TAMANHO_PAGINA, SEEK_SET);
    fwrite(&page.nroChavesNo, sizeof(int), 1, binarioIndice);
    fwrite(&page.alturaNo, sizeof(int),1, binarioIndice);
    fwrite(&page.RRNdoNo, sizeof(int), 1, binarioIndice);
    for(int i = 0; i < ORDEM - 1; i++)
    {
        fwrite(&page.P[i],sizeof(int),1, binarioIndice);
        fwrite(page.duplaChaveRRN[i].C, strlen(page.duplaChaveRRN[i].C), 1, binarioIndice);
        fwrite(lixo, TAMANHO_CHAVE - strlen(page.duplaChaveRRN[i].C), 1, binarioIndice);
        fwrite(&page.duplaChaveRRN[i].PR, sizeof(int), 1, binarioIndice);
    }
    fwrite(&page.P[ORDEM-1],sizeof(int),1, binarioIndice);

}

void lerPaginaNoBinarioIndice(NoArvoreB *page, FILE *binarioIndice, int RRN) {
    
    //fread(&page, TAMANHO_PAGINA, 1, binarioIndice);
    fseek(binarioIndice, (1 + RRN)*TAMANHO_PAGINA, SEEK_SET);
    fread(&page->nroChavesNo, sizeof(int), 1, binarioIndice);
    fread(&page->alturaNo, sizeof(int), 1, binarioIndice);
    fread(&page->RRNdoNo, sizeof(int), 1, binarioIndice);
    for(int j = 0; j < 3; j++){

        fread(&page->P[j], sizeof(int),1, binarioIndice);
        fread(page->duplaChaveRRN[j].C, TAMANHO_CHAVE, 1, binarioIndice);
        for(int i = 0; i < TAMANHO_CHAVE; i++){
            if(page->duplaChaveRRN[j].C[i] == '$'){
                page->duplaChaveRRN[j].C[i] = '\0';
                break;
            }
        }
        fread(&page->duplaChaveRRN[j].PR, sizeof(int), 1, binarioIndice);
    }

    fread(&page->P[3], sizeof(int),1, binarioIndice);
}

int acharPosicaoDaChaveNaPagina(char *chave, NoArvoreB pagina) {
    int pos = 0;
    while (pos < pagina.nroChavesNo && strcmp(chave, pagina.duplaChaveRRN[pos].C) > 0) { //AQUI QUE EH A BUSCA BINARIA!
            pos++;
    }
    return pos;
}



void create_root(FILE* binarioIndice, duplaChaveRRN key, int left, int right) {
    /*
    NoArvoreB page;
    B_Cabecalho cab;
    int rrn;
    //cabecalho.proxRRN e fseek(end);
    fseek(binarioIndice, 5, SEEK_SET);
    fread(&rrn, sizeof(int), 1, binarioIndice);
    fseek(binarioIndice, 0, SEEK_SET);
    pageinit(&page);
    page.duplaChaveRRN[0] = key;
    page.P[0] = left;
    page.P[1] = right;
    page.nroChavesNo = 1;
    escreverPaginaNoBinarioIndice(page, binarioIndice);
    if(fread(&cab.status,sizeof(char), 1, binarioIndice) == 0) {
        printf("Falha no processamento do arquivo.");
    }
    cab.noRaiz = rrn;
    fwrite(&cab.noRaiz,sizeof(int),1, binarioIndice);*/
    

}

void pageinit(NoArvoreB *page){

    page->alturaNo = 1;
    page->nroChavesNo = 0;
    page->RRNdoNo = 0;
    char lixo[TAMANHO_CHAVE];
    for(int i = 0; i < TAMANHO_CHAVE; i++){
        lixo[i] = '$';
    }

    for(int j = 0; j < ORDEM - 1; j++) {
        strcpy(page->duplaChaveRRN[j].C, lixo);
        page->duplaChaveRRN[j].PR = NIL;
        page->P[j] = NIL;
    }
    page->P[ORDEM - 1] = NIL;
}


/*
    //funcionalidade 7
void realizarInsercoes(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroInsercoes) {
    Registro novoRegistro;
    FILE *arquivoDados = fopen(nomeArquivoDados, "ab");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "rb+");

while //fazer busca binaria aqui
{

}
//Inserir no final do arquivo
    registroParaBinario;

    if (arquivoDados == NULL || arquivoIndice == NULL)
    {
        return;
        printf("Falha no processamento do arquivo.");
    }

    for (int i = 0; i < numeroInsercoes; i++) {
        // Leia os valores para o novo registro
        
       
        RegistroDados novoRegistro;
        scanf("%s %d %d %s %d",
              novoRegistro.nomeTecnologiaOrigem,
              &novoRegistro.grupo,
              &novoRegistro.popularidade,
              novoRegistro.nomeTecnologiaDestino,
              &novoRegistro.peso);

        // Insira o novo registro no arquivo de dados
        inserirRegistroNoArquivoDados(arquivoDados, novoRegistro);

        // Crie uma nova chave de busca
        ChaveBusca novaChave;
        strcpy(novaChave.chave, novoRegistro.nomeTecnologiaOrigem);
        novaChave.RRNdoRegistro = // Obtenha o RRN do registro recém-inserido;

        // Insira a nova chave na árvore-B
        inserirChaveNaArvoreB(arquivoIndice, novaChave);
    }

    // Exiba a saída dos arquivos binários
    // binarioNaTela(nomeArquivoDados);void realizarInsercoes(char *nomeArquivoDados, char *nomeArquivoIndice, int numeroInsercoes) {
    FILE *arquivoDados = fopen(nomeArquivoDados, "ab");
    FILE *arquivoIndice = fopen(nomeArquivoIndice, "rb+");

//Inserir no final do arquivo
 fseek(arquivoDados, 0, SEEK_END);
    fwrite(&novoRegistro, sizeof(RegistroDados), 1, arquivoDados);
    if (arquivoDados == NULL || arquivoIndice == NULL) {
        return;
    }

    for (int i = 0; i < numeroInsercoes; i++) {
        // Leia os valores para o novo registro
        RegistroDados novoRegistro;
        char linha[1024];
        scanf("%s", linha);
        linhaParaRegistro(linha, novoRegistro);
        // Insira o novo registro no arquivo de dados
        registroParaBinario
        inserirRegistroNoArquivoDados(arquivoDados, novoRegistro);

        // Crie uma nova chave de busca
        ChaveBusca novaChave;
        strcpy(novaChave.chave, novoRegistro.nomeTecnologiaOrigem);
        novaChave.RRNdoRegistro = // Obtenha o RRN do registro recém-inserido;

        // Insira a nova chave na árvore-B
        inserirChaveNaArvoreB(arquivoIndice, novaChave);
    }

   

    // Feche os arquivos
    fclose(arquivoDados);
    fclose(arquivoIndice);
}
}
*/



void inserirNoNo(FILE *binarioIndice, NoArvoreB *page, duplaChaveRRN *promo_key, int p_b_rrn){

        int i;

        for(i = page->nroChavesNo;  strcmp(promo_key->C, page->duplaChaveRRN[i-1].C) < 0  && i > 0; i--){
            
            printf("promokey->C: %s  page2.C: %s", promo_key->C, page->duplaChaveRRN[i].C);
            strcpy(page->duplaChaveRRN[i].C, page->duplaChaveRRN[i-1].C);
            page->duplaChaveRRN[i].PR = page->duplaChaveRRN[i].PR;
            page->P[i+1] = page->P[i];
        }
        page->nroChavesNo++;
        strcpy(page->duplaChaveRRN[i].C, promo_key->C);
        page->duplaChaveRRN[i].PR = promo_key->PR;
        page->P[i] = p_b_rrn;
        

        escreverPaginaNoBinarioIndice(*page, binarioIndice, page->RRNdoNo);
        printf("page.nroChavesNo: %d\n", page->nroChavesNo);

}


void printaNo(NoArvoreB page) {
    printf("nroChavesNo: %d , alturaNo %d , RRNdoNo %d\n", page.nroChavesNo, page.alturaNo, page.RRNdoNo);
    for(int i = 0; i < page.nroChavesNo; i++){
        printf("page.C: %s ||", page.duplaChaveRRN[i].C);
    }
    printf("\n");
}