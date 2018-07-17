rm ./build/icdar_classifier_hard -r
./3rdparty/caffe/distribute/bin/convert_imageset.bin --shuffle=true --resize_height=64 --resize_width=64 ./build/icdar2013_hard/ ./build/hard.txt ./build/icdar_classifier_hard/
cp ./build/icdar_classifier_hard ./build/icdar_classifier_hard_val -r
