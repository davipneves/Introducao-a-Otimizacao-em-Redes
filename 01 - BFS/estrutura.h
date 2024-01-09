#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fila.h"
#include "vizinho.h"

typedef struct grafo {
	int no;
	Tviz * prim_viz;
	struct grafo * prox; 
} Tgrafo;


Tgrafo* inicializa(void);

Tgrafo* ins_no(Tgrafo *g, int no);

void ins_aresta(Tgrafo *g, int no1, int no2, int custo);

Tgrafo* retira_no(Tgrafo *g, int no);

void retira_aresta(Tgrafo *g, int no1, int no2);

Tgrafo* leiaArquivo(char *file);

//imprime na tela o grafo
void imprime(Tgrafo *g);

//Imprime/salva o grafo no arquivo
void imprimeGrafo(Tgrafo *g, char *file);

int qtd_nos(Tgrafo *g);

// retorna null caso não encontre
Tgrafo* busca_no(Tgrafo *g, int no);

void libera(Tgrafo **g);

void bfsChatGPT(Tgrafo *g, int inicio, int numVertices) ;

void bfs(Tgrafo *g);

#endif //ESTRUTURA_H
