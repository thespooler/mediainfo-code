#ifndef ABOUT_H
#define ABOUT_H

#include <QtGui/QDialog>

namespace Ui {
    class About;
}

class About : public QDialog {
    Q_OBJECT
public:
    About(QWidget *parent = 0);
    ~About();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::About *ui;

private slots:
    void on_checkversion_clicked();
    void on_donate_clicked();
    void on_mail_clicked();
    void on_website_clicked();
    void on_okButton_clicked();
};

#endif // ABOUT_H
