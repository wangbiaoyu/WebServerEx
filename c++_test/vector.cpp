#include <iostream>
#include <vector>
#include <stdio.h>
#include <memory.h>
#include <algorithm>

using namespace std;

struct A{
    int a;
    int b;
};

int main(){
    struct A a1,a2,a3,a4;
    a1.a = 1;
    a1.b = 2;
    ::swap(a1.a,a1.b);
    cout << a1.a << a1.b << endl;
    a2 = a1;
    memset(&a3,1,sizeof(struct A));
    printf("addres 1 = %d\naddress 2 = %d\n",a1.a,a1.b);
    printf("addres 3 = %p\naddress 4 = %p\n",a3,a4);
    vector<int> v{1,2,3};
    int dis = static_cast<int>(v.end()-v.begin());
    cout << "a4.a = "  << a4.a<< endl;
    return 0;
}
