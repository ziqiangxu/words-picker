# words picker

[下载体验](https://github.com/ziqiangxu/words-picker/releases)

## 产品理念

这不是一款好的词典应用，但希望它能成为一款好的取词应用。
让取词更简单，减少阅读障碍。

## 使用体验

主窗口

![主窗口](./README/mainwindow.png)

OCR取词

![OCR取词](./README/ocr.gif)

鼠标选词

![鼠标选词](./README/selection.gif)

## 编译安装

目前本应用只提供debian系的二进制安装包，本应用理论上在其它系的Linux发行版都是可以运行的。不过要各位编译安装了。
```
mkdir build && cd build
cmake .. && make
sudo make install
```

## 参与开发

欢迎各位贡献代码， happy hacking！
开发库安装：
`sudo apt install g++ qt5-default libxtst-dev`
- `libxtst-dev`是x11的开发库

## 致谢

- [有道智云](https://ai.youdao.com)： 本项目使用了有道的翻译api
- [Google翻译](https://translate.google.cn)： 本项目调用了Google的网页翻译
- [Deepin](https://deepin.org)：本应用大部分开发在Deepin操作系统下完成
- [qt开源社区](http://www.qter.org)： 第一个Qt程序是在Qt开源社区教程的指导下写出来的

- 开源运动：让我可以很容易地阅读他人的代码，学习到了这样有趣的技术

- [wtz](https://github.com/zwpwjwtz)：感谢他贡献了第一版图标
- [dee-y](https://github.com/dee-y):Thanks for her or his pretty logo!
- 自由软件开发者[王勇](https://github.com/manateelazycat)，本项目使用了王勇的开源代码XRecord，参考[Linux全局事件监听技术](https://www.jianshu.com/p/80cf81413d31)
- 深度科技[Rekols](https://github.com/Rekols)：开发之前阅读了Rekols的开源代码，并在开发过程中向他进行了请教
  
## 一些题外话

freedict(原名opendict，后来在打包的时候发现软件仓库有同名，遂改之),不过最近发现freedict也已经被使用了，真是好名字争着取啊！最后定为words picker
