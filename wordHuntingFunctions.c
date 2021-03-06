#include "wordHuntingLib.h"

void userMenu(char *textOne, char * textTwo, char * dictFile){
	printf("Nome do primeiro arquivo: ");
	scanf("%s", textOne);	
	printf("Nome do segundo arquivo: ");
	scanf("%s", textTwo);
	printf("Nome do arquivo do dicionário de palavras: ");
	scanf("%s", dictFile);
  
}

FILE *openFile(char *pointerFileName){
	fopen(pointerFileName, "r");
	
	if (pointerFileName == NULL) {
		printf("Erro ao abrir o arquivo");
		exit(1);
	}
}



int contalinhas(char * pesq) {
  FILE * arqCL; //Arquivo conta linhas

  char c, letra = '\n';
  int contaLinha;

  arqCL = fopen(pesq, "r"); //Abrindo arquivo solicitado pelo usuário
  if (arqCL != NULL) {
    while (fread( & c, sizeof(char), 1, arqCL)) {
      if (c == letra) {
        contaLinha++;
      }
    }
  } else {
    printf("Erro no arquivo");
    return 0;
  }
  fclose(arqCL);
  return (contaLinha + 1); //+1 pois a quantidade de \n é igual a linhas-1

}

void huntWords(FILE *arq, FILE * uarq, char *pesq){

	while (!feof(arq)) {

		int i, j, k, tam, tam1, l = 0, contador = 0;
		char palavras[MAX][MAX];
		char buffer[nlinhas][MAX];
		char resul[nlinhas];
		char dicpalavra[MAX];
		char ch;
		int qt = 0;

		fgets(dicpalavra, MAX, arq);
		
		dicpalavra[strlen(dicpalavra) - 1] = dicpalavra[strlen(dicpalavra)]; //Retira o \0 do fgets
		tam = strlen(dicpalavra);
		
		for (i = 0; i < tam; i++) { //Convertendo palavras do dic em CapsLock
			dicpalavra[i] = toupper(dicpalavra[i]);
		}
		
		qt = 0;

		//dicpalavra é a palavra a ser pesquisada no texto

		uarq = fopen(pesq, "r"); //Abrindo o arquivo dentro do ciclo, para que ele SEMPRE volte a linha inicial para rodar novamente o texto
		
		if (uarq == NULL) {
			printf("Erro ao abrir o arquivo");
			return (0);
		}

		while (fscanf(uarq, "%s", palavras[contador]) != EOF && fscanf(uarq, "%c", & ch) != EOF) {

		tam1 = strlen(palavras[contador]); //RETIRANDO CARACTERES DO FINAL DO TEXTO
		
		if (palavras[contador][tam1] == '.' || palavras[contador][tam1] == ',' ||
			palavras[contador][tam1] == ';' || palavras[contador][tam1] == ':' ||
			palavras[contador][tam1] == '?' || palavras[contador][tam1] == '-') {
				
				palavras[contador][strlen(palavras) - 1] = palavras[contador][strlen(palavras)];
		} //FIM RETIRANDO CARACTERES DO FINAL DO TEXTO

		for (i = 0; i < tam1; i++) { //Convertendo palavras do dic em CapsLock
			palavras[contador][i] = toupper(palavras[contador][i]);
		} //FIM CONVERTENDO PALAVRAS DO DIC EM CAPSLOCK

		if (strcmp(palavras[contador], dicpalavra) == 0) {
			qt++;
			printf("A palavra %s está no texto\n", palavras[contador]);
		} else
			contador++;
		}
		
		fclose(uarq); //Fechando o arquivo dentro do ciclo, para que ele SEMPRE volte a linha inicial para rodar novamente o texto

		memset(palavras, 0, sizeof(palavras)); //Resetando vetor palavras
		contador = 0; //Redefinindo contador

		printf("A palavra %s foi encontrada %d no texto\n", dicpalavra, qt);
		memset(dicpalavra, 0, sizeof(dicpalavra));

	}

}
