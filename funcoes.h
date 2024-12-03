#include "struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "prototipos.h"

GRAFO *cria_grafo(int quantidade_vertices)
{

    if (quantidade_vertices <= 0)
    { // apenas valores positivos maiores que zero são permitidos
        return NULL;
    }

    GRAFO *g = (GRAFO *)malloc(sizeof(GRAFO)); // aloca espaço para uma estrutura do tipo grafo
    g->vertices = 0;                           // atualiza o numero de vertices
    g->arestas = 0;                            // atualiza o numero de arestas
    g->capacidade = quantidade_vertices;
    g->adj = (VERTICE *)malloc(quantidade_vertices * sizeof(VERTICE));
    // usando a quantidade passada por parametro, alocamos o espaço necessário para  a quantidade de vertices

    for (int i = 0; i < quantidade_vertices; i++)
    {
        // como é dificil saber ao certo o que o C pode colocar dentro do espaço alocado
        // inicializamos todos os ponteiros com NULL para garantir.
        g->adj[i].cabeca = NULL;
        strcpy(g->adj[i].nome, "");
        g->adj[i].num_linhas = 0; // inicializa o numero de linhas, só pra garantir
        g->adj[i].status = false; // inicializa para falso o status dos que ainda não foram associadas a linhas
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
    if (grafo == NULL)
    {
        return false;
    }
    // se for menor que zero ou um valor maior que a quantidade definidade de vertices, a funcao retorna null
    if ((valor_final < 0) || (valor_final >= grafo->vertices))
    {
        return false;
    }
    if ((valor_inicial < 0) || (valor_inicial >= grafo->vertices))
    {
        return false;
    }

    ADJACENCIA *novo1 = cria_adjacente(valor_final, peso); // criando uma nova adjacencia
    if (novo1 == NULL)
    { // verificar se o espaço foi alocado corretamente
        return false;
    }
    novo1->prox = grafo->adj[valor_inicial].cabeca; // o proximo elemento da adjacencia é o cabeça da lista
    grafo->adj[valor_inicial].cabeca = novo1;       // a cabeça da lista passa a ser esse novo elemento

    // criando o segundo vertice

    ADJACENCIA *novo2 = cria_adjacente(valor_inicial, peso);
    if (novo2 == NULL)
    {
        return false;
    }
    novo2->prox = grafo->adj[valor_final].cabeca;
    grafo->adj[valor_final].cabeca = novo2;
    grafo->arestas++;

    return true;
}

// função responsável por imprimir o grafo (legada)

// ta com um erro, não está printando o nome das estações, apenas o indice

// void imprime(GRAFO *grafo)
// {
//     printf("Vertices: %d. Arestas: %d.\n", grafo->vertices, grafo->arestas); //printa a quantidade de vertices e arestas
//     for (int i = 0; i < grafo->vertices; i++)
//     {
//         printf("%s (v%d)-> ", grafo->adj[i].nome, i);
//         ADJACENCIA *adj_temp = grafo->adj[i].cabeca;
//         while (adj_temp)
//         {
//             // printf("v%d [%d] ", adj_temp->vertice, adj_temp->peso);
//             // adj_temp = adj_temp->prox;
//             printf("%s(v%d), peso: [%d]; ", grafo->adj[adj_temp->vertice].nome, adj_temp->vertice, adj_temp->peso);
//             adj_temp = adj_temp->prox;
//         }
//         printf("\n");
//     }
// }

void imprime(GRAFO *grafo)
{
    printf("\n======================================================================================================================\n");
    printf("Vertices: %d. Arestas: %d.\n", grafo->vertices, grafo->arestas); // printa a quantidade de vertices e arestas
    for (int i = 0; i < grafo->vertices; i++)
    {
        printf("%s (v%d)-> ", grafo->adj[i].nome, i);

        // Exibe as linhas associadas à estação
        printf("Linhas: ");
        for (int j = 0; j < maximo_linhas; j++)
        {
            if (grafo->adj[i].linhas[j][0] != '\0') // Verifica se a linha está definida
                printf("%s ", grafo->adj[i].linhas[j]);
        }

        // Exibe as conexões (vizinhas)
        ADJACENCIA *adj_temp = grafo->adj[i].cabeca;
        printf("\n -> Vizinhas: ");
        while (adj_temp)
        {
            printf("%s(v%d), peso: [%d]; ", grafo->adj[adj_temp->vertice].nome, adj_temp->vertice, adj_temp->peso);
            adj_temp = adj_temp->prox;
        }
        printf("\n");
    }
    printf("\n======================================================================================================================\n");
}

void adiciona_linha(VERTICE *vertice, const char *linha)
{ // conta a quantas linhas uma estação pertence
    if (vertice->num_linhas < maximo_linhas)
    {
        strcpy(vertice->linhas[vertice->num_linhas], linha);
        vertice->num_linhas++;
        vertice->status = true;
    }
}

// função responsável por inserir as estações no grafo
void insere_estacoes(GRAFO *grafo)
{

    strcpy(grafo->adj[estacao_reboleira].nome, "Reboleira");
    adiciona_linha(&grafo->adj[estacao_reboleira], "Linha Azul");

    strcpy(grafo->adj[estacao_militar].nome, "Colegio Militar");
    adiciona_linha(&grafo->adj[estacao_militar], "Linha Azul");

    strcpy(grafo->adj[estacao_jardim].nome, "Jardim");
    adiciona_linha(&grafo->adj[estacao_jardim], "Linha Azul");

    strcpy(grafo->adj[estacao_praca].nome, "Praca");
    adiciona_linha(&grafo->adj[estacao_praca], "Linha Azul");

    strcpy(grafo->adj[estacao_sebastiao].nome, "Sebastiao");
    adiciona_linha(&grafo->adj[estacao_sebastiao], "Linha Azul");
    adiciona_linha(&grafo->adj[estacao_sebastiao], "Linha Vermelha");

    strcpy(grafo->adj[estacao_marques].nome, "Marques");
    adiciona_linha(&grafo->adj[estacao_marques], "Linha Azul");
    adiciona_linha(&grafo->adj[estacao_marques], "Linha Verde");

    strcpy(grafo->adj[estacao_estrela].nome, "Estrela");
    adiciona_linha(&grafo->adj[estacao_estrela], "Linha Azul");

    strcpy(grafo->adj[estacao_baixa_chiado].nome, "Baixa-Chiado");
    adiciona_linha(&grafo->adj[estacao_baixa_chiado], "Linha Azul");
    adiciona_linha(&grafo->adj[estacao_baixa_chiado], "Linha Verde");

    strcpy(grafo->adj[estacao_sondre].nome, "Sondre");
    adiciona_linha(&grafo->adj[estacao_sondre], "Linha Azul");

    strcpy(grafo->adj[estacao_terreiro].nome, "Terreiro");
    adiciona_linha(&grafo->adj[estacao_terreiro], "Linha Azul");

    strcpy(grafo->adj[estacao_apolonia].nome, "Apolonia");
    adiciona_linha(&grafo->adj[estacao_apolonia], "Linha Azul");

    strcpy(grafo->adj[estacao_rossio].nome, "Rossio");
    adiciona_linha(&grafo->adj[estacao_rossio], "Linha Verde");

    strcpy(grafo->adj[estacao_intendente].nome, "Intendente");
    adiciona_linha(&grafo->adj[estacao_intendente], "Linha Verde");

    strcpy(grafo->adj[estacao_alameda].nome, "Alameda");
    adiciona_linha(&grafo->adj[estacao_alameda], "Linha Verde");
    adiciona_linha(&grafo->adj[estacao_alameda], "Linha Vermelha");

    strcpy(grafo->adj[estacao_olaias].nome, "Olaias");
    adiciona_linha(&grafo->adj[estacao_olaias], "Linha Verde");

    strcpy(grafo->adj[estacao_olivais].nome, "Olivais");
    adiciona_linha(&grafo->adj[estacao_olivais], "Linha Verde");

    strcpy(grafo->adj[estacao_oriente].nome, "Oriente");
    adiciona_linha(&grafo->adj[estacao_oriente], "Linha Verde");

    strcpy(grafo->adj[estacao_encarnacao].nome, "Encarnacao");
    adiciona_linha(&grafo->adj[estacao_encarnacao], "Linha Verde");

    strcpy(grafo->adj[estacao_aeroporto].nome, "Aeroporto");
    adiciona_linha(&grafo->adj[estacao_aeroporto], "Linha Verde");

    strcpy(grafo->adj[estacao_roma].nome, "Roma");
    adiciona_linha(&grafo->adj[estacao_roma], "Linha Vermelha");

    strcpy(grafo->adj[estacao_campo_grande].nome, "Campo Grande");
    adiciona_linha(&grafo->adj[estacao_campo_grande], "Linha Verde");
    adiciona_linha(&grafo->adj[estacao_campo_grande], "Linha Amarela");

    strcpy(grafo->adj[estacao_telheiras].nome, "Telheiras");
    adiciona_linha(&grafo->adj[estacao_telheiras], "Linha Vermelha");

    strcpy(grafo->adj[estacao_ameixoeira].nome, "Ameixoeira");
    adiciona_linha(&grafo->adj[estacao_ameixoeira], "Linha Vermelha");

    strcpy(grafo->adj[estacao_senhor_roubado].nome, "Senhor Roubado");
    adiciona_linha(&grafo->adj[estacao_senhor_roubado], "Linha Vermelha");

    strcpy(grafo->adj[estacao_odivelas].nome, "Odivelas");
    adiciona_linha(&grafo->adj[estacao_odivelas], "Linha Vermelha");

    strcpy(grafo->adj[estacao_cidade_universitaria].nome, "Cidade Universitaria");
    adiciona_linha(&grafo->adj[estacao_cidade_universitaria], "Linha Amarela");

    strcpy(grafo->adj[estacao_entrecampos].nome, "Entrecampos");
    adiciona_linha(&grafo->adj[estacao_entrecampos], "Linha Amarela");

    strcpy(grafo->adj[estacao_campopequeno].nome, "Campo Pequeno");
    adiciona_linha(&grafo->adj[estacao_campopequeno], "Linha Amarela");

    strcpy(grafo->adj[estacao_saldanha].nome, "Saldanha");
    adiciona_linha(&grafo->adj[estacao_saldanha], "Linha Vermelha");
    adiciona_linha(&grafo->adj[estacao_saldanha], "Linha Verde");

    // eu sou um comentário

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

// função que acha o menor caminho de uma estação para outra, usando agoritmo djikstra
void menor_caminho(GRAFO *g, int origem, int destino) {
    if (origem < 0 || origem >= g->vertices || destino < 0 || destino >= g->vertices) {
        printf("Estacao de origem ou destino invalida.\n");
        printf("Erro!\n");
        return;
    }
    if (!g->adj[origem].status || !g->adj[destino].status) {
        printf("Erro: Uma ou ambas as estações estão inativas.\n");
        return;
    }

    TIPOPESO *distancias = (TIPOPESO *)malloc(g->vertices * sizeof(TIPOPESO));
    booleano *visitados = (booleano *)malloc(g->vertices * sizeof(booleano));
    int *predecessores = (int *)malloc(g->vertices * sizeof(int));

    // inicializa todas as distâncias com "infinito" e visitados como false
    for (int i = 0; i < g->vertices; i++) {
        distancias[i] = 9999;
        visitados[i] = false;
        predecessores[i] = -1;
    }

    distancias[origem] = 0; // de origem até ela mesma peso 0

    // percorre o grafo
    for (int i = 0; i < g->vertices; i++) {
        // escolher o vértice não visitado com a menor distância
        int menor_dist = 9999;
        int u = -1;

        for (int j = 0; j < g->vertices; j++) {
            if (!visitados[j] && distancias[j] < menor_dist) {
                menor_dist = distancias[j];
                u = j;
            }
        }

        // se não houver vértices acessíveis, ou se chegamos ao destino, parar
        if (u == -1 || u == destino) {
            break;
        }

        // marcar o vértice `u` como visitado
        visitados[u] = true;

        // Atualizar as distâncias para os vizinhos de `u`
        ADJACENCIA *adj = g->adj[u].cabeca;
        while (adj != NULL) {
            int v = adj->vertice;
            TIPOPESO peso = adj->peso;

            if (!visitados[v] && distancias[u] + peso < distancias[v]) {
                distancias[v] = distancias[u] + peso;
                predecessores[v] = u;
            }
            adj = adj->prox;
        }
    }

    // resultado: imprimir a distância para o destino
    printf("Menor distância de %s para %s é: ", g->adj[origem].nome, g->adj[destino].nome);
    if (distancias[destino] == 9999) {
        printf("Inacessivel\n");
    } else {
        printf("%d\n", distancias[destino]);

        // reconstruir e imprimir o caminho
        printf("Caminho: ");
        int *caminho = (int *)malloc(g->vertices * sizeof(int));
        int tamanho = 0;
        for (int v = destino; v != -1; v = predecessores[v]) {
            caminho[tamanho++] = v;
        }

        // imprimir o caminho na ordem correta (de origem para destino)
        for (int i = tamanho - 1; i >= 0; i--) {
            printf("%s", g->adj[caminho[i]].nome);
            if (i > 0)
                printf(" -> ");
        }
        printf("\n");

        free(caminho);
    }

    free(distancias);
    free(visitados);
    free(predecessores);
}

void menu(GRAFO *g) {
    int origem, destino, escolha;

    do {
        // exibe as opções
        printf("\nMenu:\n");
        printf("1. Imprimir o 'mapa'\n");
        printf("2. Encontrar menor caminho entre duas estacoes\n");
        printf("3. Inserir nova estacao\n");
        printf("4. Sair\n");
        printf("Insira a opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
        case 1:
            imprime(g); // Imprime as estações e suas adjacências
            break;
        case 2:
            printf("Digite a estacao de origem (0 a %d): ", g->vertices - 1);
            scanf("%d", &origem);
            printf("Digite a estacao de destino (0 a %d): ", g->vertices - 1);
            scanf("%d", &destino);
            menor_caminho(g, origem, destino); // Chama o algoritmo de Dijkstra
            break;
        case 3:
            insere_nova_estacao(g); // Insere uma nova estação
            break;
        case 4:
            printf("Saindo do menu...\n");
            break;
        default:
            printf("Opcao invalida, tente novamente.\n");
        }
    } while (escolha != 4); // Continua até o usuário escolher a opção de sair
}

//

booleano abrindo_espacoNoGrafo(GRAFO *grafo)
{
    int nova_capacidade = grafo->capacidade + 1;
    // pensando no desenvolvimento futuro, vamos usar o realloc, assim garantimos que nosso crescimento seja dinâmico e possamos nos desenvolver
    // sem maiores problemas. Tudo para oferecer o melhor de nossos serviços para os nossos usuários! Tudo pelo dinheiro! Digo, usuários!
    VERTICE *novo_adj = (VERTICE *)realloc(grafo->adj, nova_capacidade * sizeof(VERTICE));
    if (novo_adj == NULL)
    {
        printf("Erro no realloc: Alguma coisa errada não deu certo.\n");
        return false;
    }
    grafo->adj = novo_adj;
    grafo->capacidade = nova_capacidade;
    return true;
}

void insere_nova_estacao(GRAFO *grafo)
{

    if (grafo->vertices >= grafo->capacidade)
    {
        if (!abrindo_espacoNoGrafo(grafo))
        {
            return; // se não conseguir alocar memória, retornamos para a chamada da função
        }
    }
    char nome[30];
    char linha[30];

    int numero_linhas, numero_conexoes, estacao_conectada, peso, linhas = 0;

    printf("Insira o nome da nova estacao: ");
    fgets(nome, 30, stdin);

    // do...while para verificar se a quantidade de linhas inserida pelo usuario é ou não válida
    do
    {
        printf("Insira o numero de linhas:(0 a 4): ");
        scanf("%d", &linhas);
    } while (numero_linhas < 0 || numero_linhas > 4);

    numero_linhas = linhas;

    for (int i = 0; i < numero_linhas; i++)
    {
        printf("Insira o nome da linha [%d]: ", i + 1);
        fgets(linha, 30, stdin);
        adiciona_linha(&grafo->adj[grafo->vertices], linha);
    }

    strcpy(grafo->adj[grafo->vertices].nome, nome);
    grafo->adj[grafo->vertices].status = true;

    // ok, criamos uma nova estação, certo? Mas essa estação é inútil se não nos levar a lugar algum, então
    // vamos usar esse for para verificar se temos um vizinho para conectar com essa nova estação, se tudo funcionar,
    // a estação se conectará com o vizinho mais próximo

    for (int i = 0; i < numero_linhas; i++)
    {
        strcpy(linha, grafo->adj[grafo->vertices].linhas[i]);
        booleano vizinhoDeBaixo = false;
        booleano vizinhoDeCima = false;

        for (int j = grafo->vertices - 1; j >= 0; j--)
        {
            for (int k = 0; k < grafo->adj[j].num_linhas; k++)
            {
                if (strcmp(grafo->adj[j].linhas[k], linha) == 0)
                {
                    printf("Digite o peso da conexão entre %s e %s: ", grafo->adj[j].nome, nome);
                    scanf("%d", &peso);
                    cria_aresta(grafo, grafo->vertices, j, peso);
                    cria_aresta(grafo, j, grafo->vertices, peso);
                    vizinhoDeBaixo = true;
                    break;
                }
            }
            if (vizinhoDeBaixo)
            {
                break;
            }
        }

        // Procurar a estação vizinha posterior na mesma linha
        for (int j = grafo->vertices + 1; j < grafo->vertices; j++)
        {
            for (int k = 0; k < grafo->adj[j].num_linhas; k++)
            {
                if (strcmp(grafo->adj[j].linhas[k], linha) == 0)
                {
                    printf("Digite o peso da conexão entre %s e %s: ", grafo->adj[j].nome, nome);
                    scanf("%d", &peso);
                    cria_aresta(grafo, grafo->vertices, j, peso);
                    cria_aresta(grafo, j, grafo->vertices, peso);
                    vizinhoDeCima = true;
                    break;
                }
            }
            if (vizinhoDeCima)
            {
                break;
            }
        }
    }

    grafo->vertices++;
}
