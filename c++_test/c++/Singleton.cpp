#include "Singleton.h"
#include <iostream>
#include <stdio.h>
using namespace std;


int main()
{
    Singleton& a = Singleton::Instance();
    //Singleton b = Singleton(); //wrong
    //Singleton c = a;  //wrong
    //Singleton d(a);  //wrong
    Singleton& e = Singleton::Instance(); 
    printf("*a = %p,*e  = %p\n",&a,&e); //static stupid test
    //a.go();
    Singleton1& a1 = Singleton1::Instance();
    return 0;
}
