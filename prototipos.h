#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H
#include"struct.h"




GRAFO * cria_grafo(int quantidade_vertices);
booleano cria_aresta(GRAFO * grafo, int valor_inicial, int valor_final, TIPOPESO peso);
ADJACENCIA * cria_adjacente(int quantidade_vertices, int peso);
void imprime(GRAFO *grafo);
void insere_estacoes(GRAFO* grafo);
void adiciona_linha(VERTICE *vertice, const char *linha);
void menor_caminho(GRAFO *g, int origem, int destino);
void menu(GRAFO *g);
booleano abrindo_espacoNoGrafo(GRAFO * grafo);      //na teoria, é para resolver o problema do numero de estações maior que o grafo permitia.

#endif


//eu sou um comentário.
//eu também sou um comentário.
//e você? É um comentário?