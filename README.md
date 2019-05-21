# words picker

[下载体验](https://github.com/ziqiangxu/words-picker/releases)

## 产品理念

这不是一款好的词典应用，但希望它能成为一款好的取词应用。
让取词更简单，减少阅读障碍。

## 使用体验

主窗口

![主窗口](./docs/img/mainwindow.png)

`OCR取词`

![OCR取词](./docs/img/ocr.gif)

鼠标选词

![鼠标选词](./img/selection.gif)

## 参与开发

欢迎各位贡献代码，开发库安装：

- `libxtst-dev`是 `x11` 的开发库

### 为 `Debian` 系的发行版安装开发库

`sudo apt install qt5-default libxtst-dev g++ cmake make tesseract`

### 为 `RedHat` 系的发行版安装开发库

`sudo dnf install qt5-devel libXtst-devel g++ cmake make tesseract`

## 编译安装

目前本应用只提供 `Debian` 系的二进制安装包，其它系列的发行版可进行编译安装，首先安装开发库，再执行下面的命令。

``` shell
mkdir build && cd build
cmake ../words-picker && make
sudo make install
```

## 致谢

- [有道智云](https://ai.youdao.com)： 本项目使用了有道的翻译 `API`
- [Google翻译](https://translate.google.cn)： 本项目调用了 `Google` 的网页翻译
- [Deepin](https://deepin.org)：本应用大部分开发在 `Deepin` 操作系统下完成
- [Qt开源社区](http://www.qter.org)： 第一个 `Qt` 程序是在 `Qt` 开源社区教程的指导下写出来的
- 开源运动：让我可以很容易地阅读他人的代码，学习到了这样有趣的技术
- [wtz](https://github.com/zwpwjwtz)：感谢他贡献了第一版图标
- [dee-y](https://github.com/dee-y):Thanks for her or his pretty logo!
- [manateelazycat](https://github.com/manateelazycat)，本项目使用了王勇的开源代码XRecord，参考[Linux全局事件监听技术](https://www.jianshu.com/p/80cf81413d31)
- [Rekols](https://github.com/Rekols)：开发之前阅读了 `Rekols` 的开源代码，并在开发过程中向他进行了请教
  
## 一些题外话

`freedict` (原名 `opendict`，后来在打包的时候发现软件仓库有同名，遂改之),不过最近发现 `freedict` 也已经被使用了，真是好名字争着取啊！最后定为 `words-picker`
