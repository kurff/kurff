
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

#include "caffe/proto/caffe.pb.h"
#include "caffe/util/db.hpp"
#include "caffe/util/format.hpp"
#include "caffe/util/io.hpp"
#include "caffe/util/rng.hpp"

#include "utils/utils.hpp"
#include "data/dataset.hpp"
#include "utils/visualization.hpp"
#include "core/common.hpp"
#include "proposals/Proposal.hpp"
#include "proposals/CannyProposal.hpp"
#include "convert/dataio.hpp"


using namespace caffe;  // NOLINT(build/namespaces)
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
DEFINE_bool(encoded, false,
    "When this option is on, the encoded image will be save in datum");
DEFINE_string(encode_type, "",
    "Optional: What type should we encode the image as ('png','jpg',...).");

DEFINE_string(lmdb_name, "icdar2013_sub_classifier", "save name of ");

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
    gflags::ShowUsageWithFlagsRestrict(argv[0], "tools/convert_bin");
    //return 1;
  }

  const bool is_color = !FLAGS_gray;
  const bool check_size = FLAGS_check_size;
  const bool encoded = FLAGS_encoded;
  const string encode_type = FLAGS_encode_type;

    string img_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task12_Images";
    string anno_path="/media/kurff/d45400e1-76eb-453c-a31e-9ae30fafb7fd/data/ICDAR2013/Challenge2_Training_Task2_GT";
    std::shared_ptr<Dataset> dataset = DatasetRegistry()->Create("ICDAR2013Dataset", img_path, anno_path);
    dataset->load("icdar2013.txt");

    std::shared_ptr<Proposal> canny (ProposalRegistry()->Create("CannyProposal",100));

  //boost::is_directory();

  if (encode_type.size() && !encoded)
    LOG(INFO) << "encode_type specified, assuming encoded=true.";

  int resize_height = std::max<int>(0, FLAGS_resize_height);
  int resize_width = std::max<int>(0, FLAGS_resize_width);

  // Create new DB
  boost::filesystem::path path(FLAGS_lmdb_name);
  if(boost::filesystem::is_directory(path)){
      boost::filesystem::remove_all(path);
  }

  vector<Box> proposals;

  scoped_ptr<db::DB> db(db::GetDB(FLAGS_backend));
  db->Open(FLAGS_lmdb_name, db::NEW);
  scoped_ptr<db::Transaction> txn(db->NewTransaction());

  // Storing to db
  Datum datum;
  int count = 0;
  int data_size = 0;
  int label = 0;
  bool data_size_initialized = false;
    cv::Mat img;
    vector<vector<Box> > annotation;
  for (int i = 0; i < dataset->size(); ++ i) {
    bool status;
    dataset->get(i, img, annotation);
    
    for(int j =0; j < annotation.size(); ++ j){
            string label_name = annotation[j][k].label_name_[0];
            int label = annotation[j][k].label_[0];
            //LOG(INFO)<<"count: "<<count;
            status = ReadMemoryToDatum(img, annotation[j][k], FLAGS_resize_height, FLAGS_resize_width, label, &datum);
            if (status == false) continue;
            //visualize(img, annotation, Scalar(0,0,255));
            //cv::imshow("src",img);
            //cv::waitKey(0);
            
            string key_str = std::to_string(count);
            string out;
            CHECK(datum.SerializeToString(&out));
            txn->Put(key_str, out);
            //LOG(INFO)<<"read Memory";
            if(++count % 1000 ==0){
                txn->Commit();
                txn.reset(db->NewTransaction());
                LOG(INFO) << "Processed " << count << " files.";
            }
    }

    canny->run(img, proposals);
    
    for(int j = 0; j < proposals.size(); ++ j ){
      label = map_string2int.size() -1;
      status = ReadMemoryToDatum(img, proposals[j], FLAGS_resize_height, FLAGS_resize_width, label, &datum);
      if (status == false) continue;
      
      string key_str = std::to_string(count);
      string out;
      CHECK(datum.SerializeToString(&out));
      txn->Put(key_str, out);
            //LOG(INFO)<<"read Memory";
      if(++count % 1000 ==0){
          txn->Commit();
          txn.reset(db->NewTransaction());
          LOG(INFO) << "Processed " << count << " files.";
      }
    }
  }
  // write the last batch
  if (count % 1000 != 0) {
    txn->Commit();
    LOG(INFO) << "Processed " << count << " files.";
  }
#else
  LOG(FATAL) << "This tool requires OpenCV; compile with USE_OPENCV.";
#endif  // USE_OPENCV
  return 0;
}
