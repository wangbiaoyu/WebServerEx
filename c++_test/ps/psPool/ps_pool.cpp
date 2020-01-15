#include "ps_pool.h"

#include <sys/types.h>
#include <sys/socket.h>

namespace ps_pool
{
	ps_pool::ps_pool(int sockfd,uint32_t size)
		: 	sockfd_(sockfd)
			max_size_(16),
			size_(size)
	{ 
		init();
	}


	void ps_pool::run(){
		this->master_manager();
	}
	
	void ps_pool::init(){
		if(size_ > max_size_)	size_ = max_size_;
		for(int i = 0;i < size_;i++){
			ps_info info = ps_info();
			int ret = socketpair(PF_UNIX,SOCK_STREAM,0,info.pair);
			if(ret == -1){
				std::cout << "Fail +1"<< endl;
				continue;
			}
			pid_t pid = fork();
			if(pid > 0){
			//parent return
				info.sub_pid = pid;
				::close(info.pair[1]);
				pool_.push_back(info);
				break;
			}else if(pid == 0){
			//child return
			//child bind task
				::close(info.pair[0]);
				bind_task();
			}else(info.sub_pid < 0){
				std::cout << "Fail +1"<< endl;
				continue;
			}
		}	
	}

	void ps_pool::master_manager(){
		epollfd_ = epoll_create(5);
		assert(epollfd_ >= 0);
		struct epoll_event ev,rev;
		ev.data.fd = sockfd_;
		ev.events = EPOLLIN | EPOLLET;
		assert(epoll_ctl(epollfd_,EPOLL_CTL_ADD,sockfd_,&ev) >= 0);
		//Make it alone
		while(running_){
			while(!stop){
				int ret = epoll_wait(epollfd_,&rev,MAX_EVENTS,-1);
				assert(ret >= 0);
				for(int i = 0;i < ret;i++){
					if(rev[i].data.fd == sockfd_){
						struct sockaddr_in client;
						int clientfd = ::accept(sockfd_,(struct sockaddr*)&client,sizeof(struct sockaddr_in));
						if(clientfd < 0){
							std::cout << "Socket connect error:" << errno << endl;
							continue;
						}
						//Transefer clientfd to child ps
						const ps_info* cur = round_robin();
						if(::write(ps->info[0],&clientfd,sizeof(clientfd)) != sizeof(clientfd)){
							std::cout << "IPC with child fail." << endl;
						}		
					}else{
						if(rev[i].events & )				
					}
				}	
			}
		}
	}

	void ps_pool::bind_task(){
		
	}

	const ps_info* ps_pool::round_robin(){
		return ps_pool[ind_%size_];	
	}
}
