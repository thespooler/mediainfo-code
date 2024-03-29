#ifndef EDITCUSTOM_H
#define EDITCUSTOM_H

#include <QtGui/QDialog>
#include "Common/Core.h"
#include "custom.h"

namespace Ui {
    class EditCustom;
}

class EditCustom : public QDialog {
    Q_OBJECT
public:
    EditCustom(Custom* c, Core* C, QWidget *parent = 0);
    ~EditCustom();
    void apply();
    void refreshDisplay();
    void saveText();

protected:
    void changeEvent(QEvent *e);
    //void fillToolBox();

private:
    Ui::EditCustom *ui;
    Core* C;
    Custom* c;

private slots:
    void on_pushButton_clicked();
    void on_textEdit_textChanged();
    void on_treeWidget_itemSelectionChanged();
};

#endif // EDITCUSTOM_H
