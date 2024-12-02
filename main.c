#include "prototipos.h" // inclui os protótipos das funções
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "funcoes.h"



int main()
{

    GRAFO *grafo = cria_grafo(total_estacoes); // cria um grafo com 29 vertices

    insere_estacoes(grafo); // insere as estações no grafo
    menu(grafo);

    return 0;
}