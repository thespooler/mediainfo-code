#include "translate.h"
#include <QtCore/QStringList>

QString Tr(const char* string, const char * disambiguation, int n) {
    QStringList text = QString(string).split(" ");
    /* TODO
	for(int i=0;i<text.size();i++) {
        if(text[i]=="%n")
            text[i] = QString::number(n);
        else if((qrand()%3==0)&&(!text[i].contains(QRegExp("[\,|\.|\(|\)|\{|\}]")))) {
            text[i] = text[i].toUpper();
        }
    }
	*/
    return text.join(" ");
}
