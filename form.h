#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QClipboard>
#include <QPixmap>
#include <QMimeData>
#include <QBuffer>
#include <QScreen>
#include <QInputDialog>

#include "picture.h"
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

void sign();
void sign_2();
void set_id(QString);
void set_profile_name(QString);
void set_id_for_insert(QString);

void sign_command();


signals:
    void hello();


private slots:
    void on_pushButton_clicked();

    void exist(QString);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Form *ui;
    QSqlDatabase db;
    QSqlQueryModel *modelMain;
    QSqlQueryModel *model;

    bool open_sign;
    QString id;
    QString path;
    QString profile_name;
    QString new_id;
    bool command=false;

    QByteArray picture;
    Picture *picture_Form;

};

#endif // FORM_H
