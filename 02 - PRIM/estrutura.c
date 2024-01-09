#include "estrutura.h"

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


Tgrafo* inicializa(void){
	return NULL;
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

// retorna null caso não encontre
Tgrafo* busca_no(Tgrafo *g, int no){
	Tgrafo *p = g;
	while ( (p) && (p->no != no))
		p = p->prox;
	return p;
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

// foi utilizado o prim tanto para verificar se o grafo é conexo quanto para gerar a AGM
Tgrafo* AGM(Tgrafo *g){
	Tgrafo *agm = inicializa();
	Tgrafo *p = inicializa();
	Tviz *w = NULL;

	if(!g){
		printf("Grafo Nulo");
		return NULL;
	}

	int numeroNosAGM = 1, numeroNosG = qtd_nos(g);
	int i;
	//aresta a ser inserida por iteração
	int aresta[3] = { -1, -1, -1};
	
	//primeiro nó da agm
	agm = ins_no(agm,g->no);

	//enquanto a AGM não tiver a mesma quantidade de nós que o grafo
	while(numeroNosAGM != numeroNosG){
		p=g;
		while (p){
			//verifica se é um nó da AGM
			if ( busca_no( agm, p->no)){
				w = p->prim_viz;
				//verifica todas as arestas do nó
				while(w){
					//verifica se não haverá ciclo com a aresta
					if(!busca_no(agm,w->id)){
						//se ainda não ha uma aresta a ser adicionada
						if (aresta[2]==-1)
						{
							aresta[0] = p->no;
							aresta[1] = w->id;
							aresta[2] = w->custo;
						} 
						// se ha uma aresta a ser adicionada porem é pior que a atual
						if (aresta[2] > w->custo){
							aresta[0] = p->no;
							aresta[1] = w->id;
							aresta[2] = w->custo;
						}
					}
					w = w->prox_viz;
				}
			}
			p = p->prox;
		}

		//não consegui encontrar aresta para inserir na AGM
		if (aresta[0]==-1)
		{
			printf("\nGrafo não conexo\n");
			libera(&agm);
			return NULL;
		}

		agm = ins_no(agm, aresta[1]);
		ins_aresta(agm, aresta[0], aresta[1], aresta[2]);
		ins_aresta(agm, aresta[1], aresta[0], aresta[2]);
		aresta[0] = aresta[1] = aresta [2] = -1;
		numeroNosAGM++;
	}
	return agm;
}



Tviz* insere_ordenado(Tviz *w, int no, int custo){
	Tviz *ant = NULL;
	Tviz *q = w;

	while(q){
		if (q->custo > custo)
			break;

		ant = q;
		q = q->prox_viz;
	}

	Tviz *novo = (Tviz*) malloc (sizeof(Tviz));
	novo->prox_viz = NULL;
	novo->id = no;
	novo->custo = custo;
	
	if (!w) { 
		w = novo;
	} else if (!ant){
		novo->prox_viz = w;
		w = novo;
	} else{
		ant->prox_viz = novo;
		novo->prox_viz = q;
	}
	return w;
}

//verifica se é um nó ja visitado
int no_visitado(int *x, int no, int tam){
	int i;
	for ( i = 0; i < tam; i++) {
		if (x[i]==no)
			return 1;
	}
	return 0;
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

void libera(Tgrafo **g){
	while (*g)
		*g = retira_no(*g,(*g)->no);
}
