#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


struct Production{
    char Lhs ;
    char Rhs[20];
}production[20];

int numberofProduction=4;
char StartSymbol;
void TakeInput();
void First(char *first,char elm);
void Follow(char *follow,char elm);


int FirstPointer=0;
int followPointer = 0;

int main(){

{production[0].Lhs='S';
strcpy(production[0].Rhs, "cAd");
StartSymbol='S';
production[1].Lhs='A';
strcpy(production[1].Rhs, "bc");
production[2].Lhs='A';
strcpy(production[2].Rhs, "SB");
production[3].Lhs='B';
strcpy(production[3].Rhs, "e");
}

char fol[20]={0};
Follow(fol,'S');
puts(fol);

}


void First(char *first,char elm){

   

    if(islower(elm)){
        
     
        first[FirstPointer]=elm;
       
        FirstPointer++;

               

    }else if (isupper(elm)){

        //Alphabet
        
        for(int i=0;i<numberofProduction;i++){

            if(production[i].Lhs==elm){
                
                First(first,production[i].Rhs[0]);
            }
        }

    }

    

}
void TakeInput(){
    printf("give the number of productions\n");
    scanf("%d",&numberofProduction);
    puts("give the Productions");
    for(int i=0;i<numberofProduction;i++){
        char current[20];
        scanf("%s",current);
        production[i].Lhs = current[0];
        strcpy(production[i].Rhs,current+2);
        

    }


}

void Follow(char *follow,char elm){
    FirstPointer=0;
   
    if(elm==StartSymbol){

        follow[followPointer]='$';
        followPointer++;
    
    }

    for(int i=0;i<numberofProduction;i++){
        
        //for each poduction checking rhs
        for(int j=0;j<strlen(production[i].Rhs);j++){
            
            //checking ecah value in rhs
            
            if(production[i].Rhs[j]==elm && j==strlen(production[i].Rhs)-1){//check if its posion at end

                
                Follow(follow,production[i].Lhs);

            }else if(production[i].Rhs[j]==elm){
                //taking first of left alpbaet

                
             
                char fir[20] ={0};
                
                First(fir,production[i].Rhs[j+1]);
                
                for(int k=0;k<strlen(fir);k++){
                    

                    if(fir[k]!='e'){//if no epsioln in first of left alpbaet

                        follow[followPointer]= fir[k];
                        followPointer++;
                        
                    }else{//if there is epsilon
                        
                        Follow(follow,production[i].Lhs);
                    }
                    
                }
                

            }
        }
    }
}