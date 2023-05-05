#include <stdio.h>
#include <stdlib.h>

typedef struct node{

    int value;
    struct node * ndNext;
}Node;

typedef struct stack{

    int size;
    Node * topStk;//ponteiro que 'armazena' nós em uma pilha
    struct stack * stkNext;//ponteiro que linka uma pilha à outra pilha
}Stack;

typedef struct mainstk{

    int size;
    Stack * topMain;    
}MainStack;

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

MainStack * initMain(void){

    MainStack * auxMain = malloc(sizeof(MainStack));

    auxMain -> size = 0;
    auxMain -> topMain = NULL;
    return auxMain;
}

//funções da pilha coumum

void pushStk(int value, Stack * auxStk){

    Node * newNode = createNode(value);

    newNode -> ndNext = auxStk -> topStk;
    auxStk -> topStk = newNode;
    auxStk -> size++;
}

int popStk(Stack * auxStk){

    int valueReturned = -1;
    if (auxStk -> topStk != NULL){

        Node * garbage = auxStk -> topStk;
        valueReturned = auxStk -> topStk -> value;
        auxStk -> topStk = auxStk -> topStk -> ndNext;

        free(garbage);
        auxStk -> size--;
    }
    return valueReturned;
}

void printStk(Stack * auxStk){

    Node * auxPrint = auxStk -> topStk;

    printf("\nTop -> ");
    while (auxPrint != NULL){

        printf("%d ", auxPrint -> value);
        auxPrint = auxPrint -> ndNext;
    }
    printf("<- Base <=> Size: %d\n", auxStk -> size);
}

int main(){ 
    
    Stack * pilha = createStk();

    pushStk(19, pilha);
    pushStk(23, pilha);
    pushStk(48, pilha);
    pushStk(93, pilha);
    popStk(pilha);

    printStk(pilha);
    
    return 0; 
}