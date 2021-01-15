#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_year->setValidator( new QIntValidator(0, 4000, this) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setABparams(int year, int & a_val, int & b_val)
{
    if(( 33 <= year ) && ( year <= 1582 ))
    {
        a_val = 15; b_val = 6;
    }
    else if( year <= 1699 )
    {
        a_val = 22; b_val = 2;
    }
    else if( year <= 1799 )
    {
        a_val = 23; b_val = 3;
    }
    else if( year <= 1899 )
    {
        a_val = 23; b_val = 4;
    }
    else if( year <= 2099 )
    {
        a_val = 24; b_val = 5;
    }
    else if( year <= 2199 )
    {
        a_val = 24; b_val = 6;
    }
    else if( year <= 2299 )
    {
        a_val = 25; b_val = 0;
    }
    else if( year <= 2399 )
    {
        a_val = 26; b_val = 1;
    }
    else if( year <= 2499 )
    {
        a_val = 25; b_val = 1;
    }
    else if( year <= 2599 )
    {
        a_val = 26; b_val = 2;
    }
    else if( year <= 2699 )
    {
        a_val = 27; b_val = 3;
    }
    else if( year <= 2899 )
    {
        a_val = 27; b_val = 4;
    }
    else if( year <= 2999 )
    {
        a_val = 28; b_val = 5;
    }
}

QDate MainWindow::easterDate(const int year)
{
    constexpr int a_devider { 19 };
    constexpr int b_devider { 4 };
    constexpr int c_devider { 7 };

    auto a_val { 0 };
    auto b_val { 0 };

    setABparams(year, a_val, b_val);

    auto a_modulo { year%a_devider };
    auto b_modulo { year%b_devider };
    auto c_modulo { year%c_devider };

    auto d_modulo { ((a_modulo * 19) + a_val) % 30 };
    auto e_modulo { ( 2 * b_modulo + 4 * c_modulo + 6 * d_modulo + b_val) % 7 };

    QDate date { year, 3, 22 };

    if((d_modulo == 29) && (e_modulo == 6))
    {
        auto r = d_modulo + e_modulo - 7;

        date = date.addDays(r);
    }
    else if((d_modulo == 28) && (e_modulo == 6) && ( ((11 * a_val + 11) % 30) < 19 ) )
    {
        date = date.addDays(d_modulo + e_modulo - 7);
    }
    else
    {
        date = date.addDays(d_modulo + e_modulo);
    }

    return date;
}


void MainWindow::on_pushButton_calculate_clicked()
{
    auto date = easterDate(ui->lineEdit_year->text().toInt());
    ui->lineEdit_easterSunday->setText(date.toString("yyyy-MM-dd") + " " + date.toString("dddd"));
    date = date.addDays(1);
    ui->lineEdit_easterMonday->setText(date.toString("yyyy-MM-dd") + " " + date.toString("dddd"));
    date = date.addDays(59);
    ui->lineEdit_CorpusChristi->setText(date.toString("yyyy-MM-dd") + " " + date.toString("dddd"));
}
