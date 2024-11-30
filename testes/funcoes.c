#include<struct.c>
#include<stdlib.h>
#include<stdio.h>

GRAFO * cria_grafo(int quantidade_vertices){

    if(quantidade_vertices <= 0){ //apenas valores positivos maiores que zero são permitidos
        return NULL;
    }
    
    GRAFO *g = (GRAFO *) malloc(sizeof(GRAFO)); //aloca espaço para uma estrutura do tipo grafo
    g->vertices = quantidade_vertices;  //atualiza o numero de vertices
    g->arestas = 0;                     //atualiza o numero de arestas
    g->adj = (VERTICE *) malloc(quantidade_vertices * sizeof(VERTICE)); 
    //usando a quantidade passada por parametro, alocamos o espaço necessário para  a quantidade de vertices

    for (int i = 0; i < quantidade_vertices; i++)
    {
        g->adj[i].cabeca = NULL;  //como é dificil saber ao certo o que o C pode colocar dentro do espaço alocado
                                 //inicializamos todos os ponteiros com NULL para garantir.
    }
    
    return g; //retorna o grafo;
}

//adicionar algumas arestas no grafo
//lembrando que adjacencia é basicamente uma aresta ligando dois vertices responsável por conter as informações
// sobre o vertice de destino e o peso da aresta, além de um ponteiro para a próxima adjacencia
ADJACENCIA * cria_adjacente(int quantidade_vertices, int peso){ 
    ADJACENCIA * aux = (ADJACENCIA *) malloc(sizeof(ADJACENCIA)); //aloca espaço para uma estrutura do tipo adjacencia
    aux->vertice = quantidade_vertices; //atualiza o vertice
    aux->peso = peso; //atualiza o peso
    aux->prox = NULL; //proxima adjacencia eh nula
    return aux; //retorna o endereço do 
}