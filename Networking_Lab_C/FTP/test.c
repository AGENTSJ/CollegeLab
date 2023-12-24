#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(){
    FILE *fp;
    char sendStream[100];
    fp = fopen("tempr.txt","r");

    fgets(sendStream,sizeof(sendStream),fp);

    printf("%s\n", sendStream);
}