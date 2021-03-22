#include "wordHuntingFunctions.c"
#include "wordHuntingLib.h"



int main() {
	
	char pesq[MAX];
	char dictFile[MAX];
	char textB[MAX];
	

	
	FILE * arq;
	FILE * uarq;
	FILE * tarq;
	
	userMenu(pesq, textB, dictFile);
	int nlinhas = contalinhas(pesq);


	tarq = fopen("meutexto.txt", "w");



	uarq = openFile(pesq);
	arq = openFile(dictFile);
	
	//resultados da primeira busca
	huntWords(arq, uarq, pesq);
	fclose(arq);
	fclose(tarq);
		

	uarq = openFile(pesq);
	arq = openFile(dictFile);
	//resultados da segunda busca
	huntWords(arq, uarq, textB);

	
	fclose(arq);
	fclose(tarq);




}
