#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
int main(int argc,char *argv[]){

    struct sockaddr_in server;
    int socketfd = socket(AF_INET,SOCK_DGRAM,0);
    
    if(socketfd==-1){
        printf("error in socket creation");
    }else{

    server.sin_family = AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;
    server.sin_port = htons(atoi(argv[2]));

    char buffer[100];
    printf("give the data to be sent at server\n");
    fgets(buffer,100,stdin);
    

    int state = sendto(socketfd,&buffer,sizeof(buffer),0,(struct sockaddr*)&server,sizeof(server));
    if(state<0){
        printf("error in send to\n");
    }
    // socklen_t serv_len = sizeof(server);

    // int recvState = recvfrom(socketfd,buffer,sizeof(buffer),0,(struct sockaddr*)&server,&serv_len);
    // if(recvState<0){
    //     printf("error in reciving");
    // }else{
    //     printf("%s",buffer);
    // }
    }


}
