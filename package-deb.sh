# 用于自动打包成deb
cd build
cmake ..
make -j4
cp src/words-picker ../deb/words-picker/opt/words-picker/words-picker
cd ../deb
dpkg -b words-picker words-picker.deb
