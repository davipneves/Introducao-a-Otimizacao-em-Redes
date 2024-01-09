#include "estrutura.h"

void inicializarFila(Fila *f) {
    f->frente = -1;
    f->tras = -1;
}

int filaVazia(Fila *f) {
    return (f->frente == -1);
}

void enfileirar(Fila *f, int item) {
    if (f->frente == -1)
        f->frente = 0;
    f->tras = (f->tras + 1) % MAX_VERTICES;
    f->itens[f->tras] = item;
}

int desenfileirar(Fila *f) {
    int item = f->itens[f->frente];
    if (f->frente == f->tras)
        f->frente = f->tras = -1;
    else
        f->frente = (f->frente + 1) % MAX_VERTICES;
    return item;
}

