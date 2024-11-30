typedef int TIPOPESO;  //peso associado à aresta que leva ao destino. Nesse caso, o numero de pontos entre uma estação e outra


struct adjacencia{ //estrutura que representa a lista de adjacencia
    int vertice; //nosso vertice de destino
    TIPOPESO peso;      //peso da aresta, nesse caso, a distancia entre uma estacão e outra
    struct adjacencia * prox;   //próximo elemento da lista de adjacencia
};
typedef struct adjacencia ADJACENCIA;

//aresta é a linha, vertice é a estação

struct vertice{
    char nome[50]; //inserir o nome da estação
    ADJACENCIA * cabeca; //cabeça da lista de adjacencia
};
typedef struct vertice VERTICE;

struct grafo{       //guarda tudo sobre o grafo
    int vertices;   //quantidade total de vertices
    int arestas;    //quantidade total de arestas
    VERTICE * adj;  //e um arranjo de vertices, cada vertice com sua própria lista de adjacencia
};

typedef struct grafo GRAFO;
typedef int booleano;
