// GUI of MediaInfo
// Copyright (C) 2011-2012 MediaArea.net SARL, Info@MediaArea.net
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "configtreetext.h"
#include "Common/Core.h"
#include <QtCore/QDebug>

int ConfigTreeText::indexDefault = 0;
QVector<ConfigTreeText*> ConfigTreeText::configs = QVector<ConfigTreeText*>();
QStringList ConfigTreeText::names = QStringList();

ConfigTreeText::ConfigTreeText(QString name)
{
    this->name = name;
    for(int i=0;i<Stream_Max;i++)
        this->fields.append(QStringList());
    fields[0].append("CompleteName");
}

/* STATIC FUNCTIONS */

void ConfigTreeText::load(QSettings* settings) {
    qDebug() << "loading configs";
    int size = settings->beginReadArray("configs");
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        ConfigTreeText* ctt = new ConfigTreeText(settings->value("name").toString());
        qDebug() << "...loading " << ctt->getName();
        for(int j=0;j<4;j++)
            ctt->setFields(j,settings->value("fields"+QString::number(j),QStringList()).toStringList());
        configs.append(ctt);
        names.append(ctt->getName());
    }
    settings->endArray();
    indexDefault = settings->value("ConfigTreeTextIndexDefault",0).toInt();
    qDebug() << "end loading";
}

void ConfigTreeText::save(QSettings* settings) {
    qDebug() << "saving configs";
    settings->beginWriteArray("configs");
    for (int i = 0; i < configs.size(); ++i) {
        settings->setArrayIndex(i);
        qDebug() << "...saving " << configs[i]->getName();
        settings->setValue("name", configs[i]->getName());
        for(int j=0;j<4;j++)
            settings->setValue("fields"+QString::number(j),configs[i]->getFields(j));
    }
    settings->endArray();
    settings->setValue("ConfigTreeTextIndexDefault",indexDefault);
    qDebug() << "end saving";
}

void ConfigTreeText::remove(int i) {
    configs.remove(i);
    names.removeAt(i);
    if(getIndex()>=configs.size())
        setDefault(configs.size()-1);
}

void ConfigTreeText::removeLast() {
    remove(configs.size()-1);
}

ConfigTreeText* ConfigTreeText::get(int i) {
    return configs[i];
}

ConfigTreeText* ConfigTreeText::getConfigTreeText() {
    return get(indexDefault);
}

int ConfigTreeText::getNbConfigTreeTexts() {
    return configs.size();
}

void ConfigTreeText::setDefault(int i) {
    indexDefault = i;
}

int ConfigTreeText::getIndex() {
    return indexDefault;
}

ConfigTreeText* ConfigTreeText::add(QString name) {
    if(names.contains(name)) {
        int n;
        for(n=2;names.contains(name+QString::number(n));n++);
        name.append(QString::number(n));
    }
    ConfigTreeText* s = new ConfigTreeText(name);
    configs.append(s);
    names.append(name);
    setDefault(configs.size()-1);
    return s;
}

void ConfigTreeText::fillComboBox(QComboBox* qcb) {
    qcb->clear();
    for(int i=0;i<ConfigTreeText::getNbConfigTreeTexts();i++) {
        qcb->addItem(ConfigTreeText::get(i)->getName(),i);
    }
    qcb->setCurrentIndex(ConfigTreeText::getIndex());
}

/* METHODS */

QList<QStringList> ConfigTreeText::getFields() {
    return fields;
}

QStringList ConfigTreeText::getFields(int i) {
    return fields[i];
}

void ConfigTreeText::setFields(int i, QStringList fs) {
    fields[i] = fs;
}

QString ConfigTreeText::getName() {
    return name;
}

void ConfigTreeText::setName(QString n) {
    name = n;
}

void ConfigTreeText::addField(int i, QString f) {
    if(!fields[i].contains(f))
        fields[i].append(f);
}

void ConfigTreeText::removeField(int i, QString f) {
#if QT_VERSION >= 0x404000
    fields[i].removeOne(f);
#else
    if(fields[i].indexOf(f))
        fields[i].removeAt(fields[i].indexOf(f));
#endif
}
