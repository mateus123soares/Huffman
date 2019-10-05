/** Funcoes basicas para arvores binarias de pesquisa com ponteiros 
 *  @author pilla@ufpel.edu.br
 *  @memo para Estrutura de Dados I 
 */

#define ALFABETO 27 /* número de caracteres */

/** codigos de erro */
enum codigo_erro { ok = 0, nao_encontrado, chave_existe, erro_malloc, parametro_null, formato_incorreto };


/** O que estamos armazenado
 */
typedef struct nodo{
	char caracter;
	unsigned int codigo; /* codigo pode ter mais que 8 bits */
	char comprimento; /* número de bits do código */
	int ocorrencias;  /* porcentagem de ocorrencia em textos */
	struct nodo * dir, *esq;
} nodo;


/** Estrutura auxiliar para uma lista ordenada de nodos */
typedef struct prioridade{
	nodo * um_nodo;
	struct prioridade * prox;
} prioridade;


enum codigo_erro conta_ocorrencias(char *arquivo, int * contadores,int *totalCaracteres);
enum codigo_erro le_ocorrencias(char *arquivo, int * contadores);
void imprime_ocorrencias(int * contador);
void gera_probabilidades(char *arquivoSaida,int *contadores, int total);
