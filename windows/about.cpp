#include "about.h"
#include "SQL/sqlite.h"

About::About(QWidget *parent) : DMainWindow(parent)
{
    buildGUI();
    connect(update, &DPushButton::clicked,
            this, &About::get_update);
    connect(derive, &DPushButton::clicked,
            this, [=]{derive_new();});
}
 void About::buildGUI()
 {
     setWindowTitle(tr("关于"));
     setWindowFlags(Qt::WindowStaysOnTopHint);
     setFixedSize(400,270);
     help = new QTextBrowser(this);
     help->setGeometry(100,100,400,270);
     help->setText(help_text());

     derive = new DPushButton(this);
     derive->setText(tr("导出生词"));
     derive->move(220,10);
     derive->adjustSize();

     update = new DPushButton(this);
     update->move(310,10);
     update->setText(tr("检查更新"));
     update->adjustSize();
 }

 void About::get_update()
 {

 }

 void About::derive_new()
 {
     SQLite sqlite;
     sqlite.derive_new();
 }

 QString About::help_text()
 {
     QString content;
     content =
             "应用版本：2017-2.0\n\
特别鸣谢:有道词典、谷歌翻译\n\
使用了有道词典的翻译API，谷歌网页翻译\n\
1.支持翻译选中文本\n\
2.bug反馈：ziqiang_xu@yeah.net";
     return content;
 }
