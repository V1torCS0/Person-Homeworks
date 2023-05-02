#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct node{

    int operand;
    struct node * bottom;
}Node;

typedef struct stk{

    Node * top;
    int size;
}Stack;

Stack * initCalc(void){

    Stack * auxStk = malloc(sizeof(Stack));
    auxStk -> top = NULL;
    auxStk -> size = 0;

    return auxStk;
}

void pushCalc(Stack * auxStk, int value){

    Node * newNode = malloc(sizeof(Node));
    newNode -> operand = value;
    newNode -> bottom = NULL;

    if (auxStk -> top == NULL){
        auxStk -> top = newNode;
    }else{

        newNode -> bottom = auxStk -> top;
        auxStk -> top = newNode;
    }
    auxStk -> size++;
}

int popCalc(Stack * auxStk){

    Node * garbage = auxStk -> top;
    int value = 0;

    if (auxStk -> top != NULL){

        value = auxStk -> top -> operand;
        auxStk -> top = auxStk -> top -> bottom;
    }

    free(garbage);
    auxStk -> size--;
    return value;
}

void printStkCalc(Stack * auxStk){

    Node * auxPrint = auxStk -> top;

    printf("Topo -> ");
    while (auxPrint != NULL){

        printf("%d ", auxPrint -> operand);
        auxPrint = auxPrint -> bottom;
    }
    printf("<- Base\nTamanho: %d\n", auxStk -> size);
}


int main(void){

    Stack * operandStk = initCalc();

    char inputUser[20];

    printf("Adicione uma entrada: ");
    fgets(inputUser, 20, stdin);

    for (int i = 0; inputUser[i] != '\0'; i++){

        if (isdigit(inputUser[i])){

            int operand = atoi(&inputUser[i]);
            pushCalc(operandStk, operand);

            while (isdigit(inputUser[i])){
                i++;
            }
            i--;
        }else if (isspace(inputUser[i])){
            continue;
        }else{

            int operandOne = popCalc(operandStk), operandTwo = popCalc(operandStk);
            int result;

            switch (inputUser[i]){

                case '+': result = operandTwo + operandOne; break;
                case '-': result = operandTwo - operandOne; break;
                case '*': result = operandTwo * operandOne; break;
                case '/': result = operandTwo / operandOne; break;
                
                default: printf("Expressao que nao consta.\n"); exit(1);
            }
            pushCalc(operandStk, result);
        }
    }

    int resultExpression = popCalc(operandStk);

    if (operandStk -> top != NULL) { 
        printf("Sentenca numerica nao formulada corretamente.\n");
        exit(1);    
    }else{ printf("RESULTADO = %d\n", resultExpression); exit(0); }
}