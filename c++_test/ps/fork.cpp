#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
int main(int argc,char* argv[])
{
    pid_t pid;
    printf("begin\n");
	//fork() || fork();
    int num = 0;
    //printf("ppid = %d\n",pid);
    pid = fork();
    for(int i = 0; i < atoi(argv[1]);++i)
            {
				//pid = fork();
							
				std::cout << pid << endl;
				if(pid > 0){
					
					cout << "father" << endl;
					break;
				}else if(pid == 0){
					cout << "child" << endl;
				}else{
					std::cout << "error" << endl;
				}
                ++num;
                printf("# = %d\n",num);
            }
	
    return 0;
}
