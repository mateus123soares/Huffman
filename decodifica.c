#include "decodifica.h"
#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "arvore.h"
#include "fila.h"
#include <string.h>
#include<unistd.h> 
#include <time.h>
#include <string.h>

void menu_decodifica(){
char arq_prob[100],arq_cod[100];
int i;
enum codigo_erro erro;
int alfabeto[ALFABETO]; /* última posição mantém o espaço */
prioridade * cabeca=NULL; /* elemento de menor prioridade, lista encadeada */
nodo * raiz; /* arvore com os nodos para gerar a codificacao */
  

	printf("=======Menu Principal===================\n");
   	printf("Informe nome do arquivo de probabilidades\n");
   	scanf("%s",arq_prob);
   	printf("Informe nome do arquivo codificado\n");
   	scanf("%s",arq_cod);
   	if ((erro = le_ocorrencias(arq_prob,alfabeto))!=ok){
	if (erro == nao_encontrado)
	  fprintf(stderr, "Nao pode abrir arquivo \n");
	else if (erro == formato_incorreto)
		fprintf(stderr, "Formato incorreto no arquivo %s\n");
	exit(1);
  }
  cabeca = gera_folhas(alfabeto);
  printf("=======gerando arvore===================\n");
  raiz = gera_arvore(cabeca); 
}


