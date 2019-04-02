#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include <netinet/in.h>
#include <string.h>
#include <memory.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#define MAXSIZE 10
char buf[MAXSIZE];

void work(int connfd);

int main(int argc,char* argv[]){
    pid_t pid;
    int connfd;
    int num;
    int listenfd = socket(PF_INET,SOCK_STREAM,0);
    assert(listenfd != -1);

    struct sockaddr_in servaddr,cliaddr;
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(8888);

    int ret = bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    assert(ret != -1);
    ret = listen(listenfd,5);
    assert(listenfd != -1);
    
    //connfd = accept(listenfd,NULL,NULL);
    //assert(connfd >= 0);

    fd_set readFds;
    fd_set exceptionFds;
    FD_ZERO(&readFds);
    FD_ZERO(&exceptionFds);

    FD_SET(listenfd,&readFds);
    int readn;
    while(true){
        //while((connfd = accept(listenfd,(struct sockaddr*)NULL,NULL)) > 0){
        fd_set curFds = readFds;
        memset(buf,'\0',MAXSIZE);
        ret = select(FD_SETSIZE,&curFds,NULL,NULL,NULL);
        assert(ret >= 0);
        for(int i =0;i < FD_SETSIZE;++i){
            if(FD_ISSET(i,&curFds)){
                if(i == listenfd){
                    connfd = accept(listenfd,NULL,NULL);
                    FD_SET(connfd,&readFds);
                    printf("new conntion\n");
                }
                else{ //if(FD_ISSET(i,&readFds)){
                    ioctl(i,FIONREAD,&readn);
                    //ret = recv(i,buf,MAXSIZE-1,0);

                    if(readn <= 0){
                   // printf("get %d bytes,data = %s\n",ret,buf);
                    close(i);
                    FD_CLR(i,&readFds);
                    }else{
                        read(i,buf,readn);
                        printf("get %d bytes,data = %s\n",readn,buf);
                    }
                }
            }
        }
        /*&if((pid = fork()) == 0){
            close(listenfd);
            work(connfd);
            close(connfd);
            exit(0);
        }
        close(connfd);
        }*/
    }
    close(connfd);
    close(listenfd);
    return 0;
}

void work(int connfd){
    memset(buf,'\0',MAXSIZE);
    int readn = recv(connfd,buf,MAXSIZE-1,0);
    printf("new connfd = %,buf address = %p\n",connfd,buf);
}
