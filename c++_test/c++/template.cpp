#include <iostream>
#include "../base/noncopyable.h"

using namespace std;

class Test// : public  noncopyable
{
public:
    Test() {++num;}
    void getNum() {cout << "num" << num << endl;}
private:
    int num;
};

template<typename T>

void swap(T& a,T& b){
    T temp = a;
    a = b;
    b = temp;
    cout << a << b << endl;
}

int main(){
    int a = 1,b = 2;
    //::swap(a,b);
    Test* t =new  Test();
    t->getNum();
    Test* t1 =new Test();
    delete t;
    t->getNum();
    t1->getNum();
    return 0;
}
