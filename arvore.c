#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
//-==================================GERENCIA DA ARVORE======================================-/

/** @author pilla@ufpel.edu.br 
 *  @description insere em uma lista ordenada por probabilidade de ocorrência
 *  @param cabeca primeiro elemento da lista
 *  @param um_nodo nodo a ser inserido
 */

prioridade * insere_ordenado(prioridade * cabeca, nodo * um_nodo){
  prioridade * iterador = cabeca;
  prioridade * anterior = NULL;
  prioridade * novo = (prioridade*) malloc(sizeof(prioridade));
  
  if (!novo){ /* erro no malloc */
	return (NULL);
  }
  novo->um_nodo = um_nodo;
  novo->prox = NULL;
  /* se cabeca for NULL, entao esse eh o primeiro nodo */
  if (cabeca==NULL){
	return novo;
  }
  //printf("Inserindo %c\n",um_nodo->caracter+'A');
  while(iterador){
	if (iterador->um_nodo->ocorrencias > um_nodo->ocorrencias){ /* deve ser inserido antes */
	  novo->prox = iterador;
	  if (anterior){
		anterior->prox = novo;
		return cabeca; /* nao mudou a cabeca */
	  }
	  else{
		return novo; /* nova cabeca */
	  }
	}
	anterior = iterador;
    iterador = iterador->prox;
  }
  anterior->prox = novo;
  
  return cabeca;

}

/** @author pilla@ufpel.edu.br
  * @description gera as folhas da arvore e as coloca em ordem numa lista
  * @param contadores vetor com as frequencias de cada letra 
  * @return lista ordenada de folhas
  */
prioridade * gera_folhas(int * contadores){
  int i;
  nodo * um_nodo;
  prioridade * cabeca = NULL;
  
  for(i=0;i<ALFABETO;i=i+1){
	um_nodo = (nodo *) malloc(sizeof (nodo));
	if (um_nodo==NULL){ /* malloc falhou */
	  return NULL;
	}
	um_nodo->caracter = i;
	um_nodo->ocorrencias = contadores[i];
	um_nodo->codigo = 0;
	um_nodo->comprimento = 0;
	um_nodo->dir = um_nodo->esq = NULL;
	cabeca = insere_ordenado(cabeca,um_nodo);

  }
 
  return cabeca;

}


/** @author pilla@ufpel.edu.br
  * @description imprime a lista ordenada de nodos
  * @param cabeca primeiro elemento da lista
  */

void imprime_conjunto_P(prioridade * cabeca){

  prioridade * iterador = cabeca;
  int i = 1;
  
  while (iterador){
	printf("Elemento %d\t ocorrencias\t%d\%\t caracter \'%c\'\n",i,iterador->um_nodo->ocorrencias, iterador->um_nodo->caracter==ALFABETO-1? ' ' : iterador->um_nodo->caracter+'A');
	iterador = iterador->prox;
	i = i + 1;
  }


}

/** @author pilla@ufpel.edu.br
  * @description implementa  o algoritmo para gerar a arvore
  * @param cabeca primeiro elemento da lista ordenada de nodos
  * @return raiz da arvore gerada
  */
nodo * gera_arvore(prioridade * cabeca){
  nodo *um_nodo, *Sdir, *Sesq;
  prioridade * temp;
  /* se nao houver fila, nao gera arvore */
  if (cabeca==NULL){
	return NULL; 
  }

  /* enquanto houver mais de um elemento na lista */
  while (cabeca && cabeca->prox){
	Sdir = cabeca->um_nodo;
	Sesq = cabeca->prox->um_nodo;
	temp = cabeca->prox;
	free(cabeca);
	cabeca = temp->prox;
	free(temp);
    um_nodo = (nodo *) malloc(sizeof(nodo));
	if (um_nodo == NULL) /* erro! */
	  return NULL;
	
	um_nodo->dir = Sdir;
	um_nodo->esq = Sesq;
	um_nodo->ocorrencias = Sdir->ocorrencias + Sesq->ocorrencias;
	cabeca=insere_ordenado(cabeca, um_nodo);  
	printf(" +++ Adicionado nodo com OcorrenciaTotal %d/%x, somando %d/%x e %d/%x\n",um_nodo->ocorrencias,um_nodo, Sdir->ocorrencias, Sdir, Sesq->ocorrencias, Sesq);
  }
  return um_nodo;
}
