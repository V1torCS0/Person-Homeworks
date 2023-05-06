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

MainStack * createMain(void){

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

//funções da pilha main

void pushMain(Stack * auxStk, MainStack * auxMain){

    auxStk -> stkNext = auxMain -> topMain;
    auxMain -> topMain = auxStk;
    auxMain -> size++;
}

void popMain(MainStack * auxMain){

    if (auxMain -> topMain != NULL){

        Stack * stkGarbage = auxMain -> topMain;
        Node * ndReturned = auxMain -> topMain -> topStk; 
        auxMain -> topMain = auxMain -> topMain -> stkNext;
        
        printf("Removed Elements: ( ");
        while (ndReturned != NULL){
            
            printf("%d ", ndReturned -> value);
            ndReturned = ndReturned -> ndNext;
        }
        printf(")\n");
        
        free(stkGarbage);
        auxMain -> size--;
    }else{ printf("Empty Stack\n");}
}

void printMain(MainStack * auxMain){

    Stack * auxPrint = auxMain -> topMain;

    printf("\nTop ->(");
    while (auxPrint != NULL){

        printStk(auxPrint);
        auxPrint = auxPrint -> stkNext;
    }
    printf(")<- Base <=> Size: %d\n", auxMain -> size);
}

int main(){ 
    
    Stack * pilha = createStk();
    Stack * pilha2 = createStk();
    MainStack * masterPilha = createMain();

    pushStk(19, pilha);
    pushStk(23, pilha);
    pushStk(48, pilha);
    pushStk(93, pilha);
    popStk(pilha);

    pushMain(pilha, masterPilha);
    pushMain(pilha2, masterPilha);
    printMain(masterPilha);
    popMain(masterPilha);
    popMain(masterPilha);
    printMain(masterPilha);
    popMain(masterPilha);
    return 0; 
}