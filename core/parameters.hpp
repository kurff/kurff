#ifndef __PARAMETERS_HPP__
#define __PARAMETERS_HPP__

#include "proto/kurff.pb.h"
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <stdint.h>
using google::protobuf::Message;
using google::protobuf::io::FileInputStream;
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include "glog/logging.h"
using namespace std;


namespace kurff{


void read_from_text(string file, Parameters* parameters){
    int fd = open(file.c_str(), O_RDONLY);
                
    FileInputStream* input = new FileInputStream(fd);
    bool success = google::protobuf::TextFormat::Parse(input, (Message*)(parameters));
    delete input;
    close(fd);
    LOG(INFO)<< "mean lower: "<<parameters->mean().lower();
    LOG(INFO)<< "mean upper: "<<parameters->mean().upper();
    LOG(INFO)<< "transform size: "<< parameters->transform_size();
    for(int i = 0; i < parameters->transform_size(); ++ i){
        LOG(INFO)<<"transform: "<< parameters->transform(i);
    }

}

static Parameters* global_parameters(){
    static Parameters* param = new Parameters();
    return param;
}



}


#endif