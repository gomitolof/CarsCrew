#ifndef CONTAINER_H
#define CONTAINER_H
#include "Controller/anomalia.h"

template <class T>
class Container
{
private:
    template <class U>
    class Nodo
    {
    public:
        T info;
        Nodo *prev, *next;
        Nodo(const T& i, Nodo* p=nullptr, Nodo* n=nullptr):info(i), prev(p), next(n){}
        ~Nodo(){
            if(next) delete next;
        }
    };
    static Nodo<T>* copy(Nodo<T>* fir, Nodo<T>*& lst){
        if(fir==nullptr) return lst=nullptr;
        Nodo<T>* f=new Nodo<T>(fir->info, nullptr, nullptr), *p=f;
        while(fir->next!=nullptr){
            p->next=new Nodo<T>(fir->next->info, p, nullptr);
            fir=fir->next;
            p=p->next;
        }
        lst=p;
        return f;
    }
    Nodo<T>* first, *last;
    unsigned int size;
public:
    class iterator{
        friend class Container<T>;
    private:
        Nodo<T>* punt;
        bool pte; //true if past-the-end
        iterator(Nodo<T>*, bool =false);
    public:
        bool operator!=(const iterator&) const;
        bool operator==(const iterator&) const;
        iterator& operator++(); //op prefisso
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+=(int);
        iterator& operator-=(int);
        T& operator*() const;
        T* operator->() const;
    };
    class const_iterator{
        friend class Container<T>;
    private:
        Nodo<T>* punt;
        bool pte; //true if past-the-end
        const_iterator(Nodo<T>*, bool =false);
    public:
        bool operator!=(const const_iterator& i) const;
        bool operator==(const const_iterator& i) const;
        const_iterator& operator+=(int);
        const_iterator& operator-=(int);
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        const T& operator*() const;
        const T* operator->() const;
    };

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    T& operator[](unsigned int) const;

    bool search(const T&) const;

    iterator insert(const iterator&, const T&);

    void insert(iterator, const unsigned int&, const T&);

    iterator erase(iterator);

    iterator erase(iterator, iterator);

    Container(const unsigned int&, const T&);

    Container(const unsigned int& =0);

    Container(const Container<T>&);

    Container& operator=(const Container&);

    void clear() throw(Anomalia);

    void push_back(const T&);

    void pop_back() throw(Anomalia);

    void push_front(const T&);

    void pop_front() throw(Anomalia);

    ~Container();
};

//METODI DI ITERATOR
template <class T>
Container<T>::iterator::iterator(Nodo<T>* p, bool a):punt(p), pte(a){}

template <class T>
bool Container<T>::iterator::operator!=(const iterator& i) const{
    return i.punt!=punt;
}

template <class T>
bool Container<T>::iterator::operator==(const iterator& i) const{
    return i.punt==punt;
}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator++(){//operatore prefisso
    if(!pte && punt){
        if(punt->next==nullptr){
            pte=true;
            punt=punt+1;
        }
        else
            punt=punt->next;
    }
    return *this;
}

template <class T>
typename Container<T>::iterator Container<T>::iterator::operator++(int){//operatore postfisso
    iterator aux=*this;
    if(!pte && punt){
        if(punt->next==nullptr){
            pte=true;
            punt=punt+1;
        }
        else
            punt=punt->next;
    }
    return aux;
}

template <class T>
typename Container<T>::iterator& Container<T>::iterator::operator--(){//operatore prefisso
    if(pte){
        pte=false;
        punt=punt-1;
    }
    else if(punt){
        punt=punt->prev;
    }
    return *this;
}

template <class T>
typename Container<T>::iterator Container<T>::iterator::operator--(int){
    iterator aux=*this;
    if(pte){
        pte=false;
        punt=punt-1;
    }
    else if(punt){
        punt=punt->prev;
    }
    return aux;
}

template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator+=(int x) {
    if(!pte && punt){
        for(int i=0; i<x && punt!=nullptr; ++i){
            if(punt->next==nullptr){
                pte=true;
                punt=punt+1;
            }
            else
                punt=punt->next;
        }
    }
    return *this;
}

template<class T>
typename Container<T>::iterator& Container<T>::iterator::operator-=(int x) {
   for(int i=0; i<x && punt->prev!=nullptr; ++i){
       if(pte){
            pte=false;
            punt=punt-1;
       }
       else if(punt){
            punt=punt->prev;
        }
    }
    return *this;
}

template <class T>
T& Container<T>::iterator::operator*() const{
    return punt->info;
}

template <class T>
T* Container<T>::iterator::operator->() const{
    return &(punt->info);
}

//METODI DI CONST_ITERATOR

template <class T>
Container<T>::const_iterator::const_iterator(Nodo<T>* p, bool a):punt(p), pte(a){}

template <class T>
bool Container<T>::const_iterator::operator!=(const const_iterator& i) const{
    return i.punt!=punt;
}

template <class T>
bool Container<T>::const_iterator::operator==(const const_iterator& i) const{
    return i.punt==punt;
}

template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator++(){//operatore prefisso
    if(!pte && punt){
        if(punt->next==nullptr){
            pte=true;
            punt=punt+1;
        }
        else
            punt=punt->next;
    }
    return *this;
}

template <class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator++(int){//operatore postfisso
    const_iterator aux=*this;
    if(!pte && punt){
        if(punt->next==nullptr){
            pte=true;
            punt=punt+1;
        }
        else
            punt=punt->next;
    }
    return aux;
}

template <class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator--(){//operatore prefisso
    if(pte){
        pte=false;
        punt=punt-1;
    }
    else if(punt){
        punt=punt->prev;
    }
    return *this;
}

template <class T>
typename Container<T>::const_iterator Container<T>::const_iterator::operator--(int){
    const_iterator aux=*this;
    if(pte){
        pte=false;
        punt=punt-1;
    }
    else if(punt){
        punt=punt->prev;
    }
    return aux;
}

template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator+=(int x) {
    if(!pte && punt){
        for(int i=0; i<x && punt!=nullptr; ++i){
            if(punt->next==nullptr){
                pte=true;
                punt=punt+1;
            }
            else
                punt=punt->next;
        }
    }
    return *this;
}
template<class T>
typename Container<T>::const_iterator& Container<T>::const_iterator::operator-=(int x) {
    for(int i=0; i<x && punt->prev!=nullptr; ++i){
        if(pte){
             pte=false;
             punt=punt-1;
        }
        else if(punt){
             punt=punt->prev;
         }
     }
     return *this;
}

template <class T>
const T& Container<T>::const_iterator::operator*() const{
    return punt->info;
}

template <class T>
const T* Container<T>::const_iterator::operator->() const{
    return &(punt->info);
}

//METODI DI CONTAINER

template <class T>
typename Container<T>::iterator Container<T>::begin(){
    return iterator(first);
}

template <class T>
typename Container<T>::iterator Container<T>::end(){
    if(first==nullptr)
        return iterator(nullptr);
    else
        return iterator(last+1, true);
}

template <class T>
typename Container<T>::const_iterator Container<T>::begin() const{
    return const_iterator(first);
}

template <class T>
typename Container<T>::const_iterator Container<T>::end() const{
    if(first==nullptr)
        return const_iterator(nullptr);
    else
        return const_iterator(last+1, true);
}

template <class T>
T& Container<T>::operator[](unsigned int i) const{
    if(i >= size)
        throw Anomalia();
    Nodo<T>* p=first;
    unsigned int x=0;
    while(p!=last && x<i){
        p=p->next;
        ++x;
    }
    if(p == last && x > i)
        throw Anomalia();
    return p->info;
}


template <class T>
bool Container<T>::search(const T& i) const{
    if(size==0)
        return false;
    Nodo<T>* p=first;
    for(; p!=last && p->info != i; p=p->next);
    if(p->info == i)
        return true;
    return false;
}

//inserisce l'elementro t prima dell'elemento puntato da it e ritorna un iteratore che punta all'elemento appena inserito
template<class T>
typename Container<T>::iterator Container<T>::insert(const iterator& it, const T& t){
        if(it==begin()){
            size=size+1;
            first=new Nodo<T>(t,nullptr,first);
            if(first->next!=nullptr)
                (first->next)->prev=first; //aggiorno il puntatore prev del nodo successivo
            else //if(last==nullptr)
                last=first; //primo e ultimo elemento sono uguali perchè last=0 significa che la lista era vuota
            return begin();
        }
        else if(it==end()){ //d e t
            size=size+1;
            last=new Nodo<T>(t, last, nullptr);
            if(last->prev==nullptr)
                first=last;
            else
                (last->prev)->next=last;
            return iterator(last);
        }
        else{
            size=size+1;
            Nodo<T>* prec=it.punt->prev;
            Nodo<T>* prox=it.punt;
            Nodo<T>* p=new Nodo<T>(t,prec,prox);
            prec->next=p;
            prox->prev=p;
            return iterator(p);
        }
    return iterator(nullptr);
}

//inserisce n copie dell'elemento t nella sequenza c immediatamente prima dell'elemento puntato da it
template <class T>
void Container<T>::insert(iterator it, const unsigned int& n, const T& t){
    if(it==begin()){
        for(unsigned int i=0; i<n; ++i){
            first=new Nodo<T>(t, nullptr, first); //creo il nodo iniziale che punta alla lista già creata finora
            if(last==nullptr)
                last=first; //primo e ultimo elemento sono uguali perchè last=0 significa che la lista era vuota
            else
                (first->next)->prev=first; //aggiorno il puntatore prev del nodo successivo
            size=size+1;
        }
    }
    else if(it==end()){
        for(unsigned int i=0; i<n; ++i){
            last=new Nodo<T>(t,last,nullptr);
            if(first==nullptr)
                first=last;
            else
                (last->prev)->next=last;
            size=size+1;
        }
    }
    else{
        for(unsigned int i=0; i<n; ++i){
            Nodo<T>* prec=it.punt->prev;
            Nodo<T>* prox=it.punt;
            Nodo<T>* p=new Nodo<T>(t,prec,prox);
            prec->next=p;
            prox->prev=p;
            size=size+1;
        }
    }
}

//distrugge l'elemento puntato da it, lo rimuove dalla sequenza c e ritorna un iterator che punta all'elemento successivo
template <class T>
typename Container<T>::iterator Container<T>::erase(iterator it){ //l=(1|null)
    if(first!=nullptr && it!=end()){
        size=size-1;
        if(it==begin()){
            if(first->next!=nullptr){
                Nodo<T>* p=first->next;
                p->prev=nullptr;
                first->next=nullptr;
                delete first;
                first=p;
                if(first->next==nullptr)
                    last=first;
                return begin();
            }
            else{
                delete first;
                first=last=nullptr;
                return end();
            }
        }
        else{
            if(it.punt==last){
                Nodo<T>* prec=last->prev;
                prec->next=nullptr;
                delete last;
                if(prec==first)
                    last=first;
                else
                    last=prec;
                return end();
            }
            else{
                Nodo<T>* prec=it.punt->prev;
                prec->next=it.punt->next;
                (it.punt->next)->prev=prec;
                it.punt->next=nullptr;
                delete it.punt;
                return iterator(prec->next);
            }
        }
    }
    else{
        throw(Anomalia('v'));
    }
    return iterator(nullptr);
}

/*distrugge gli elementi nell'intervallo [a,b), li rimuove dalla sequenza c e ritorna un iteratore che punta all'elemento che seguiva
 * l'elemento rimosso*/
template <class T>
typename Container<T>::iterator Container<T>::erase(iterator it1, iterator it2){
     //controllo se it1 è < di it2
    iterator  it=it1;
    unsigned int s=0;
    for(; it!=it2 && it!=end(); ++it){
        ++s; //elementi da rimuovere
    }
    if(first!=nullptr && it==it2 && s>0){
        size=size-s;
        if(it1 == begin()){
            if(it2==end()){
                delete first;
                first=last=nullptr;
                return end();
            }
            for(; first->next && first!=it2.punt; ++it1){
                Nodo<T>* prox=first->next;
                first->next=nullptr;
                prox->prev=nullptr;
                delete first;
                first=prox;
            }
            return iterator(first);
        }
        else{
            Nodo<T>* p=it1.punt;
            if(it2==end()){
                Nodo<T>* q=p->prev;
                q->next=nullptr;
                delete p;
                last=q;
                return end();
            }
            for(; p->next && p!=it2.punt; ++it1){
                Nodo<T>* prox=p->next;
                (p->prev)->next=prox;
                prox->prev=p->prev;
                p->next=nullptr;
                delete p;
                p=prox;
            }
            return iterator(p);
        }
    }
    else{
        throw(Anomalia('v'));
    }
    return iterator(nullptr);
}

template<class T>
Container<T>::Container(const unsigned int& n, const T& t):first(nullptr), last(nullptr), size(0){
    insert(begin(),n,t);
}

template <class T>
Container<T>::Container(const unsigned int& n):first(nullptr), last(nullptr), size(0){
    T t; //implementare costruttore di default nella classe T
    Container(n,t);
}

template <class T>
Container<T>::Container(const Container<T>& c):first(copy(c.first, last)),size(c.size){}

template <class T>
Container<T>& Container<T>::operator=(const Container& l){
    if(this != &l){
        if(first)
            delete first;
		size=l.size;
        first=copy(l.first, last);
    }
    return *this;
}

template <class T>
void Container<T>::clear() throw(Anomalia){
    try {
        erase(begin(), end());
    } catch (Anomalia) {
        throw;
    }
}

template <class T>
void Container<T>::push_back(const T& t){
    insert(end(), t);
}

template <class T>
void Container<T>::pop_back() throw(Anomalia){
    try{
        erase(--end());
    }
    catch(Anomalia){
        throw;
    }
}

template <class T>
void Container<T>::push_front(const T& t){
    insert(begin(),t);
}

template <class T>
void Container<T>::pop_front() throw(Anomalia){
    try {
        erase(begin());
    } catch (Anomalia) {
        throw;
    }

}

template <class T>
Container<T>::~Container(){
    if(first) delete first;
}

#endif // CONTAINER_H
