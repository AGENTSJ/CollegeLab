#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>

int main(int argc,char *argv[]){
    
    int socketfd = socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    socklen_t server_len = sizeof(server);
    
    int bindState = bind(socketfd,(struct sockaddr*)&server,server_len);
    
    if(bindState<0){
        printf("error in bind\n");
    }else{

        char buffer[100];
        printf("server running in %s \n",argv[1]);
        int recvState = recvfrom(socketfd,buffer,100,0,(struct sockaddr*)&server,&server_len);
        if(recvState<0){
            printf("error in reciver\n");
        }else{
            printf("%s",buffer);
        }
        // char temp[] = "yes its client id";
        // int sendState = sendto(socketfd,temp,sizeof(temp),0,(struct sockaddr*)&server,sizeof(server));
        // if(sendState<0){
        //     printf("error in sending");
        // }

    }

}