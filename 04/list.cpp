#include "list.h"
#include <iostream>

template <class T>
list<T>::list():head(nullptr), tail(nullptr), length(0){}

template <class T>
list<T>::~list()
{
    node<T>* tmp = head;
    while(tmp != nullptr)
    {
        node<T>* tmp_next = tmp->next;
        delete tmp;
        tmp = tmp_next;
    }
    length = 0;
}
template <class T>
list<T>::list(const list<T> &l)
{
    node<T>* tmp = l.head;

    while(tmp != nullptr)
    {
        this->append(tmp.data);
    }
}

template <class T>
node<T>* list<T>::get_head()
{
    return this->head;
}

template <class T>
node<T>* list<T>::get_tail()
{
    return this->tail;
}

template <class T>
size_t list<T>::get_length()
{
    return this->length;
}

template <class T>
void list<T>::append(const T& data)
{
    if(head == nullptr)
    {
        head = new node<T>();
        head->data = data;
        head->next = nullptr;
        tail = head;
        length++;
    }
    else
    {
        tail->next = new node<T>();
        tail->next->data = data;
        tail->next->next = nullptr;
        tail = tail->next;
        length++;
    }
}


template <class T>
T list<T>::pop()
{
    node<T>* tmp = this->head;
    while(tmp->next != this->tail)
        tmp = tmp->next;

    T data = this->tail->data;
    delete this->tail;
    this->length--;
    this->tail = tmp;
    tmp->next = nullptr;
    return data;
}

template <class T>
void list<T>::print()
{
    node<T>* tmp = head;
    while(tmp != nullptr)
    {
        std::cout<<tmp->data<<" ";
        tmp = tmp->next;
    }
    std::cout<<'\n';
}
