//#include "Server.h"
#include "EventLoop.h"
#include "Server.h"
#include "base/Logging.h"
#include <string>

int main(int argc,char *argv[]){
	int threadNum = 4;
	int port = 80;
	std::string logPath = "WebServer.log";
	Logger::setLogFileName(logPath); 
	EventLoop mainLoop;
	Server* HttpServer = new Server(&mainLoop,threadNum,port);
	HttpServer->start();
    mainLoop.loop();
    return 0;
}
