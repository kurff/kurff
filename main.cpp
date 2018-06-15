

#include "core/parameters.hpp"
using namespace kurff;
int main(int argc, char* argv[]){

    Parameters* parameters = global_parameters();
    read_from_text("parameters.txt", parameters);
    



    return 1;


}   
