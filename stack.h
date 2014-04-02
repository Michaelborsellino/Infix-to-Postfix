#ifndef STACK_H
#define STACK_H
#include<iostream>
#include<list>

namespace cop4530
{
  template<typename T>
  class Stack{
    public:
      std::list<T> c;//
    public:
      Stack<T>();//
      ~Stack<T>();//
      Stack<T>(const Stack<T>&);//
      Stack<T>(Stack<T>&&);
      Stack<T>& operator= (const Stack<T>&);//
      Stack<T>& operator= (const Stack<T>&&);
      bool empty() const;
      void clear();
      void push(const T& x);
      void push(T&& x);
      void pop();
      T& top();
      const T& top() const;
      int size() const;
      void print(std::ostream& os, char ofc= ' ') const;
//   friend Stack<T>;
  };
  template<typename T>
  std::ostream& operator<<(std::ostream& os, const Stack<T>& a);
  template<typename T>
  bool operator==(const Stack<T>&, const Stack<T>&);
  template<typename T>
  bool operator!=(const Stack<T>&, const Stack<T>&);
  template<typename T>
  bool operator< (const Stack<T>& a, const Stack<T>& b);

  #include "stack.hpp"
}//end namespace
#endif
