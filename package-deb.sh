# 用于自动打包成deb
cp build/words-picker deb/words-picker/opt/words-picker/words-picker
cd deb
dpkg -b words-picker words-picker.deb
