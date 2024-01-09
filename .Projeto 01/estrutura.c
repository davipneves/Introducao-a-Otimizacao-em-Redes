#include "estrutura.h"

Tgrafo* inicializa(void){
	return NULL;
}

Tgrafo* ins_no(Tgrafo *g, int no){
	Tgrafo *novo = (Tgrafo*) malloc(sizeof(Tgrafo));
	novo->no=no;
	novo->prim_viz=NULL;
	novo->prox=g;
	return novo;
}

void ins_aresta(Tgrafo *g, int no1, int no2, int custo){
	Tgrafo *p = busca_no(g, no1);
	if (!p || !busca_no(g,no2) || no1==no2) {
		printf("Erro\n");
		return;
	}
	Tviz *ant = NULL;
	Tviz *q = p->prim_viz;
	while(q){
		if (q->id == no2)
		{
			q->custo = custo;
			return;
		}
		ant = q;
		q = q->prox_viz;
	}
	Tviz *novo = (Tviz*) malloc (sizeof(Tviz));
	novo->prox_viz = NULL;
	novo->id = no2;
	novo->custo = custo;
	if (!ant)
		p->prim_viz = novo;
	else
		ant->prox_viz = novo;
}

Tgrafo* retira_no(Tgrafo *g, int no){
	Tgrafo *ant = NULL;
	Tgrafo *p = g;

	while ((p) && (p->no!=no) ){
		ant = p;
		p = p->prox;
	}

	if (!p){
		printf("Erro\n");
		return g;
	}
	Tviz *q= p->prim_viz;

	while (q) {
		int no2 = q->id;
		q = q->prox_viz;
		retira_aresta(g,no,no2);
		retira_aresta(g,no2,no);
	}

	if (!ant) 
		g = g->prox;
	else 
		ant->prox = p->prox;

	free(p);

	return g;
}

void retira_aresta(Tgrafo *g, int no1, int no2){
	Tgrafo *p = busca_no(g, no1);
	
	if (!p || !busca_no(g, no2)){
		printf("Erro\n");
		return;
	}
	
	Tviz *ant = NULL;
	Tviz *q = p->prim_viz;

	while( (q) && (q->id != no2) ){
		ant = q;
		q=q->prox_viz;
	}
	
	if (q){
		if (!ant)
			p->prim_viz = q->prox_viz;
		else
			ant->prox_viz = q->prox_viz;
	}

	free(q);
}

Tgrafo* leiaArquivo(char *file){
	FILE *arq = NULL;
	Tgrafo *g = inicializa();

	// Abre um arquivo TEXTO para LEITURA
	arq = fopen(file, "rt");
	if (arq == NULL)  // Se houve erro na abertura
	{
    	printf("Problemas na abertura do arquivo\n");
    	return NULL;
    }

    //printf("%s\n", file);

  	int nvertices, narestas, no1 , no2, custo, i;
  	//le o numero de vertices
  	fscanf(arq, "%i", &nvertices);

  	//le os vertices
  	for (i = 0; i < nvertices; i++){
  		fscanf(arq, "%i", &no1);
  		g = ins_no(g,no1);
  	}

  	//le o arquivo enquanto nao chega ao final
  	for (i = 0; !feof(arq) ; i++){
  		//le a aresta e insere nos dois nos
  		fscanf(arq, "%i %i %i",&no1, &no2, &custo);
  		ins_aresta(g, no1, no2, custo);
  		ins_aresta(g, no2, no1, custo);
  	}

  	fclose(arq);
  	return g;
}

void imprime(Tgrafo *g){
	if (!g){
		printf("\nGrafo Vazio\n");
		return;
	}

	Tgrafo *p = g;
	while (p) {
		printf("Nó: %i\n", p->no);
		Tviz *q = p->prim_viz;
		while(q){
			printf("Vizinho %d \tcusto %d\n", q->id,q->custo);
			q = q->prox_viz;
		}
		p=p->prox;
	}
}

void imprimeGrafo(Tgrafo *g, char *file){
	Tgrafo *p = inicializa();
	Tgrafo *ant = inicializa();
	Tviz *w = NULL;
	FILE *arq = NULL;
	int controle=0;

	// Abre um arquivo TEXTO para LEITURA
	arq = fopen(file, "w");
	if (arq == NULL)  // Se houve erro na abertura
	{
    	printf("Problemas na abertura do arquivo\n");
    	return;
    }

    fprintf(arq, "%i\n", qtd_nos(g) );
    p=g;
    while(p){
    	fprintf(arq, "%i\n", p->no );
    	p=p->prox;
    }

    p=g;
    while(p){
    	w = p->prim_viz;
    	while(w){
    		ant = g;
    		controle=0;
    		while(ant!=p){
    			if (w->id == ant->no)
	    			controle++;
	    		ant=ant->prox;
    		}
    		//imprime se houver nó anteriormente
    		if (controle>0)
    			fprintf(arq, "%i %i %i\n", p->no, w->id, w->custo );
    		w = w->prox_viz;
    	}
    	p=p->prox;
    }

    fclose(arq);
}

int qtd_nos(Tgrafo *g){
    Tgrafo *p = g;
	if (!g)
		return 0;

	int count=0;
	while (p){
		count++;
		p=p->prox;
	}

	return count;
}

// retorna null caso não encontre
Tgrafo* busca_no(Tgrafo *g, int no){
	Tgrafo *p = g;
	while ( (p) && (p->no != no))
		p = p->prox;
	return p;
}

void libera(Tgrafo **g){
	while (*g)
		*g = retira_no(*g,(*g)->no);
}


void bfs(Tgrafo *g) {
    Fila fila;
    inicializarFila(&fila);
	Tgrafo *aux = g;

	if(!g){
		printf("Grafo Nulo");
		return NULL;
	}

	int n = qtd_nos(g);
	int i, j;
	int visitados[2][n];

	visitados[0][i] = aux->no; //atribuindo o rótulo do primeiro nó
	visitado[1][i] = 1; //marcando como visitado
	aux = aux->prox;

	for (i=0; i<n; i++){
		visitados[0][i] = aux->no; //atribuindo o rótulo
		visitado[1][i] = 0; //marcando como não visitado
		aux = aux->prox;
	}

    enfileirar(&fila, visitados[0][0]);

    while (!filaVazia(&fila)) {
        int noAtual = desenfileirar(&fila);
        printf("%d ", noAtual);

        Tviz *vizinho = g[noAtual].prim_viz;
        while (vizinho != NULL) {
			//encontra em que posição está o vizinho a ser expandido
			for (i=0; i<n; i++){
				if (visitados[0][i]==vizinho->id)
					break;
			}

			//verifica se ele já é visitado
            if (!visitados[i]) {
                visitados[i] = 1;
                enfileirar(&fila, vizinho->id);
            }
            vizinho = vizinho->prox_viz;
        }
    }

	//verifica se todos foram visitados
	for (i=0; i<n; i++){
		if (!visitados[0][i]){
			printf("Grafo Não é conexo\n");
			return;
		}
	}

	printf("grafo conexo!\n");

}

