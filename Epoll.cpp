
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


std::vector<SP_Channel> Epoll::poll()
{
    while(true)
    {
        int event_count = epoll_wait(epollFd_,&*events_.begin(),events_.size(),EPOLLWAIT_TIME);
        if(event_count < 0)
            perror("epoll wait error");
        std::vector<SP_Channel> req_data = getEventsRequest(event_count);
        if(req_data.size() > 0)
            return req_data;
    }
} 

void Epoll::handleExpired()
{
    timerManager_.handleExpiredEvent();
}

std::vector<SP_Channel> Epoll::getEventRequest(int events_num)
{
    std::vector<SP_Channel> req_data;
    for(int i = ; i < event_num; ++i)
    {
        int fd = events_[i].data.fd;
        SP_Channel cur_req = fd2chan_[fd];
        if(cur_req)
        {
            cur_req->setRevents(events_[i].events);
            cur_req->setEvents(0);
            req_datra.push_back(cur_req);
        }
        else
        {
            LOG << "SP cur_req is invalid!";
        }
    }
    return req_data;
}

void Epoll::add_timer(SP_Channel request_data,int timeout)
{
    shared_ptr<HttpData> t = request_data->getHolder();
    if(t)
        timerManager_.addTimer(t,timeout);
    else
        LOG << "timer add fail!";
}
