#include <stdio.h>
#include <stdlib.h>

typedef struct node{//criação de nó padrão para implementar na estrutura

    int weight;
    struct node * bottom;
}Node;

typedef struct stk{//estrutura designada para pilha, que recebe os nós

    Node * top;
    int size;
}Stack;

Stack * initStack(void){//função de inicializar uma pilha, um constructor

    Stack * auxStk = malloc(sizeof(Stack));
    auxStk -> top = NULL;
    auxStk -> size = 0;

    return auxStk;
}

void push(Stack * auxStk, int value){//adiciona elementos à pilha

    Node * newNode = malloc(sizeof(Node));
    newNode -> weight = value;
    newNode -> bottom = NULL;

    if (auxStk -> top == NULL){
        auxStk -> top = newNode;
    }else{

        newNode -> bottom = auxStk -> top;
        auxStk -> top = newNode;
    }
    auxStk -> size++;
}

int pop(Stack * auxStk){//remove elementos existentes na pilha

    Node * garbage = auxStk -> top;
    int value = 0;

    if (auxStk -> top != NULL){

        value = auxStk -> top -> weight;
        auxStk -> top = auxStk -> top -> bottom;
    }

    free(garbage);
    auxStk -> size--;
    return value;
}

void printStack(Stack * auxStk){

    Node * auxPrint = auxStk -> top;

    printf("\nTopo -> ");
    while (auxPrint != NULL){

        printf("%dt ", auxPrint -> weight);
        auxPrint = auxPrint -> bottom;
    }
    printf("<- Base <=> Tamanho: %d\n", auxStk -> size);
}

int main(){

    Stack * stackA = initStack();
    Stack * stackB = initStack();
    Stack * stackC = initStack();
    int inputUser, cont = 1;

    printf("Quantas cargas a adicionar: ");
    scanf("%d", &inputUser);

    do{
        int cargo;
        printf("Adicionar nova carga a pilha: ");
        scanf("%d", &cargo);

        if (cargo == 3 || cargo == 5 || cargo == 7){

            if (stackA -> top == NULL){//pilha principal vazia
                push(stackA, cargo);
            }else{//há elementos em A

                if (stackA -> top -> weight == 7){//Caso base
                    push(stackA, cargo);
                }else{//As condições possíveis

                    if (cargo == 7){

                            while (stackA -> size != 0 && stackA -> top -> weight != 7){

                                if (stackA -> top -> weight == 5){

                                    push(stackB, stackA -> top -> weight);
                                    pop(stackA);
                                }else{

                                    push(stackC, stackA -> top -> weight);
                                    pop(stackA);
                                }
                            }
                        push(stackA, cargo);
                    }else if (cargo == 5){

                        while (stackA -> size != 0 && stackA -> top -> weight != 5 && stackA -> top -> weight != 7){

                            push(stackC, stackA -> top -> weight);
                            pop(stackA);
                        }
                        push(stackA, cargo);
                    }else{ push(stackA, cargo); }
                }
            }
        }else{ printf("Carga invalida para empilhamento.\n"); }

        cont++;
    }while (cont <= inputUser);

    while (stackB -> top != NULL){

        if (stackA -> top -> weight == 3){

            while (stackA -> size != 0 && stackA -> top -> weight != 7){

                push(stackC, stackA -> top -> weight);
                pop(stackA);
            }
        }
        push(stackA, stackB -> top -> weight);
        pop(stackB);
    }

    while (stackC -> top != NULL){

        push(stackA, stackC -> top -> weight);
        pop(stackC);
    }

    printStack(stackA);
    printStack(stackB);
    printStack(stackC);

    return 0;
}
