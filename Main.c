#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "pfuncoes.h"
#include <math.h>

int main(){
    int esc;
    int tamDic;
    int *ContA, *ContB;

    char dic [10000][MAX];
    FILE *arqDic = NULL; //dicionario
    FILE *arqTRA = NULL; //ref a
    FILE *arqTRB = NULL; //ref b
    FILE *arqbowTRA = NULL; //bow tra
    FILE *arqbowTRB = NULL; //bow trb


    do{
        printf("==========BAG OF WORDS=========\n");
        printf("1- Inserir arquivo de dicionário\n");
        printf("2- Inserir Texto de referência A\n");
        printf("3- Inserir Texto de referência B\n");
        printf("4- Exibir BOWs de TRA e TRB\n");
        printf("5- Exibir similaridade entre os textos\n");
        printf("6 - SAIR\n");
        printf("Opção escolhida: ");
        scanf("%d", &esc);

        switch (esc)
        {
        case 1: //Ler arquivo dicionario
            readDic(arqDic, &tamDic, dic);
            //Complexidade total case1 - O(n), n = numero de palavras no dicionario.
            break;
        case 2:
            bows(arqTRA, tamDic, dic, arqbowTRA, ContA, "TRA");
            break;
        case 3:
            bows(arqTRB, tamDic, dic, arqbowTRB, ContA, "TRB");
            break;
        case 4:
            mBows(tamDic, ContA, ContB, dic);
            break;
        case 5:
            dEuclides(tamDic, ContA, ContB);
            break;    
        case 6:
            printf("Encerrando...");
            return 0;    
        default:
            break;
        }

    }while(esc>0 || esc <7);

}