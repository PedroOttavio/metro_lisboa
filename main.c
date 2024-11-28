#include<stdio.h>
#include<stdlib.h>


//definição das estruturas
struct vizinho{
    int info_vizinho;
    struct vizinho* prox;
};
typedef struct vizinho vizinho;

struct grafo{
    int info_vertice;
    vizinho* primeiro_vizinho;
    struct grafo * prox;
};
typedef struct grafo grafo;

//protótipos de funções
grafo * inicializa_grafo();
void imprime(grafo * g);
void libera(grafo * g);
void libera_vizinhos(vizinho * v);

int main(){


    return 0;
}

grafo * inicializa_grafo(){
    return NULL;
}

void imprime(grafo * g){
    while (g != NULL)
    {
        printf("Vertice: %d\n", g->info_vertice);
        printf("Vizinhos: ");
        vizinho * aux = g->primeiro_vizinho;
        while (aux != NULL)
        {
            printf("%d ", aux->info_vizinho);
            aux = aux->prox;
        }
        printf("\n");
        g = g->prox;
    }
    
}


void libera(grafo * g){
    while (g != NULL){
        libera_vizinhos(g->primeiro_vizinho);
        vizinho * aux = g;
        g = g->prox;
        free(aux);
    }
}

void libera_vizinhos(vizinho * v){
    while (v != NULL){
        vizinho * aux = v;
        v = v->prox;
        free(aux);
    }
}
    

