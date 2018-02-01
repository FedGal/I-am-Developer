#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtGui>
#include <QFileDialog>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QInputDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QSettings>
#include <QListView>


#include "form.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void exist(QString);

public slots:
    void create_profile();

    void delete_profile();
private slots:



    void on_pushButton_clicked();


    void on_pushButton_2_clicked();

    void update();

    void hide_row();

    void data_about_profiles();

    void on_tableView_2_doubleClicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged();

    void switch_Off_Action_Requestion();
    void switch_On_Action_Requestion();

    int check();

private:
    Ui::MainWindow *ui;

    QString data_base_name;
    QSqlQueryModel *modelMain;
    QSqlQueryModel *modelMain_1;
    QSqlQueryModel *modelMain_2;
    QSqlQueryModel *modelMain_for_check;
    QSqlQueryModel *modelDevice;
    QSqlDatabase db;
    QMessageBox *msg_box;
    Form *item;
    QListView *list_view;
    bool requestion;




};

#endif // MAINWINDOW_H
