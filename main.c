#include "prototipos.h" // inclui os protótipos das funções
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "funcoes.h"



int main(){

    //função de teste para verificar se os grafos estavam sendo criados corretamente, a principio, estavam. Felizmente ou não
    //testa_cria_grafo(); // testa a criação do grafo 


    GRAFO *grafo = cria_grafo(); // alocando as posições para o nosso grafo

    insere_estacoes(grafo); // insere as estações no grafo
    menu(grafo);

    return 0;
}