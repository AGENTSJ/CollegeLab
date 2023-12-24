#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netdb.h>

int main(int argc ,char *argv[]){

    int socketfd  = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in server;
    if(socketfd==-1){
        printf("error in socket description");
    }else{

        server.sin_family=AF_INET;
        server.sin_addr.s_addr=INADDR_ANY;
        server.sin_port=3000;

        int conState = connect(socketfd,(struct sockaddr*)&server,sizeof(server));
        if(conState<0){
            printf("error in connection to server");
        }else{
            
            char buffer[100];
            printf("give the data to send\n");
            fgets(buffer,100,stdin);

            int sendState = send(socketfd,buffer,sizeof(buffer),0);
            if(sendState<0){
                printf("error in send");
            }else{
                printf("data send \n");
            }
        }
    }
}