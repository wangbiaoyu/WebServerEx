#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>


int main(int argc,char* argv[])
{
    pid_t pid;
    printf("begin\n");
    int num = 0;
    pid = fork();
    printf("ppid = %d\n",pid);
    for(int i = 0; i < atoi(argv[1]);++i)
            {
                ++num;
                printf("# = %d\n",num);
            }
    return 0;
}
