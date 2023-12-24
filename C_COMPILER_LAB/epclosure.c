#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STATE_COUNT 20

struct Transitions
{
    char alphabet;
    int destState;
    
};

struct state
{
    struct Transitions *TranArr;
};

int statecount = 0, transicount =0, transiLenghtArr[MAX_STATE_COUNT];

struct state * statespointer;



void SetTransitions();
void printFilled(int arr[]);
void printStatesDetails(int currentstate);
void printtrans(int currentstate,struct Transitions *TranArr);
int* FindEpsilonClosure(int currentstate);
int* findEpsilon(int currentstatenum);
int* fill(int size);




int main(){
    printf("give the total number of states \n");
    scanf("%d",&statecount);

    SetTransitions();
    for(int i =0;i<statecount;i++){
        
        int *value = FindEpsilonClosure(i);
        printf("epsilon closure of state %d\n",i);
        printFilled(value);
        free(value);
    }
    free(statespointer);

}


void SetTransitions(){
    struct state * states;

    states  = (struct state*)malloc(statecount*sizeof(struct state));
    if (states == NULL) {
        fprintf(stderr, "Memory allocation for states failed\n");
        exit(EXIT_FAILURE); 
    }
    statespointer = states;

    char current[20];
    int source;
    int alpha;
    int dest;

    for(int i=0;i<statecount;i++){

        printf("give the number of transition from state %d\n",i);
        scanf("%d",&transicount);
        transiLenghtArr[i]=transicount;
        if(transicount!=0){
            
        struct Transitions *transiArr;
        transiArr = (struct Transitions *)malloc(transicount*sizeof(struct Transitions));
        if (transiArr == NULL) {
        fprintf(stderr, "Memory allocation for states failed\n");
        exit(EXIT_FAILURE); 
        }

        for(int j = 0;j<transicount;j++){
            printf("give the alphabet and destination of  %dth transition\n",j);
            scanf("%s",current);
            char alpha =  current[1];
            int dest =  current[2]-'0';
            transiArr[j].alphabet = alpha;
            transiArr[j].destState = dest;
        }
    
        states[i].TranArr = transiArr;
        }else{
            states[i].TranArr = NULL;
        }



}


 
}

int* FindEpsilonClosure(int currentstate){

        int checkedPoint=0;
        int *closure = findEpsilon(currentstate);
        
        checkedPoint++;

      
        while(closure[checkedPoint]!=9999){
            int *temp = findEpsilon(closure[checkedPoint]);
           
            int tempPointr=1;
            checkedPoint++;

            for(int i =0;i<20;i++){

                if(closure[i]==9999&&temp[tempPointr]!=9999){
                    closure[i]=temp[tempPointr];
                    tempPointr++;
                }
            }

            free(temp);
    
        }
    return closure;

  


}



int* findEpsilon(int currentstatenum){

    struct state currentstate = statespointer[currentstatenum];
    int *epsilnstates = fill(20);
    int epsilonPointer=0;
  
    epsilnstates[epsilonPointer]= currentstatenum;
    epsilonPointer++;

    for(int i =0;i<transiLenghtArr[currentstatenum];i++){

        if(currentstate.TranArr[i].alphabet=='e'){

            epsilnstates[epsilonPointer] = currentstate.TranArr[i].destState;    
            epsilonPointer++;
        }
    }
    return epsilnstates;

}


int* fill(int size){
    int *arr = malloc(size*sizeof(int));
    for(int i=0;i<size;i++){
        arr[i]=9999;
    }
    if (arr == NULL) {
    fprintf(stderr, "Memory allocation for states failed\n");
    exit(EXIT_FAILURE);
}
return arr;

}
void printFilled(int arr[]){
int arrpoint=0;
while(arr[arrpoint]!=9999){
    printf("%d\n",arr[arrpoint]);
    arrpoint++;
}
}
void printtrans(int currentstate,struct Transitions *TranArr){
    
    printf("state no : %d\n",currentstate);
    for(int i = 0 ;i<transiLenghtArr[currentstate];i++){
        printf("{alphabet : %c ,destination : %d}\n",TranArr[i].alphabet,TranArr[i].destState);
    }
}
void printStatesDetails(int currentstate){

    struct state currntstate =statespointer[currentstate];

    printtrans(currentstate,currntstate.TranArr);


}