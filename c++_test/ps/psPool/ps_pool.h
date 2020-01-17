#pragma once

#include <vector>
#include <unistd.h>
#include <stdint.h>

using namespace std;
namespace psPool
{

struct ps_info{
	pid_t sub_pid;
	int pair[2];
	ps_info(){ sub_pid = -1, pair[0] = -1,pair[1] = -1;}
};
class ps_pool //: public ISingleton<ps_pool>
{

public:
	explicit ps_pool(int ,uint32_t size);
	ps_pool (const ps_pool&) = delete;
	ps_pool& operator=(const ps_pool&) = delete;
	~ps_pool();
	//pid_t get_pid();
	//bool add_task();
	void run();
	void bind_task(ps_info*);
	void init();

private:
	void init_pool();
	ps_info* round_robin();
	void master_manager();
private:
	vector<ps_info*> pool_;
	int sockfd_;
	uint32_t max_size_;	
	uint32_t size_;
	bool running_;
	bool stop_;
	int epollfd_;
	int ind_;
};

}
