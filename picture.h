#ifndef PICTURE_H
#define PICTURE_H

#include <QWidget>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class Picture;
}

class Picture : public QWidget
{
    Q_OBJECT

public:
    explicit Picture(QWidget *parent = 0);
    ~Picture();

private:
    Ui::Picture *ui;


    QByteArrayList screen;
    int times;
    QStringList names;
    QStringList gl_id;
    QString main_id;
    QSqlDatabase db;
    QString pr;

public slots:
    void getData(QByteArrayList data, QStringList name, QStringList id, QString profile);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
};

#endif // PICTURE_H
