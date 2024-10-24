#include "widget.h"
#include "ui_widget.h"

int global_counter = 0;
int bulls = 0;
int cows = 0;
const QString space = "";
QString str_random = "1234";

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this -> setWindowTitle("Быки и коровы");
    ui->textEdit_input->setReadOnly(false);
    model = new QStandardItemModel(100, 2);

    // установка заголовков таблицы
    model->setHeaderData(0, Qt::Horizontal, "Число");
    model->setHeaderData(1, Qt::Horizontal, "Результат");

    // определяем представление
    view = new QTableView(this);
    // устанавливаем модель для представления
    view->setModel(model);
    view->move(20, 110);
    view->resize(440, 360);
    view->setColumnWidth(0, 190);
    view->setColumnWidth(1, 190);

    //создание таблицы результатов
    secw.setWindowTitle("Рекорды");
    for (int i = 0; i < 10; i++)
    {
        secw.insertRow(i);
    }
    secw.insertColumn(0);
    secw.insertColumn(1);
    secw.setColumnWidth(0, 150);
    secw.setColumnWidth(1, 150);
    QStringList lst;
    lst << "Попыток" << "Имя";
    secw.setHorizontalHeaderLabels(lst);
    secw.setFixedSize(360, 360);

    /*QTableWidgetItem* ptwi = 0;
    for (int i = 0; i < 10; i++)
        {
            ptwi = new QTableWidgetItem(QString(QString::number(i)));
            secw.setItem(i, 0, ptwi);
            ptwi = new QTableWidgetItem(QString("a"));
            secw.setItem(i, 1, ptwi);
        }
    secw.sortItems(0);*/

    //создание окна диалога
    win.setModal(true);
    win.setWindowTitle("Input");
    win.setFixedSize(360, 240);

    QPushButton *ok_button = new QPushButton(&win);
    ok_button->setFixedSize(140, 40);
    ok_button->setText("OK");
    ok_button->move(200, 180);
    connect(ok_button, SIGNAL(clicked()), this, SLOT(ok_button_clicked()));

    QPushButton *cancel_button = new QPushButton(&win);
    cancel_button->setFixedSize(140, 40);
    cancel_button->setText("Cancel");
    cancel_button->move(20, 180);
    connect(cancel_button, SIGNAL(clicked()), this, SLOT(cancel_button_clicked()));

    QTextEdit* txt_edit = new QTextEdit(&win);
    txt_edit->setFixedSize(320, 40);
    txt_edit->move(20, 120);
    QFont font;
    font.setPixelSize(22);
    txt_edit->setFont(font);
    txt = txt_edit;

    QLabel* name_label = new QLabel(&win);
    name_label->setText("NAME:");
    name_label->move(40, 80);
    name_label->setFont(font);

    //предупреждение при неправильном вводе
    warn.setModal(true);
    warn.setWindowTitle("WARNING!");
    warn.setFixedSize(480, 120);
    QLabel* warn_label = new QLabel(&warn);
    warn_label->setText(" Неправильный ввод! \n Все цифры должны быть различными \n и их должно быть 4");
    warn_label->setFont(font);
    warn_label->move(10, 20);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ok_button_clicked()
{
    QString temp;
    temp = txt->toPlainText();
    QTableWidgetItem* p = 0;

    p = new QTableWidgetItem(QString(QString::number(global_counter)));
    secw.setItem(9, 0, p);
    p = new QTableWidgetItem(QString(temp));
    secw.setItem(9, 1, p);

    secw.sortItems(0);
    secw.show();
    win.hide();
}

void Widget::cancel_button_clicked()
{
    win.hide();
}


void Widget::on_pushButton_check_clicked()
{
    bool ok = true;
    QString temp;
    temp = ui->textEdit_input->toPlainText();
    if (temp.size() < 4)
    {
        ok = false;
    }

    if (ok)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (temp[i] == temp[j] && i != j)
                {
                    ok = false;
                }
            }
        }
    }

    if (ok)
    {
        bool cow = false;
        bool bull = false;
        model->setItem(global_counter, 0, new QStandardItem(temp));
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (temp[i] == str_random[j])
                {
                    if (i == j)
                    {
                        bull = true;
                    }
                    else
                    {
                        cow = true;
                    }
                }
            }

            if (bull)
            {
                bulls++;
            }
            else
            {
                if (cow)
                {
                    cows++;
                }
            }

            bull = false;
            cow = false;
        }

        QString output = QString::number(bulls) + " быков, " + QString::number(cows) + " коров";
        model->setItem(global_counter, 1, new QStandardItem(output));

        if (bulls == 4)
        {
            ui->label_2->setText("Победа!!!");
            //ui->pushButton_check->setEnabled(false);
            win.show();
        }
        else
        {
            ui->label_2->setText("Не угадали");
        }

        if (global_counter == 100)
        {
            ui->label_2->setText("Ну это проигрыш, лол");
            ui->pushButton_check->setEnabled(false);
        }
        bulls = 0;
        cows = 0;
        global_counter++;
        ui->textEdit_input->setPlainText("");
    }
    else
    {
        ui->textEdit_input->setPlainText("");
        warn.show();
    }

}

void Widget::on_pushButton_newgame_clicked()
{
    ui->label_2->setText("Игра не начата");
    ui->pushButton_check->setEnabled(true);
    int a, b, c, d;
    for (int i = 0; i < global_counter; i++)
    {
        model->setItem(i, 0, new QStandardItem(space));
        model->setItem(i, 1, new QStandardItem(space));
    }
    global_counter = 0;
    a = rand() % 10;
    b = rand() % 10;
    while (b == a)
    {
        b = rand() % 10;
    }
    c = rand() % 10;
    while (c == a || c == b)
    {
        c = rand() % 10;
    }
    d = rand() % 10;
    while (d == a || d == b || d == c)
    {
        d = rand() % 10;
    }

    str_random = QString::number(a) + QString::number(b) + QString::number(c) + QString::number(d);
}

void Widget::on_pushButton_records_clicked()
{
    secw.show();
}

void Widget::on_textEdit_input_textChanged()
{
    QString temp;
    temp = ui->textEdit_input->toPlainText();
    if (temp.isEmpty() == false)
    {
        if (temp[temp.size() - 1] < "0" || temp[temp.size() - 1] > "9" || temp.size() > 4)
        {
            temp.resize(temp.size() - 1);
            ui->textEdit_input->setPlainText(temp);
        }
    }
}
