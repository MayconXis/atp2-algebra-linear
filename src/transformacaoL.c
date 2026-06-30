int isSobrejetora(int dimensaoImagem, int dimensaoDestino){
    if(dimensaoDestino == dimensaoImagem) return TRUE;
    else return FALSE;
}

int dimensaoNucleo(int dimensaoEntrada, int dimensaoImagem){
    return dimensaoEntrada - dimensaoImagem;
}

int linhasUteis(Matriz m){ //Dimensao da imagem
    int uteis = 0;
    for(int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){
            if(m.dados[i][j] != 0){
                uteis++;
                break;
            }
        }
    }
    return uteis;
}

