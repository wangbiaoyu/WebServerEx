#include <iostream>
#include <pthread.h>
#include <string.h>
//#include <condition.h>

using namespace std;

int num_ = 0;
int MAX_ = 10;
pthread_mutex_t mutex_;
pthread_cond_t condition_;

void* consume(void* arg)
{
    pthread_mutex_lock(&mutex_);
    while(num_ <= 0)
        pthread_cond_wait(&condition_,&mutex_);
    --num_;
    cout << "consume done!!!"<< " buf is:"<<num_<<endl;    
    pthread_mutex_unlock(&mutex_);
    pthread_cond_signal(&condition_);
}

void* produce(void* arg)
{
    pthread_mutex_lock(&mutex_);
    while(num_ >= MAX_)
        pthread_cond_wait(&condition_,&mutex_);
    ++num_;
    cout << "produce done!!!"<< " buf is:"<<num_<<endl;
    pthread_mutex_unlock(&mutex_);
    pthread_cond_signal(&condition_);
}

int main()
{
    pthread_t thread_[1000];
    pthread_mutex_init(&mutex_,NULL);
    pthread_cond_init(&condition_,NULL);
    for(int i = 0;i < 500;++i)
        pthread_create(&thread_[i],NULL,&produce,NULL);
    for(int i = 500;i < 1000;++i)
        pthread_create(&thread_[i],NULL,&consume,NULL);
    for(int i = 0;i < 1000;++i)
        pthread_join(thread_[i],NULL);
    return 0;
}
