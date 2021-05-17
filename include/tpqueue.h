// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>

template<typename T>
class TPQueue {
  struct ITEM {
    T data;
    ITEM * next;
  };
 public:
  TPQueue() : head(nullptr), tail(nullptr) {}
  ~TPQueue();
  void push(const T&);
  T pop();
 private:
  TPQueue:: ITEM * create(const T&);
  ITEM *head;
  ITEM *tail;
};

template <typename T>
TPQueue<T>::~TPQueue() {
  while (head)
  pop();
}

template <typename T>
typename TPQueue <T>::ITEM *TPQueue <T>::create(const T& data) {
  ITEM *item = new ITEM;
  item->data = data;
  item->next = nullptr;
  return item;
}

template <typename T>
void TPQueue <T>::push(const T& data) {
  if (head && tail) {
    ITEM *temp = head;
    if (temp->data.prior < data.prior) {
      temp = create(data);
      temp->next = head;
      head = temp;
    } else {
      while (temp->next) {
        if (temp->next->data.prior < data.prior) {
          ITEM *t = create(data);
          t->next = temp->next;
          temp->next = t;
          break;
        } else {
          temp = temp->next;
        }
      }
    }
    if (!temp->next) {
      tail->next = create(data);
      tail = tail->next;
    } else {
    head = create(data);
    tail = head;
  }
}

template <typename T>
T TPQueue<T>::pop() {
  if (head) {
    ITEM* temp = head->next;
    T data = head->data;
    delete head;
    head = temp;
    return data;
  } else {
    return (T)0;
  }
}

struct SYM {
  char ch;
  int  prior;
};

#endif // INCLUDE_TPQUEUE_H_
