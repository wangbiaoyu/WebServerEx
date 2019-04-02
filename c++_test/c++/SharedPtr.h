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
    T &operator*();
private:
    T* obj_;
    int* refCount_;
};
