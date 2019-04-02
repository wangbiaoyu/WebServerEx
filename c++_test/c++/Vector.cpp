#include "Vector.h"
#include <iostream>

using namespace std;

//FIXME THREAD SAFE
template<class T>
Vector<T>::Vector()
:  data_(NULL),
   ind_(0),
   size_(0),
   capcity_(0)
{ } 

template<class T>
Vector<T>::Vector(const int size)
:   //data(size),
    ind_(0),
    size_(judge(size)),
    capcity_(allocCap(size))
{   
   this->data_ = new T[capcity_]; 
}

template<class T>
void Vector<T>::push_back(const T obj)
{
   if(size_ + 1 > capcity_)
   {
        //FIXME ALLOC
   } 
   data_[ind_] = obj; 
   ++ind_;
}

template<class T>
T Vector<T>::operator[](const int ind)
{
    assert(ind >= 0);
    assert(ind < ind_);
    return data_[ind];
}

int main()
{
    Vector<int> a(2);
    a.push_back(1);
    cout << a[0] << endl;
    return 0;
}
