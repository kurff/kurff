#include "synthesis/synthesis.hpp"
#include "core/parameters.hpp"
//#include "synthesis/deform.hpp"
using namespace kurff;
int main(){
    Parameters* parameters = global_parameters();
    read_from_text("parameters.txt", parameters);
    


    Synthesis* synthesis = new Synthesis("fonts.txt");
    synthesis->init(parameters);
    synthesis->run("file.txt", "./images/" );


}