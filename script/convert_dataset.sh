rm ./build/icdar_classifier -r
./3rdparty/caffe/distribute/bin/convert_imageset.bin --shuffle=true --resize_height=64 --resize_width=64 ./build/icdar2013/ ./build/label.txt ./build/icdar_classifier/
cp ./build/icdar_classifier ./build/icdar_classifier_val -r