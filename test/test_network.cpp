//#include "classifier/classifier.hpp"
#include "classifier/net.h"
using namespace kurff;
int main(){

    NetDef data;
    Net* net = new Net(data);
    
    net->AddCreateDbOp("dbreader", "lmdb", "train-lmdb");
                //predict_net_->AddInput("dbreader");
    net->AddInput("dbreader");
    net->AddTensorProtosDbInputOp("dbreader", "data_uint8", "label", 16);
    net->AddCastOp("data_uint8", "data", TensorProto_DataType_FLOAT);
    net->AddScaleOp("data", "data", 1.f/255);
    net->AddStopGradientOp("data");

    Workspace* ws = new Workspace();

    unique_ptr<NetBase> n = caffe2::CreateNet(data,ws);
    n->Run();
    Blob* d = ws->GetBlob("data");
    TensorPrinter x;
    x.Print<float>(*(d->GetMutable<TensorCPU>()));
    // std::shared_ptr<Classifier<CPUContext> > classifier = ClassifierRegistry()->Create("CNNClassifier<CPUContext>");
    // classifier->build_from_database();
    // classifier->update();
    return 0;
}