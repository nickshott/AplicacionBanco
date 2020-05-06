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

#include"registroempleados.h"

#include"registroclientes.h"
#include"basededatos.h"

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

    RegistroEmpleados *registroEmple;
    RegistroClientes *registroClient;

    BaseDeDatos *baseBanco;
};

#endif // MAINWINDOW_H
