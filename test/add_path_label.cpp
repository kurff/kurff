#include <fstream>
using namespace std;

int main(int argc, char* argv[]){
    ifstream f(argv[1], ios::in);
    string name;
    string path = argv[2];
    ofstream fo(argv[3], ios::out);
    int label;
    while(f >> name >> label){
        fo << path+name <<" "<< label<< endl;

    }
    fo.close();
    f.close();
    return 1;
}