/*int buscarRRNNoIndice(FILE *binarioIndice, NoArvoreB *indice, char *chaveBusca, int condicaoDeParada, int *RRN, int *pos, int P) {
    if(condicaoDeParada != 0){
        return condicaoDeParada;
    }
    fseek(binarioIndice, (P+1)*TAMANHO_PAGINA, SEEK_SET);
   
    fread(&indice->nroChavesNo, sizeof(int), 1, binarioIndice);
    fread(&indice->alturaNo, sizeof(int), 1, binarioIndice);
    fread(&indice->RRNdoNo, sizeof(int), 1, binarioIndice);
    for(int j = 0; j < 3; j++){

        fread(&indice->P[j], sizeof(int),1, binarioIndice);
        fread(indice->duplaChaveRRN[j].C, 55, 1, binarioIndice);
       
        for(int i = 0; i < TAMANHO_CHAVE; i++){
            if(indice->duplaChaveRRN[j].C[i] == '$'){
                indice->duplaChaveRRN[j].C[i] = '\0';
                break;
            }
        }
        fread(&indice->duplaChaveRRN[j].PR, sizeof(int), 1, binarioIndice);
    }
    
    fread(&indice->P[3], sizeof(int),1, binarioIndice);
    
    while (condicaoDeParada == 0) {
        int i = 0;
        
        // Percorre as chaves do nó
        i = acharPosicaoDaChaveNaPagina(chaveBusca, *indice);
        *pos = i;
        printf("\nchave busca: %s pos: %d\n", chaveBusca, *pos);

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

*/