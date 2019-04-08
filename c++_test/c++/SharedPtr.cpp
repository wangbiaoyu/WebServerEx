#include "SharedPtr.h"
#include <iostream>
#include <memory>
#include <string>
#include <string.h>
#include <vector>
using namespace std;

template<class T>
SharedPtr<T>::SharedPtr()
:   obj_((T*)0),
    refCount_(0)
{ }

template<class T>
SharedPtr<T>::SharedPtr(T* obj)
:   obj_(obj),
    refCount_(new int(1))
{
    cout << "init shared_ptr" << endl;//*obj_ <<endl;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other)
{
   if(this == &other)
   {
      return *this;
   }
   ++*other.refCount_; 
   /*if(--*refCount_ == 0)
   {
        delete obj_;
        delete refCount_;
   }*/
   cout << "shared_ptr<T> a = b"<<endl;
    obj_ = other.obj_;
    refCount_ = other.refCount_;
    return *this;
}

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr& other)
:   obj_(other.obj_),
    refCount_(other.refCount_)
{
    ++*other.refCount_;
    //cout << *refCount_ << " " << *other.refCount_ << endl;
   cout << "shared_ptr<T> a(b)"<<endl;
}

template<class T>
SharedPtr<T>::~SharedPtr()
{
    if(obj_ != NULL  && --*refCount_ == 0)
    {
        cout << "~SharedPtr"<<endl;
        delete obj_;
        delete refCount_;
    }//else
       // cout << "233" <<endl;
    cout << "refCount_: "<< *refCount_ << endl;
}

template<class T>
T SharedPtr<T>::operator&()
{
    if(obj_)
    {
        return *obj_;     
    }
    return NULL;
}

class Derive;

class Base
{
public:
    void t1() { cout << "I am Base\n"; }  

    vector<SharedPtr<Derive> > b;
};

class Derive
{
public:
    void t1() {cout << "I am Derive\n"; }

    SharedPtr<Base> d;
};

int main()
{
    //SharedPtr<string> a(new string("23"));
    //SharedPtr<string> b;
    //SharedPtr<string> c(a);
    //shared_ptr<int> c1;
    //b = a;
    SharedPtr<Base> base(new Base());
    SharedPtr<Derive> derive(new Derive());
    base.getObj()->b.push_back(derive);
    derive.getObj()->d = base;
    cout <<  base.getrefCount() << " "<< derive.getrefCount() <<endl;
    //base.b.push_back(derive);
    return 0;
}
