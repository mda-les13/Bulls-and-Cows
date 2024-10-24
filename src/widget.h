#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QString>
#include <QStringList>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QDialog>
#include <QPushButton>
#include <QTextEdit>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    QStandardItemModel* model;
    QTableView *view;
    QTableWidget secw;
    QDialog win;
    QDialog warn;
    QTextEdit* txt;
    ~Widget();

private slots:

    void on_pushButton_check_clicked();

    void on_pushButton_newgame_clicked();

    void on_pushButton_records_clicked();

    void ok_button_clicked();

    void cancel_button_clicked();

    void on_textEdit_input_textChanged();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
