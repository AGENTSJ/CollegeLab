#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/select.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>


#define PORT 3000

int main(){
    
    struct sockaddr_in server,client;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0){
        perror("server socket error");
        exit(1);
    }else{

        server.sin_addr .s_addr= INADDR_ANY;
        server.sin_family = AF_INET;
        server.sin_port = PORT;

        socklen_t server_len= sizeof(server);
        int connectState = connect(sockfd,(struct sockaddr*)&server,server_len);
        if(connectState<0){
            perror("connect error");
            exit(1);
        }else{

            char msg[100];
            int tem[100];
            int flag[100];
            int error=0;
            printf("listenin from server..\n");
            // fflush(stdout);
            int packetq[100],top=0,count=0;

            for(int i = 1;i<=15;i++){

                int recvstate = recv(sockfd,tem,sizeof(tem),0);
                if(recvstate<0){
                    perror("error in recv");
                }else{


                    printf("packet arrived:\t%d \t count %d error %d \n",tem[0],count,error);
                    packetq[top]=tem[0];
                    count++;
                    // printf("%d\n",packetq[top]);

                    // if(top!=0){
                    //     printf("....%d....%d-%d\n",packetq[top-1]-packetq[top],packetq[top-1],packetq[top]);
                    // }else{
                    //     printf(" first\n");
                    // }

                    if(top!=0&&packetq[top-1]-packetq[top]!=-1){
                        error = 1;
                    }
                    if(error==0&&count==5){
                        printf("end packet\n");
                        int ack = send(sockfd,flag,sizeof(flag),0);
                        if(ack<0){
                            perror("ack error");
                        }
                    }
                    top++;
            }   }
            close(sockfd);

            
        }
    }

}