#include<stdio.h>
#include<stdlib.h>



#define true 1
#define false 0

typedef int bool;
typedef int TIPOPESO;  //peso associado à aresta que leva ao destino. Nesse caso, o numero de pontos entre uma estação e outra


//definição das estruturas

typedef struct vertice {
    // Dados armazenados vão aqui
    ADJACENCIA * cab;
}VERTICE;                       //é a bolinha do grafo


typedef struct grafo{
    int vertices;
    int arestas;                //é a linha que liga as bolinhas(vertice) do grafo
    VERTICE * adj;
}GRAFO;                 //guarda apenas o ponteiro para o arranjo e não o arranjo em si

typedef struct adjacencia{
    int vertice;
    TIPOPESO peso;
    struct adjacencia * prox;
}ADJACENCIA;









//=========================================================PROTÓTIPOS DAS FUNÇÕES=============================================



GRAFO *cria_grafo(int v);
ADJACENCIA *cria_adj(int quantidade_vertices, int peso);
bool cria_aresta(GRAFO *gr, int valor_inicial, int valor_final, TIPOPESO peso);


//======================================================FIM PROTÓTIPOS=========================================================


//=========================================================FUNÇÃO MAIN=========================================================



int main(){
    
    return 0;
}

//=========================================================FIM FUNÇÃO MAIN=====================================================



//============================================FUNÇÕES===========================================================================


GRAFO * cria_grafo(int quantidade_vertices){            
    GRAFO * g  = (GRAFO * )malloc(sizeof(GRAFO));
    g-> vertices = quantidade_vertices;
    g-> arestas = 0;
    g-> adj = (VERTICE * )malloc(quantidade_vertices * sizeof(VERTICE)); //cria um arranjo de vertices com x elementos(passados por parametro)
    
    for(int i = 0; i < quantidade_vertices; i++){
        g->adj[i].cab = NULL; //pra garantir que não haja nenhum valor estranho, inicializamos todos os ponteiros com NULL. Ninguém tem adjacencia no começo
    }
    
    return g; //retornamos a coleção de nós, todos sem nenhuma aresta;
}

ADJACENCIA * cria_adj(int quantidade_vertices, int peso){     //recebe como parametro o nó final da aresta e o peso dela

    ADJACENCIA * temp = (ADJACENCIA *) malloc(sizeof(ADJACENCIA)); //alocamos espaço para um nó nessa lista de adjacencia

    temp -> vertice = quantidade_vertices;  //preenchemos o campo vertice com o valor passado por parametro, o "vertice alvo"
    temp -> peso = peso;            //peso da aresta, nesse caso, o peso será o numero de pontos entre uma estação e outra
    temp -> prox = NULL;            //mesmo esquema de listas encadeadas, o proximo nó é NULL

    return temp;            //retornamos o endereço dessa adjacencia que criamos
}


//função que cria a aresta entre dois vertices, grafo dirigido
bool cria_aresta(GRAFO *gr, int valor_inicial, int valor_final, TIPOPESO peso){

    //teste de parâmetros
    if(gr == NULL)
        return false;

    if((valor_final < 0) || (valor_final >= gr->vertices))  //evitar valores finais inválidos, os nós vão de 0 até n - 1;
        return false;

    if((valor_inicial < 0) || (valor_inicial >= gr->vertices))  //também para evitar valores invalidos, agora testando o valor inicial
        return false;
    
    ADJACENCIA * novo = cria_adj(valor_final, peso); //se os parâmetros estiverem corretos, criamos a adjacencia

    //criamos a nossa adjacencia, agora precisamos colocar ela na lista de adjacenca do nosso vertice inicial

    novo -> prox = gr -> adj[valor_inicial].cab; //campo prox está recebendo a cabeça da lista;
    gr -> adj[valor_inicial].cab = novo; // a cabeça da lista passa a ser esse novo elemento
    gr -> arestas++; //somamos a quantidade de arestas do grafo
    
    return true;
}

//============================================ FIM FUNÇÕES=======================================================================
