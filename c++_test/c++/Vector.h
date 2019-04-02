#pragma once
#include <assert.h>

template<class T>

class Vector
{
public:
    Vector();  //case: vector<int> a
    Vector(const int size); //case: vector<int> b(1);
    Vector(const Vector& obj); //case: vector<int> c(a);
    Vector& operator=(const Vector& obj); //case: a = b;
    void push_back(const T obj);
    T operator[](const int ind);
private:
    T* data_;
    int size_;
    int capcity_;
    int ind_;

    int judge(const int size)
    {
        assert(size >= 0);
        return size;
    } 

    int allocCap(const int size)
    {
        assert(size >= 0);
        return size + 20;
    }

};
