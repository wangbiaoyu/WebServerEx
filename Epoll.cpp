
#include "Epoll.h"
#include "Util.h"
#include "base/Logging.h"
#include "sys/epoll.h"
#include "errno.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "string.h"
#include <queue>
#include <deque>
#include <assert.h>

#include <arpa/inet.h>
#include <iostream>
using namespace std;

const int EVENTSUM = 4096;
const int EPOLLWAIT_TIME = 10000;

typedef shared_ptr<Channel> SP_Channel;

Epoll::Epoll()
:   epollFd_(epoll_createl(EPOLL_CLOEXEC)),
    events_(EVENTSUM)
    {
        assert(epollFd_ > 0);
    }

Epoll::~Epoll() {}

void Epoll::epoll_add(SP_Channel request,int timeout)
{
    int fd = request->getFd();
    if(timeout > 0)
    {
        add_timer(request,timeout);
        fd2http_[fd] = request->getHolder();
    }
    struct epoll_event event;
    event.data.fd = fd;
    event.events = request->getEvents();

    request->EqualAndUpdateLastEvents();

    fd2chan_[fd] = request;
    if(epoll_ctl(epollFd_,EPOLL_CTL_ADD,fd,&event) < 0)
    {
        perror("epoll_add error");
        fd2chan_[fd].reset();
    }
}


void Epoll::epoll_mod(SP_Channel request,int timeout)
{
    if(timeout > 0)
    {
        add_timer(request,timeout);
    }
    int fd = request->getFd();
    if(!request->EqualAndUpdateLastEvents())
    {
        struct epoll_event event;
        event.data.fd = fd;
        event.events = request->getEvents();
        if(epoll_ctl(epollFd_,EPOLL_CTL_MOD,fd,&eveng) < 0)
        {
            perror("epoll_mod error");
            fd2chan_[fd].reset();
        }
    }
}

void Epoll::epoll_del(SP_Channel request)
{
    int fd = request->getFd();
    struct epoll_eveent event;
    event.data.fd = fd;
    event.events = reuqest->getLastEvents();
    if(epoll_ctl(epoll_Fd_,EPOLL_CTL_DEL,fd,&event) < 0)
    {
        perror("epoll_del error");
    }
    fd2chan_[fd].reset();
    fd2http_[fd].reset();
} 
