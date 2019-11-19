#include <iostream>
#include <string.h>

#include "has_class_member.h"

DECLARE_HAS_MEMBER(name)

struct Dummy {
  std::string name() {return "Dummy";}
};

struct Student {
  void name(const std::string& name, int age) {
    std::cout <<"student name:" << name <<", age " << age << std::endl;
  }
};

#if __cplusplus < 201500L //C++17
template <typename T> 
typename std::enable_if<HAS_CLASS_MEMBER<T, name, const string&, int>::value>::type say(T & obj) {
  obj.name("Leon, 18);
}

template <typename T> 
typename std::enable_if<!HAS_CLASS_MEMBER<T, name, const string&, int>::type say(T & obj) {
  std::cout <<" name: " << obj.name() << std::endl;
}

#endif 

int main()
{
#if __cplusplus > 201500L //C++17
  constexpr if(HAS_CLASS_MEMBER<T, name, const string&, int>::value)
  {
    obj.name("Leon, 18);
  }
  else 
  {
    std::cout <<" name: " << obj.name() << std::endl;
  }
#else
  Student student;
  say(student);
  return 0;
#endif
}
