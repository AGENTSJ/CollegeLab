#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stack[20];int top=0;
char inputString[20];int pointer=0;
char Production[5][4] = {
        "E+E",
        "E-E",
        "E*E",
        "(E)",
        "i"
    };

int checkProduction(char Substk[]);
void checkStack();
void updateStack(char Substk[]);
int main(){

    stack[top] = '$';
    top++;
  

    strcpy(inputString,"i*i+i");
    int len = strlen(inputString);
    inputString[len]= '$';
    
    while(inputString[pointer]!='$'){
        
        printf("shift %c\n",inputString[pointer]);
        stack[top] = inputString[pointer];
        puts(stack);
        top++;

        checkStack();

        pointer++;
        
    }
    if(stack[1]=='E'){
        printf("ACCEPT\n");
    }else{
        puts("ERROR / REJECT");
    }

    





}
int checkProduction(char Substk[]){
    for(int i = 0;i<5;i++){
        
        int val = strcmp(Substk,Production[i]);
        if(val==0){

            printf("reduce %s to E\n" ,Substk);
            
            return val;
        }  
    }   
}
void updateStack(char Substk[]){

int len = strlen(Substk);

    for(int j=0;j<len;j++){//reducing

        if(j==len-1){//last elem
            top--;
            stack[top]='E';
            top++;
        }else{
            top--;
            stack[top]='\0';
            
        }
    }
    puts(stack);
}
void checkStack(){

    int Dial = strlen(stack)-1;

    while(Dial!=0){
        
        int result = checkProduction(stack+Dial);
        if(result==0){
            
            updateStack(stack+Dial);
            checkStack();
            break;
        }

        Dial--;
    }
}