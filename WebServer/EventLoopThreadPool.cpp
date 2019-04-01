
#include "EventLoopThreadPool.h"
#include <stdio.h>

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop,int numThread)
:   baseLoop_(baseLoop),
    started_(false),
    numThreads_(numThread),
    next_(0)
{
    if(numThreads_ <= 0)
    {
        LOG << "numThreads_ <= 0";
        abort();
    }
}

void EventLoopThreadPool::start()
{
    cout << "elppool start"<<endl;
    baseLoop_->assertInLoopThread();
    started_ = false;
    for(int i = 0;i < numThreads_;++i)
    {
        std::shared_ptr<EventLoopThread> t(new EventLoopThread());
        threads_.push_back(t);
        loops_.push_back(t->startLoop());
        perror("init pool");
    }
}

EventLoop *EventLoopThreadPool::getNextLoop()
{
    baseLoop_->assertInLoopThread();
    assert(started_);
    EventLoop *loop = baseLoop_;
    if(!loops_.empty())
    {
        loop = loops_[next_];
        next_ = (next_ + 1) % numThreads_;
    }
    perror("can't get loop");
    return loop;
}
