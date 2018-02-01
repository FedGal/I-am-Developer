#include "picture.h"
#include "ui_picture.h"

Picture::Picture(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Picture)
{
    ui->setupUi(this);

    times=0;
}

Picture::~Picture()
{
    delete ui;
}

void Picture::getData(QByteArrayList data, QStringList name, QStringList id, QString profile)
{

    screen = data;
    names = name;
    gl_id = id;
    main_id = gl_id[0];
    pr = profile;

    qDebug() << "Вот все данные: "<<main_id << "  "<< pr;

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(screen[0]);
    ui->label->setPixmap(outPixmap);
    ui->label_2->setText(names[0]);
 qDebug() << screen.count();

times++;
}


void Picture::on_pushButton_clicked()
{

    if (times<=screen.count()-2)
    {

        QPixmap outPixmap = QPixmap();
        outPixmap.loadFromData(screen[times]);
        ui->label->setPixmap(outPixmap);
         ui->label_2->setText(names[times]);
         main_id = gl_id[times];
         times++;
    }
    else
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(true);
        times--;
    }

}

void Picture::on_pushButton_2_clicked()
{
    if (times>0)
    {
        times--;

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData(screen[times]);
    ui->label->setPixmap(outPixmap);
     ui->label_2->setText(names[times]);
     main_id = gl_id[times];
    ui->pushButton->setEnabled(true);

}
    else
    {
        ui->pushButton_2->setEnabled(false);
    }
}

void Picture::on_pushButton_3_clicked()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("I'm_Developer.db");
    if (db.open())
    {

        QSqlQuery query(db);
        query.prepare("Delete from pictures_"+pr+ " where id = "+ main_id +";");
                if (query.exec())
        {
            qDebug() << "Удалено";
            ui->label_2->setText("Скриншот удален. Для обновления закройте и откройте данное окно.");
        }
                else
                {
                    qDebug() << "НЕ Удалено " << query.lastError();


                }


    }
}
