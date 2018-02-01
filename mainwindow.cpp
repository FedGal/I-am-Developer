#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);


    QSettings settings("settings.ini", QSettings::IniFormat, this);
    settings.beginGroup("Request");
    requestion = settings.value("Request",false).toBool();
    settings.endGroup();



    list_view = new QListView(ui->comboBox);
    ui->comboBox->setView(list_view);

    item = new Form();

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("I'm_Developer.db");


    connect(this,SIGNAL(exist(QString)),item,SLOT(exist(QString)));
    connect(item, SIGNAL(hello()),this, SLOT(update()));
    connect(ui->action,SIGNAL(triggered()),this,SLOT(create_profile()));
    connect(ui->action_2,SIGNAL(triggered()),this,SLOT(delete_profile()));
    connect(ui->action_3,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->action_4,SIGNAL(triggered()),this,SLOT(switch_Off_Action_Requestion()));
    connect(ui->action_5,SIGNAL(triggered()),this,SLOT(switch_On_Action_Requestion()));

    if (db.open())
    {
        qDebug() << "Yes";

        //Делаем запрос
        QSqlQuery query(db);



        //Здесь нужно будет сделать запись в реестр на проверку в первый раз прога запускается или нет
        //QString qr =  "CREATE TABLE profiles (name text NOT NULL UNIQUE);";
        //query.exec(qr);
        query.exec("SELECT name from profiles;");
        modelMain_2 = new QSqlQueryModel(this);
        modelMain_2->setQuery(query);
        int i=0;
        qDebug() << modelMain_2->record(i).value("name").toString();
        while(modelMain_2->record(i).value("name").toString()!="")
        {
            ui->comboBox->addItem(modelMain_2->record(i).value("name").toString());

            i++;
        }


        qDebug() << QSqlError(query.lastError());
qDebug() << "i="<< i ;


        if (ui->comboBox->currentText()!="")
        {
            qDebug() << "Сюда я попадаю когда все есть" ;
            modelMain = new QSqlQueryModel(this);
            query.exec("select * from commands_"+ui->comboBox->currentText()+";");
            modelMain->setQuery(query);
            // send_id = modelMain->record(modelMain->rowCount()).value("id").toString();

            ui->tableView_2->setModel(modelMain);
            //  ui->tableView_2->setColumnHidden(0, true);


            modelMain_1 = new QSqlQueryModel(this);
            query.exec("select * from command_"+ui->comboBox->currentText()+";");
            modelMain_1->setQuery(query);
            ui->tableView->setModel(modelMain_1);
            //  ui->tableView_2->setColumnHidden(0, true);

            // ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);

            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(true);
            ui->pushButton_4->setEnabled(true);

            modelMain->setHeaderData(0,Qt::Horizontal,"Наименование");
            modelMain->setHeaderData(1,Qt::Horizontal,"Этапы");

            modelMain_1->setHeaderData(0,Qt::Horizontal,"Команда");

        }
        else
        {
            qDebug() << "Для начала работы необходимо создать профиль";
            ui->label_2->setText("Для начала работы необходимо создать новый профиль в меню 'Профиль' -> 'Создать новый профиль'");


            ui->pushButton->setEnabled(false);
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_4->setEnabled(false);


        }


    }
    ui->tabWidget->setTabText(0,"Последовательности команд");
    ui->tabWidget->setTabText(1,"Команды");
}


MainWindow::~MainWindow()
{
    QSettings settings("settings.ini", QSettings::IniFormat, this);
    settings.beginGroup("Request");
    settings.setValue("Request",requestion);
    settings.endGroup();

    delete ui;
    db.close();
}

void MainWindow::update()
{QSqlQuery query(db);
//    query.exec("select max(id) from commands_"+ui->comboBox->currentText()+" ;");
//     modelMain->setQuery(query);
//     int a = modelMain->record(0).value("id").toInt();
//     qDebug() << "Это выведенное" << a;

    modelMain_1 = new QSqlQueryModel(this);
    modelMain = new QSqlQueryModel(this);

    query.exec("select * from commands_"+ui->comboBox->currentText()+" ;");
    modelMain->setQuery(query);
    ui->tableView_2->setModel(modelMain);

    query.exec("select max(id) from commands_"+ui->comboBox->currentText()+" ;");
    //send_id = modelMain->record()




    qDebug() << "ZB";

    query.exec("select * from command_"+ui->comboBox->currentText()+" ;");
    modelMain_1->setQuery(query);
    ui->tableView->setModel(modelMain_1);
    qDebug() << "ZB command";
    modelMain->setHeaderData(1,Qt::Horizontal,"Наименование");
    //modelMain->setHeaderData(1,Qt::Horizontal,"Этапы");

    modelMain_1->setHeaderData(0,Qt::Horizontal,"Команда");

}

void MainWindow::hide_row()
{
    qobject_cast<QListView *>(ui->comboBox->view())->setRowHidden(ui->comboBox->currentIndex(), true);
    QSqlQuery query(db);
    query.exec("SELECT name from profiles;");
    modelMain_for_check = new QSqlQueryModel(this);
    modelMain_for_check->setQuery(query);
    QStringList cnt;
    int i = 0;
    while(modelMain_for_check->record(i).value("name").toString()!="")
    {
        cnt += modelMain_for_check->record(i).value("name").toString();

        i++;

    }
    qDebug() << cnt;
    if (cnt.count()==0)
    {
        ui->comboBox->setVisible(false);

    }


}

void MainWindow::data_about_profiles()
{
    QSqlQuery query(db);
    modelMain = new QSqlQueryModel(this);
    query.exec("SELECT name from profiles;");
    modelMain->setQuery(query);
    int i=0;
    qDebug() << modelMain->record(i).value("name").toString();
    while(modelMain->record(i).value("name").toString()!="")
    {
        if (ui->comboBox->itemText(i)!=modelMain->record(i).value("name").toString())
            ui->comboBox->addItem(modelMain->record(i).value("name").toString());


        i++;
    }
}

void MainWindow::create_profile()
{
    list_view = new QListView(ui->comboBox);
    ui->comboBox->setView(list_view);
    bool ok=true;
    QString table,qr;
    table = QInputDialog::getText(this,
                                  QString::fromUtf8("Наименование профиля"),
                                  QString::fromUtf8("Введите наименование профиля"),
                                  QLineEdit::Normal,
                                  QDir::home().dirName(), &ok);
    if (!table.isEmpty() && !table.isNull())
    {
        table = "'" + table + "'";
        QSqlQuery query(db);

        QSettings settings("settings.ini", QSettings::IniFormat, this);
        settings.beginGroup("MainWindow");
        bool setting = settings.value("exist",false).toBool();
        settings.endGroup();

        if (!setting)
        {
            qr =  "CREATE TABLE profiles (id INTEGER PRIMARY KEY AUTOINCREMENT, name text NOT NULL UNIQUE);";
            query.exec(qr);
            settings.beginGroup("MainWindow");
            settings.setValue("exist",true);
            settings.endGroup();
            qDebug() << "Создана таблица профилей, её не было";
        }
        else
        {
            qDebug() << "Не создана таблица профилей, она было";
        }
        qr = "Insert into profiles (name) values (" + table + ");";

        qDebug() << qr;



        /* *******************************
     создание таблицы
     **************************** */

        if(!query.exec(qr))
        {
            qDebug() << "OK (Новая запись НЕ создана)";

            msg_box = new QMessageBox();
            msg_box->setText("Профиль не удалось создать (должно быть профиль с таким именем уже существует)");
            msg_box->setWindowTitle("Ошибка");
            msg_box->show();

        }

        else
        {
            qDebug() << "OK (Новая запись создана)";
            msg_box = new QMessageBox();
            msg_box->setText("Профиль успешно создан!");
            msg_box->setWindowTitle("Успех");
            msg_box->show();

            data_about_profiles();
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(true);
            ui->pushButton_4->setEnabled(true);

            QString prf = table;
            QStringList p = prf.split("'");
            qr =  "CREATE TABLE commands_" +p[1]  + " (id INTEGER PRIMARY KEY AUTOINCREMENT, name text NOT NULL, seq text NOT NULL);";
            qDebug() << qr ;
            if (query.exec(qr))
            {
                qDebug() << "Таблица к профилю добавлена";
                ui->comboBox->setVisible(true);

                qr =  "CREATE TABLE pictures_" +p[1]  + " (id INTEGER PRIMARY KEY AUTOINCREMENT, name text NOT NULL, pic BLOB, pic_name text DEFAULT 'name' NOT NULL);";
                if (query.exec(qr))
                {
                    qDebug() << "Таблица картинок создана";
                }
                else
                {
                    qDebug() << "Таблица картинок НЕ создана";
                }

            }
            else
            {
                qDebug() << "Таблица к профилю НЕ добавлена";
            }
            qr =  "CREATE TABLE command_" +p[1]  + " (id INTEGER PRIMARY KEY AUTOINCREMENT, name text NOT NULL);";
            qDebug() << qr ;
            if (query.exec(qr))
            {
                qDebug() << "Таблица к профилю добавлена  command";
                ui->label_2->setText("");
            }
            else
            {
                qDebug() << "Таблица к профилю НЕ добавлена command";
            }
        }
    }
    else
    {
        msg_box = new QMessageBox();
        msg_box->setWindowTitle("Ошибка!");
        msg_box->setText("Значение не должно быть пустым");
        msg_box->show();
    }

    modelMain_2 = new QSqlQueryModel(this);
    modelMain_1 = new QSqlQueryModel(this);
    modelMain->setHeaderData(0,Qt::Horizontal,"Наименование");
    modelMain->setHeaderData(1,Qt::Horizontal,"Этапы");
    modelMain_1->setHeaderData(0,Qt::Horizontal,"Команда");
}

void MainWindow::delete_profile()
{

    QMessageBox* pmbx =
            new QMessageBox("Вы уререны???",
                            "<b>Вы дествитель хотите удалить данный профиль?</b> ",
                            QMessageBox::Warning,
                            QMessageBox::Yes,
                            QMessageBox::No,
                            QMessageBox::Cancel | QMessageBox::Escape);
    int n = pmbx->exec();
    delete pmbx;
    if (n == QMessageBox::Yes)
    {


        QString str = "'" +  ui->comboBox->currentText()+"'" ;
        QSqlQuery query(db);
        QString   qr =  "Delete from profiles where name=" +  str +";";
        if (query.exec(qr))
        {
            qDebug() << qr << "OK";
            qr = "DROP TABLE commands_" + ui->comboBox->currentText() + ";";
            query.exec(qr);
            qr = "DROP TABLE command_" + ui->comboBox->currentText() + ";";
            query.exec(qr);
            qr = "DROP TABLE pictures_" + ui->comboBox->currentText() + ";";
            query.exec(qr);


            hide_row();

        }
        else
        {
            qDebug() << "NOT";
        }
    }
    //   data_about_profiles();
}




void MainWindow::on_pushButton_clicked()
{
    QSqlQuery query(db);
    item->sign();

    modelMain = new QSqlQueryModel(this);
    query.exec("select * from commands_"+ui->comboBox->currentText()+";");
    modelMain->setQuery(query);
   // send_id = modelMain->record(modelMain->rowCount()).value("id").toString();

    item->set_profile_name(ui->comboBox->currentText());
    item->show();



}





void MainWindow::on_pushButton_2_clicked()
{


    if ( check() == QMessageBox::Yes)
    {

        int current_item = ui->tableView_2->currentIndex().row();
        QSqlQuery query(db);

        QString id =  "'"+modelMain->record(current_item).value("id").toString()+"'";

        QString name =  "'"+modelMain->record(current_item).value("name").toString()+"'";

        QString str = "DELETE FROM commands_"+ ui->comboBox->currentText() + " WHERE id = " +  id +   ";";

        query.exec(str);
        qDebug() << id << str << current_item;

        str = "DELETE FROM pictures_"+ ui->comboBox->currentText() + " WHERE name = " +  name +   ";";
        if (query.exec(str))
        {
            qDebug() << "Картинки удалены" << str ;

        }
        else
        {
            qDebug() << "Картинки НЕ удалены" ;
        }

        query.exec("select * from commands_" + ui->comboBox->currentText() +";");
        modelMain->setQuery(query);

    }
}

void MainWindow::on_tableView_2_doubleClicked(const QModelIndex &index)
{
    QString id =  modelMain->record(index.row()).value("id").toString();
    QSqlQuery query(db);
    QString str = "select  name, seq from commands_"+ui->comboBox->currentText()+ " where id = "+ id +" ;";

    qDebug() << id;
    qDebug() << str;

    emit exist(str);
    item->sign_2();
    item->set_id(id);
    item->set_profile_name(ui->comboBox->currentText());
    item->show();


}



void MainWindow::on_pushButton_3_clicked()
{
    item->sign_command();
    item->set_profile_name(ui->comboBox->currentText());
    item->show();
}

void MainWindow::on_pushButton_4_clicked()
{

    if (check() == QMessageBox::Yes)
    {

        int current_item = ui->tableView->currentIndex().row();
        QSqlQuery query(db);

        QString id =  modelMain_1->record(current_item).value("id").toString();
        QString str = "DELETE FROM command_"+ ui->comboBox->currentText() + " WHERE id = " +  id +   ";";

        query.exec(str);
        qDebug() << id << str << current_item;

        query.exec("select * from command_" + ui->comboBox->currentText() +";");
        modelMain_1->setQuery(query);
    }
}


void MainWindow::on_comboBox_currentIndexChanged()
{
    QSqlQuery query(db);
    QString prf = ui->comboBox->currentText();
    QString qr =  "select * from  commands_" + prf + ";";
    if (query.exec(qr))
    {
        qDebug() << "Текущий профиль установлен";

        modelMain = new QSqlQueryModel(this);
        query.exec("select * from commands_"+prf+ ";");
        modelMain->setQuery(query);

        ui->tableView_2->setModel(modelMain);
        //  ui->tableView_2->setColumnHidden(0, true);
        ui->tableView_2->setColumnHidden(2, true);



        ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView_2->resizeColumnsToContents();
    }

    // это для второго таба, где отдельные команды
    qr =  "select * from  command_" + prf + ";";
    if (query.exec(qr))
    {
        qDebug() << "Текущий профиль установлен";

        // modelMain_ = new QSqlQueryModel(this);
        query.exec("select * from command_"+prf+ ";");
        modelMain_1 = new QSqlQueryModel(this);
        modelMain_1->setQuery(query);
        ui->tableView->setModel(modelMain_1);
        //  ui->tableView_2->setColumnHidden(0, true);
        ui->tableView->setColumnHidden(2, true);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableView->resizeColumnsToContents();
    }

}

void MainWindow::switch_Off_Action_Requestion()
{
    requestion = false;
}

void MainWindow::switch_On_Action_Requestion()
{
    requestion = true;
}

int MainWindow::check()
{
    if (requestion)
    {
        QMessageBox* pmbx =
                new QMessageBox("Вы уререны???",
                                "<b>Вы дествитель хотите удалить данный профиль?</b> ",
                                QMessageBox::Warning,
                                QMessageBox::Yes,
                                QMessageBox::No,
                                QMessageBox::Cancel | QMessageBox::Escape);
        int n = pmbx->exec();
        delete pmbx;
        qDebug() << QMessageBox::Yes;
        return n;
    }
    else return 16384;
}
