//fUNÇÕES PRIMÁRIAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define MAX 173 //Maior palavra do mundo possui 173 letras

typedef struct 
{
    char letra;
    int inicio;
    int fim;
}Comp;

/*
Percorre todo o dicionario e salva a posicao de inicio e fim de cada letra
Complexidade - O(n), n = numero de elementos no dic.
*/
void dist(Comp Compes[], int *tamanhoArrayCompes, char dic[][MAX], int tamDic){

    int i = 0;

    char LetraInicial = dic[0][0];

    Comp CompMom;

    CompMom.letra = LetraInicial;
    CompMom.inicio = 0;

    for (i=0; i<tamDic-1; i++){
        LetraInicial = dic[i][0];
        if(LetraInicial != CompMom.letra)
        {
            CompMom.fim = i - 1;
            Compes[*tamanhoArrayCompes] = CompMom;
            *tamanhoArrayCompes = (*tamanhoArrayCompes) + 1;

            CompMom.letra = LetraInicial;
            CompMom.inicio = i;
        }
        else if(i == tamDic - 1)
        {
            CompMom.fim = i;
            Compes[*tamanhoArrayCompes] = CompMom;
            *tamanhoArrayCompes = (*tamanhoArrayCompes) + 1;
        }
    }

}

Comp resetCompMom(char palavra, Comp Compes[], int tamanhoArrayCompes){

    Comp CompMom = {' ',-1,-1};

    for(int i = 0; i < tamanhoArrayCompes; i++){
        CompMom = Compes[i];
        if(CompMom.letra == palavra){
            break;
        }
    }
        return CompMom;
}

/*
Complexidade - O(n + a), n = numero de palavras no dicionario, a = numero de palavras no arquivo de referencia
*/
//calcBOW(ver, Cont, dic, tamDic,arqbowTR);
void calcBOW(FILE *arqTR, int Cont[], char dic[][MAX], int tamDic, FILE* arqbowTR){

    int i;

    char palavra[MAX];
    Comp Compes[MAX];
    Comp CompMom;
    int tamanhoArrayCompes = 0;

        dist(Compes, &tamanhoArrayCompes, dic, tamDic); // O(n), n = palavras no dicionario

    while(fscanf(arqTR, "%s", palavra) != EOF){// O(a), a = palavras no arquivo de referencia

        fgetc(arqTR);

        format(palavra);

        CompMom = resetCompMom(palavra[0], Compes, tamanhoArrayCompes);// O(b), b = numero de indices, b <= n

        if(CompMom.inicio != -1){
            for(i=CompMom.inicio;i<=CompMom.fim;i++){ // O(c), c = numero de elementos no indice, c <= n
                if(strcmp(palavra, dic[i])==0){
                    Cont[i]++;
                }       

            }
        }

    } 

    for(i = 0; i< tamDic; i++){
        fprintf(arqTR, "%d %s\n", Cont[i], dic[i]);
    }
    // Complexidade total = O(n + a(b + c) + n) = O(n + a)
}


void format(char text[]) //Remover caracteres e deixar maiusculo
{
    text[strcspn(text, ",.!?;:")] = 0;

    for(int i = 0; i < strlen(text); i++){
        text[i] = tolower(text[i]);
    }
}

/*
criardic - O(n), n = numero de linhas no dicionario
*/
void cpyDic(FILE *arqDic, char dic[][MAX]){

    int i = 0;

    while(fscanf(arqDic, "%s", dic[i]) != EOF){
        fgetc(arqDic);
        format(dic[i]);
        i++;
    }

}

/*
contaLinhas - O(n), n = numero de caracteres no arquivo.
*/
//Contador de linhas
int numLinhas(FILE *arq) {

    char c;
    int tam = 0;
    
    while(!feof(arq))
    {
        c = fgetc(arq);
        if(c == '\n') tam++;
    }

    fseek(arq, 0, SEEK_SET);
    return tam;
}

//Leitura de dicionário
void readDic(FILE *arqDic, int *tamDic, char dic[][MAX]){

    char pesqDic[MAX];
    system("clear");
    printf("==================================\n");
    printf("=========NOME DO DICIONÁRIO=======\n");
    printf("==================================\n");

    printf("Arquivo do dicionário: ");
    scanf(" %[^\n]s", &pesqDic);
    
    arqDic = fopen(pesqDic, "r");
    if(arqDic == NULL){
        printf("Erro, não foi possível abrir o arquivo");
    }else{
        printf("%s foi aberto, pressione enter para continuar\n", pesqDic);
        *tamDic = numLinhas(arqDic); //calcular tamanho do dicionario
        cpyDic(arqDic, dic); //Copiar os arquivos do texto para um vetor de dicionario
    }

}


void bows(FILE * arqTR, int tamDic, char dic[][MAX], FILE *arqbowTR, int *Cont, char ver[2]){
 
    system("clear");
    printf("===================================\n");
    printf("====NOME DO TEXTO DE REFERENCIA====\n");
    printf("===================================\n");

    char pesqTR[MAX];

    printf("Arquivo do %s: ", ver);
    scanf(" %[^\n]s", &pesqTR);
    
    arqTR = fopen(pesqTR, "r");
    if(arqTR == NULL){
        printf("Erro, não foi possível abrir o arquivo");
    }else{

        printf("%s foi aberto\n", pesqTR);


            if(ver[2]== 'A'){ //TRA

                arqbowTR = fopen("bowA.txt","w");
            }
            else if (ver[2]=='B'){//TRB
                arqbowTR = fopen("bowB.txt","w");
            }    
        calcBOW(arqTR, Cont, dic, tamDic,arqbowTR);
        fclose(arqbowTR);
    }

    


}
void mostraBows(int *ContA, int *ContB, char dic[][MAX], int tamDic){
    //Complexidade - O(n), n = tamanho do dict.
    printf("    Palavras                 Texto A(#)    Texto B(#)\n");

    for(int i=0; i<tamDic; i++){
        if(ContA[i] + ContB[i] != 0){
            printf("%s\n", dic[i]);
            printf("                 %d", ContA[i]);
            printf("                                %d\n", ContB[i]);
        }
    }
}

void mBows(int tamDic, int *ContA, int *ContB, char dic[][MAX]){
    system("clear");
    printf("===================================\n");
    printf("===========EXIBIR BOWS=============\n");
    printf("===================================\n");


    mostraBows(ContA, ContB, dic, tamDic);

}

void dEuclides(int tamDic, char *ContA, char *ContB){
    system("clear");
    printf("===================================\n");
    printf("=========Distância Euclidiana======\n");
    printf("===================================\n");

    double s = 0;
    
    for(int i=0; i<tamDic; i++){
        s += pow(ContA[i] - ContB[i], 2);
    }
    double feuc = pow(s, 0.5);
    printf("A distância entre os dois textos é: %f\n", feuc);

}



