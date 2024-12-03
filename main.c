#include "prototipos.h" // inclui os protótipos das funções
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "funcoes.h"



int main(){

    int capacidade_inicial = 29; //o grafo já inicia com 29 posições ocupadas

    GRAFO *grafo = cria_grafo(capacidade_inicial); // alocando as posições para o nosso grafo

    insere_estacoes(grafo); // insere as estações no grafo
    menu(grafo);

    return 0;
}