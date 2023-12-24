#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#define PORT  3000

int main(){
    struct sockaddr_in server ,client;
    FILE *fp;
    char tempr[100];
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    if(sockfd<0){
        printf("error in socket description\n");
        exit(1);
    }
   
   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_family= AF_INET;
   server.sin_port = htons(PORT);
   
    socklen_t server_len = sizeof(server);
    int conState = connect(sockfd,(struct sockaddr*)&server,server_len);
    if(conState<0){
        printf("error in conncet state\n");
        exit(1);
    }
    while(1){
        printf("give the name of file\n");

        
        fgets(tempr,sizeof(tempr),stdin);

        int sendState= send(sockfd,tempr,sizeof(tempr),0);
        if(sendState<0){
            printf("error in sendsate\n");
        }else{
            printf("data send\n");
        }
        char response[100];
        int recvstate = recv(sockfd,response,sizeof(response),0);
        // printf("response:\t%s\n",response);
        if(recvstate<0){
            perror("error in reciving");
            exit(1);
        }
        printf("give the name of file:\n");
        char name[100];
        scanf("%s",name);
        fp = fopen(name,"w");
        if(fwrite(response,sizeof(char),strlen(response),fp)){
            printf("%s\n",response);
        }else{
            perror("data write error\n");
        }
    }
}