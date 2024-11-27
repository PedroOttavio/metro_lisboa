#include<stdio.h>
#include<stdlib.h>


//definição
struct vizinho{
    int info_vizinho;
    struct vizinho* prox;
};
typedef struct vizinho vizinho;

struct vertice{
    int info_vertice;
    vizinho* primeiro_vizinho;
    struct vertice * prox;
};
typedef struct vertice vertice;