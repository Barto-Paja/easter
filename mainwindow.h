#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QDate easterDate(const int year);

private slots:
    void on_pushButton_calculate_clicked();

private:
    Ui::MainWindow *ui;
    void setABparams(int year, int &a_val, int &b_val);
};
#endif // MAINWINDOW_H
