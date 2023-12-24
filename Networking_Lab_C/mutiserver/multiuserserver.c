#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>

#define PORT  3000


int main(){
    struct sockaddr_in server,client;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    if(sockfd<0){
        printf("error in socket description");
        exit(1);
    }else{

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = PORT;

        socklen_t ser_len = sizeof(server);

        int bindState = bind(sockfd,(struct sockaddr*)&server,ser_len);
        if(bindState<0){
            printf("error in binding server socket");
            exit(1);
        }else{

            int listenState = listen(sockfd,5);
            if(listenState<0){
                printf("error while listening in port :\t %d\n",PORT);
                exit(1);
            }else{

                printf("server listening in port %d\n",PORT);

                socklen_t len = sizeof(client);

                for(;;){
                    int childServer = fork();
                    
                    int comm_sockfd = accept(sockfd,(struct sockaddr*)&client,&len);
                    if(comm_sockfd<0){
                        printf("error in communictaion server socket description");
                        exit(1);
                    }else{
                        printf("connection accepetd..\n");
                    
                        // int childServer = fork();
                        if(childServer<0){
                            printf("error in creating child server");
                            exit(1);
                        }else{
                            
                            close(sockfd);
                            char buffer[100];

                            for(;;){
                                
                                int recvState = recv(comm_sockfd,buffer,sizeof(buffer),0);
                                if(recvState<0){
                                    printf("error while reciving");
                                    exit(1);
                                }else{

                                    printf("data recived :\t %s",buffer);
                                    int sendState = send(comm_sockfd,buffer,sizeof(buffer),0);

                                    if(sendState <0){
                                        printf("error in send to client");
                                    }
                                }
                            }
                            close(comm_sockfd);

                          
                        }
                    }
                }
            }
        }
    }
    return close(sockfd);
}