#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mem.h>
#include <math.h>
#include <string.h>

struct node
{
    int data;    //data in node
    struct node* next;   //address tp next node
};
struct node* push(struct node* top,double data) // push an element onto the stack
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if(temp == NULL)
    {
        exit(0);
    }
    temp->data = data;
    temp->next = top;
    top = temp;
    return top;
}
struct node* pop(struct node *top,double *item) //pop element off the stack
{
    struct node* tmp = top;
    *item = top->data;
    top = top->next;
    free(tmp);
    return top;
}
void initialize(struct node* top)
{
    top = NULL;
}
int empty(struct node* top)  //checking if stack is empty or not. 1 if empty
{
    return top == NULL ? 1 : 0;

}
void printStack(struct node* top)
{
    struct node *current;
    current = top;
    if(current == NULL)
    {
        printf("Stack empty\n");

    }
    else
    {
        printf("\nItem on stack ");

            while(current != NULL)
        {
            printf("%d ",current->data);
            current = current->next;
        }
        printf("\n ----------------");
    }


}
char stack[20];
int top = -1;
void push1(char x)
{
    stack[++top] = x;
}
char pop1()
{
    if(top == -1)
        return -1;
    else
        return stack[top--];
}

int priority(char x)
{
    if(x == 40)
        return 0;
    if(x == 43 || x == 45)
        return 1;
    if(x == 42 || x == 47)
        return 2;
}
char postFixCalculation(char infixConverted) {
    struct node* top = NULL;
    int size = 128;
    char element[128];
    double number1, number2, answer;
    FILE *file = fopen("file.txt", "r");
    char *ch = fgets(element, size, file);
    ch = strtok (element," ");
    initialize(top);
    while (ch != NULL)
    {
        if(strchr("  ", ch[0]) ) {
            printStack(top);

        }
        else if(priority(strchr("+-X/^", ch[0])) ){
            switch(ch[0]){
                case 43 :
                    printf("%s  ", ch);
                    top = pop(top, &number1);
                    top = pop(top, &number2);
                    answer = number1 + number2;
                    top = push(top, answer);
                    printStack(top);
                    break;


                case 45 :
                    printf("%s  ", ch);
                    top = pop(top, &number1);
                    top = pop(top, &number2);
                    answer = number1 - number2;
                    top = push(top, answer);
                    printStack(top);
                    break;
                case 88 :
                    printf("%s ", ch);
                    top = pop(top, &number1);
                    top = pop(top, &number2);
                    answer = number1 * number2;
                    top = push(top, answer);
                    printStack(top);
                    break;
                case 47 :
                    printf("%s  ", ch);
                    top = pop(top, &number1);
                    top = pop(top, &number2);
                    answer = number1 / number2;
                    top = push(top, answer);
                    printStack(top);
                    break;
                case 94 :
                    printf("%s  ", ch);
                    top = pop(top, &number1);
                    top = pop(top, &number2);
                    answer = pow(number2, number1);
                    top = push(top, answer);
                    printStack(top);
                    break;

            }
        }
        else if(ch[0] >= 48 && ch[0] <= 57){
            double number = atof(ch);
            top = push(top, number);
            printStack(top);
        }
        ch = strtok(NULL, " ");
    }
    char answer123 = top;
    return answer123;
}

char infixToPostfix()
{
    char element[128];
    char exp[20];
    char x, *eof;
    FILE *file = fopen("file.txt", "r");
    int size = 128;
    char *ch = fgets(element, size, file);
    ch = strtok (element," ");
    eof = ch;
    while(*eof != '\0')
    {
        if(*eof == 40)
            push1(*eof);
        else if(*eof == 41)
        {
            while((x = pop1()) != 40)
                printf("%c ", x);
        }
        else if(isalnum(*eof))
            printf("%c ",*eof);
        else
        {
            while(priority(stack[top]) >= priority(*eof))
                printf("%c ",pop1());
            push1(*eof);
        }
        eof++;
    }
    while(top != -1)
    {
        printf("%c",pop1());
    }
    char infixConverted = pop1();
    return infixConverted;
}
int main(int argc, char ** argv)

{
    int fullResult = 0;

    //postFixCalculation(infixToPostfix());



    FILE *filename = fopen("file.txt", "r");

    if ( argc == 1 ) {
        printf("Error: No input filename provided\n");
        printf("Usage: %s file.txt\n", argv[0]);
        exit(1);
    }
    else if ( argc > 2 ) {
        printf("Error: Too many command line parameters\n");
        printf("Usage: %s file.txt\n", argv[0]);
        exit(1);
    }
    else {
        filename = argv[1];
    }
    char inputFile[128] = {' '};
    char inArray[128] = {' '};
    char changedInput[128] = {' '};
    FILE *pToFile = fopen("filename", " r ");
    // create the output file
    FILE *myFile = fopen("file.results.txt", "w");
    while(fgets(inputFile, 128, pToFile)) {
        for (int i = 0; i < 128; i++) {
            if(inputFile[i] != '\n')
                fprintf(myFile, "%c", inputFile[i]);
        }
        if( inputFile[0] == 'i') {
            infixToPostfix(inArray);
              fullResult = infixToPostfix();
            } else {
            for (int i = 8; i <128 ; i++) {
                changedInput[i - 8] = inputFile[i];

            }
            fullResult = postFixCalculation(changedInput);
        }
        fprintf(myFile, "\n %g  ", fullResult);

    }
    fclose(pToFile);
    fclose(myFile);
}
