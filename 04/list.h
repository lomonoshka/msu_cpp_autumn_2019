#pragma once

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
    long long length;

    public:
        list();
        ~list();
        list(const list<T>&);
        void append(const T&);
        T pop();
        node<T>* get_head();
        node<T>* get_tail();
        long long get_length();
        void print();
};
