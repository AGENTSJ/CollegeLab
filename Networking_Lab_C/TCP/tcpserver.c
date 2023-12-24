#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>

int main(int argc,char * argv[]){
    
    int socketfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server,client;
    if(socketfd<0){
        printf("error in socket description");
    }else{

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = 3000;

        client.sin_family = AF_INET;
        client.sin_addr.s_addr = INADDR_ANY;
        client.sin_port = 3000;

        socklen_t serv_len = sizeof(server);

        int bindState = bind(socketfd,(struct sockaddr*)&server,serv_len);
        if(bindState<0){
            printf("error in binding");
        }else{


            printf("server listening at port 3000\n");

            int listenState = listen(socketfd,5);
            if(listenState<0){
                printf("error in listen");
            }
            else{

                socklen_t client_len = sizeof(client);

                int comm_sockfd = accept(socketfd,(struct sockaddr*)&client,&client_len);
                if(comm_sockfd<0){
                    printf("error in communication socket");
                }else{

                    char buffer[100];

                    int recvState = recv(comm_sockfd,buffer,100,0);
                    if(recvState<0){
                        printf("error while recving");
                    }else{
                        printf("data arrived:\t %s",buffer);
                    }
                }
            }
        }

    }
}