
#include "EventLoop.h"
#include "Server.h"
#include "base/Logging.h"
#include <string>

int main(int argc,char *argv[]){
	int threadNum = 4;
	int port = 8080;
	std::string logPath = "./WebServer.log";
	Logger::setLogFile(logPath); 
	EventLoop mainLoop;
	Server HttpServer(&mainLoop,threadNum,port);
	mainLoop.loop();
}
