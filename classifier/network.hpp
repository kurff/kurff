#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__
#include "classifier/net.h"
#include "glog/logging.h"
#include <memory>
#include <string>
#include <vector>
#include "caffe2/core/tensor.h"
#include <map>
using namespace std;
using namespace caffe2;
namespace kurff{
    
    template<typename DataContext>
    class Network{
        typedef typename caffe2::Tensor<DataContext> T;

        public:
            Network(const std::map<string, vector<int> >& inputs, const std::map<string, vector<int> >& outputs
            , const std::map<string , vector<int> > labels, bool training, bool use_gpu = false )
            : training_(training), inputs_(inputs), outputs_(outputs), labels_(labels), use_gpu_(use_gpu){
                LOG(INFO)<<"create network";
                // inputs_.insert(inputs.begin(), inputs.end());
                // outputs_.insert(outputs.begin(), outputs.end());
                // labels_.insert(labels.begin(), labels.end());

            }
            Network(int batch_size, int num_output, bool training = true):batch_size_(batch_size), num_output_(num_output), training_(training){
                

            }

            Network(){

            }

            ~Network(){


            }

        public:
            void init(NetDef& init_model, NetDef& predict_model, NetDef& update_model){
                
                init_model_ = init_model;
                predict_model_ = predict_model;
                update_model_ = update_model;
                init_net_.reset(new Net(init_model_));
                predict_net_.reset(new Net(predict_model_));
                update_net_.reset(new Net(update_model_)); 
                if(use_gpu_){
                    init_net_->SetDeviceCUDA();
                    predict_net_->SetDeviceCUDA();
                    update_net_->SetDeviceCUDA();
                }
                workspace_.reset(new Workspace("workspace"));
                // create input data
            }

            void allocate_inputs(){
                for(auto in : inputs_ ){
                    Blob* data = workspace_->CreateBlob(in.first);
                    T* input = data->GetMutable<T>();
                    input->Resize(in.second);
                    input->template mutable_data<float>();
                }
                // create label pai, action prediction
                for(auto lab : labels_){
                    Blob* l = workspace_->CreateBlob(lab.first);
                    T* label_pai = l->GetMutable<T>();
                    label_pai->Resize(lab.second);
                    label_pai->template mutable_data<int>();
                }
            }






            void allocate(){
                init_ = CreateNet( init_model_,workspace_.get());
                init_->Run();
                LOG(INFO)<<"create init network finish";
                predict_ = CreateNet(predict_model_, workspace_.get());
                LOG(INFO)<<"create predict network finish";
                update_ = CreateNet(update_model_, workspace_.get());
                LOG(INFO)<<"create update network finish";
            }

            void create_network(){
                //create_lenet(training);
                LOG(INFO)<<"create network";

                allocate_inputs();
                LOG(INFO)<<"allocate inputs";
                add_feed_data();
                LOG(INFO)<<"add feed data";
                add_label_data();
                LOG(INFO)<<"add label data";
                auto input = inputs_.find("data");
                if(input == inputs_.end()){
                    LOG(INFO)<<"can not find data input";
                }
                string middle;
                create_base_network(input->first,middle);
                LOG(INFO)<<"create base network";
                auto output = outputs_.find("class");
                if(output == outputs_.end()){
                    LOG(INFO)<<"can not find data output";
                }

                create_head_classifier(middle,output->first, output->second[0]);
                LOG(INFO)<<"create head classifier";
                create_classification_loss("class", "label");
            }

            void create_network_classifier_from_db(){
                LOG(INFO)<<"create network from db";
                add_database("train-lmdb","lmdb", batch_size_);
                string middle;
                create_base_network("data", middle);
                create_head_classifier(middle,"class", num_output_);
                LOG(INFO)<<"create head classifier";
                create_classification_loss("class", "label"); 


            }

            void add_convolutional_block(const string inputs, 
            string& outputs, vector<int> shapes,int index, bool pooling = false){
                string w = "conv_w_"+std::to_string(index);
                string b = "conv_b_"+std::to_string(index);
                string o = "conv_o_"+std::to_string(index);
                string m = "conv_m_"+std::to_string(index);
                
                LOG(INFO)<<"size of inputs is 1";
                update_net_->AddConvOp(inputs,w,b,m,1,0,shapes[2]);
                predict_net_->AddConvOp(inputs,w,b,m,1,0,shapes[2]);
                update_net_->AddInput(w);
                update_net_->AddInput(b);
                predict_net_->AddInput(w);
                predict_net_->AddInput(b);
                update_net_->AddReluOp(m,m);
                predict_net_->AddReluOp(m,m);
                if(pooling){
                    update_net_->AddMaxPoolOp(m,o,2,0,2);
                    predict_net_->AddMaxPoolOp(m,o,2,0,2);
                    outputs = o;
                }else{
                    outputs = m;
                }
                if(training_){
                    init_net_->AddXavierFillOp(shapes, w);
                    init_net_->AddConstantFillOp({shapes[0]}, b);
                }
            }

            void add_fc_block_with_output(const string inputs, 
             const string outputs, vector<int> shapes,
                int index, bool add_relu = true, bool add_softmax = false
                , bool add_tanh = false){
                LOG(INFO)<<"add fc block with const output";
                string w = "fc_w_"+std::to_string(index);
                string b = "fc_b_"+std::to_string(index);
                string o = "fc_o_"+std::to_string(index);
                
                update_net_->AddFcOp(inputs,w,b,o);
                predict_net_->AddFcOp(inputs,w,b,o);
                update_net_->AddInput(w);
                update_net_->AddInput(b);
                predict_net_->AddInput(w);
                predict_net_->AddInput(b);
                if(add_relu){
                    update_net_->AddReluOp(o,outputs);
                    predict_net_->AddReluOp(o,outputs);
                }
                if(add_softmax){
                    update_net_->AddSoftmaxOp(o,outputs);
                    predict_net_->AddSoftmaxOp(o,outputs);
                }
                if(add_tanh){
                    update_net_->AddTanh(o,outputs);
                    predict_net_->AddTanh(o,outputs);
                }
                if(training_){
                    init_net_->AddXavierFillOp(shapes, w);
                    init_net_->AddConstantFillOp({shapes[0]}, b);
                }
            }


            void add_fc_block(const string inputs, 
            string& outputs, vector<int> shapes,
                int index, bool add_relu = true, bool add_softmax = false
                , bool add_tanh = false){
                LOG(INFO)<<"add fc block with non-const output";
                string w = "fc_w_"+std::to_string(index);
                string b = "fc_b_"+std::to_string(index);
                string o = "fc_o_"+std::to_string(index);
                string t = "t_"+std::to_string(index);               
                outputs = o;                
                update_net_->AddFcOp(inputs,w,b,t);
                predict_net_->AddFcOp(inputs,w,b,t);
                update_net_->AddInput(w);
                update_net_->AddInput(b);
                predict_net_->AddInput(w);
                predict_net_->AddInput(b);
                if(add_relu){
                    update_net_->AddReluOp(t,o);
                    predict_net_->AddReluOp(t,o);
                }
                if(add_softmax){
                    update_net_->AddSoftmaxOp(t,o);
                    predict_net_->AddSoftmaxOp(t,o);
                }
                if(add_tanh){
                    update_net_->AddTanh(t,o);
                    predict_net_->AddTanh(t,o);
                }
                if(training_){
                    init_net_->AddXavierFillOp(shapes, w);
                    init_net_->AddConstantFillOp({shapes[0]}, b);
                }

            }


            void add_residual_block(const string inputs, 
            string& outputs){


            }

            void add_feed_data(){
                for(auto in : inputs_){
                    update_net_->AddInput(in.first);
                    predict_net_->AddInput(in.first);
                }
            }

            void add_database(const string db, const string & db_type, int batch_size){
                init_net_->AddCreateDbOp("dbreader", db_type, db);
                //predict_net_->AddInput("dbreader");
                update_net_->AddInput("dbreader");
                update_net_->AddTensorProtosDbInputOp("dbreader", "data_uint8", "label", batch_size);
                update_net_->AddCastOp("data_uint8", "data", TensorProto_DataType_FLOAT);
                update_net_->AddScaleOp("data", "data", 1.f/255);
                update_net_->AddStopGradientOp("data");
            }

            void add_label_data(){
                for(auto lab : labels_ ){
                    update_net_->AddInput(lab.first);
                }           
            }


            void create_base_network(const string input, 
            string& output){
                string output_block1;
                string output_block2;
                string output_block3;
                add_convolutional_block(input, output_block1,{32,3,3,3},0,true);
                add_convolutional_block(output_block1, output_block2,{32,32,3,3},1, true);
                add_convolutional_block(output_block2, output_block3,{32,32,3,3},2, true);
                add_convolutional_block(output_block3, output,{32,32,3,3},3,true);
                //vector<string> fc_block1;
                //vector<string> fc_block2;
                //add_fc_block(output_block3,fc_block1,{100,},1,0,1);
                //add_fc_block(fc_block1,fc_block2,{},1,1,0);
            }

            void create_head_classifier(const string input, const string output, int num_output){
                string middle;
                add_fc_block(input,middle,{100,8*8*32},0);
                add_fc_block_with_output(middle, output, {num_output,100} ,1 ,0,1,0);
            }
            


            void create_head_regression(const string inputs, 
            const string outputs){
                string output_block1;
                
                // add_convolutional_block(inputs, output_block1, {2,32,1,1},3);
                // //vector<string> fc_block1;

                // add_fc_block(output_block1, outputs,{ output_dim_,162},0,0,0,1);
                // string output_block2;
                // add_convolutional_block(inputs,output_block2,{1,32,1,1},4);
                // //vector<string> fc_block2;
                // add_fc_block(output_block2, outputs,{1,81},1,0,1,0);

            }

            void add_iter(){
                update_net_->AddInput("ITER");
                init_net_->AddConstantFillOp({1}, 1.f, "ONE");
                if(use_gpu_){
                    init_net_->AddConstantFillOp({1}, (int64_t)0, "ITER")->mutable_device_option()->set_device_type(CUDA);
                }else{
                    init_net_->AddConstantFillOp({1}, (int64_t)0, "ITER")->mutable_device_option()->set_device_type(CPU);
                }
                update_net_->AddInput("ONE");
                update_net_->AddIterOp("ITER");
                update_net_->AddLearningRateOp("ITER", "LR", 0.1);
                LOG(INFO)<<"add input and iter";
            }

            void add_update(){
                params_.clear();
                for(auto op : init_model_.op()){
                    for(auto out: op.output()){
                        if(!(out.compare("ITER")==0 || out.compare("ONE")==0 || out.compare("dbreader") ==0)){
                            params_.push_back(out);
                        }
                    }
                }
                for(auto param : params_){
                    LOG(INFO)<<"init model output: "<<param;
                    update_net_->AddWeightedSumOp({param,"ONE", param+"_grad","LR"},param);
                }
            }

            void create_classification_loss(const string predict, const string label){
                add_iter();
                update_net_->AddLabelCrossEntropyOp(predict,label,"xent");
                update_net_->AddAveragedLossOp("xent","loss");
                update_net_->AddConstantFillWithOp(1.f, "loss", "loss_grad");
                update_net_->AddGradientOps();
                add_update();
            }



            void create_regression_loss(){


            }

            void create_multi_task_loss(const vector<string>& predict, const vector<string>& label ){
                //update_net_->AddLabelCrossEntropyOp();
                add_iter();
               
                update_net_->AddConstantFillOp({1}, 0.5f,"weight1");
                update_net_->AddConstantFillOp({1}, 0.5f,"weight2");



                update_net_->AddLabelCrossEntropyOp(predict[0], label[0], "xent");
                update_net_->AddAveragedLossOp("xent","loss1");
                update_net_->AddSquaredL2DistanceOp({predict[1],label[1]},"l2_loss");
                update_net_->AddAveragedLossOp("l2_loss","loss2");
                //update_net_->AddInput("weight1");
                //update_net_->AddInput("weight2");

                update_net_->AddWeightedSumOp({"loss1","weight1","loss2","weight2"},"loss");
                LOG(INFO)<<"add loss op";
                update_net_->AddConstantFillWithOp(1.f, "loss", "loss_grad");
                update_net_->AddConstantFillWithOp(1.f, "loss1", "loss1_grad");
                update_net_->AddConstantFillWithOp(1.f, "loss2", "loss2_grad");
                LOG(INFO)<<"AddConstantFillWithOp";
                update_net_->AddGradientOps();
                LOG(INFO)<<"AddGradientOps";
                update_net_->AddLearningRateOp("ITER", "LR", 0.1);
                LOG(INFO)<<"add params";
                params_.clear();
                for(auto op : init_model_.op()){
                    for(auto out: op.output()){
                        if(!(out.compare("ITER")==0 || out.compare("ONE")==0|| out.compare("dbreader") ==0)){
                            params_.push_back(out);
                        }
                    }
                }
                for(auto param : params_){
                    LOG(INFO)<<"init model output: "<<param;
                    update_net_->AddWeightedSumOp({param,"ONE", param+"_grad","LR"},param);
                }

            }


            void create_lenet(){
                // update_net_->AddInput("data");
                // predict_net_->AddInput("data");

                // update_net_->AddInput("pai");
                // update_net_->AddConvOp("data", "conv1_w", "conv1_b", "conv1", 1, 0, 5);
                // predict_net_->AddConvOp("data", "conv1_w", "conv1_b", "conv1", 1, 0, 5);

                // update_net_->AddReluOp("conv1", "conv1");
                // predict_net_->AddReluOp("conv1", "conv1");
                
                // update_net_->AddInput("conv1_w");
                // predict_net_->AddInput("conv1_w");
               
                // update_net_->AddInput("conv1_b");
                // predict_net_->AddInput("conv1_b");

                // if (training_) {
                //     init_net_->AddXavierFillOp({20, 3, 5, 5}, "conv1_w");
                //     init_net_->AddConstantFillOp({20}, "conv1_b");
                // }

                // update_net_->AddMaxPoolOp("conv1", "pool1", 2, 0, 2);
                // update_net_->AddConvOp("pool1", "conv2_w", "conv2_b", "conv2", 1, 0, 5);
                // update_net_->AddInput("conv2_w");
                // update_net_->AddInput("conv2_b");

                // predict_net_->AddMaxPoolOp("conv1", "pool1", 2, 0, 2);
                // predict_net_->AddConvOp("pool1", "conv2_w", "conv2_b", "conv2", 1, 0, 5);
                // predict_net_->AddInput("conv2_w");
                // predict_net_->AddInput("conv2_b");

                // if (training_) {
                //     init_net_->AddXavierFillOp({50, 20, 5, 5}, "conv2_w");
                //     init_net_->AddConstantFillOp({50}, "conv2_b");
                // }



                // update_net_->AddMaxPoolOp("conv2", "pool2", 2, 0, 2);
                // update_net_->AddFcOp("pool2", "fc3_w", "fc3_b", "fc3");
                // update_net_->AddInput("fc3_w");
                // update_net_->AddInput("fc3_b");

                

                // predict_net_->AddMaxPoolOp("conv2", "pool2", 2, 0, 2);
                // predict_net_->AddFcOp("pool2", "fc3_w", "fc3_b", "fc3");
                // predict_net_->AddInput("fc3_w");
                // predict_net_->AddInput("fc3_b");


                // if (training_) {
                //     init_net_->AddXavierFillOp({500, 50}, "fc3_w");
                //     init_net_->AddConstantFillOp({500}, "fc3_b");
                // }


                // update_net_->AddReluOp("fc3", "fc3");

                
                // update_net_->AddFcOp("fc3", "pred_w", "pred_b", "pred");
                // update_net_->AddInput("pred_w");
                // update_net_->AddInput("pred_b");





                // predict_net_->AddReluOp("fc3", "fc3");
                // predict_net_->AddFcOp("fc3", "pred_w", "pred_b", "pred");
                // predict_net_->AddInput("pred_w");
                // predict_net_->AddInput("pred_b");



                // if (training_) {
                //     init_net_->AddXavierFillOp({output_dim_, 500}, "pred_w");
                //     init_net_->AddConstantFillOp({output_dim_}, "pred_b");
                // }

                // update_net_->AddSoftmaxOp("pred", "softmax");
                // predict_net_->AddSoftmaxOp("pred", "softmax");




                // LOG(INFO)<<predict_model_.external_input().size();
                // for(auto x: predict_model_.external_input()){
                //     LOG(INFO)<<x;
                // }
                // LOG(INFO)<<init_model_.external_input().size();
                // for(auto x: init_model_.external_input()){
                //     LOG(INFO)<<x;
                // }
                //for(auto op: init_model_.op()){
                //    LOG(INFO)<<op.type()<<" "<<op.name();
                //}
                //for(auto op: predict_model_.op()){
                //    LOG(INFO)<<op.type()<<" "<<op.name();
                //}
            }

            void add_loss(){
                update_net_->AddInput("ITER");
                init_net_->AddConstantFillOp({1}, 1.f, "ONE");
                init_net_->AddConstantFillOp({1}, (int64_t)0, "ITER")->mutable_device_option()->set_device_type(CPU);
                update_net_->AddInput("ONE");
                update_net_->AddIterOp("ITER");


                update_net_->AddLabelCrossEntropyOp("softmax", "pai", "xent");
                update_net_->AddAveragedLossOp("xent","loss");
                update_net_->AddConstantFillWithOp(1.f, "loss", "loss_grad");
                update_net_->AddGradientOps();
                update_net_->AddLearningRateOp("ITER", "LR", 0.1);

                params_.clear();
                for(auto op : init_model_.op()){
                    for(auto out: op.output()){
                        if(!(out.compare("ITER")==0 || out.compare("ONE")==0
                        || out.compare("dbreader") ==0)){
                            params_.push_back(out);
                        }
                    }
                }
                for(auto param : params_){
                    LOG(INFO)<<"init model output: "<<param;
                    update_net_->AddWeightedSumOp({param,"ONE", param+"_grad","LR"},param);
                }

                
            }

            void print_shape(){
                for(auto x: workspace_->Blobs()){
                    LOG(INFO)<<"workspace: "<<x;
                    auto y = workspace_->GetBlob(x);
                    LOG(INFO)<<y->Get<TensorCPU>().dims();
                }
            }

            void init_parameters(){
                init_->Run();
                //print_shape();

            }

            void update_parameters(){
                update_->Run();
                //print_shape();

            }
            void forward(){

            }

            

            void train(){
  
                //predict_->Run();
            }


            void save_model(string init_pb){
                auto op = init_net_->AddSaveOp(params_,1,"minidb",init_pb,"minidb",{});
                workspace_->RunOperatorOnce(*op);
                //for(auto x: params_){
                //    auto b = workspace_->GetBlob(x);
                //    TensorPrinter tensor_print(x,"save"+x);
                //    tensor_print.Print<float>((b->template Get<TensorCPU>()));
                    //tensor_print.PrintMeta(b->Get<>);
                //}
            }

            void load_model(string init_pb){
                auto op = init_net_->AddLoadOp(params_,1,"",{},init_pb,{},"minidb",1,1,1,{});
                workspace_->RunOperatorOnce(*op);
                
                //for(auto x : ws.Blobs()){
                //    LOG(INFO)<<"blob names "<<x;
                //    auto b = ws.GetBlob(x);
                //    TensorPrinter tensor_print(x,"load"+x);
                //    tensor_print.Print<float>(b->template Get<TensorCPU>());
                //}
            }

            void save(string proto_name){
                WriteProtoToTextFile(predict_model_,proto_name+"_pred.pbtxt");
                WriteProtoToTextFile(init_model_, proto_name+"_init.pbtxt");
                WriteProtoToTextFile(update_model_, proto_name+"_update.pbtxt");
            }

        protected:
            
            std::shared_ptr<Net> init_net_;
            std::shared_ptr<Net> predict_net_;
            std::shared_ptr<Net> update_net_;
            std::shared_ptr<Workspace> workspace_;
            NetDef init_model_;
            NetDef predict_model_;
            NetDef update_model_;
            unique_ptr<NetBase> init_;
            unique_ptr<NetBase> predict_;
            unique_ptr<NetBase> update_;
            std::vector<std::string> params_;

            std::map<string, vector<int> > inputs_;
            std::map<string, vector<int> > outputs_;
            std::map<string, vector<int> > labels_;

            int batch_size_;
            int num_output_;
            bool training_;
            bool use_gpu_;

    };




}







#endif