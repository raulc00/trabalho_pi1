#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<time.h>
#include<omp.h>


typedef struct RegistroBD{

    char assessmentId[90];
    char scientificName[90];
    char redlistCategory[90];

}RegistroBD;

typedef struct Lista{

    int qtd;
    struct Registro * inicio;

}Lista;

typedef struct Registro{

    char ID[90];
    char NomeEspecie[90];
    char EstadoRisco[90];

    struct Registro * proximo;

}Registro;

typedef struct NoArvore{

    char ID[90];
    char nomeEspecie[90];
    char situacaoAtual[90];
    int valorString;

    struct NoArvore * esquerda;
    struct NoArvore * direita;

}NoArvore;

Lista * aloca_lista(){

    Lista * x;

    x = (Lista*)malloc(sizeof(Lista));

    x -> inicio = NULL;
    x -> qtd = 0;

    return x;
}

Registro * aloca_registro(){

    Registro * x;

    x = (Registro*)malloc(sizeof(Registro));

    x -> ID[0] = '\0';
    x -> NomeEspecie[0] = '\0';
    x -> EstadoRisco[0] = '\0';

    x -> proximo = NULL;

    return x;
}

Lista * adiciona_struct(Lista * l1, RegistroBD registros[], int i){

    Registro * x;
    Registro * aux;
 
        x = aloca_registro();

        strcpy(x->ID, registros[i].assessmentId);
        strcpy(x->NomeEspecie, registros[i].scientificName);
        strcpy(x->EstadoRisco, registros[i].redlistCategory);


        if(l1 -> inicio == NULL){

            l1 -> inicio = x;
        }
        else{

            aux = l1 -> inicio;

            while(aux -> proximo != NULL){

                aux = aux -> proximo;
            }

            aux -> proximo = x;
        }

        l1 -> qtd++;

}

NoArvore * InsercaoArvore(NoArvore * noPai, RegistroBD vetorRegistro[], int i, int vetorStrings[]){

    NoArvore * aux;

    if(noPai == NULL){

        aux = (NoArvore*)malloc(sizeof(NoArvore));

        strcpy(aux->ID, vetorRegistro[i].assessmentId);
        strcpy(aux->nomeEspecie, vetorRegistro[i].scientificName);
        strcpy(aux->situacaoAtual, vetorRegistro[i].redlistCategory);
        aux -> valorString = vetorStrings[i];

        aux -> direita = NULL;
        aux -> esquerda = NULL;

        return aux;
    }
    else if(vetorStrings[i] > noPai->valorString){

        noPai -> direita = InsercaoArvore(noPai->direita, vetorRegistro, i, vetorStrings);
    }
    else if(vetorStrings[i] < noPai->valorString){

        noPai -> esquerda = InsercaoArvore(noPai->esquerda, vetorRegistro, i, vetorStrings);
    }
    else if(vetorStrings[i] == noPai->valorString){

        noPai -> direita = InsercaoArvore(noPai->direita, vetorRegistro, i, vetorStrings);
    }

    return noPai;

}

void libera_Arvore(NoArvore * noPai){

    if(noPai != NULL){

        libera_Arvore(noPai->esquerda);
        libera_Arvore(noPai->direita);

        free(noPai);
    }
}

void mostra_elementosArvore(NoArvore * no){


    if(no != NULL){

        printf("\nID da Espécie: %s , Nome da Espécie: %s , Situação atual: %s , ValorString: %d", no->ID, no->nomeEspecie, no->situacaoAtual, no->valorString);

        printf("\n");

        mostra_elementosArvore(no->esquerda);

        mostra_elementosArvore(no->direita);


    }

}

void mostra_elementos(Lista * l1){

    Registro * x;

    if(l1 -> inicio == NULL){

        printf("\nLista vazia");
    }
    else{

        x = l1 -> inicio;

        do{
            printf("\n");

            printf("\nID da Espécie: %s , Nome da Espécie: %s , Situação atual: %s", x ->ID, x ->NomeEspecie, x ->EstadoRisco);
             
            x = x -> proximo;

        }while(x != NULL);

    }
}

void busca_registro(Lista * l1, char nomePrimario[90], char nomeSecundario[90]){//Função funcionando

    Registro * aux;
    char nome[90];
    int flag = 0;
    int i = 0;
    int teste = 0;
   
    strcat(nomePrimario, " ");

    strcat(nomePrimario, nomeSecundario);

    for(i=0; i<strlen(nomePrimario); i++){

        strcpy(nome, nomePrimario);
    }

   
    if(l1 -> inicio == NULL){

        printf("\nA lista está vazia");

    }
    else{

        aux = l1 -> inicio;

        while(aux ->proximo != NULL){

            if(strcmp(aux->NomeEspecie, nome) != 0){

                teste = teste + 1;
        
            }
            else{

                flag = flag + 1;
                break;

            }

            aux = aux -> proximo;
            
        }
        if(strcmp(aux->NomeEspecie, nome) != 0){

                teste = teste + 1;
                
            }
            else{

                flag = flag + 1;


            }

            printf("\n");
        
        if(flag == 0){

            printf("\nRegistro não encontrado");
        }
        else{

            printf("\nID da Espécie: %s", aux->ID);
            printf("\nNome da Espécie: %s", aux->NomeEspecie);
            printf("\nSituação atual: %s", aux->EstadoRisco);

            printf("\n");

            printf("\nEncontrado no Registro %d da Lista Ligada", teste);

            printf("\n");
        }

        
    }
}

void mostraVetor(RegistroBD valores[]){

    int i;

    for(i=0; i<743; i++){

        printf("\nRegistro %d", i);

        printf("\nId: %s, Nome cientifico: %s, Situação Atual: %s", valores[i].assessmentId, valores[i].scientificName, valores[i].redlistCategory);

        printf("\n===========================================================================================================================");
    }
}

int valorString(RegistroBD VetordeStruct[], int indiceString[], int vetorAlvo[]){ //Função funcionando 
     int i = 0;
     int j = 0;
     char * nomes;
     int valor; 
     int tam = 743;
     int vetorValores[743];

     for(i=0; i<743; i++){

          nomes = VetordeStruct[i].scientificName;

          valor = 0;

          for(j=0; j<strlen(nomes); j++){

              char letra = nomes[j];

              valor = valor + (int)letra;

              
          }

            indiceString[i] = valor;
            
     }

     for(i=0; i<743; i++){

         vetorAlvo[i] = indiceString[i];
     }

}

int criaIndice(int vetorIndiceString[], int tamHash, int vetorIndiceResto[]){ //Função Funcionando

    int resto[743];
    int i = 0;

    for(i=0; i<743; i++){

        resto[i] = (vetorIndiceString[i] % tamHash);

    }

    for(i=0; i<743; i++){

        vetorIndiceResto[i] = resto[i];
    }

}

int criaIndiceBusca(int valorBusca, int tamHash){//Função funcionando

    int valor = 0;

    valor = (valorBusca % tamHash);

    return valor;
}

void busca_registroLinear(RegistroBD vetor[], char nomePrimario[90]){//Função funcionando

    int i = 0;
    RegistroBD vetorLinear[744];
    int flag = 0;
    int indiceAlvo = 0;
    char nome[90];

    
    for(i=0; i<743; i++){

        if(strcmp(nomePrimario, vetor[i].scientificName) == 0){

            flag = flag + 1;
            break;
        }
        
    }

    if(flag != 1){

        printf("\nRegistro não encontrado");
    }
    else{

        printf("\nID da Espécie: %s", vetor[i].assessmentId);
        printf("\nNome da Espécie: %s", vetor[i].scientificName);
        printf("\nSituação atual: %s", vetor[i].redlistCategory);

        printf("\n");

        printf("\nEncontrado na posição: %d", i);

        printf("\n");
    }


}

void busca_registroBinaria(RegistroBD vetor[], char nomePrimario[90]){//Função finalizada


    int i = 0;
    int meio = 0;
    int final = 90;
    int inicio = 65;
    int flag = 0;
    int letraValor = 0;
    char nomeBusca[90];

    strcpy(nomeBusca, nomePrimario);

    meio = (final + inicio)/2;

    for(i=0; i<strlen(nomeBusca); i++){

        char letraBusca = nomeBusca[i];

        letraValor = (int)letraBusca;

        break;
    }

    if(letraValor < meio){

        for(i=0; i<371; i++){

            if(strcmp(nomePrimario, vetor[i].scientificName) == 0){

                flag = flag + 1;
                break;
            }
        }
    }
    else if(letraValor > meio){

        for(i=371; i<743; i++){

            if(strcmp(nomePrimario, vetor[i].scientificName) == 0){

                flag = flag + 1;
                break;
            }
        }
    }
    else if(letraValor == meio){

        for(i=371; i<743; i++){

            if(strcmp(nomePrimario, vetor[i].scientificName) == 0){

                flag = flag + 1;
                break;
            }
        }
    }

    if(flag != 1){

        printf("\nRegistro não encontrado");
    }
    else{

        printf("\nID da Espécie: %s", vetor[i].assessmentId);
        printf("\nNome da Espécie: %s", vetor[i].scientificName);
        printf("\nSituação atual: %s", vetor[i].redlistCategory);

        printf("\n");

        printf("\nEncontrado na posição: %d", i);

        printf("\n");
    }

}

void busca_registroArvore(NoArvore * no, char nomePrimario[90], int valorBusca){

    if(no != NULL){

        if((no->valorString == valorBusca) && (strcmp(no->nomeEspecie, nomePrimario) == 0)){

            printf("\nID da Espécie: %s", no->ID);
            printf("\nNome da Espécie: %s", no->nomeEspecie);
            printf("\nSituação atual: %s", no->situacaoAtual);

            printf("\n");

        }
        else{

            if((valorBusca > no->valorString) && (strcmp(no->nomeEspecie, nomePrimario) != 0)){

                busca_registroArvore(no->direita, nomePrimario, valorBusca);
            }
            else if((valorBusca < no->valorString) && (strcmp(no->nomeEspecie, nomePrimario) != 0)){

                busca_registroArvore(no->esquerda, nomePrimario, valorBusca);
            }
            else if((valorBusca == no->valorString) && (strcmp(no->nomeEspecie, nomePrimario) != 0)){

                busca_registroArvore(no->direita, nomePrimario, valorBusca);
            }
        }

    }

}

void InsertionSort(RegistroBD vetor[]){

    int i = 0;
    int j = 0;
    RegistroBD aux;

    for(i=1; i<744; i++){

        aux = vetor[i];

        for(j=i; (j>0) && (strcmp(aux.scientificName, vetor[j-1].scientificName)<0); j--){

            vetor[j] = vetor[j-1];
        }
        vetor[j] = aux;
    }
}

void arruma_vetorBinario(RegistroBD DadosLinear[], RegistroBD Dados[]){

    int i = 0;

    for(i=0; i<743; i++){

        strcpy(DadosLinear[i].assessmentId, Dados[i].assessmentId);
        strcpy(DadosLinear[i].scientificName, Dados[i].scientificName);
        strcpy(DadosLinear[i].redlistCategory, Dados[i].redlistCategory);
    }

    InsertionSort(DadosLinear);

}

void abreArquivo(RegistroBD Dados[]){

    FILE * db;
    char * coluna;
    char linha[744];
    int qtd_linha = 0;
    int qtd_coluna = 0;
    int i = 0;

    db = fopen("simple_summary.csv", "r");

    if(db == NULL){

        printf("\nArquivo não encontrado");

    }

    while(fgets(linha, 745, db)){

        qtd_coluna = 0;

        qtd_linha++;

        if(qtd_linha == 1){

            continue;
        }

        coluna = strtok(linha, ",");

        while(coluna){

            if(qtd_coluna == 0){

                strcpy(Dados[i].assessmentId, coluna);
                
            }

            if(qtd_coluna == 2){

                strcpy(Dados[i].scientificName, coluna);
            }

            if(qtd_coluna == 12){

                strcpy(Dados[i].redlistCategory, coluna);
            }

            coluna = strtok(NULL, ",");

            qtd_coluna++;
        }

        i++;
    }

    fclose(db);

} 

void menu(RegistroBD Dados[], Lista ** TabelaHash, RegistroBD DadosLinear[], NoArvore * noPai){

    int op = 0;
    int i = 0;
    int tam = 26;
    int valorIndiceBusca = 0;
    int valorBusca = 0;
    double t1, t2, t3, t4, t5, t6, t7, t8;
    char nomePrimarioBuscado[90];
    char nomeSecundarioBuscado[90];

    do{

        printf("\n0 - Sair");
        printf("\n1 - Mostrar banco de dados");
        printf("\n2 - Iniciar as buscas");

        printf("\n");

        printf("\nDigite a opção desejada:");
         scanf("%d", &op);
        printf("\n");

        switch(op){

            case 0: 
                    printf("\nSaindo do programa...");
                    break;

            case 1:       
                    mostraVetor(Dados);
                    break;

            case 2: 

                    valorBusca = 0;

                    printf("\nDigite o nome primário da espécie a ser buscada:");
                    scanf("%s", nomePrimarioBuscado);

                    printf("\nDigite o nome secundário da espécie a ser buscada:");
                    scanf("%s", nomeSecundarioBuscado);   

                    for(i=0; i<strlen(nomePrimarioBuscado); i++){

                        valorBusca = valorBusca + (int)nomePrimarioBuscado[i];
                    }

                    valorBusca = valorBusca + 32;

                    printf("\n");

                    for(i=0; i<strlen(nomeSecundarioBuscado); i++){

                        valorBusca = valorBusca + (int)nomeSecundarioBuscado[i];
                    }

                    printf("\n===========================================================================================================================\n");

                    printf("\nValor da String convertida: %d", valorBusca);

                    valorIndiceBusca = criaIndiceBusca(valorBusca, tam);

                    printf("\nValor da chave: %d", valorIndiceBusca); 

                    printf("\n");

                    printf("\n===========================================================================================================================");

                    printf("\nBusca na Tabela Hash:");

                    t1 = omp_get_wtime();
                    busca_registro(TabelaHash[valorIndiceBusca], nomePrimarioBuscado, nomeSecundarioBuscado);
                    t2 = omp_get_wtime();

                    printf("\nTempo de processamento: %0.10f", t2-t1);

                    printf("\n===========================================================================================================================");

                    printf("\nBusca Linear:");

                    printf("\n");

                    t3 = omp_get_wtime();
                    busca_registroLinear(Dados, nomePrimarioBuscado);
                    t4 = omp_get_wtime();

                    printf("\nTempo de processamento: %0.10f", t4-t3);

                    printf("\n===========================================================================================================================");

                    printf("\nBusca binária:");

                    printf("\n");

                    t5 = omp_get_wtime();
                    busca_registroBinaria(DadosLinear, nomePrimarioBuscado);
                    t6 = omp_get_wtime();

                    printf("\nTempo de processamento: %0.10f", t6-t5);

                    printf("\n===========================================================================================================================");

                    printf("\nBusca em Árvore Binária:");

                    printf("\n");

                    t7 = omp_get_wtime();
                    busca_registroArvore(noPai, nomePrimarioBuscado, valorBusca);
                    t8 = omp_get_wtime();

                    printf("\nTempo de processamento: %0.10f", t8-t7);

                    printf("\n===========================================================================================================================");

                    printf("\n");

                    


        } 

    }while(op != 0);

}

int main(){
    setlocale(LC_ALL,"portuguese_Brazil");

    FILE * db;
    char * coluna;
    char linha[744];
    char * limite;
    int qtd_linha = 0;
    int qtd_coluna = 0;
    int i = 0;
    int j = 0;
    int indiceString[743];
    int vetorIndiceString[743];
    int vetorIndiceResto[743];
    char * nomes;
    int valor;
    int tam = 26;
    char nomeCompleto[90];
    int indiceAlvo = 0;
    int nomeConvertido = 0;
    int indice[743];
    int indiceRegistro = 0;
    int IndiceLista[743];
    int valorStringBusca = 0;
    int testeString[743];
    int stringAlvo[743];
    Lista ** TabelaHash;
    Lista * ListaLigada;
    NoArvore * noPai;

    TabelaHash = (Lista**)malloc(sizeof(Lista*)* tam);
    
    RegistroBD Dados[744];
    RegistroBD DadosLinear[744];
    RegistroBD VetorDadosArvore[2000];
    
    abreArquivo(Dados);

    printf("\n");

    valorString(Dados, indiceString, vetorIndiceString);

    criaIndice(vetorIndiceString, tam, vetorIndiceResto);


    for(i=0; i<tam; i++){

        ListaLigada = aloca_lista();

        TabelaHash[i] = ListaLigada;
        
    }

    
    for(i=0; i<743; i++){

            vetorIndiceResto[i] = (vetorIndiceString[i] % tam);

            adiciona_struct(TabelaHash[vetorIndiceResto[i]], Dados, i);

    }

    arruma_vetorBinario(DadosLinear, Dados);

    strcpy(VetorDadosArvore[0].assessmentId, Dados[1].assessmentId);
    strcpy(VetorDadosArvore[0].scientificName, Dados[1].scientificName);
    strcpy(VetorDadosArvore[0].redlistCategory, Dados[1].redlistCategory);

    strcpy(VetorDadosArvore[1].assessmentId, Dados[0].assessmentId);
    strcpy(VetorDadosArvore[1].scientificName, Dados[0].scientificName);
    strcpy(VetorDadosArvore[1].redlistCategory, Dados[0].redlistCategory);

    for(i=2; i<743; i++){

        strcpy(VetorDadosArvore[i].assessmentId, Dados[i].assessmentId);
        strcpy(VetorDadosArvore[i].scientificName, Dados[i].scientificName);
        strcpy(VetorDadosArvore[i].redlistCategory, Dados[i].redlistCategory);

    }

    valorString(VetorDadosArvore, testeString, stringAlvo);

    for(i=0; i<743; i++){

        noPai = InsercaoArvore(noPai, VetorDadosArvore, i, stringAlvo);
    }

    menu(Dados, TabelaHash, DadosLinear, noPai);

    libera_Arvore(noPai);

    return 0;
}
