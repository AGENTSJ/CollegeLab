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

        socklen_t server_len = sizeof(server); 
        socklen_t client_len = sizeof(client);

        int bindState = bind(sockfd,(struct sockaddr*)&server,server_len);
        if(bindState<0){
            perror("binding error");
            exit(1);
        }else{

            printf("server lisenting in porttyu %d\n",PORT);

            int listenState = listen(sockfd,5);
            if(listenState<0){
                perror("listen error");
                exit(1);
            }else{
                for(;;){
                    int childserver = fork();

                    if(childserver<0){
                        perror("error in child");
                    }else{

                    int comm_fd = accept(sockfd,(struct sockaddr*)&client,&client_len);
                    if(comm_fd<0){
                        printf("error in comm\n");
                        exit(1);
                    }else{
                        printf("connection accepted..\n");

                        char temp[100];
                        int tem[100],i;
                        int window = 5;
                        int flag[100];
                        int occr=0;
                        flag[0]=0;

                        // fgets(temp,sizeof(temp),stdin);
                        for(i=1;i<=15;i++){
                            
                            fflush(stdout);
                            if(flag[0]==1){
                                printf("reTransmiting packets from %d",i);
                                flag[0]=0;
                            }
                            if(i==7&&occr==0){
                                printf("...simulating packet lost...\n");
                                occr = 1;
                            }else{

                                tem[0]=i;
                                int sendstate = send(comm_fd,tem,sizeof(tem),0);
                                if(sendstate<0){
                                    perror("error");
                                }else{
                                    printf("packet sent: %d\n",i);
                                }
                            }

                            if(i%5==0&&i!=0){
                                fflush(stdout);
                                printf("waiting for ack...\n");
                                fflush(stdout);
                                
                                int recvstate = recv(comm_fd,flag,sizeof(flag),0);
                                if(recvstate<0){
                                    printf("error in recvstate");
                                }else{
                                    if(flag[0]==1){
                                        i=i-5;
                                    }
                                }

                            }

                            fflush(stdout);
                        }


                    }
                    }
                }
            }
        }
    }
                  
    
}