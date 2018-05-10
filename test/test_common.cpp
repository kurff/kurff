#include "core/common.hpp"
#include <iostream>
using namespace kurff;
int main(){
    auto x = map_int2string.find(0);
    std::cout<< x->second<<std::endl;
}