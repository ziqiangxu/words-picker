#include "result.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include "../defined.h"

Result::Result(QByteArray res)
{
    QString res_str = QString(res);
    INFO << "reply of server:" << res_str;
    QJsonDocument json_doc = QJsonDocument::fromJson(res);
    QJsonObject json_obj = json_doc.object();

    this->explain = json_obj.take("explain").toString();
    this->translation = json_obj.take("translation").toString();
    this->uk_phonetic = json_obj.take("uk-phonetic").toString();
    this->us_phonetic = json_obj.take("us-phonetic").toString();
    this->error_code = json_obj.take("errorCode").toInt();
    this->error_msg = json_obj.take("errorMsg").toString();

//    QStringList L1 = json_obj.keys();
//    INFO << "the reply keys:" << L1;

//    //Get the translation
//    QJsonArray translation_array = json_obj.take("translation").toArray();
//    int counter = translation_array.count();
//    for (int i = 0; i < counter; i++)
//    {
//        translation.append(translation_array.at(i).toString() + "\n");
//    }

//    //Get the basic：contain almost information we need
//    QJsonObject basic_obj = json_obj.take("basic").toObject();

//    us_phonetic = basic_obj.take("us-phonetic").toString();
//    uk_phonetic = basic_obj.take("uk-phonetic").toString();

//        //Get the explains in basic_obj
//    QJsonArray explains_array = basic_obj.take("explains").toArray();
//    counter = explains_array.count();
//    for (int i = 0; i < counter; i++){
//        explain.append(explains_array.at(i).toString() + "\n");
//    }
//    INFO << "explains" << ":" << explain;

//    //Get the way of translation：from English to Chinese-simple as the default way
//    QString language = json_obj.take("l").toString();
//    INFO << "way of translation:" << language;

//    // Get the erroCode：0 means everything on it's way.You can get more from
//    // http://ai.youdao.com/docs/api.s
//    error_code = json_obj.take("erroCode").toInt();
}

Result::~Result() {

}
