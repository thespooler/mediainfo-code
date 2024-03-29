#ifndef EXPORT_H
#define EXPORT_H

#include <QtGui/QDialog>
#include <QtCore/QIODevice>
#include <QtCore/QDebug>

namespace Ui {
    class Export;
}

class Export : public QDialog {
    Q_OBJECT
public:
    enum ExportMode {
        TEXT=0,
        HTML=1,
        XML,
        PBCORE,
        MPEG7,
        CSV,

        NB_EXPORT_MODE
    };

    Export(QString filename, int mode, QWidget *parent = 0);
    ~Export();
    int getExportMode();
    int getExportConfig();
    QString getFileName();
    QIODevice::OpenMode getOpenMode();
    bool isAdvancedChecked();
    QString extension(int mode);
    QString name(int mode);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::Export *ui;

private slots:
    void on_checkBoxAdvanced_toggled(bool checked);
    void on_comboBoxMode_currentIndexChanged(int index);
    void on_toolButton_pressed();
};

#endif // EXPORT_H
