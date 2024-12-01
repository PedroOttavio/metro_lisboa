#include <struct.c>
#include <stdlib.h>
#include <stdio.h>


GRAFO *cria_grafo(int quantidade_vertices)
{

    if (quantidade_vertices <= 0)
    { // apenas valores positivos maiores que zero são permitidos
        return NULL;
    }

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO)); // aloca espaço para uma estrutura do tipo grafo
    g->vertices = quantidade_vertices;         // atualiza o numero de vertices
    g->arestas = 0;                            // atualiza o numero de arestas
    g->adj = (VERTICE *)malloc(quantidade_vertices * sizeof(VERTICE));
    // usando a quantidade passada por parametro, alocamos o espaço necessário para  a quantidade de vertices

    for (int i = 0; i < quantidade_vertices; i++)
    {
        // como é dificil saber ao certo o que o C pode colocar dentro do espaço alocado
        // inicializamos todos os ponteiros com NULL para garantir.
        g->adj[i].cabeca = NULL;
        strcpy(g->adj[i].nome, "");
    }

    return g; // retorna o grafo;
}

// adicionar algumas arestas no grafo
// lembrando que adjacencia é basicamente a seta que aponta para outro vertice, responsável por conter as informações
//  sobre o vertice de destino e o peso da aresta, além de um ponteiro para a próxima adjacencia
ADJACENCIA *cria_adjacente(int quantidade_vertices, int peso)
{
    ADJACENCIA *aux = (ADJACENCIA *)malloc(sizeof(ADJACENCIA)); // aloca espaço para uma estrutura do tipo adjacencia
    aux->vertice = quantidade_vertices;                         // atualiza o vertice
    aux->peso = peso;                                           // atualiza o peso
    aux->prox = NULL;                                           // proxima adjacencia eh nula
    return aux;                                                 // retorna o endereço do adjacente
}

// na criação de um vertice não direcionado, é necessário criar duas adjacencias, uma para cada vertice
// valor inicial e valor final seria a identificação do indice que representa os vertices que estamos inserindo;
booleano cria_aresta(GRAFO *grafo, int valor_inicial, int valor_final, TIPOPESO peso)
{

    // se o grafo não existir, retorna null
    if (grafo == NULL){
        return false;
    }
    // se for menor que zero ou um valor maior que a quantidade definidade de vertices, a funcao retorna null
    if ((valor_final < 0) || (valor_final >= grafo->vertices)){
        return false;
    }
    if ((valor_inicial < 0) || (valor_inicial >= grafo->vertices)){
        return false;
    }

    ADJACENCIA *novo1 = cria_adjacente(valor_final, peso); // criando uma nova adjacencia
    if(novo1 == NULL){          //verificar se o espaço foi alocado corretamente
        return false;
    }
    novo1->prox = grafo->adj[valor_inicial].cabeca;        // o proximo elemento da adjacencia é o cabeça da lista
    grafo-> adj[valor_inicial].cabeca = novo1;             // a cabeça da lista passa a ser esse novo elemento



    //criando o segundo vertice

    ADJACENCIA * novo2 = cria_adjacente(valor_inicial, peso);
    if(novo2 == NULL){
        return false;
    }
    novo2->prox = grafo->adj[valor_final].cabeca;
    grafo->adj[valor_final].cabeca = novo2;
    grafo->arestas++;

    return true;
    
}

// função responsável por imprimir o grafo
void imprime(GRAFO *grafo)
{
    printf("Vertices: %d. Arestas: %d.\n", grafo->vertices, grafo->arestas);
    for (int i = 0; i < grafo->vertices; i++)
    {
        printf("%s (v%d): ", grafo->adj[i].nome, i);
        ADJACENCIA *adj_temp = grafo->adj[i].cabeca;
        while (adj_temp)
        {
            printf("v%d(%d) ", adj_temp->vertice, adj_temp->peso);
            adj_temp = adj_temp->prox;
        }
        printf("\n");
    }
}


void insere_estacoes(GRAFO* grafo){

    cria_aresta(grafo, estacao_reboleira, estacao_militar, 5);
    cria_aresta(grafo, estacao_militar, estacao_jardim, 3);
    cria_aresta(grafo, estacao_jardim, estacao_praca, 1);
    cria_aresta(grafo, estacao_praca, estacao_sebastiao, 1);
    cria_aresta(grafo, estacao_sebastiao, estacao_marques, 1);
    cria_aresta(grafo, estacao_marques, estacao_estrela, 1);
    cria_aresta(grafo, estacao_marques, estacao_baixa_chiado, 3);
    cria_aresta(grafo, estacao_baixa_chiado, estacao_sondre, 1);
    cria_aresta(grafo, estacao_baixa_chiado, estacao_terreiro, 1);
    cria_aresta(grafo, estacao_terreiro, estacao_apolonia, 1);
    cria_aresta(grafo, estacao_baixa_chiado, estacao_rossio, 1);
    cria_aresta(grafo, estacao_rossio, estacao_intendente, 1);
    cria_aresta(grafo, estacao_intendente, estacao_alameda, 2);
    cria_aresta(grafo, estacao_alameda, estacao_olaias, 1);
    cria_aresta(grafo, estacao_olaias, estacao_olivais, 3);
    cria_aresta(grafo, estacao_olivais, estacao_oriente, 2);
    cria_aresta(grafo, estacao_oriente, estacao_encarnacao, 2);
    cria_aresta(grafo, estacao_encarnacao, estacao_aeroporto, 1);
    cria_aresta(grafo, estacao_alameda, estacao_roma, 2);
    cria_aresta(grafo, estacao_roma, estacao_campo_grande, 2);
    cria_aresta(grafo, estacao_campo_grande, estacao_telheiras, 1);
    cria_aresta(grafo, estacao_campo_grande, estacao_ameixoeira, 2);
    cria_aresta(grafo, estacao_ameixoeira, estacao_senhor_roubado, 2);
    cria_aresta(grafo, estacao_senhor_roubado, estacao_odivelas, 1);
    cria_aresta(grafo, estacao_campo_grande, estacao_cidade_universitaria, 1);
    cria_aresta(grafo, estacao_cidade_universitaria, estacao_entrecampos, 1);
    cria_aresta(grafo, estacao_entrecampos, estacao_campopequeno, 1);
    cria_aresta(grafo, estacao_campopequeno, estacao_saldanha, 1);
    cria_aresta(grafo, estacao_saldanha, estacao_alameda, 1);
    cria_aresta(grafo, estacao_saldanha, estacao_sebastiao, 1);

}