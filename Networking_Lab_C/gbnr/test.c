int childServer = fork();
                    if(childServer<0){
                        perror("error in child server creation ");
                        exit(1);
                    }else{
                        
                        int comm_sock = accept(sockfd,(struct sockaddr*)&client,&client_len);
                    
                        if(comm_sock<0){
                            perror("accept error");
                            exit(1);
                        }else{

                            char buff[100];

                            close(sockfd);

                            int recvState = recv(comm_sock,buff,sizeof(buff),0);
                            if(recvState<0){
                                perror("recv error");
                            }else{
                                printf("%s",buff);
                            }
                        }
                        close(comm_sock);
                    }