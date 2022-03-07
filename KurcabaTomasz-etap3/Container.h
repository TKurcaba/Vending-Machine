//
// Created by tomasz on 07.01.2021.
//

#ifndef KURCABATOMASZ_ETAP3_CONTAINER_H
#define KURCABATOMASZ_ETAP3_CONTAINER_H
#include <iostream>
#include "Errors.h"

template <typename T>
class Container {
public:
    explicit Container(size_t capacity=8): capacity(capacity), Tab(new T[capacity]{}) {

    }
    ~Container();
    void Add(const T&  t);
    void ChangeCapacity(int new_size);
    T& operator[](int index)const;
    int Size() const { return size; }
    void Add(const T*  t, int size_t);
    void Delete(int id);
private:
    void Clear();
    int size=0;
    T* Tab= nullptr;
    int capacity=0;
};

template<typename T>
void Container<T>::Add(const T& t) {
    if(capacity <= size )
        ChangeCapacity(++capacity);
    Tab[size++] = t;
    // Add one item to the container
}

template<typename T>
void Container<T>::ChangeCapacity(int new_size) {
    T* new_tab= new T[new_size];
    if(new_size < size)
        size=new_size;
    for(int i=0; i < size; i++)
        new_tab[i]=Tab[i];
    delete[] Tab;
    Tab=new_tab;
    capacity=new_size;
// change the container capacity
}

template<typename T>
T &Container<T>::operator[](int index) const {
    if(index >= size)
        throw ContainerErrors();
    return Tab[index];
}

template<typename T>
void Container<T>::Add(const T *t, int size_t) {
    if(size + size_t >= capacity)
        ChangeCapacity(size_t + size + 1);
    for(int i = size,  j=0; i < size_t + size; i++, j++)
        Tab[i]=t[j];
    size+=size_t;
// Add an array of elements to the container
}

template<typename T>
void Container<T>::Clear() {
    for(int i =0; i < size; i++)
        delete Tab[i];
    size=0;

}

template<typename T>
Container<T>::~Container() {
    Clear();
    delete[] Tab;
}

template<typename T>
void Container<T>::Delete(int id) {
    if(id >= size || id < 0)
        throw ContainerErrors();
    T* new_tab= new T[size - 1];
    for(int i=0; i < size; i++){
        if(i == id)
            continue;
        new_tab[i]=Tab[i];
    }
    delete [] Tab;
    Tab=new_tab;
    size--;
    // delete one container element
}





/*
template<typename T>
Container_drinks<T>::Container_drinks(const Container_drinks<T> &t) {
    size=t.size;
    capacity=t.capacity;
    Container_drinks = new T[capacity];
    for( int i=0; i<size; i++)
        Container_drinks[i]=t.Container_drinks[i];
}
*/

#endif //KURCABATOMASZ_ETAP3_CONTAINER_H
