#include "classifier/classifier.hpp"
using namespace kurff;
int main(){
    
    std::shared_ptr<Classifier<CPUContext> > classifier = ClassifierRegistry()->Create("CNNClassifier<CPUContext>");
    classifier->build();
    return 0;
}