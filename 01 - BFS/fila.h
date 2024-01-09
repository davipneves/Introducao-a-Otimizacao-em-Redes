#ifndef FILA_H
#define FILA_H

#define MAX_VERTICES 100

typedef struct fila {
    int itens[MAX_VERTICES];
    int frente, tras;
} Fila;

void inicializarFila(Fila *f);

int filaVazia(Fila *f);

void enfileirar(Fila *f, int item);

int desenfileirar(Fila *f);

#endif //FILA_H
