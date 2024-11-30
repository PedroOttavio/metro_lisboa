#include<struct.c>
#include<stdlib.h>
#include<stdio.h>



#define true 1
#define false 0


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
        //como é dificil saber ao certo o que o C pode colocar dentro do espaço alocado
        //inicializamos todos os ponteiros com NULL para garantir.
        g->adj[i].cabeca = NULL;  
        strcpy(g->adj[i].nome, ""); 
    }
    
    return g; //retorna o grafo;
}

//adicionar algumas arestas no grafo
//lembrando que adjacencia é basicamente a seta que aponta para outro vertice, responsável por conter as informações
// sobre o vertice de destino e o peso da aresta, além de um ponteiro para a próxima adjacencia
ADJACENCIA * cria_adjacente(int quantidade_vertices, int peso){ 
    ADJACENCIA * aux = (ADJACENCIA *) malloc(sizeof(ADJACENCIA)); //aloca espaço para uma estrutura do tipo adjacencia
    aux->vertice = quantidade_vertices; //atualiza o vertice
    aux->peso = peso; //atualiza o peso
    aux->prox = NULL; //proxima adjacencia eh nula
    return aux; //retorna o endereço do adjacente
}


//na criação de um vertice não direcionado, é necessário criar duas adjacencias, uma para cada vertice
//valor inicial e valor final seria a identificação do indice que representa os vertices que estamos inserindo;
booleano cria_aresta(GRAFO * grafo, int valor_inicial, int valor_final, TIPOPESO peso){
    
    //se o grafo não existir, retorna null
    if(grafo == NULL){          
        return false;
    }
    //se for menor que zero ou um valor maior que a quantidade definidade de vertices, a funcao retorna null
    if((valor_final < 0) || (valor_final >= grafo->vertices)){
        return false;
    }
    if((valor_inicial < 0)|| (valor_inicial >= grafo->vertices)){
        return false;
    }

    ADJACENCIA * novo = cria_adjacente(valor_final, peso); //criando uma nova adjacencia
    novo -> prox = grafo->adj[valor_inicial].cabeca; //o proximo elemento da adjacencia é o cabeça da lista 

}
