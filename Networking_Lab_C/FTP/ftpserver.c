#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>

#define PORT  3000

int main(){
    struct sockaddr_in server ,client;
    FILE *fp;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    
    if(sockfd<0){
        printf("error in socket description\n");
        exit(1);
    }

   printf("program enterd\n");

   server.sin_addr.s_addr = INADDR_ANY;
   server.sin_family= AF_INET;
   server.sin_port = htons(PORT);

   socklen_t server_len = sizeof(server) ;
   int bindState = bind(sockfd,(struct sockaddr*)&server,server_len);
   if(bindState<0){
    printf("error in binding\n");
    exit(1);
   } 

  

   int liState = listen(sockfd,5);
   if(liState<0){
    printf("error in li state\n");
    exit(1);
   }

   socklen_t client_len =sizeof(client); 
   
    printf("server listening at port 5000\n");
   
   int count =0;
   while(1){
    int comm_sockfd = accept(sockfd,(struct sockaddr*)&client,&client_len);
    if(comm_sockfd<0){
        // printf("error in comminication file descrpt\n");
        perror("comm error");
        exit(1);
    }

    int childServer = fork();
    if(childServer<0){
        printf("error in child server\n");
        exit(1);
    }else{

        // close(sockfd);
        char fileName[100];

        int recvState = recv(comm_sockfd,fileName,100,0);
        if(recvState<0){
            printf("error from recv\n");
            exit(1);
        }
        
        
        char temp[]="tempr.txt";
        fp = fopen(temp,"r");
        // printf("%s",temp);

        // fileName[recvState] = '\0';
        // fp = fopen(fileName,"r");
        // printf("%s",fileName);

        if(fp==NULL){
            perror("error");
        }
        char sendStream[100];

        if(fgets(sendStream,sizeof(sendStream),fp)){

        int sendState = send(comm_sockfd,sendStream,sizeof(sendStream),0);
        if(sendState<0){
            perror("send error");
        }

        }else{
            perror("error");
        }

        close(comm_sockfd);
        


    }
   

   }
return close(sockfd);
}