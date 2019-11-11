#pragma once
#include <cstdio>


template <class T>
struct node
{
    T data;
    node<T>*  next;
};

template <class T>
class list
{
    node<T>* head;
    node<T>* tail;
    size_t length;

    public:
        list();
        ~list();
        list(const list<T>&);
        void append(const T&);
        T pop();
        node<T>* get_head();
        node<T>* get_tail();
        size_t get_length();
        void print();
};
