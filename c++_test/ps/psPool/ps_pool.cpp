#include "ps_pool.h"

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <assert.h>
#include <arpa/inet.h>
#include <memory.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define MAX_EVENTS 2048
using namespace std;
namespace psPool
{
	static bool service_fd(int pairfd,int sockfd){
		struct iovec iov[1];
		struct msghdr msg;
		char   buf[1];
		union{
			struct cmsghdr cm;
			char spce[CMSG_SPACE(sizeof(int))];
		}cmsg;
		msg.msg_control = (caddr_t)&cmsg;
		msg.msg_controllen = sizeof(cmsg);
		
		memset(&cmsg,0,sizeof(cmsg));
		cmsg.cm.cmsg_len = CMSG_LEN(sizeof(int));
		cmsg.cm.cmsg_level = SOL_SOCKET;
		cmsg.cm.cmsg_type = SCM_RIGHTS;
		//*(int *)CMSG_DATA(&cmsg.cm) = sockfd;
		memcpy(CMSG_DATA(&cmsg.cm),&sockfd,sizeof(int));
		
		msg.msg_flags = 0;
		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		iov[0].iov_base = buf;
		iov[0].iov_len = 1;
		msg.msg_iov = iov;
		msg.msg_iovlen = 1;
		if(sendmsg(pairfd,&msg,0) < 0){
			std::cout << "Service send socket error:"<< errno << endl;
			return false;
		}
		return true;
	}

	static bool client_fd(int pairfd,int *sockfd){
		struct iovec iov[1];
		struct msghdr msg;
		char   buf[1];

		union{
			struct cmsghdr cm;
			char space[CMSG_SPACE(sizeof(int))];
		}cmsg;

		msg.msg_control = (caddr_t)&cmsg;
		msg.msg_controllen = sizeof(cmsg);
		msg.msg_name = NULL;
		msg.msg_namelen = 0;
		iov[0].iov_base = buf;
		iov[0].iov_len = 1;
		msg.msg_iov = iov;
		msg.msg_iovlen = 1;
		if(recvmsg(pairfd,&msg,0) <  0){
			std::cout << "Chile get socket error:" << errno << endl;
			return false;
		}
		if(msg.msg_flags & (MSG_TRUNC | MSG_CTRUNC)){
			std::cout << "Receive truncated data." << endl;
			return false;
		}
		//int sssockfd = *(int *)CMSG_DATA(&cmsg.cm);
		//sockfd = &sssockfd;
		memcpy(sockfd,CMSG_DATA(&cmsg.cm),sizeof(int));
		return true;
	}

	ps_pool::ps_pool(int sockfd,uint32_t size)
		: 	sockfd_(sockfd),
			max_size_(16),
			size_(size),
			running_(true),
			stop_(false),
			epollfd_(0),
			ind_(0)
	{ 
		init();
	}


	void ps_pool::run(){
		this->master_manager();
	}
	
	void ps_pool::init(){
		if(size_ > max_size_)	size_ = max_size_;
		for(int i = 0;i < size_;i++){
			ps_info* info =new  ps_info();
			int ret = socketpair(PF_UNIX,SOCK_STREAM,0,info->pair);
			if(ret == -1){
				std::cout << "Fail +1"<< endl;
				continue;
			}
			pid_t pid = fork();
			if(pid > 0){
			//parent return
				info->sub_pid = pid;
				::close(info->pair[1]);
				pool_.push_back(info);
				break;
			}else if(pid == 0){
			//child return
			//child bind task
				::close(info->pair[0]);
				bind_task(info);
			}else if(info->sub_pid < 0){
				std::cout << "Fail +1"<< endl;
				continue;
			}
		}	
	}

	void ps_pool::master_manager(){
		epollfd_ = epoll_create(5);
		assert(epollfd_ >= 0);
		struct epoll_event ev,rev[1024];
		ev.data.fd = sockfd_;
		ev.events = EPOLLIN | EPOLLET;
		assert(epoll_ctl(epollfd_,EPOLL_CTL_ADD,sockfd_,&ev) >= 0);
		//Make it alone
		while(running_){
			while(!stop_){
				std::cout << "Father go..."<<endl;
				int ret = epoll_wait(epollfd_,rev,MAX_EVENTS,-1);
				//assert(ret >= 0);
				std::cout << "Revents: " << ret  << endl;
				for(int i = 0;i < ret;i++){
					if(rev[i].data.fd == sockfd_){
						struct sockaddr_in client;
						socklen_t len = sizeof(struct sockaddr_in);
						int clientfd = ::accept(sockfd_,(struct sockaddr*)&client,&len);
						std::cout << "Accept fd:" << clientfd << endl;
						if(clientfd < 0){
							std::cout << "Socket connect error:" << errno << endl;
							continue;
						}
						char buft[1024] = {0};
						::read(clientfd,buft,1024);
						std::cout << "dasd"<< buft << endl;
						::close(clientfd);
						break;
						std::cout << "Recvfd: "<< clientfd << endl;
						//Transefer clientfd to child ps
						ps_info* cur = round_robin();
						if(!service_fd(cur->pair[0],clientfd)){
						//if(::write(cur->pair[0],&clientfd,sizeof(clientfd)) != sizeof(clientfd)){
							std::cout << "IPC with child fail." << endl;
						}
						::close(clientfd);		
					}else{
						//if(rev[i].events & EPOLLHUB)				
					}
				}	
			}
		}
	}

	#define Buffer 1024
	void ps_pool::bind_task(ps_info* child){
		while(true){
			//char buf[1];
			//memset(buf,0,sizeof(buf));
			int clientfd = -1;
			while(!client_fd(child->pair[1],&clientfd)){
				std::cout << "Child waiting..."<<endl;
			};
			//while(::read(child->pair[1],&clientfd,sizeof(clientfd)) != sizeof(clientfd));
			int copyfd = clientfd,recv = 0;
			
			char buf[Buffer];
			std::cout << "Chilefd: " << copyfd << endl;
			memset(buf,0,Buffer);
			int readn = -1;
			while(true){
				readn = ::read(copyfd,buf,Buffer);
				if(readn == 0) break;
				if(readn < 0){
					if(errno == EINTR) continue;
					else break;//std::cout << "Read error:" << errno << endl;
				}else{
					recv += readn;
				}
			}
			buf[recv] = '\0';
			::close(copyfd);
			std::cout << "Success receive buf:" << buf << endl;	
		}
	}

	ps_info* ps_pool::round_robin(){
		return pool_[ind_++%size_];	
	}

	ps_pool::~ps_pool(){
		for(int i = 0;i < pool_.size();++i){
			kill(pool_[i]->sub_pid,SIGSTOP);
		}
	}
}
