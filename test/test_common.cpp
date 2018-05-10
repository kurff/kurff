#include "core/common.hpp"
#include <iostream>
#include "core/registry.h"
#include <assert.h>
using namespace kurff;


class Foo {
 public:
  explicit Foo() { std::cout << "Foo " ; }
  virtual void run(){
    std::cout<<"run Foo"<<std::endl;
  }
};

CAFFE_DECLARE_REGISTRY(FooRegistry, Foo);
CAFFE_DEFINE_REGISTRY(FooRegistry, Foo);
//#define REGISTER_FOO(clsname) \
  CAFFE_REGISTER_CLASS(FooRegistry, clsname, clsname)

class Bar : public Foo {
 public:
  explicit Bar() : Foo() { std::cout << "Bar " ; }
  void run(){
    std::cout<<"run Bar"<<std::endl;
  }
};
CAFFE_REGISTER_CLASS(FooRegistry, Bar, Bar);

class AnotherBar : public Foo {
 public:
  explicit AnotherBar() : Foo() {
    std::cout << "AnotherBar ";
  }
  void run(){
    std::cout<<"run AnotherBar"<<std::endl;
  }
};
CAFFE_REGISTER_CLASS(FooRegistry, AnotherBar, AnotherBar);

int main(){
    auto x = map_int2string.find(0);
    std::cout<< x->second<<std::endl;
    unique_ptr<Foo> bar(FooRegistry()->Create("Bar"));
    bar->run();
    assert(bar != nullptr);
    unique_ptr<Foo> another_bar(FooRegistry()->Create("AnotherBar"));
    another_bar->run();
    assert(another_bar != nullptr);


}