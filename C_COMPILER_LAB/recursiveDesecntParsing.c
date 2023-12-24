#include<stdio.h>
#include<string.h>
#include<ctype.h>

// char inputString[]="a*((b+c))$";
char inputString[20];
int pointer= 0;
int brackets = 0;

void checkF();
void checkP();
void checkM();

int main(){

    printf("give the expression\n");
    scanf("%s",inputString);
    inputString[strlen(inputString)]='$';

    checkF();

    if(inputString[pointer]=='$'&&brackets==0){
        printf("valid\n");

    }else{
        printf("invalid\n");
    }


    
}

void checkP(){
    
    checkM();
    if(inputString[pointer]=='+'){

        pointer++;
        checkF();
    }
   
}
void checkM(){
    
    if(inputString[pointer]=='*'){

        pointer++;
        checkF();
    }
}
void checkF(){
    
    if(isalnum(inputString[pointer])){

        pointer++;
        checkP();

    }
    else if(inputString[pointer]== '('){

        pointer++;
        brackets++;
        checkF();

        if(inputString[pointer]==')'){


            pointer++;
            brackets--;
        }

    }
}