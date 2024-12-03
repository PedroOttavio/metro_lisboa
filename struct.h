#ifndef STRUCT_H
#define STRUCT_H

#define maximo_linhas 5

//beba aguá.

typedef enum { false, true } booleano;




typedef int TIPOPESO;  //peso associado à aresta que leva ao destino. Nesse caso, o numero de pontos entre uma estação e outra

struct adjacencia{ //estrutura que representa a lista de adjacencia
    int vertice; //nosso vertice de destino
    TIPOPESO peso;      //peso da aresta, nesse caso, a distancia entre uma estacão e outra
    struct adjacencia * prox;   //próximo elemento da lista de adjacencia
};
typedef struct adjacencia ADJACENCIA;

//aresta é a linha, vertice é a estação

struct vertice{
    char linhas[maximo_linhas][30]; //inserir a linha da estação
    int num_linhas; //estação pertence a quantas linhas
    char nome[30]; //inserir o nome da estação
    ADJACENCIA * cabeca; //cabeça da lista de adjacencia
    booleano status;
};
typedef struct vertice VERTICE;

struct grafo{       //guarda tudo sobre o grafo
    int vertices;   //quantidade total de vertices
    int arestas;    //quantidade total de arestas
    VERTICE * adj;  //e um arranjo de vertices, cada vertice com sua própria lista de adjacencia
};

typedef struct grafo GRAFO;


//DEFINES: 


#define true 1
#define false 0

#define total_estacoes 29 //total de estações, já que fazer de forma dinâmica não deu muito certo, vamos fazer dessa forma mesmo;
//um pouco funcionando é melhor que nada funcionando.

//estações 
#define estacao_reboleira 0
#define estacao_militar 1
#define estacao_jardim 2
#define estacao_praca 3
#define estacao_sebastiao 4
#define estacao_marques 5
#define estacao_estrela 6
#define estacao_baixa_chiado 7
#define estacao_sondre 8
#define estacao_terreiro 9
#define estacao_apolonia 10
#define estacao_rossio 11
#define estacao_intendente 12
#define estacao_alameda 13
#define estacao_olaias 14
#define estacao_olivais 15
#define estacao_oriente 16
#define estacao_encarnacao 17
#define estacao_aeroporto 18
#define estacao_roma 19
#define estacao_campo_grande 20
#define estacao_telheiras 21
#define estacao_ameixoeira 22
#define estacao_senhor_roubado 23
#define estacao_odivelas 24
#define estacao_cidade_universitaria 25
#define estacao_entrecampos 26
#define estacao_campopequeno 27
#define estacao_saldanha 28

#endif // STRUCT_H