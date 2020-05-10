#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSql>
#include<QSqlDatabase>
#include<QSqlTableModel>
#include<QSqlError>

#include<QMessageBox>

#include<QTimer>
#include<QTime>

#include<QSqlRecord>
#include"basededatos.h"
#include "inside_bank.h"
#include "tarjeta_credito.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void actualizarHora();
    ~MainWindow();

private slots:
    int on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    tarjeta_Credito *tar;
    inside_bank *in;
    BaseDeDatos *baseBanco;

};

#endif // MAINWINDOW_H
