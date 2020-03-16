#ifndef DEEPPTR_H
#define DEEPPTR_H

template <class T>
class DeepPtr
{
public:
    T* p; // puntatore (super)polimorfo: DeepPtr
    DeepPtr(T* =nullptr);
    DeepPtr(const DeepPtr&);
    DeepPtr& operator=(const DeepPtr&);
    ~DeepPtr();
    T* operator->() const;
    T& operator*() const;
    bool operator==(const T&) const;
};

template <class T>
DeepPtr<T>::DeepPtr(T* q):p(q != nullptr ? q->clone() : nullptr){}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr& v):p(v.p != nullptr ? v.p->clone() : nullptr){}

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& v){
    if(this != &v){
            delete p;
            p=v.p->clone();
    }
    return *this;
}

template <class T>
DeepPtr<T>::~DeepPtr(){
    if(p) delete p;
}

template <class T>
bool DeepPtr<T>::operator==(const T& c) const{
    return p == &c;
}

template<class T>
T* DeepPtr<T>::operator->() const{
    return p;
}

template<class T>
T& DeepPtr<T>::operator*() const{
    return *p;
}

#endif // DEEPPTR_H
