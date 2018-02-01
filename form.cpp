#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    ui->lineEdit->setText("");
    ui->textEdit->setText("");


    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("I'm_Developer.db");

    if (db.open())
    {
        qDebug() << "OK from form";
    }
}

Form::~Form()
{
    delete ui;
}
// при открытии через кнопку
void Form::sign()
{
    open_sign = true;
    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->textEdit->setText("");
    ui->textEdit->setReadOnly(false);
    ui->lineEdit_2->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->lineEdit->setEnabled(true);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setVisible(true);

    ui->lineEdit_2->setVisible(true);
    ui->pushButton_5->setVisible(false);
    ui->textEdit->setVisible(true);
    ui->label_2->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(true);
    ui->label->setText("Введите команду и пояснение к ней");
    this->setMinimumHeight(368);
    this->setMinimumHeight(368);
    ui->pushButton->setGeometry(480,340,61,23);
    ui->label_3->setText("");
    command = false;

}
// при открытии через щелчок по итему
void Form::sign_2()
{
    open_sign = false;

    ui->lineEdit_2->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->pushButton_3->setEnabled(true);
    ui->textEdit->setReadOnly(true);
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(true);
    ui->lineEdit_2->setVisible(true);
    ui->textEdit->setVisible(true);
    ui->label_2->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_3->setVisible(true);

    ui->label->setText("Введите команду и пояснение к ней");
    this->setGeometry(500,100,545,368);
    ui->pushButton->setGeometry(480,340,61,23);
    this->setMinimumHeight(368);
    this->setMinimumHeight(368);
    ui->label_3->setText("");
    command = false;


}

void Form::set_id(QString id_default)
{
    id = id_default;
}



void Form::set_profile_name(QString name)
{
    profile_name = name;

}

void Form::set_id_for_insert(QString get_id)
{
    new_id = get_id;
}

void Form::sign_command()
{
    ui->lineEdit_2->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->label_2->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_3->setVisible(false);
    ui->pushButton_4->setVisible(false);
    ui->pushButton_5->setVisible(false);
    ui->lineEdit->setEnabled(true);
    ui->label->setText("Введите команду и пояснение к ней");
    this->setMaximumHeight(90);
    this->setMinimumHeight(90);
    ui->pushButton->setGeometry(495,53,50,30);
    ui->lineEdit->setText("dsfsdf");
    ui->label_3->setText("");
    ui->textEdit->setText("sdf");
    command = true;
}

void Form::on_pushButton_clicked()
{
    if (ui->lineEdit->text().isEmpty() || ui->textEdit->toPlainText().isEmpty())
    {
        ui->label_3->setText("Все поля должны быть заполнены");
    }
    else
    {
        if (!command)
        {
            if (open_sign)
            {
                QString  name = ui->lineEdit->text();
                QString  content = ui->textEdit->toPlainText();

                QSqlQuery query(db);
                QString str;
                // str =   "Insert into commands_" + profile_name +" (name, seq, pic) values (" + name + "," + content + " );";
                query.prepare("Insert into commands_" + profile_name +" (name, seq) values (:name, :seq)");

                query.bindValue(":name", name);
                query.bindValue(":seq", content);


                qDebug() << str;
                if (query.exec())
                {
                    qDebug() << "OK";
                    emit hello();


                }
                else
                {
                    qDebug() << "NOPE";
                    qDebug() << QSqlError(query.lastError());
                }
            }
            if (ui->pushButton_3->isEnabled())
            {
                QString  name = ui->lineEdit->text();
                QString  content = ui->textEdit->toPlainText();

                QSqlQuery query(db);
                QString str, str_2;
                str =  "DELETE FROM commands_" + profile_name +" WHERE id = " +  id +   ";";
                // str_2 =   "Insert into commands_" + profile_name +" (name, seq) values (" + name + "," + content" );";
                qDebug() << str;
                if (query.exec(str))
                    qDebug() << "Удалилось";
                else
                    qDebug() << "НЕ удалилось";
                query.prepare("Insert into commands_" + profile_name +" (name, seq) values (:name, :seq)");

                query.bindValue(":name", name);
                query.bindValue(":seq", content);



                if (query.exec())
                {
                    qDebug() << "OK Вставилось";
                    emit hello();


                }
                else
                {
                    qDebug() << "NOPE НЕ вставилось";
                    qDebug() << QSqlError(query.lastError());
                }
            }
        }

        // то что при записи команды
        else
        {
            QString  name = ui->lineEdit->text();



            QSqlQuery query(db);
            QString str;
            str =   "Insert into command_" + profile_name +" (name) values (" + "'"+name +"'"+ " );";
            qDebug() << str;
            if (query.exec(str))
            {
                qDebug() << "OK команда записана";
                emit hello();


            }
            else
            {
                qDebug() << "NOPE команда НЕ записана";
                qDebug() << QSqlError(query.lastError());
            }
        }
        this->hide();
    }
}

void Form::exist(QString str)
{

    QSqlQuery query(db);

    QString name,content;
    if (query.exec(str))
    {

        modelMain = new QSqlQueryModel(this);

        modelMain->setQuery(query);

        name =  modelMain->record(0).value("name").toString();
        content =  modelMain->record(0).value("seq").toString();

        qDebug() << "Works" << content;


    }
    else  {
        qDebug() << "no Works";
        qDebug() << QSqlError(query.lastError());
    }
    ui->lineEdit->setText(name);
    ui->textEdit->setText(content);
}

void Form::on_pushButton_2_clicked()
{
    QString data,text;
    QStringList data_2;

    data = ui->textEdit->toPlainText();

    data_2 = data.split("\n");
    int i = data_2.count();

    //    if (data_2[data_2.count()-1]=="")
    //    {

    //    qDebug() << "То от чего нужно избавиться" << data_2[data_2.count()-1];

    //}


    if (i==0) i++;



    qDebug() << i;
    qDebug() << data;
    qDebug() << "Это оно" << data_2;

    data = data + "\n" + QString::number(i) + ". " + ui->lineEdit_2->text();

    ui->textEdit->setText(data);
}

void Form::on_pushButton_3_clicked()
{
    ui->textEdit->setReadOnly(false);
    ui->lineEdit_2->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    //ui->lineEdit->setEnabled(true);
    ui->pushButton_5->setVisible(false);
    ui->pushButton_4->setVisible(true);
}


void Form::on_pushButton_4_clicked()
{
    if (!ui->lineEdit->text().isEmpty())
    {
        QClipboard *clipboard = QApplication::clipboard();

        const QMimeData* mime = clipboard->mimeData();
        if (mime->hasUrls() )
        {
            QRegExp reg(".*\\.(png|jpg|xpm)$");
            reg.setCaseSensitivity(Qt::CaseInsensitive);

            QList<QUrl> urls = mime->urls();
            for ( int i = 0; i < urls.size(); ++i ) {
                path = urls[ i ].toLocalFile();

                if ( !path.contains( reg ) )
                    continue;
                QPixmap pix(path);
                ui->label_3->setPixmap(pix);
            }
        }
        else
            if (mime->hasImage())
            {

                bool bOk;
                QString input_str = QInputDialog::getText( 0,
                                                     "Введите имя скриншота",
                                                     "Ввод:",
                                                     QLineEdit::Normal,
                                                     "",
                                                     &bOk
                                                    );
                if (bOk)
                {



                QPixmap pix(clipboard->pixmap());

                QBuffer inBuffer( &picture);
                inBuffer.open( QIODevice::WriteOnly );
                pix.save( &inBuffer, "PNG" );



                QSqlQuery query(db);

                query.prepare("Insert into pictures_" + profile_name +" (name, pic, pic_name) values (:name, :pic, :pic_name)");

                query.bindValue(":name", ui->lineEdit->text());
                query.bindValue(":pic", picture);
                query.bindValue(":pic_name", input_str);

                if (query.exec())
                {
                    qDebug() << "Картинка вставлена";
                    ui->label_3->setText(ui->label_3->text()+" Картинка вставлена");
                }
                else
                {
                    qDebug() << "Запись номер" << new_id << "Картинка НЕ вставлена" << query.lastError();

                }

            }
                }// досюда
    }
    else
    {
        ui->label_3->setText("Для начала введите наименование последовательности");
    }


}

void Form::on_pushButton_5_clicked()
{
    QSqlQuery query(db);

    if (query.exec("SELECT id, pic, pic_name FROM pictures_"+profile_name+"  where name = " + "'"+ui->lineEdit->text()+"'"+ + ";"))
    {
        qDebug() << "Есть картинка!!!";
    }
    else
    {
        qDebug() << "Нет картинки)))" << id;
    }
    model = new QSqlQueryModel(this);
    model->setQuery(query);

    picture_Form = new Picture();

    QByteArrayList images;
    QStringList names,ids;
    int i=0;

    while(i<=model->rowCount())
    {
        images << model->record(i).value("pic").toByteArray();
        names << model->record(i).value("pic_name").toString();
        ids << model->record(i).value("id").toString();
        i++;
    }
    picture_Form->getData(images,names,ids,profile_name);


    picture_Form->show();
}
