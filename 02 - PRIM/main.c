#include "estrutura.h"
#include <string.h>

int main(int argc, char *argv[])
{
	Tgrafo *g, *agm;
	int **cm;
	int i, j, op;
	char no[20], no2[20], custo[20];

	agm  = inicializa();

	g = leiaArquivo(argv[1]);

	do {

		printf("\n\n");
		printf("##############################################\n");
		printf("#\t 1 - Inserir nó                      #\n");
		printf("#\t 2 - Inserir aresta                  #\n");
		printf("#\t 3 - Remover nó                      #\n");
		printf("#\t 4 - Remover aresta                  #\n");
		printf("#\t 5 - Verificar se é conexo/AGM       #\n");
		printf("#\t 6 - Imprimir grafo                  #\n");
		printf("#\t 7 - Libera grafo                    #\n");
		printf("##############################################\n");
		printf("#                                            #\n");
		printf("#\t 0 - Para sair                       #\n");
		printf("#                                            #\n");
		printf("##############################################\n");
		printf("\n\n");


		scanf("%i", &op);



		switch (op){
			case 0:
				break;
			case 1:
				printf("Digite o valor do nó que deseja inserir\n");
				scanf(" %s", no);
				if (atoi(no)>0 && !busca_no(g, atoi(no)))
					g = ins_no(g, atoi(no));
				else
					printf("Erro\n");
				break;
			case 2:
				printf("Digite o 1º nó da aresta\n");
				scanf(" %s", no);
				printf("Digite o 2º nó da aresta\n");
				scanf(" %s", no2);
				printf("Digite o custo da aresta\n");
				scanf(" %s", custo);
				if (atoi(custo)>0)
				{
					ins_aresta(g, atoi(no), atoi(no2), atoi(custo));
					ins_aresta(g, atoi(no2), atoi(no), atoi(custo));
				} else
					printf("Custo deve ser maior que 0\n");
				break;
			case 3:
				printf("Digite o valor do nó que deseja remover\n");
				scanf(" %s", no);
				g = retira_no(g, atoi(no));
				break;
			case 4:
				printf("Digite o 1º nó da aresta\n");
				scanf(" %s", no);
				printf("Digite o 2º nó da aresta\n");
				scanf(" %s", no2);
				retira_aresta(g, atoi(no), atoi(no2));
				retira_aresta(g, atoi(no2), atoi(no));
				break;
			case 5:
				agm = AGM(g);
				if (agm){
					printf("grafo conexo\n");
					imprimeGrafo(g, "NOVO.TXT");
					imprimeGrafo(agm, "AGM.TXT");
					libera(&agm);
				}
				break;
			case 6:
				imprime(g);
				break;
			case 7:
				libera(&g);
				break;
			default:
				printf("Opção Inválida\n\n");
				break;
		}
	} while (op!=0);

	libera(&g);

	return 0;
}
