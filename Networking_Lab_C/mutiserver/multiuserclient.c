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
        printf("error in socket description\n");
        exit(1);
    }else{

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = PORT;

        socklen_t serv_len =sizeof(server);
        int connectState = connect(sockfd,(struct sockaddr*)&server,serv_len);
        if(connectState<0){
            printf("error in connect state\n");
            exit(1);
        }else{

            char buffer[100];
            printf("give the message to be sent\n");
            
            while(fgets(buffer,100,stdin)!=NULL){
                
                int sendState = send(sockfd,buffer,sizeof(buffer),0);
                if(sendState<0){
                    printf("error while sending to server\n");
                }else{
                    printf("data sent \n");
                }
                int recvState = recv(sockfd,buffer,sizeof(buffer),0);
                if(recvState<0){
                    printf("error reciving msg from server\n");

                }else{
                    printf("response from server :\t %s\n",buffer);
                }
            }
            close(sockfd);
            

        }
    }

}