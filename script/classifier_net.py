import caffe 
from caffe import layers as L 
from caffe import params as P 
import numpy as np 
import argparse

def base_net(prototxt):
    prototxt_file=open(prototxt)
    base_net_str=prototxt_file.read()
    prototxt_file.close()
    return base_net_str

def inception_net(bottom_name='inception_4e/output', num_output = 62):

    net=caffe.NetSpec()
    net[bottom_name],net['label']=L.Data(ntop=2)
    net['output'] = L.InnerProduct(net[bottom_name], num_output=num_output, \
                                    param = [dict(lr_mult=1, decay_mult=1),  \
                                             dict(lr_mult=2, decay_mult=0)],
                                    weight_filler=dict(type="xavier", std=0.1),
                                    bias_filler=dict(type="constant", value=0.2))
    net['loss'] = L.SoftmaxWithLoss(net['output'], net['label']);
    net['accuracy'] = L.Accuracy(net['output'], net['label'], include=dict(phase=1));
    proto_str='%s'%net.to_proto()
    return proto_str[proto_str.find('}')+1:]
def write_file(file_name,proto_str):
    text_file = open(file_name, "w")
    text_file.write(proto_str)
    text_file.close()


if __name__ == '__main__':
    base_str=base_net("train_val.prototxt");    
    last_str=base_str[base_str.rfind('top'):]
    last_str=last_str[last_str.find('\"')+1:]
    print last_str
    feature_name=last_str[:last_str.find('\"')]
    proto_str = inception_net(bottom_name=feature_name);
    print proto_str
    write_file("inception.prototxt", base_str+proto_str);

