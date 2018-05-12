#include "core/common.hpp"
#include <iostream>
#include "core/registry.h"
#include "core/parameters.hpp"
#include <assert.h>
using namespace kurff;


class Foo {
 public:
  explicit Foo(Parameters* x) { std::cout << "Foo " ; }
  virtual void run(){
    std::cout<<"run Foo"<<std::endl;
  }
};

CAFFE_DECLARE_REGISTRY(FooRegistry, Foo, Parameters*);
CAFFE_DEFINE_REGISTRY(FooRegistry, Foo, Parameters*);
//#define REGISTER_FOO(clsname) \
  CAFFE_REGISTER_CLASS(FooRegistry, clsname, clsname)

class Bar : public Foo {
 public:
  explicit Bar(Parameters* x) : Foo(x) { std::cout << "Bar " ; }
  void run(){
    std::cout<<"run Bar"<<std::endl;
  }
};
CAFFE_REGISTER_CLASS(FooRegistry, Bar, Bar);

class AnotherBar : public Foo {
 public:
  explicit AnotherBar(Parameters* x) : Foo(x) {
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
    Parameters* p;
    unique_ptr<Foo> bar(FooRegistry()->Create("Bar", p));
    bar->run();
    assert(bar != nullptr);
    shared_ptr<Foo> another_bar(FooRegistry()->Create("AnotherBar", p));
    another_bar->run();
    assert(another_bar != nullptr);


}