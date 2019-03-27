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

    int flag;
        connfd = accept(listenfd,(struct sockaddr*)NULL,NULL);
        printf("connfd =%d\n",connfd);
        memset(buf,'\0',MAXSIZE);
        printf("size = %d\n",sizeof(buf));
        int readn = recv(connfd,buf,MAXSIZE-1,0);
        printf("%d\n",readn);
        sleep(30);
        printf("estab\n");
    //}
    return 0;
}

