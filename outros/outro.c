#include <stdio.h>
#include <stdlib.h>

// Definição do nó da lista
struct Node {
    int data;
    struct Node* next;
};

// Função para adicionar um nó no início da lista
void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

// Função para imprimir a lista
void printList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

// Função principal
int main() {
    struct Node* head = NULL;

    push(&head, 1);
    push(&head, 2);
    push(&head, 3);
    push(&head, 4);

    printf("Lista encadeada: ");
    printList(head);

    return 0;
}