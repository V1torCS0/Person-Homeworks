#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int value;
    struct node * ndNext;
}Node;

typedef struct stack{

    int size;
    Node * topStk;
    struct stack * stkNext;
}Stack;

typedef struct mainqe{

    int size;
    Stack * head;
    Stack * tail;
}MainQueue;

Node * createNode(int value){

    Node * auxNode = malloc(sizeof(Node));

    auxNode -> value = value;
    auxNode -> ndNext = NULL;
    return auxNode;
}

Stack * createStk(void){

    Stack * auxStk = malloc(sizeof(Stack));

    auxStk -> size = 0;
    auxStk -> topStk = NULL;
    auxStk -> stkNext = NULL;
    return auxStk;
}

MainQueue * createMain(void){

    MainQueue * auxMain = malloc(sizeof(MainQueue));

    auxMain -> head = NULL;
    auxMain -> tail = NULL;
    auxMain -> size = 0;
    return auxMain;
}

void push(int newValue, Stack * auxStk){

    Node * newNode = createNode(newValue);

    newNode -> ndNext = auxStk -> topStk;
    auxStk -> topStk = newNode;
    auxStk -> size++;
}

int pop(Stack * auxStk){

    int valueReturned = -1;
    if (auxStk -> topStk != NULL){

        Node * ndGarbage = auxStk -> topStk;
        valueReturned = auxStk -> topStk -> value;
        auxStk -> topStk = auxStk -> topStk -> ndNext;

        free(ndGarbage);
        auxStk -> size--;
    }
    return valueReturned;
}

void printStk(Stack * auxStk){

    Node * auxPrint = auxStk -> topStk;

    printf("|Top -> ");
    while (auxPrint != NULL){

        printf("%d ", auxPrint -> value);
        auxPrint = auxPrint -> ndNext;
    }
    printf("<- Base <=> Size: %d|", auxStk -> size);
}

void enqueue(Stack * auxStk, MainQueue * auxMain){

    if (auxMain -> head == NULL){

        auxMain -> head = auxStk;
        auxMain -> tail = auxStk;
    }else{

        auxMain -> tail -> stkNext = auxStk;
        auxMain -> tail = auxStk;
    }
    auxMain -> size++;
}

void dequeue(MainQueue * auxMain){

    if (auxMain -> size != 0){

        Stack * stkGarbage = auxMain -> head;
        Node * ndReturned = auxMain -> head -> topStk;
        auxMain -> head = auxMain -> head -> stkNext;

        printf("Removed Elements: ( ");
        while (ndReturned != NULL){
            
            printf("%d ", ndReturned -> value);
            ndReturned = ndReturned -> ndNext;
        }
        printf(")\n");

        free(stkGarbage);
        auxMain -> size--;        
    }else{ printf("Empty Queue\n");}
}

void printMain(MainQueue * auxMain){

    Stack * auxPrint = auxMain -> head;

    printf("\nHead ->(");
    while (auxPrint != NULL){

        printStk(auxPrint);
        auxPrint = auxPrint -> stkNext;
    }
    printf(")<- Tail <=> Size: %d\n", auxMain -> size);

}

int main(void){

    Stack * pilha = createStk();
    Stack * pilha2 = createStk();
    MainQueue * fila = createMain();
    
    push(27, pilha);
    push(36, pilha);
    push(45, pilha);
    push(54, pilha);
    push(63, pilha);
    pop(pilha);

    enqueue(pilha, fila);
    enqueue(pilha2, fila);
    printMain(fila);

    dequeue(fila);
    printMain(fila);

    dequeue(fila);
    dequeue(fila);
    printMain(fila);
    return 0;
}