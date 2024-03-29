#ifndef SHEETVIEW_H
#define SHEETVIEW_H

#include <QtGui/QFrame>
#include "Common/Core.h"
#include <QtCore/QDebug>

namespace Ui {
    class SheetView;
}

class SheetView : public QFrame {
    Q_OBJECT
public:
    SheetView(Core* C, QWidget *parent = 0);
    ~SheetView();

protected:
    void changeEvent(QEvent *e);

public slots:
    void adaptColumnsToContent();
    void resetColumnsSizes();

private:
    Core* C;
    void refreshDisplay();
    Ui::SheetView *ui;
    QString url;

private slots:
    void on_toolButton_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_tableWidget_itemSelectionChanged();
};

#endif // SHEETVIEW_H
