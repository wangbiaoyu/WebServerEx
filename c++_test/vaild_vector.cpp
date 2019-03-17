#include <iostream>
using namespace std;
#include <vector>
//#define vector<int>::iterator it

int main()
{
    vector<int> v{1,2,3,4,5};
    auto i1 = v.end();
    auto i2 = v.begin();
    v.insert(i2,0);
    cout << "*it" << *i1 << endl;
    return 0;
}
