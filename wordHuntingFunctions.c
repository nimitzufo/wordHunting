#include "wordHuntingLib.h"


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
