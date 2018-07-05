freedict(原名opendict，后来在打包的时候发现软件仓库有同名，遂改之)当前最新版本2018-5.1

### 开发背景    
学习Qt和Deepin系统下软件的开发，与此同时学习其他的计算机技术，需要阅读英文资料。Google浏览器的翻译插件和深度用户社区的Rekols-dict都很好用，但是我觉得还不够，需要一个记录查询历史的功能，以便日后复习，这样对英语水平的提高是有帮助的。本应用超轻量的，由于目前基本都是我自己和同学在使用这个软件，Linux版本的有道词典也在重构中，所以我并没有对本应用做进一步进行优化。如果有同学需要我修改一些东西，我很乐意帮助的，直接在issue中提出或者给我发邮件就好了。感谢wtz设计的图标！    
### 技术分享
我的应用界面设计得很丑，所以在Ubuntu下更丑了，所以还是还是尽量在deepin下用本应用吧。    
翻译使用了有道的API：目前是我个人的开发账号，免费的查询条数暂时还够用。
OCR识别使用的是Tesseract，计划后面进行深入研究后，对模型进行训练以提高识别精度。

### 发行注记
二进制安装包在本仓库deb目录下   
#### - 2018-5.1    
2018.07.05
适用于deepin [下载](https://github.com/ziqiangxu/freedict/raw/master/deb/freedict_v2018-5.1_amd64_deepin.deb)    
适用于ubuntu（仅在18.04和16.04.4版本测试）[下载](https://github.com/ziqiangxu/freedict/raw/master/deb/freedict_v2018-5.1_amd64_ubuntu.deb)    
1. 对较小文字的识别略有改善；
2. 新增对Ubuntu的支持；
3. 更换了图标；
4. 跟进了Google网页翻译的URL变化。

#### - 2018-5.0[下载](https://github.com/ziqiangxu/freedict/raw/master/deb/freedict_v2018-5.0_amd64.deb)
1. 新增收起到托盘；
2. 新增OCR翻译功能，配合截图软件使用，截取无法被鼠标选择的文字的图片，进行文字识别，再进行翻译。以deepin系统为例：Ctrl+Alt+A开始截图，选择好需要识别的区域，Ctrl+C复制图像到剪切板。目前对较小的文字识别很糟糕，后期将进行优化，敬请期待。

#### - 2018-4.0[下载](https://github.com/ziqiangxu/freedict/raw/master/deb/freedict_v2018-4.0_amd64.deb)
发现身边有些朋友的电脑不能使用deepin操作系统，自己的代码又写得很垃圾，别人懒得改。而且DTK是基于Qt5.6深度定制的，最近和同学开发一个工控程序，使用了5.10，编译不能通过。为了让这个软件被更多的人使用，无奈又回到了Qt原生控件。这个版本没有增加新的功能!修复了Google网页翻译的错误

#### - 2017-3.0[下载](https://github.com/ziqiangxu/freedict/raw/master/deb/freedict_v2017-3.0_amd64.deb)    
1. 新增单词本管理功能；    
2. 应用只能创建一个实例；    
3. 其他的一些小调整。 

#### - 2017-2.0[下载](https://github.com/ziqiangxu/freedict/raw/master/deb/freedict_v2017-2.0_amd64.deb)     
专为Deepin平台开发，欢迎各位大佬移植，只需要把相关控件修改为Qt原生控件就可以

#### - 2017-1.0[下载](https://github.com/ziqiangxu/freedict/raw/master/deb/freedict_v2017-1.0_amd64.deb)     
Linux平台通用        

### 软件截图
主窗口    
![主窗口](./README/mainwindow.png)    
管理生词
![管理生词](./README/manage_words.gif)    
屏幕选词
![屏幕选词](./README/using.gif)

### 致谢    
有道词典，本项目使用了有道的翻译api    
Google,本项目调用了Google的网页翻译    
qt开源社区，第一个Qt程序是在Qt开源社区教程的指导下写出来的    
深度科技王勇，本项目使用了王勇的开源代码XRecord，    
深度社区Rekols，开发之前阅读了Rekols的开源代码，并在开发过程中向他进行了请教    
感谢开源运动，让我可以很容易地阅读他人的代码，学习到了这样有趣的技术！    
