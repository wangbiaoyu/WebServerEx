
#include "Util.h"
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

const int MAX_BUFF = 4096;
ssize_t readn(int fd,void* buff,size_t n)
{	
    size_t nleft = n;
    ssize_t nread = 0;
    ssize_t readSum = 0;
    char *ptr = (char*buff);
    while(nleft > 0)
    {
        if((nread = read(fd,ptr,nleft)) < 0)
        {
            if(errno == EINTR)
                nread = 0;
            else if(errno == EAGAIN)
            {
                return readSum;
            }
            else
            {
                return -1;
            }
        }
        else if(nread == 0)
        {
            break;
        }
        readSum += nread;
        nleft-= nread;
        ptr += nread;
    }   
}
