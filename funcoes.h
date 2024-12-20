#include "struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "prototipos.h"



GRAFO *cria_grafo()
{

    GRAFO *grafo = (GRAFO *)malloc(sizeof(GRAFO)); // aloca espaço para uma estrutura do tipo grafo
    grafo->vertices = 0;                           // atualiza o numero de vertices
    grafo->arestas = 0;                            // atualiza o numero de arestas
    grafo->adj = (VERTICE *)malloc(total_estacoes * sizeof(VERTICE));
    // usando a quantidade passada por parametro, alocamos o espaço necessário para  a quantidade de vertices

    for (int i = 0; i < total_estacoes; i++)
    {
        // como é dificil saber ao certo o que o C pode colocar dentro do espaço alocado
        // inicializamos todos os ponteiros com NULL para garantir.
        grafo->adj[i].cabeca = NULL;
        strcpy(grafo->adj[i].nome, "");
        grafo->adj[i].num_linhas = 0; // inicializa o numero de linhas, só pra garantir
        grafo->adj[i].status = false; // inicializa para falso o status dos que ainda não foram associadas a linhas
        for (int j = 0; j < maximo_linhas; j++)
        {
            grafo->adj[i].linhas[j][0] = '\0';
        }
    }

    return grafo; // retorna o grafo;
}

// void testa_cria_grafo() {
//     GRAFO *grafo = cria_grafo(10); // Cria um grafo com capacidade para 10 vértices

//     if (grafo == NULL) {
//         printf("Falha ao criar o grafo.\n");
//         return;
//     }

//     printf("Grafo criado com sucesso.\n");
//     printf("Vertices: %d\n", grafo->vertices);
//     printf("Arestas: %d\n", grafo->arestas);

//     for (int i = 0; i < grafo->vertices; i++) {
//         printf("Vertice %d: Nome: %s, Status: %d, Num Linhas: %d\n", i, grafo->adj[i].nome, grafo->adj[i].status, grafo->adj[i].num_linhas);
//     }

//     // Libera a memória alocada para o grafo
//     free(grafo->adj);
//     free(grafo);
// }



// adicionar algumas arestas no grafo
// lembrando que adjacencia é basicamente a seta que aponta para outro vertice, responsável por conter as informações
//  sobre o vertice de destino e o peso da aresta, além de um ponteiro para a próxima adjacencia
ADJACENCIA *cria_adjacente(int quantidade_vertices, int peso)
{   // aloca espaço para uma estrutura do tipo adjacencia
    ADJACENCIA *aux = (ADJACENCIA *)malloc(sizeof(ADJACENCIA)); 

    if(aux == NULL)
    {   
        printf("ERRO! Paciente não sobreviveu ao malloc!\n");
        return NULL;
    }
    // atualiza o vertice
    aux->vertice = quantidade_vertices;     
     // atualiza o peso                    
    aux->peso = peso;        
    // proxima adjacencia eh nula                                  
    aux->prox = NULL;  
      // retorna o endereço do adjacente                                         
    return aux;                                               
}

// na criação de um vertice não direcionado, é necessário criar duas adjacencias, uma para cada vertice
// valor inicial e valor final seria a identificação do indice que representa os vertices que estamos inserindo;
booleano cria_aresta(GRAFO *grafo, int valor_inicial, int valor_final, TIPOPESO peso) //A PRINCIPIO OK
{

    // se o grafo não existir, retorna false!
    if (grafo == NULL)
    {
        return false;
    }
    // se for menor que zero ou um valor maior que a quantidade definidade de vertices, a funcao retorna false!
    if ((valor_final < 0) || (valor_final >= total_estacoes))
    {
        return false;
    }
    if ((valor_inicial < 0) || (valor_inicial >= total_estacoes))
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

    if (grafo == NULL)
    {
        printf("Grafo não existe!\n");
        return;
    }

    printf("Vertices: %d. Arestas: %d.\n", grafo->vertices, grafo->arestas); // printa a quantidade de vertices e arestas
    for (int i = 0; i < total_estacoes; i++)
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

    grafo->vertices = total_estacoes;

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
void menor_caminho(GRAFO *g, int origem, int destino)
{
    if (origem < 0 || origem >= total_estacoes || destino < 0 || destino >= total_estacoes)
    {
        printf("Estacao de origem ou destino invalida.\n");
        printf("Erro!\n");
        return;
    }
    if (!g->adj[origem].status || !g->adj[destino].status)
    {
        printf("Erro: Uma ou ambas as estações estão inativas.\n");
        return;
    }

    TIPOPESO *distancias = (TIPOPESO *)malloc(total_estacoes * sizeof(TIPOPESO));
    booleano *visitados = (booleano *)malloc(total_estacoes * sizeof(booleano));
    int *predecessores = (int *)malloc(total_estacoes * sizeof(int));

    // inicializa todas as distâncias com "infinito" e visitados como false
    for (int i = 0; i < total_estacoes; i++)
    {
        distancias[i] = 9999;
        visitados[i] = false;
        predecessores[i] = -1;
    }

    distancias[origem] = 0; // de origem até ela mesma peso 0

    // percorre o grafo
    for (int i = 0; i < total_estacoes; i++)
    {
        // escolher o vértice não visitado com a menor distância
        int menor_dist = 9999;
        int u = -1;

        for (int j = 0; j < total_estacoes; j++)
        {
            if (!visitados[j] && distancias[j] < menor_dist)
            {
                menor_dist = distancias[j];
                u = j;
            }
        }

        // se não houver vértices acessíveis, ou se chegamos ao destino, parar
        if (u == -1 || u == destino)
        {
            break;
        }

        // marcar o vértice `u` como visitado
        visitados[u] = true;

        // Atualizar as distâncias para os vizinhos de `u`
        ADJACENCIA *adj = g->adj[u].cabeca;
        while (adj != NULL)
        {
            int v = adj->vertice;
            TIPOPESO peso = adj->peso;

            if (!visitados[v] && distancias[u] + peso < distancias[v])
            {
                distancias[v] = distancias[u] + peso;
                predecessores[v] = u;
            }
            adj = adj->prox;
        }
    }

    // resultado: imprimir a distância para o destino
    printf("Menor distância de %s para %s é: ", g->adj[origem].nome, g->adj[destino].nome);
    if (distancias[destino] == 9999)
    {
        printf("Inacessivel\n");
    }
    else
    {
        printf("%d\n", distancias[destino]);

        // reconstruir e imprimir o caminho
        printf("Caminho: ");
        int *caminho = (int *)malloc(total_estacoes * sizeof(int));
        int tamanho = 0;
        for (int v = destino; v != -1; v = predecessores[v])
        {
            caminho[tamanho++] = v;
        }

        // imprimir o caminho na ordem correta (de origem para destino)
        for (int i = tamanho - 1; i >= 0; i--)
        {
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

// void menu(GRAFO *g)
// {
//     int origem, destino, escolha, vertice;
//     int total_estacoes = g->vertices;   //verificar se funcionou mesmo, qualquer coisa, apagar essa linha e procurar outra solução
//     //"A regra é clara, se funcionou, não mexa", Tite, Adenor Bachia Santos, 2021

//     do {
//         // exibe as opções
//         printf("\nMenu:\n");
//         printf("1. Imprimir o 'mapa'\n");
//         printf("2. Encontrar menor caminho entre duas estacoes\n");
//         printf("3. Inserir nova estacao\n");
//         printf("4. Sair\n");
//         printf("5. Desativar Estacao\n");
//         printf("Insira a opcao: ");
//         scanf("%d", &escolha);

//         switch (escolha) {
//         case 1:

//             if(g == NULL){
//                 printf("Grafo não existe!\n");
//                 break;
//             }

//             imprime(g); // Imprime as estações e suas adjacências
//             break;
//         case 2:
//             printf("Digite a estacao de origem (0 a %d): ", g->vertices - 1);
//             scanf("%d", &origem);
//             printf("Digite a estacao de destino (0 a %d): ", g->vertices - 1);
//             scanf("%d", &destino);
//             menor_caminho(g, origem, destino); // Chama o algoritmo de Dijkstra
//             break;
//         case 3:
//             insere_nova_estacao(g); // Insere uma nova estação
//             break;
//         case 4:
//             printf("Saindo do menu...\n");
//             break;
//         case 5:
//             printf("insira a estacao que deseja desativar (0 a %d): ", total_estacoes);
//             scanf("%d",&vertice);
//             remove_vertice(g,vertice);

//             break;

//         default:
//             printf("Opcao invalida, tente novamente.\n");
//         }
//     } while (escolha != 4); // Continua até o usuário escolher a opção de sair
// }
void menu(GRAFO *g)
{
    if (g == NULL)
    {
        printf("Grafo não existe.\n");
        return;
    }

    int origem, destino, escolha, vertice;

    do
    {
        // exibe as opções
        printf("\nMenu:\n");
        printf("1. Imprimir o 'mapa'\n");
        printf("2. Encontrar menor caminho entre duas estacoes\n");
        printf("3. Inserir nova estacao\n");
        printf("4. Sair\n");
        printf("5. Desativar Estacao\n");
        printf("Insira a opcao: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            imprime(g); // Imprime as estações e suas adjacências
            break;
        case 2:
            printf("Digite a estacao de origem (0 a %d): ", total_estacoes - 1);
            scanf("%d", &origem);
            printf("Digite a estacao de destino (0 a %d): ", total_estacoes - 1);
            scanf("%d", &destino);
            menor_caminho(g, origem, destino); // Chama o algoritmo de Dijkstra
            break;
        case 3:
            // insere_nova_estacao(g); // Insere uma nova estação
            printf("Erro! Funcao em manutencao! Tente novamente mais tarde.\n");
            break;
        case 4:
            printf("Saindo do menu...\n");
            break;
        case 5:
            printf("Insira a estacao que deseja desativar (0 a %d): ", total_estacoes - 1);
            scanf("%d", &vertice);
            remove_vertice(g, vertice);
            break;
        default:
            printf("Opcao invalida, tente novamente.\n");
        }
    } while (escolha != 4); // Continua até o usuário escolher a opção de sair
}

void remove_vertice(GRAFO *g, int vertice)
{
    if (vertice < 0 || vertice >= total_estacoes)
    {
        printf("Estação inválida.\n");
        return;
    }

    // Remover todas as arestas que partem deste vértice
    ADJACENCIA *atual = g->adj[vertice].cabeca;
    while (atual != NULL)
    {
        ADJACENCIA *temp = atual;
        atual = atual->prox;
        free(temp); // Libera memória das arestas
    }
    g->adj[vertice].cabeca = NULL;

    // Remover todas as arestas que chegam a este vértice
    for (int i = 0; i < total_estacoes; i++)
    {
        if (i == vertice)
            continue; // Ignora o próprio vértice
        ADJACENCIA *anterior = NULL;
        ADJACENCIA *adjacente = g->adj[i].cabeca;

        while (adjacente != NULL)
        {
            if (adjacente->vertice == vertice)
            {
                if (anterior == NULL)
                {
                    // Remover primeiro elemento da lista
                    g->adj[i].cabeca = adjacente->prox;
                }
                else
                {
                    // Ajustar ponteiros para remover o nó
                    anterior->prox = adjacente->prox;
                }
                free(adjacente);
                break; // Só precisamos remover uma ocorrência
            }
            anterior = adjacente;
            adjacente = adjacente->prox;
        }
    }

    printf("Estação '%s' desativada.\n", g->adj[vertice].nome);
}



//devido a erros na produção, a implementação dessa função assim como a de outras funções foi comprometida
//para evitar que todo o projeto seja prejudicado, optamos por comentar a função e deixar para correções futuras

// booleano abrindo_espacoNoGrafo(GRAFO *grafo)
// {
//     int nova_capacidade = grafo->capacidade + 1;
//     // pensando no desenvolvimento futuro, vamos usar o realloc, assim garantimos que nosso crescimento seja dinâmico e possamos nos desenvolver
//     // sem maiores problemas. Tudo para oferecer o melhor de nossos serviços para os nossos usuários! Tudo pelo dinheiro! Digo, usuários!
//     VERTICE *novo_adj = (VERTICE *)realloc(grafo->adj, nova_capacidade * sizeof(VERTICE));
//     if (novo_adj == NULL)
//     {
//         printf("Erro no realloc: Alguma coisa errada não deu certo.\n");
//         return false;
//     }
//     grafo->adj = novo_adj;
//     grafo->capacidade = nova_capacidade;
//     return true;
// }



//devido a erros na produção, a implementação dessa função assim como a de outras funções foi comprometida
//para evitar que todo o projeto seja prejudicado, optamos por comentar a função e deixar para correções futuras


// void insere_nova_estacao(GRAFO *grafo)
// {

//     if (grafo->vertices >= grafo->capacidade)
//     {
//         if (!abrindo_espacoNoGrafo(grafo))
//         {
//             return; // se não conseguir alocar memória, retornamos para a chamada da função
//         }
//     }
//     char nome[30];
//     char linha[30];

//     int numero_linhas = 0, peso, linhas = 0;

//     printf("Insira o nome da nova estacao: ");
//     fgets(nome, 30, stdin);

//     // do...while para verificar se a quantidade de linhas inserida pelo usuario é ou não válida
//     do
//     {
//         printf("Insira o numero de linhas:(0 a 4): ");
//         scanf("%d", &linhas);
//     } while (numero_linhas < 0 || numero_linhas > 4);

//     numero_linhas = linhas;

//     for (int i = 0; i < numero_linhas; i++)
//     {
//         printf("Insira o nome da linha [%d]: ", i + 1);
//         fgets(linha, 30, stdin);
//         adiciona_linha(&grafo->adj[grafo->vertices], linha);
//     }

//     strcpy(grafo->adj[grafo->vertices].nome, nome);
//     grafo->adj[grafo->vertices].status = true;

//     // ok, criamos uma nova estação, certo? Mas essa estação é inútil se não nos levar a lugar algum, então
//     // vamos usar esse for para verificar se temos um vizinho para conectar com essa nova estação, se tudo funcionar,
//     // a estação se conectará com o vizinho mais próximo

//     for (int i = 0; i < numero_linhas; i++)
//     {
//         strcpy(linha, grafo->adj[grafo->vertices].linhas[i]);
//         booleano vizinhoDeBaixo = false;
//         booleano vizinhoDeCima = false;

//         for (int j = grafo->vertices - 1; j >= 0; j--)
//         {
//             for (int k = 0; k < grafo->adj[j].num_linhas; k++)
//             {
//                 if (strcmp(grafo->adj[j].linhas[k], linha) == 0)
//                 {
//                     printf("Digite o peso da conexão entre %s e %s: ", grafo->adj[j].nome, nome);
//                     scanf("%d", &peso);
//                     cria_aresta(grafo, grafo->vertices, j, peso);
//                     cria_aresta(grafo, j, grafo->vertices, peso);
//                     vizinhoDeBaixo = true;
//                     break;
//                 }
//             }
//             if (vizinhoDeBaixo)
//             {
//                 break;
//             }
//         }

//         // Procurar a estação vizinha posterior na mesma linha
//         for (int j = grafo->vertices + 1; j < grafo->vertices; j++)
//         {
//             for (int k = 0; k < grafo->adj[j].num_linhas; k++)
//             {
//                 if (strcmp(grafo->adj[j].linhas[k], linha) == 0)
//                 {
//                     printf("Digite o peso da conexão entre %s e %s: ", grafo->adj[j].nome, nome);
//                     scanf("%d", &peso);
//                     cria_aresta(grafo, grafo->vertices, j, peso);
//                     cria_aresta(grafo, j, grafo->vertices, peso);
//                     vizinhoDeCima = true;
//                     break;
//                 }
//             }
//             if (vizinhoDeCima)
//             {
//                 break;
//             }
//         }
//     }

//     grafo->vertices++;
// }
