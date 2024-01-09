#ifndef VISINHO_H
#define VISINHO_H

#include <stdlib.h>

typedef struct viz {
	int id;
	int custo;
	struct viz * prox_viz;
} Tviz;

#endif //VISINHO_H