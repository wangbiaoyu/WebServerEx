
#include "EventLoopThreadPool"

EventLoopThreadPool::EventLoopThreadPool(EventLoop* baseLoop,int numThread)
:   baseLoop_(baseLoop),
    started_(false);
    numThreads_(numThreads),
    next_(0)
{
    if(numThreads_ <= 0)
    {
        LOG << "numThreads_ <= 0";
        abort(0);
    }
}

void EventLoopThreadPool::start()
{
    baseLoop_->assertInLoopThread();
    started_ = false;
    for(int i = 0;i < numThreads_;++i)
    {
        std::shared_ptr<EventLoopThread> t(new EventLoopThread());
        threads_push_back(t);
        loops_.push_back(t->startLoop());
    }
}

EventLoop *EventLoopThreadPool::getNextLoop()
{
    baseLoop_->assertInLoopThread();
    assert(started);
    EventLoop *loop = baseLoop_;
    if(!loops_.empty())
    {
        loop = loops_[next_];
        next_ = (next_ + 1) % numThreads_;
    }
    return loop;
}
