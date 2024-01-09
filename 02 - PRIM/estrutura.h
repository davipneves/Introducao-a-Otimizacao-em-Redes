#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vizinho.h"

typedef struct grafo {
	int no;
	Tviz * prim_viz;
	struct grafo * prox; 
} Tgrafo;

Tgrafo* leiaArquivo(char *file);

void imprimeGrafo(Tgrafo *g, char *file);

Tgrafo* inicializa(void);

void imprime(Tgrafo *g);

// retorna null caso não encontre
Tgrafo* busca_no(Tgrafo *g, int no);

Tgrafo* ins_no(Tgrafo *g, int no);

void ins_aresta(Tgrafo *g, int no1, int no2, int custo);

void retira_aresta(Tgrafo *g, int no1, int no2);

Tgrafo* retira_no(Tgrafo *g, int no);

//se for null arvore não conexa
Tgrafo* AGM(Tgrafo *g);

Tviz* insere_ordenado(Tviz *w, int no2, int custo);

int no_visitado(int *x, int no, int tam);

int qtd_nos(Tgrafo *g);

void libera(Tgrafo **g);

#endif //ESTRUTURA_H
