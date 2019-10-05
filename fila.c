#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "huffman.h"
#include "arvore.h"

Desc_fila *Ini_fila(void){
	Desc_fila *f =(Desc_fila*)malloc(sizeof(Desc_fila));
	f->ini=NULL;
	f->fim=NULL;
	f->quant=0;
	return f;
}

void coloca_fila(Desc_fila *f,int v,struct nodo *dados){
	Fila *novo=(Fila*)malloc(sizeof(Fila));
	novo->chave=v;
	novo->dados=dados;
	novo->prox=NULL;
		if(f->ini==NULL && f->fim==NULL){
			f->ini=novo;
			f->fim=novo;
			f->quant++;
		}
		else{
			f->fim->prox=novo;
			f->fim=novo;
			f->quant++;
		}
}

struct nodo *tira_fila(Desc_fila *f){
	Fila *aux;
	nodo *v;
	if(f->ini->prox==NULL){
		aux=f->ini;
		v=aux->dados;
		f->ini=NULL;
		f->fim=NULL;
		free(aux);
		f->quant--;
		return v;
	}
	else{
		aux=f->ini;
		v=aux->dados;
		f->ini=aux->prox;
		free(aux);
		f->quant--;
		return v;
	}
}

void mostra_fila(Desc_fila *f){
	Fila *aux=f->ini;
	while(aux != NULL){
		printf("[%d]\n",aux->chave);
		aux=aux->prox;
	}
}