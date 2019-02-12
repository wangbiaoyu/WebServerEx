
#pragma once //#IFNDEF
#include "EventLoop.h"
#include "Channel.h"
#include "EventLoopThreadPool.h"
#include <memory>

class Server{
	public:
	    Server(EventLoop *loop,int threadNum,int port);
        ~Server() {}
        EventLoop* getLoop() const {return loop_;}
        void start;
        void handleNewConn();
        void handThisConn() {loop_->updatePoller(acceptChannel_);}
    
    private: 
        EventLoop *loop_;
        int threadNum_;
        int port;
        int listenFd_;
        std::unique_ptr<EventLoopThreadPool> eventLoopThreadPool_;
        bool started_;
        std::shared_ptr<Channel> acceptChannel_;
        static const int MAXFDS = 100000;
}
