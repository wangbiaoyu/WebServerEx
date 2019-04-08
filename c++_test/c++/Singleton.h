#pragma once
#include <iostream>
#include <pthread.h>
using namespace std;

//not thread safe
class Singleton
{

public:
    
    static Singleton& Instance()
    {
        static Singleton st = Singleton();
        return st;
    }

    void go() { cout << "go()\n"; }
private:
    
    Singleton() { }
    Singleton(const Singleton& );
    Singleton& operator=(const Singleton& );

};

//thread safe
//template <typename T>
class Singleton1
{
private:
    static void init_once()
    {
        st = new Singleton1();      
    }

public:
    static Singleton1& Instance()
    {
        pthread_once(&once_,&Singleton1::init_once);
        return *st;
    }

private:
    static pthread_once_t once_;
    static Singleton1* st;

    Singleton1() { } ;
    ~Singleton1() { };
};

pthread_once_t Singleton1::once_ = PTHREAD_ONCE_INIT;
Singleton1* Singleton1::st = NULL;
/*
template<typename T>
pthread_once_t Singleton1<T>::once_control;

template<typename T>
Singleton1 Singleton1<T>::st;*/
