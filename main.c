// Implementação de huffman
// autor: Mateus Soares (mateus123soares@hotmail.com) Marcelo Cordeiro (marcelo_1411@hotmail.com)
// Data: 06/07/2018

#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"
#include "arvore.h"
#include "fila.h"
#include <string.h>
#include<unistd.h> 
#include <time.h>
#include "decodifica.h"

void imprimirPre(nodo *a);
void *BFS(nodo *a);
int Gera_codigo(nodo *a,int l,char *buffer,int i);
void Gera_arq(nodo *raiz);
void menu_decodifica();
nodo *realiza_decode(nodo *a,nodo *raiz,char *buffer);

int main(int argc, char ** argv){
  int i;
  enum codigo_erro erro;
  int alfabeto[ALFABETO]; /* última posição mantém o espaço */
  prioridade * cabeca=NULL; /* elemento de menor prioridade, lista encadeada */
  nodo * raiz; /* arvore com os nodos para gerar a codificacao */
  
  /* primeiro parâmetro é o arquivo de entrada de prioridades, segundo é o arquivo de saída */
  if (argc!=3){
	fprintf(stderr,"Uso: %s entradaProbabilidades saida\n",argv[0]); /* argv[0] tem o nome do executável invocado */
	exit(1);
  }
  /* inicializa contadores com zero, para depois contar ocorrências neste vetor */
  for (i=0;i<ALFABETO;i++){
	alfabeto[i] = 0;
  }
  int total=0;
  //PARSER DO ARQUIVO A SER CODIFICADO REALIZANDO A CONTAGEM TOTAL DE CARACTERES (A-Z-ESPAÇO) E A CONTAGEM INDIVIDUALIZADA
  conta_ocorrencias(argv[1],alfabeto,&total);
  //imprime_ocorrencias(alfabeto);
  //GERA UM ARQUIVO DE PROBABILIDADES COM OS VALORES DA CONTAGEM INDIVIDUALIZADA POR PORCENTAGEM EM RELACAO A TODOS OS CARACTERES
  gera_probabilidades(argv[2],alfabeto,total);
  /* Lê arquivo para calcular probabilidade de ocorrência de um caracter */
  if ((erro = le_ocorrencias(argv[2],alfabeto))!=ok){
	if (erro == nao_encontrado)
	  fprintf(stderr, "Nao pode abrir arquivo %s\n",argv[1]);
	else if (erro == formato_incorreto)
		fprintf(stderr, "Formato incorreto no arquivo %s\n",argv[1]);
	exit(1);
  }
  imprime_ocorrencias(alfabeto);
  /* Gera lista com folhas ordenadas por ordem crescente de ocorrencia */
   printf("=======lista encadeada de elementos===================\n");
  cabeca = gera_folhas(alfabeto);
  //IMPRIME A LISTA DE FOLHAS (LISTA ENCADEADA)
  imprime_conjunto_P(cabeca);
  
  /* Gera árvore */
   //APLICA AS TRANSFORMAÇÕES RETIRANDO DA LISTA ENCADEADA E INSERINDO NA RAIZ COMO SE FOSSE UMA ARVORE
   printf("=======gerando arvore===================\n");
   raiz = gera_arvore(cabeca);
   printf("raiz da %x\n",raiz);
   //Funções do programa
   	int op;
   	while (op != 5){
   		printf("=======Menu Principal===================\n");
   		printf("1 - Imprimir em Pré-ordem\n");
   		printf("2 - Imprimir árvore em amplitude \n");
   		printf("3 - Codificar Mensagem \n");
   		printf("4 - Decodificar mensagem\n");
   		printf("5 - Sair \n");
   		scanf("%d",&op);
   		switch(op){
   			case 1:
   				imprimirPre(raiz);
   				printf("\n");
   			break;
   			case 2:
   				BFS(raiz);
   				printf("\n");
   			break;
   			case 3:
   				Gera_arq(raiz);
   			break;
   			case 4:
          menu_decodifica();
   			break;
   			case 5:
   			break;
   			default:
   			printf("Opção invalida\n");
   			break;
   		}
	}
}

void imprimirPre(nodo *a){
  if(a != NULL){
    printf("<%d", a->ocorrencias);
      if(a->esq == NULL || a->dir == NULL){
        printf("[%c]",a->caracter+'A');
      }
    imprimirPre(a->esq);
    imprimirPre(a->dir);
    printf(">");
  }
  else{
    printf("<>");
  }
}

void *BFS(nodo *a){
    nodo *z;
    Desc_fila *f;
    f=Ini_fila();
    coloca_fila(f,15,a);
    while (f->quant != 0) {
       a=tira_fila(f);
       printf("%d ", a->ocorrencias);
       if (a->esq != NULL) coloca_fila(f,15,a->esq);
       if (a->dir != NULL) coloca_fila(f,15,a->dir); 
    }
}

int Gera_codigo(nodo *a,int l,char *buffer,int i){
  if(a->caracter == l && a->esq==NULL && a->dir == NULL){
    buffer[i]='\0';
  	return 1;
  }
  else{
    int encontrado = 0;
        if (a->esq != NULL){
            buffer[i] = '0';
			encontrado = Gera_codigo(a->esq,l,buffer,i + 1);
        }
        if (encontrado==0 && a->dir){
            buffer[i] = '1';
            encontrado = Gera_codigo(a->dir,l,buffer,i+1);
        }
        if (encontrado ==0){
            buffer[i] = '\0';
        }
        return encontrado;
    }
}


/** @author mateus123soares@hotmail.com 
 *  @description Le arquivo com a mensagem a ser decodificada
 *  @testa se é um espaço ou um caractere
 *  @chama função que retorna o codigo em binario da arvore 
 *  @salva no arquivo txt criado
 */

void Gera_arq(nodo *a){
nodo *aux;
FILE *entrada;
FILE *msg;
char buffer[1024]={0};
char lido,i,ant;
int x;
entrada = fopen("entrada.txt", "r");	
msg=fopen("msgcodificada.txt","w");
aux=a;	
    while ((lido=fgetc(entrada))!=EOF){
      if(ant != lido){
		if (lido == ' '){
			Gera_codigo(aux,26,buffer,0);
			fprintf(msg,"%s",buffer);
		}
		else{
			i=0;
			x=0;
			while(i != lido){
				i='A'+x;
				x++;
			}
			Gera_codigo(aux,x-1,buffer,0);
			fprintf(msg,"%s",buffer);
		}
    ant=lido;
    aux=a;
    }
    else{
      fprintf(msg,"%s",buffer);
    }
	}
	fclose(entrada);
	fclose(msg);
	char lido2;
	msg=fopen("msgcodificada.txt","r");
	entrada = fopen("entrada.txt", "r");
	printf("=========Mensagem a ser codificada ============\n");
	while ((lido=fgetc(entrada))!=EOF){
		printf("%c",lido);
	}
	x=0;
	printf("\n");
	printf("=========Mensagem Codificada============\n");
	while ((lido2=fgetc(msg))!=EOF){
		printf("%c",lido2);
	}
	printf("\n");
	fclose(entrada);
	fclose(msg);
	printf("\n");
  printf("Mensagem Codificada com sucesso \n");
}


void menu_decodifica(){
char arq_prob[100],arq_cod[100];
int i,x=0;
FILE *arq;
FILE *arq2;
char lido;
enum codigo_erro erro;
int alfabeto[ALFABETO]; /* última posição mantém o espaço */
prioridade * cabeca=NULL; /* elemento de menor prioridade, lista encadeada */
nodo * raiz; /* arvore com os nodos para gerar a codificacao */
nodo *aux;

  printf("=======Menu Principal===================\n");
    printf("Informe nome do arquivo de probabilidades\n");
    scanf("%s",arq_prob);
    strcpy(arq_prob,"saida.txt");
    printf("Informe nome do arquivo codificado\n");
    scanf("%s",arq_cod);
    strcpy(arq_cod,"msgcodificada.txt");
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
  // Gerando arquivo 
  aux=raiz;
  arq=fopen(arq_cod,"r");
  arq2=fopen("original.txt","w");
  char buffer[2]={0};
  while((lido=fgetc(arq))!=EOF){
    if(lido == '0'){
        aux=realiza_decode(aux->esq,raiz,buffer);
      }
    else{
        aux=realiza_decode(aux->dir,raiz,buffer);
      }
      fprintf(arq2,"%s",buffer);
      buffer[0]='\0';
    }
    fclose(arq2);
    fclose(arq);
    printf("\n");
    printf("=======Decodificação realizada com sucesso===================\n");
    printf("\n");
}
nodo *realiza_decode(nodo *a,nodo *raiz,char *buffer){
   if(a->esq == NULL && a->dir == NULL){
      buffer[0]=a->caracter==26? ' ' : a->caracter+'A';
      buffer[1]='\0';
      return raiz;
   }
   else{
    return a;
   }
}