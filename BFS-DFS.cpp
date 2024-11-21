#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
    int vertices;
    int adj[MAX][MAX];
} Grafo;

void inicializarGrafo(Grafo *g, int vertices) {
    g->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adj[i][j] = 0;
        }
    }
}

void agregarArista(Grafo *g, int origen, int destino) {
    g->adj[origen][destino] = 1;
    g->adj[destino][origen] = 1; 
}

typedef struct {
    int items[MAX];
    int top;
} Pila;

void inicializarPila(Pila *p) {
    p->top = -1;
}

int pilaVacia(Pila *p) {
    return p->top == -1;
}

void push(Pila *p, int valor) {
    if (p->top == MAX - 1) {
        printf("Pila llena\n");
        return;
    }
    p->items[++(p->top)] = valor;
}

int pop(Pila *p) {
    if (pilaVacia(p)) {
        printf("Pila vacía\n");
        return -1;
    }
    return p->items[(p->top)--];
}

typedef struct {
    int items[MAX];
    int frente, final;
} Cola;

void inicializarCola(Cola *c) {
    c->frente = 0;
    c->final = 0;
}

int colaVacia(Cola *c) {
    return c->frente == c->final;
}

void encolar(Cola *c, int valor) {
    if (c->final == MAX) {
        printf("Cola llena\n");
        return;
    }
    c->items[c->final++] = valor;
}

int desencolar(Cola *c) {
    if (colaVacia(c)) {
        printf("Cola vacía\n");
        return -1;
    }
    return c->items[c->frente++];
}

void DFS(Grafo *g, int inicio, int visitado[]) {
    Pila pila;
    inicializarPila(&pila);
    push(&pila, inicio);
    printf("DFS:\n");
    printf("+-----+-----------------+\n");
    printf("| Paso| Nodo Visitado   |\n");
    printf("+-----+-----------------+\n");

    int paso = 1;
    while (!pilaVacia(&pila)) {
        int actual = pop(&pila);
        if (!visitado[actual]) {
            printf("| %3d | %c               |\n", paso++, actual + 'A');
            visitado[actual] = 1;
            for (int i = g->vertices - 1; i >= 0; i--) {
                if (g->adj[actual][i] == 1 && !visitado[i]) {
                    push(&pila, i);
                }
            }
        }
    }
    printf("+-----+-----------------+\n");
}

void BFS(Grafo *g, int inicio) {
    int visitado[MAX] = {0};
    Cola cola;
    inicializarCola(&cola);

    printf("BFS:\n");
    printf("+-----+-----------------+\n");
    printf("| Paso| Nodo Visitado   |\n");
    printf("+-----+-----------------+\n");

    int paso = 1;
    printf("| %3d | %c               |\n", paso++, inicio + 'A');
    visitado[inicio] = 1;
    encolar(&cola, inicio);

    while (!colaVacia(&cola)) {
        int actual = desencolar(&cola);
        for (int i = 0; i < g->vertices; i++) {
            if (g->adj[actual][i] == 1 && !visitado[i]) {
                printf("| %3d | %c               |\n", paso++, i + 'A');
                visitado[i] = 1;
                encolar(&cola, i);
            }
        }
    }
    printf("+-----+-----------------+\n");
}

int main() {
    Grafo g;
    inicializarGrafo(&g, 7);

    agregarArista(&g, 0, 1); 
    agregarArista(&g, 0, 3); 
    agregarArista(&g, 0, 2); 
    agregarArista(&g, 1, 5); 
    agregarArista(&g, 1, 6); 
    agregarArista(&g, 5, 6); 
    agregarArista(&g, 6, 3); 
    agregarArista(&g, 6, 4); 
    agregarArista(&g, 4, 3); 
    agregarArista(&g, 3, 2); 

    int visitado[MAX] = {0};

    DFS(&g, 0, visitado);
    printf("\n");

    BFS(&g, 0);
    printf("\n");

    return 0;
}
