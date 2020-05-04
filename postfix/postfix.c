#define SIZE 20 /* Size of Stack */
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define ERROR printf("Error in position:\n")
char    s[SIZE];
double s2[SIZE];
int top = -1; /* global declarations */
int top2 = -1;
/* ADT */
void    RemoveSpaces(char*);
void    push(char);
char    pop(void);
void    push2(double); //evaluate postfix
double  pop2(void);        //evaluate postfix
int     pr(char);
void    to_postfix(char *,char *);
double  eval_postfix(char *);
void    isNegative(char *);
int     Check_input(char *);

int main() {

    while(1) {
        char infx[20], pofx[20];
        printf("Please enter an infix expression and press enter:\n(If you want to exit, please press Blank Key then press Enter)\n" );
        fgets(infx,50, stdin);
        while(strlen(infx)-1>SIZE){
            printf("Error - line contains more characters than allowed.\n");
            printf("Please enter an infix expression and press enter:\n" );
            fgets(infx,50, stdin);
        }
        while(Check_input(infx)!=0){
            printf("Please enter an infix expression and press enter:\n" );
            fgets(infx,50, stdin);
        }
        Check_input(infx);
        if(infx[0]==' '){
                return 0;
            }
        isNegative(infx);
        to_postfix(infx, pofx);
        printf("The postfix expression: %s ",pofx);
        top = -1;
        printf(" \n= %.4f\n", eval_postfix(pofx));
    }
}


/*remove spaces from given string */
void RemoveSpaces(char* source) {
    char* i = source;
    char* j = source;
    while(*j!=0) {
        *i = *j++;
        if(*i != ' ')
            i++;
    }
    *i = 0;
}

/*PUSH*/
void push(char elem) {
    s[++top] = elem;
}

/*POP*/
char pop() {
    return (s[top--]);
}
/*PUSH2  */
void push2(double elem) {
    s2[++top2] = elem;
}

/*POP2 */
double pop2() {
    return (s2[top2--]);
}
/*precedence */
int pr(char elem) {
    switch (elem) {
        case '#':
            return 0;
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
    }
    return 0;
}


/*infix to postfix*/
void to_postfix(char *infix, char *postfix) {
    char ch, elem;
    int i = 0, k = 0;
    RemoveSpaces(infix);
    push('#');

    while ((ch = infix[i++]) != '\n') {
        if (ch == '(')
            push(ch);
        else if (isalnum(ch))
            postfix[k++] = ch;
        else if (ch == ')') {
            while (s[top] != '(')
                postfix[k++] = pop();
            elem = pop(); /* Remove ( */
        }
        else { /* Operator */
            while (pr(s[top]) >= pr(ch))
                postfix[k++] = pop();
            push(ch);
        }
    }
    while (s[top] != '#') /* Pop from stack till empty */
        postfix[k++] = pop();
    postfix[k] = 0; /* Make postfix as valid string */
}

/*evaluate postfix*/
double eval_postfix(char *postfix) {
    char ch;
    int i = 0;
    double op1, op2;
    while((ch = postfix[i++]) != 0) {
        if(isdigit(ch))
            push2(ch-'0'); /* push operand */
        else { /* pop two operands */
            op2 = pop2();
            op1 = pop2();
            switch(ch) {
                case '+' : push2(op1+op2);
                    break;
                case '-' : push2(op1-op2);
                    break;
                case '*' : push2(op1*op2);
                    break;
                case '/' : push2((op1+0.0)/(op2+0.0));
                    break;
            }
        }
    }
    return s2[top2];
}

void isNegative(char *infix){ //3*(-3) idk
    for(int i=0;infix[i]!= '\n';i++){
        if(infix[i]=='(' && infix[i+1]=='-'&&infix[0]!='('){
            if((infix[i-1]=='+')||(infix[i-1]=='-')){
                if(infix[i-1]=='-'){
                    infix[i+1]='+';}
                int a=2;
                for(int j=i-1;infix[j]!= '\n';j++){
                    infix[j]=infix[j+a];
                    if(infix[j]==')'){
                        a=3; infix[j]=infix[j+a];}
                }
            }
            else if((infix[i-1]=='*')||(infix[i-1]=='/')){
                int b=i-3;
                //do{
                if(infix[b]=='-'){
                    infix[b]='+';}
                else if(infix[b]=='+'){
                    infix[b]='-';}
                else {
                    do{b--;
                        if(infix[b]=='-'){
                            infix[b]='+';}
                        else if(infix[b]=='+'){
                            infix[b]='-';}
                    }
                    while(b!='-'||b!='+');}
                //else{b--;}
                //}while((infix[b]!='*')||(infix[b]!='/'));
                int a=2;
                for(int j=i;infix[j]!= '\n';j++){
                    infix[j]=infix[j+a];
                    if(infix[j]==')'){
                        a=3; infix[j]=infix[j+a];}
                }
            }
        }
    }
    //printf("%s\n ",infix);
}

int Check_input(char *infix){
    int lpare=0,rpare=0,num=0,op=0;
    int count=0,tagr=0,tagl=-1;
    if(infix[0]==' '){
                return 0;
            }
    if(infix[0]=='+'||infix[0]=='-'||infix[0]=='*'||infix[0]=='/'){
        if(count==0)
            ERROR;count++;
        printf(" In the 1st character, First character an operator.\n");
    }
    if(infix[strlen(infix-1)]=='+'||infix[strlen(infix-1)]=='-'||infix[strlen(infix-1)]=='*'||infix[strlen(infix-1)]=='/'){
        if(count==0)
            ERROR;count++;
        printf(" In the %dth character, Last character an operator.\n",strlen(infix-1));
    }
    int tag[SIZE]={};
    for(int i=0;i<SIZE;i++){tag[i]='\n';}
    for(int i=0;infix[i]!= '\n';i++){

        if (isdigit(infix[i])){
            tag[i]=infix[i]-'0';num++;}
        else if(infix[i]=='+'||infix[i]=='-'||infix[i]=='*'||infix[i]=='/'){
            tag[i]=infix[i];op++;}
        else if(infix[i]==')'){
            tag[i]=infix[i];rpare++;tagr=i;}
        else if(infix[i]=='('){
            tag[i]=infix[i];lpare++;
            if(tagl==-1){tagl=i;}}
        else  {
            if(count==0)
                ERROR;count++;
            printf("In the %dth character, Illegal character.\n",i+1);
        }
    }
    if(num==0||op==0){
        if(count==0)
            ERROR;count++;
        printf("Illegal operand.\n");
    }
    for(int i=0;i<(strlen(infix)-1);i++){
        if (tag[i]=='('){
            if(tag[i+1]=='+'||tag[i+1]=='*'||tag[i+1]=='/'){
                if(count==0)
                    ERROR;count++;
                printf("In the %d-%dth, Left parenthesis followed by an operator.\n",i+1,i+2);}
            if(((0<=tag[i-1]&&tag[i-1]<=9))&&tag[0]!='('){
                if(tag[i-1]!='+'&&tag[i-1]!='*'&&tag[i-1]!='/'&&tag[i-1]!='-'){
                    if(count==0)
                        ERROR;count++;
                    printf("In the %d-%dth, Identifier followed by a left parenthesis.\n",i,i+1);}}
            if(tag[i+1]==')'){
                if(count==0)
                    ERROR;count++;
                printf("In the %d-%dth, Left parenthesis followed by a right parenthesis.\n",i+1,i+2);}
            if(tag[i-1]==')'){
                if(count==0)
                    ERROR;count++;
                printf("In the %d-%dth, Right parenthesis followed by a left parenthesis.\n",i,i+1);}
        }
        if (tag[i]==')'){
            if(tag[i-1]=='+'||tag[i-1]=='*'||tag[i-1]=='/'||tag[i-1]=='-'){
                if(count==0)
                    ERROR;count++;
                printf("In the %d-%dth, Operator followed by a right parenthesis.\n",i,i+1);}
            if(0<=tag[i+1]&&tag[i+1]<=9){
                if(tag[i+1]!='+'&&tag[i+1]!='*'&&tag[i+1]!='/'&&tag[i+1]!='-'&&tag[i+1]!='\n'&&tag[i+1]!=')'){
                    if(count==0)
                        ERROR;count++;
                    printf("In the %d-%dth, Right parenthesis followed by an identifier.\n",i+1,i+2);}}
        }
        if(tag[i]=='+'||tag[i]=='*'||tag[i]=='/'||tag[i]=='-'){
            if(tag[i+1]=='+'||tag[i+1]=='*'||tag[i+1]=='/'||tag[i+1]=='-'){
                if(count==0)
                    ERROR;count++;
                printf("In the %d-%dth, Operator followed by an operator\n",i+1,i+2);}
        }
    }
    if(rpare>lpare){
        if(count==0)
            ERROR;count++;

        printf("In the %dth, Unmatched right parenthesis.\n",tagr+1);
    }
    else if(rpare<lpare){
        if(count==0)
            ERROR;count++;
        printf("In the %dth, Unmatched left parenthesis.\n",tagl+1);
    }
    return count;
}


