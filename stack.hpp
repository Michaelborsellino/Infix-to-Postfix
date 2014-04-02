
//default constructor initializes the adapter class
template<typename T>
Stack<T>::Stack():c()
{
}

//default destructor. As adapter class goes out of scope, its
//own destructor gets called
template<typename T>
Stack<T>::~Stack()
{
}

//copies the adapter class object. Via its own assignment operator
template<typename T>
Stack<T>::Stack(const Stack<T>& s)
{
  c = s.c;
}

//move version of above, calling the move function of the object
template<typename T>
Stack<T>::Stack(Stack<T> && s)
{
  c = std::move(s.c);
}

//pushes the object onto the stack
template<typename T>
void Stack<T>::push(const T& x)
{
  c.push_back(x);
}
//move version of above
template<typename T>
void Stack<T>::push(T&& x)
{
  c.push_back(x);
}

//pops the object off the top of the stack
template<typename T>
void Stack<T>::pop()
{
  c.pop_back();
}

//returns the object on the top of the stack
template<typename T>
T& Stack<T>::top()
{
  return c.back();
}

//const version of the above
template<typename T>
const T& Stack<T>::top()const
{
  return c.back();
}

//returns the size of the stack
template<typename T>
int Stack<T>::size() const
{
  return c.size();
}

//returns true if the stack is empty
template<typename T>
bool Stack<T>::empty() const
{
  return c.empty();
}

//clears out the stack object
template<typename T>
void Stack<T>::clear()
{
  c.clear();
}

//specialized print function for stack
template<typename T>
void Stack<T>::print(std::ostream& os, char ofc) const
{
  for(auto it = c.begin(); it != c.end(); it++)
  {
    os<<*it;
    os<<ofc;
  }
}

//overloaded assignment operator
template<typename T>
Stack<T>& Stack<T>::operator= ( const Stack<T>& l)
{
  c = l.c;
}

//move version of above
template<typename T>
Stack<T>& Stack<T>::operator= ( const Stack<T>&& l)
{
  c = std::move(l.c);

}

//overloaded equality operator
template<typename T>
bool operator==(const Stack<T>& lhs, const Stack<T>& rhs)
{
  return lhs.c == rhs.c;
}

//overloaded inequality operator
template <typename T>
bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs)
{
  return !(lhs.c == rhs.c);
}

//comparison operator of the stacks
template<typename T>
bool operator< (const Stack<T>& a, const Stack<T>& b)
{
  return a.size()<b.size();
} 

//overloaded output operator
template<typename T>
std::ostream& operator<<(std::ostream& os, const Stack<T>& a)
{
  a.print(os);
  return os;
}
