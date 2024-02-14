//Bárbara Fernandes Madera      nUSP: 11915032
//Viktor Sérgio Ferreira        nUSP: 11800570
#include <stdio.h>
#include "todasfuncoes.h"
#include "lista.h"

Cabecalho* alocaNovoCabecalho(){
    Cabecalho* novoCabecalho = (Cabecalho*)malloc(sizeof(Cabecalho));
    if(novoCabecalho == NULL){
        fprintf(stderr, "Erro: Falha na alocacao de memoria para novoCabecalho.\n");
        exit(1);
    }
    novoCabecalho->status = '0';//Crialção de um novo cabeçalho com as especificações pedidas no trabalho
    novoCabecalho->proxRRN = 0;
    novoCabecalho->proxRRN = 0;
    novoCabecalho->nroTecnologias = 0;
    novoCabecalho->nroParesTecnologias = 0;
    return novoCabecalho;
}

Registro* alocaNovoRegistro() {
    Registro* novoRegistro = (Registro*)malloc(sizeof(Registro));
    if (novoRegistro == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para novoRegistro.\n");
        exit(1);
    }
    
    //// Inicializção de todos os campos da estrutura aqui, se necessário.
    novoRegistro->removido = '0';
    novoRegistro->grupo = 0;
    novoRegistro->popularidade = 0;
    novoRegistro->peso = 0;

    novoRegistro->nomeTecnologiaOrigem.tamanho = 0;
    novoRegistro->nomeTecnologiaOrigem.string = (char*)malloc(64*sizeof(char));
    if (novoRegistro->nomeTecnologiaOrigem.string == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para nomeTecnologiaOrigem.string.\n");
        exit(1);
    }

    novoRegistro->nomeTecnologiaDestino.tamanho = 0;
    novoRegistro->nomeTecnologiaDestino.string = (char*)malloc(64*sizeof(char));
    if (novoRegistro->nomeTecnologiaDestino.string == NULL) {
        fprintf(stderr, "Erro: Falha na alocação de memória para nomeTecnologiaDestino.string.\n");
        exit(1);
    }

    return novoRegistro;
}

//Função que libera a memória do registro
void liberaRegistro(Registro *registro) { 
    free(registro->nomeTecnologiaOrigem.string);
    free(registro->nomeTecnologiaDestino.string);
    free(registro);
}

//Função abrir aquivo .csv
FILE* abreCsv(char* arquivoCsv) {
    FILE* stream;
    abrirArquivo(&stream,arquivoCsv, "rt");
    return stream; 
}

//Função dada que permite melhor leitura do arquivo
char* getfield(char* line, int num) {
    const char* start = line;
    const char* end;
    int count = 0;

    while ((end = strchr(start, ',')) != NULL || (end = strchr(start, '\0')) != NULL)
    {
        if (++count == num)
        {
            // Verifica se o campo está vazio e retorna "-1" nesse caso
            if (start == end)
            {
                char* result = (char*)malloc(3*sizeof(char));  // Alocando memória para "-1" e o caractere nulo
                strcpy(result, "-1");
                return result;
            }

            // Alocar memória dinamicamente para o campo
            char* result = (char*)malloc(end - start + 1);
            strncpy(result, start, end - start);
            result[end - start] = '\0';
            if(result[0] == 13 && result[1] == 10){
                return "-1";
            }
            return result;
        }

        // Move para o próximo caractere após a vírgula
        start = end + 1;
    }

    return NULL;
}

//Função permite conversão do arquivo .csv para binário a partir de listas organizada pelos requisitos
// csv->registro e registro->binario

void csvParaBinario(FILE* stream, FILE* binario) {
    char line[1024];
    Lista *li1 = criaLista();
    Lista *li2 = criaLista();
    int nroTecnologias = 0;
    int nroParTecnologias = 0;
    Cabecalho *c1 = alocaNovoCabecalho();

    fgets(line, 1024, stream);
    while (fgets(line, 1024, stream))
    {
        int jaTem1, jaTem2, jaTem3;
        char aux[128];
        jaTem1 = 1;
        jaTem2 = 1;
        jaTem3 = 1;
        
        Registro* registroTemp;
        registroTemp = alocaNovoRegistro();      

/*esse sscanf equivale a "registro->grupo = getfield(tmp, 2);" , mas sem problema de conversao de tipos */

        linhaParaRegistro(line,registroTemp);

        if(strcmp(registroTemp->nomeTecnologiaOrigem.string,"-1")){
            jaTem1 = dadoExisteLista(li1,registroTemp->nomeTecnologiaOrigem.string);
            if(!jaTem1){
                insereListaInicio(li1, registroTemp->nomeTecnologiaOrigem.string);
            }
            strcpy(aux,registroTemp->nomeTecnologiaOrigem.string);
        }
        if(strcmp(registroTemp->nomeTecnologiaDestino.string,"-1")){
            jaTem2 = dadoExisteLista(li1, registroTemp->nomeTecnologiaDestino.string);
            if(!jaTem2){
                insereListaInicio(li1, registroTemp->nomeTecnologiaDestino.string);
            }
            strcat(aux,registroTemp->nomeTecnologiaDestino.string);
        }

        jaTem3 = dadoExisteLista(li2, aux);
        if(!jaTem3){
            c1->proxRRN++;
            if(strcmp(registroTemp->nomeTecnologiaDestino.string,"-1")){
                insereListaInicio(li2, aux);
            }
        }

        registroParaBinario(binario, registroTemp);
        free(registroTemp);
    }  
        c1->nroTecnologias = tamanhoLista(li1);
        c1->nroParesTecnologias = tamanhoLista(li2); 
        liberaLista(li1);
        liberaLista(li2);
        cabecalhoParaBinario(binario, c1);
}

//Função permite conversão de linha para o registro conforme especificações do projeto
void linhaParaRegistro(char* line, Registro *registroTemp) {

    char *tmp = (char*)malloc(64*sizeof(char));
    if(tmp == NULL)
    {
        printf("ERRO de alocacao de memoria\n");
    }
    tmp = strdup(line);
    sscanf(getfield(tmp, 2), "%d", &(registroTemp->grupo));
    sscanf(getfield(tmp, 3), "%d", &(registroTemp->popularidade));
    sscanf(getfield(tmp, 5), "%d", &(registroTemp->peso));   
    strcpy(registroTemp->nomeTecnologiaOrigem.string, getfield(tmp, 1));
    registroTemp->nomeTecnologiaOrigem.tamanho = strlen(registroTemp->nomeTecnologiaOrigem.string);
    strcpy(registroTemp->nomeTecnologiaDestino.string, getfield(tmp, 4));
    registroTemp->nomeTecnologiaDestino.tamanho = strlen(registroTemp->nomeTecnologiaDestino.string);
    free(tmp);

}

//Função permite converção do que está no cabe
void cabecalhoParaBinario(FILE* arquivo, Cabecalho* cabecalho) {
    fseek(arquivo,0,SEEK_SET);
    cabecalho->status = '1';
    fwrite(&cabecalho->status, sizeof(char),1, arquivo);
    fwrite(&cabecalho->proxRRN,sizeof(int), 1, arquivo);
    fwrite(&cabecalho->nroTecnologias, sizeof(int), 1, arquivo);
    fwrite(&cabecalho->nroParesTecnologias, sizeof(int), 1, arquivo);
    fclose(arquivo);
}

FILE* criarBinario(const char *nomeTabela) {
    FILE *arquivo;
    abrirArquivo(&arquivo, nomeTabela, "wb+"); // append(ab): escreve no final do arquivo apenas
    Cabecalho cabecalho;

    // Inicialize o cabeçalho com os valores padrão
    cabecalho.status = '0'; // Marca o arquivo como inconsistente, 0 = inconsistente, 1 = consstnt
    cabecalho.proxRRN = 0;
    cabecalho.nroTecnologias = 0;
    cabecalho.nroParesTecnologias = 0;

    // Escreva o cabeçalho no arquivo
    fwrite(&cabecalho.status, sizeof(char), 1, arquivo);
    fwrite(&cabecalho.proxRRN, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.nroTecnologias, sizeof(int), 1, arquivo);
    fwrite(&cabecalho.nroParesTecnologias, sizeof(int),1, arquivo);
    return arquivo;
    
}

//Função de leitura do string para o arquivo binário
void stringParaBinario(char* string, FILE* arquivo, int tamanho) {  
    fwrite(string, sizeof(char), tamanho, arquivo);

}

// Função para inserir um registro em uma tabela
void registroParaBinario(FILE *arquivo, Registro *registro) {
    int qtdCifrao;

    if (arquivo == NULL) {
        perror("Erro ao abrir tabela para inserção");
        exit(1);
    }

    fwrite(&registro->removido, sizeof(char), 1, arquivo);
    fwrite(&registro->grupo, sizeof(int), 1, arquivo);
    fwrite(&registro->popularidade, sizeof(int), 1, arquivo);
    fwrite(&registro->peso, sizeof(int), 1, arquivo);
    if(!strcmp(registro->nomeTecnologiaOrigem.string,"-1")){
        registro->nomeTecnologiaOrigem.tamanho = 0;
        fwrite(&registro->nomeTecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
    }else{
        fwrite(&registro->nomeTecnologiaOrigem.tamanho, sizeof(int), 1, arquivo);
        stringParaBinario(registro->nomeTecnologiaOrigem.string, arquivo, registro->nomeTecnologiaOrigem.tamanho);
    }
    if(!strcmp(registro->nomeTecnologiaDestino.string,"-1")){
        registro->nomeTecnologiaDestino.tamanho = 0;
        fwrite(&registro->nomeTecnologiaDestino.tamanho, sizeof(int), 1, arquivo);        
    }else{
        fwrite(&registro->nomeTecnologiaDestino.tamanho, sizeof(int), 1, arquivo);
        stringParaBinario(registro->nomeTecnologiaDestino.string, arquivo, registro->nomeTecnologiaDestino.tamanho);
    }

    qtdCifrao = TAMANHO_REGISTRO - (registro->nomeTecnologiaOrigem.tamanho + registro->nomeTecnologiaDestino.tamanho)*sizeof(char) - 5*sizeof(int) -1;
    char cifrao[qtdCifrao];
    for(int i = 0; i < qtdCifrao; i++){
        cifrao[i] = '$';
    }

    fwrite(cifrao, sizeof(char), qtdCifrao, arquivo);
    }

// Função para listar todos os registros de uma tabela
void listarRegistros(char *nomeTabela) {
    int qtdRegistros, RRN = 0;
    FILE *arquivo;
    abrirArquivo(&arquivo, nomeTabela, "rb");
    if(arquivo == NULL){
        return;
    }
    qtdRegistros =  contaRegistros(arquivo);
    while (RRN < qtdRegistros){ 
        recuperacaoDoRegistro(arquivo, RRN);
        RRN++;
    }
    
}

//Função permite a contações dos registros
int contaRegistros(FILE* binario) {
   int totalDeRegistros;
   fseek(binario, 0, SEEK_END);
   totalDeRegistros = (ftell(binario) - TAMANHO_CABECALHO) / TAMANHO_REGISTRO;
    return totalDeRegistros;
}

//Função que recupera o registro pelo RRN 
void recuperacaoDoRegistro(FILE* binario, int RRN) {
    if( RRN >= contaRegistros(binario) || RRN < 0 ){
        printf("Registro inexistente.");
        return;
    }
    Registro* regTemp = alocaNovoRegistro();
    
    if(binario == NULL){
        printf("Falha no processamento do arquivo.\n");
        return;
    }
    fseek(binario, TAMANHO_REGISTRO*RRN + TAMANHO_CABECALHO,SEEK_SET);
    binarioParaRegistro(binario,regTemp); 
    
    if(regTemp->removido == '1'){ // esta logicamente removido
        printf("Registro inexistente.");
        return;
    }else{
        imprimeLinha(regTemp);
        printf("\n");
    }
    free(regTemp->nomeTecnologiaOrigem.string);
    free(regTemp->nomeTecnologiaDestino.string);
    free(regTemp);
}

//Função permite mostrar campo vazio como campo NULO, facilita entendimento
void printaConsiderandoNulo(int campo) {
    if(campo == -1){
        printf("NULO, ");
    }else{
        printf("%d, ", campo);
    }
}

//Função printa String e formatação conforme especificações e mostra NULO quando algum dos campos é vazio
void printaString(char* string, int tamanhoString) {
    if(tamanhoString == 0){
        printf("NULO, ");
    }else{
        if(strlen(string) > tamanhoString)
        {
            for(int i = 0; i < tamanhoString; i++){
                printf("%c",string[i]);
            }
            printf(", ");
        }else{
            printf("%s, ", string);
        }
    }
}

//Função permite otimizar a impressão da linha conforme as especificações
void imprimeLinha(Registro* r) {
    printaString(r->nomeTecnologiaOrigem.string, r->nomeTecnologiaOrigem.tamanho);
    printaConsiderandoNulo(r->grupo);
    printaConsiderandoNulo(r->popularidade);
    printaString(r->nomeTecnologiaDestino.string, r->nomeTecnologiaDestino.tamanho);
        if(r->peso == -1){
        printf("NULO");
    }else{
        printf("%d", r->peso);
    }
}

//Função lê os dados do requisto quando em binário conforme especificações do projeto
void binarioParaRegistro(FILE *arquivo, Registro *registro) {
    fread(&(registro->removido), sizeof(char), 1, arquivo);
    fread(&(registro->grupo), sizeof(int), 1, arquivo);
    fread(&(registro->popularidade), sizeof(int), 1, arquivo);
    fread(&(registro->peso), sizeof(int), 1, arquivo);
    fread(&(registro->nomeTecnologiaOrigem.tamanho), sizeof(int), 1, arquivo);
    fread(registro->nomeTecnologiaOrigem.string, registro->nomeTecnologiaOrigem.tamanho * sizeof(char), 1, arquivo);
    fread(&(registro->nomeTecnologiaDestino.tamanho), sizeof(int), 1, arquivo);
    fread(registro->nomeTecnologiaDestino.string, registro->nomeTecnologiaDestino.tamanho * sizeof(char), 1, arquivo);
}

//Função abre o arquivo
void abrirArquivo(FILE **arquivo, const char *nomeArquivo, const char *modo) {
    *arquivo = fopen(nomeArquivo, modo);
    if (*arquivo == NULL) {
        printf("Falha no processamento do arquivo.");
        return;
    }
}

//Função fecha o arquivo
void fecharArquivo(FILE *arquivo) {
    if (fclose(arquivo) != 0) {
        perror("Erro ao fechar arquivo binário");
        exit(1);
    }
}

//Função permite a comparação dos campos com o campo buscado
int comparaCampo(Registro *registro, const char *nomeCampo, const char *valorCampo) {
    if (strcmp(nomeCampo, "nomeTecnologiaOrigem") == 0) {
        return strncmp(registro->nomeTecnologiaOrigem.string, valorCampo, registro->nomeTecnologiaOrigem.tamanho) == 0;
    } else if (strcmp(nomeCampo, "grupo") == 0) {
        return registro->grupo == atoi(valorCampo);
    } else if (strcmp(nomeCampo, "popularidade") == 0) {
        return registro->popularidade == atoi(valorCampo);
    } else if (strcmp(nomeCampo, "nomeTecnologiaDestino") == 0) {
        return strncmp(registro->nomeTecnologiaDestino.string, valorCampo, registro->nomeTecnologiaDestino.tamanho) == 0;
    } else if (strcmp(nomeCampo, "peso") == 0) {
        return registro->peso == atoi(valorCampo);
    }
    return 0; // Campo desconhecido
}

//Função permiete recuperar dados por busca feita pelo usuário
void recuperaDadosBuscados(char *arquivoEntrada, int n) {
    FILE *binario = NULL;
    abrirArquivo(&binario, arquivoEntrada, "rb");
    Cabecalho *c = alocaNovoCabecalho();
    fread(&(c->status), sizeof(char), 1, binario);
    
    if (c->status == '0') {
        printf("Falha no processamento do arquivo.");
        fecharArquivo(binario);
        return;
    }

    int qtdRegistros = contaRegistros(binario);
    
    Registro *registro = alocaNovoRegistro();
    
    if (registro == NULL) {
        printf("Falha na alocação de memória para registro.");
        fecharArquivo(binario);
        exit(1);
    }
    
    char line[n][1024];
    char nomeDoCampo[n][50], valorDoCampo[n][50];
    
    for (int i = 0; i < n; i++) {
       
        scanf("%s", nomeDoCampo[i]);
        scan_quote_string(valorDoCampo[i]);
        int RRN = 0;
    
        fseek(binario, TAMANHO_CABECALHO, SEEK_SET); // Pular o cabeçalho

        int encontrouRegistro = 0;
        while (RRN < qtdRegistros) {
            binarioParaRegistro(binario, registro);
            // o numero 21 é a soma dos tamanhos fixos do Registro
            fseek(binario, TAMANHO_REGISTRO - 21 - registro->nomeTecnologiaOrigem.tamanho - registro->nomeTecnologiaDestino.tamanho, SEEK_CUR);
            if (registro->removido == '0') {
                    if (comparaCampo(registro, nomeDoCampo[i], valorDoCampo[i])) {
                        imprimeLinha(registro);
                        printf("\n");
                        encontrouRegistro = 1;
                        continue; // Você encontrou o registro, não é necessário continuar verificando os outros campos.
                    }
            }
        RRN++;
        }
        if (!encontrouRegistro) {
            printf("Registro inexistente.");
            break;
        }
    }

    free(registro);
    fecharArquivo(binario);
}
