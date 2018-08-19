
// This program converts a set of images to a lmdb/leveldb by storing them
// as Datum proto buffers.
// Usage:
//   convert_imageset [FLAGS] ROOTFOLDER/ LISTFILE DB_NAME
//
// where ROOTFOLDER is the root folder that holds all the images, and LISTFILE
// should be a list of files as well as their labels, in the format as
//   subfolder1/file1.JPEG 7
//   ....
#define USE_OPENCV
#include <algorithm>
#include <fstream>  // NOLINT(readability/streams)
#include <string>
#include <utility>
#include <vector>

#include "boost/scoped_ptr.hpp"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include "utils/utils.hpp"
#include "data/dataset.hpp"
#include "utils/visualization.hpp"
#include "core/common.hpp"
#include "proposals/Proposal.hpp"
#include "proposals/ProposalGen.hpp"
#include "convert/dataio.hpp"

using namespace kurff;
using std::pair;
using boost::scoped_ptr;
DEFINE_bool(gray, false,
    "When this option is on, treat images as grayscale ones");
DEFINE_bool(shuffle, false,
    "Randomly shuffle the order of images and their labels");
DEFINE_string(backend, "lmdb",
        "The backend {lmdb, leveldb} for storing the result");
DEFINE_int32(resize_width, 64, "Width images are resized to");
DEFINE_int32(resize_height, 64, "Height images are resized to");
DEFINE_bool(check_size, false,
    "When this option is on, check that all the datum have the same size");

int main(int argc, char** argv) {
#ifdef USE_OPENCV
  ::google::InitGoogleLogging(argv[0]);
  // Print output to stderr (while still logging)
  FLAGS_alsologtostderr = 1;

#ifndef GFLAGS_GFLAGS_H_
  namespace gflags = google;
#endif

  gflags::SetUsageMessage("Convert a set of images to the leveldb/lmdb\n"
        "format used as input for Caffe.\n"
        "Usage:\n"
        "    convert_imageset [FLAGS] ROOTFOLDER/ LISTFILE DB_NAME\n"
        "The ImageNet dataset for the training demo is at\n"
        "    http://www.image-net.org/download-images\n");
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  if (argc < 4) {
    //gflags::ShowUsageWithFlagsRestrict(argv[0], "tools/convert_bin");
    //return 1;
  }

  const bool is_color = !FLAGS_gray;


    string img_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task12_Images";
    string anno_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task2_GT";
    std::shared_ptr<Dataset> dataset = DatasetRegistry()->Create("ICDAR2013Dataset", img_path, anno_path);
    dataset->load("icdar2013.txt");
    vector<string> proposal_name={"Canny","MSER"};
    std::shared_ptr<ProposalGen> proposal_method (new ProposalGen(proposal_name));
    proposal_method->create();
   // std::shared_ptr<Proposal> canny (ProposalRegistry()->Create("CannyProposal",100));

  //boost::is_directory();



  int resize_height = std::max<int>(0, FLAGS_resize_height);
  int resize_width = std::max<int>(0, FLAGS_resize_width);

  vector<Box> proposals;
  int count = 0;
  int data_size = 0;
  int label = 0;
  bool data_size_initialized = false;
  cv::Mat img;
  vector<vector<Box> > annotation;
 ofstream fo("diff.txt", ios::out);
  for (int i = 0; i < dataset->size(); ++ i) {
    bool status;
    dataset->get(i, img, annotation);
    vector<Box> proposals;
    proposal_method->run(img, proposals);
    LOG(INFO)<<"proposals size: "<< proposals.size();
    vector<Box> gt;
    vector<float> ov;
    overlap_gt(proposals, annotation, gt, ov);
    for(int j =0; j < proposals.size(); ++ j){
        //string label_name = annotation[j][k].label_name_[0];
        //int label = annotation[j][k].label_[0];
        //LOG(INFO)<<"count: "<<count;
        if( ov[j] <= 0.1 ) {
          label = map_int2string.size() - 1;
        }else{
          LOG(INFO)<<"gt[j].label_[0]: "<< gt[j].label_[0] <<" "<<gt[j].label_name_[0];
          label = gt[j].label_[0];
        }

       
        float dx = 0.0f, dy = 0.0f, dw = 0.0f, dh = 0.0f;
        diff(proposals[j],gt[j],dx, dy, dw ,dh);
        fo<< label<<" "<< dx <<" "<<dy<<" "<< dw<<" "<< dh << std::endl;
    }

  }
  fo.close();
#else
  LOG(FATAL) << "This tool requires OpenCV; compile with USE_OPENCV.";
#endif  // USE_OPENCV
  return 0;
}
