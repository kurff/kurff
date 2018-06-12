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
    net[bottom_name],net['label']=L.Data(ntop=2, data_param=dict(source="./classifier",batch_size=64,backend=1))
    return net.to_proto();
def write_file(file_name,proto_str):
    text_file = open(file_name, "w")
    print proto_str
    text_file.write(proto_str)
    text_file.close()


if __name__ == '__main__':
    proto_str = inception_net(bottom_name='data');
    print proto_str
    write_file("test_input.prototxt", str(proto_str));

