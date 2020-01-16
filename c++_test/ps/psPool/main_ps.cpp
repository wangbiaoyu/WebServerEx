#include "ps_pool.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <assert.h>

#define IP 127.0.0.1
#define PORT 8888

using namespace psPool;

int socket(){
	struct sockaddr_in service;
	socklen_t addr_len;
	memset(&service,0,sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = htonl(INADDR_ANY);
	service.sin_port = htons(8888);
	int servicefd = ::socket(AF_INET,SOCK_STREAM | SOCK_NONBLOCK,0);
	bind(servicefd,(struct sockaddr *)&service,sizeof(service));
	assert(listen(servicefd,5) >= 0);
	return servicefd;
}

int main(){
	int servicefd = socket();
	ps_pool* pool = new ps_pool(servicefd,2);
	pool->run();
	return 0;
}
