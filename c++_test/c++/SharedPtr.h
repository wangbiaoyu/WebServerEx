#pragma once


template <class T>

class SharedPtr
{
public:
    SharedPtr();
    SharedPtr(T* obj);
    SharedPtr(const SharedPtr& other);
    SharedPtr& operator=(const SharedPtr& obj);
    ~SharedPtr();
    T operator&();
    T* getObj() { return obj_; }
    int getrefCount() { return *refCount_; }
private:
    T* obj_;
    int* refCount_;
};
