/** Funcoes basicas para implementar códigos de Huffman
 *  @author pilla@ufpel.edu.br
 *  @memo para Estrutura de Dados I 
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "huffman.h"



//-===========================GERAÇÂO DA ESTATISTICA DO DOCUMENTO===================================-/
/** @author pilla@ufpel.edu.br
 *  @description função para copiar de uma struct elemento para outra 
 *  @param origem ponteiro para origem
 *  @param destino ponteiro para destino
 *  @return erro
 */
enum codigo_erro conta_ocorrencias(char *arquivo, int * contadores,int *totalCaracteres){
  /* abre o arquivo */
  FILE * entrada; 
  char lido;
  
  entrada = fopen(arquivo, "r");
  if (!entrada){
	return nao_encontrado;
  }
  int caracteresContador=0;
  while ((lido=fgetc(entrada))!=EOF){ /* varre arquivo lendo caracter a caracter, podia ser mais otimizado */
	//printf("lido %c\n",lido);
	if (lido == ' '){
	  caracteresContador++;
	  contadores[ALFABETO-1] = contadores[ALFABETO-1] + 1; 
	}
	else{ 
	  if ((lido >= 'A') && (lido <= 'Z')){ //verifica se o dado lido está no range ascii esperado
        caracteresContador++;
		lido = lido - 'A'; 
		contadores[lido] = contadores[lido]+1;
	  }
    }
  }
  fclose(entrada);
  printf("total %d\n",caracteresContador);
  *totalCaracteres = caracteresContador;
  return ok;

}

/** @author pilla@ufpel.edu.br 
 *  @description Le arquivo com distribuicao de probabilidades, um caracter por linha 
 *  @param nome do arquivo
 *  @param contadores para retornar as probabilidades 
 *  @return erro
 */
enum codigo_erro le_ocorrencias(char *arquivo, int * contadores){
  /* abre o arquivo */
  FILE * entrada; 
  int i = 0; 
  int soma = 0; /* para verificar se soma 100 */
 
  
  entrada = fopen(arquivo, "r");
  if (!entrada){
	return nao_encontrado;
  }
  
  while (!feof(entrada)){ /* varre arquivo ate seu fim */
	fscanf(entrada, "%d\n",&contadores[i]); //faz a leitura do elemento (porcentagem) do arquivo de probabilidade
	printf("Caracter \'%c\'\t%d\%\n",(i==ALFABETO-1)?' ':'A'+i, contadores[i]); //lógica para printar corretamente o caractere e o valor da contagem
	soma = soma + contadores[i]; //soma as porcentagens para ver se existe 100%
	i = i + 1;
  }
  
  printf("Total\t%d\%\n",soma);
  
  if ((i!=ALFABETO)||(!feof(entrada))||(soma!=100)){
    /* faltou ou sobrou coisa no arquivo */
	fclose(entrada);
	return formato_incorreto;
  }
    
  fclose(entrada);
  return ok;

}

/** @author pilla@ufpel.edu.br 
 *  @description imprime vetor com ocorrencias de caracteres
 *  @param contador vetor com contagem de ocorrencias
 */
void imprime_ocorrencias(int * contador){
	int i;
	printf("Ocorrencias \n\n");
	for (i=0;i<ALFABETO-1;i++){
	  printf("%c %d\n",'A'+i,contador[i]);
	}
	printf("Espaco %d\n",contador[ALFABETO-1]);
}

/** @author juliodomingus@unipampa.edu.br 
 *  @description gera o arquivo de probabilidades do texto lido
 *  @param nome do arquivo de saida de probabilidades
 *  @param contador vetor com contagem de ocorrencias
 */
void gera_probabilidades(char *arquivoSaida,int *alfabeto, int total){
	int i;
	FILE *arqSaida = fopen(arquivoSaida,"w");
	if(arqSaida  == NULL){
		printf("ERRO ao abrir arquivo\n");
		return nao_encontrado;
	}
	printf("==========gerando arquivo de probabilidades===========\n");
	int totalPorcentagem = 0; //variável para manter os 100% adicionando o que falta no espaço
 	for(i=0;i<ALFABETO-1;i++){
		float porcentagem = floor(((float)alfabeto[i]*100)/(float)total); //trunca para baixo a porcentagem
		fprintf(arqSaida,"%d\n",(int)porcentagem);		
		totalPorcentagem = totalPorcentagem+(int)porcentagem;
	}
	//trata o espaço e o que falta da porcentagem para 100%
	totalPorcentagem = (100-totalPorcentagem);
	fprintf(arqSaida,"%d\n",(int)totalPorcentagem);		
	fclose(arqSaida);
}
