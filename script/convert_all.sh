rm ./build/icdar_classifier_all -r
./3rdparty/caffe/distribute/bin/convert_imageset.bin --shuffle=true --resize_height=64 --resize_width=64 ./build/ ./build/all.txt ./build/icdar_classifier_all/
cp ./build/icdar_classifier_all ./build/icdar_classifier_val_all -r