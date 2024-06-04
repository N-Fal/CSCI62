
#ifndef NODE_H
#define NODE_H
#include <cstdlib>
#include <ostream>
#include <iostream>
using namespace std;

template <typename T>
class node
{
public:
    node(const T & initdata = T(),//By providing default values for parameters, we get
         node * initlink = nullptr){//4 constructors for the price of one
        data_ = initdata;
        link_ = initlink;
    }
    T data() const{
        return data_;
    }
    T data(){
        return data_;
    }
    node * link(){
        return link_;
    }
    const node * link() const{
        return link_;
    }
    void set_data(const T & newdata){
        data_ = newdata;
    }
    void set_link(node * newlink){
        link_ = newlink;
    }
private:
    T data_;
    node * link_;
};

// linked list toolkit functions

template <typename T>
int list_size(const node<T> * head){
  int count = 0;
  for(const node<T> *temp = head; temp !=nullptr ; temp = (*temp).link()){
    count++;
  }
  return count;
}

template <typename T>
void list_head_insert(node<T>* & head,//Shares memory with the head pointer passed in
                      node<T>* & tail,
                      const T & value){
      head = new node<T>(value, head);
      if(tail==nullptr)
        tail=head;
}
template <typename T>
void list_tail_insert(node<T> * & head, node<T>* & tail,
    const T & value){
      node<T>* temp = new node<T>(value, nullptr);
      if(tail !=nullptr)
        (*tail).set_link(temp);
      else
        head = temp;
      tail = temp;
    }

template <typename T>
ostream & operator <<(ostream & os,
  const node<T>* head){
    for(const node<T>* p=head; p!=nullptr; p=(*p).link()){
      os<<(*p).data()<<" ";
    }
    return os;
  }

template <class T>//Return a pointer to a node with the given value
node<T>* list_search(node<T> * head, const T & value){

    for(node<T>* p=head; p!=nullptr; p=(*p).link()){
      if((*p).data()==value)
        return p;
    }
    return nullptr;
}

template <class T>
void list_copy(const node<T> *orig_head,
               const node<T> *orig_tail,
               node<T> * & new_head,
               node<T> * & new_tail){

      //  new_head = orig_head;//Why is this a bad idea?
      //  new_tail = orig_tail;//We want a deep copy!
      //Any of our functions helpful here?
    new_head = new_tail = nullptr;

      for(const node<T>* p=orig_head; p!=nullptr; p=(*p).link()){
        list_tail_insert(new_head, new_tail, (*p).data());
      }

}
template <class T>
void list_head_remove(node<T> * & head, node<T> * &tail){
    node<T>* temp = (*head).link();
    delete head;
    head=temp;
}

template <class T>
void list_remove(node<T> * previous, node<T> * &tail){
  node<T>* temp = (*previous).link();
  (*previous).set_link((*temp).link());
  delete temp;
}


//Remember, we already have head insert and tail insert
template <class T>
void list_insert(node<T> * previous, const T & value){
  node<T>* temp = new node<T>(value, (*previous).link());
  (*previous).set_link(temp);
}

template <class T>
void list_clear(node<T> * & head, node<T> * &tail){////fix
      for(node<T>* p = head; p!=tail; p=(*p).link()){ // the loop should stop when the iterator reaches the tail, not a 'nullptr'
        delete p;
      }
}

#endif // NODE_H
