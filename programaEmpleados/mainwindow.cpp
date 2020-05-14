#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *t = new QTimer(this);

    t->setInterval(1000);
    connect(t, &QTimer::timeout,this,&MainWindow::actualizarHora);

    t->start();

    baseBanco = new BaseDeDatos();
}

void MainWindow::actualizarHora(){
    QString hora = QTime::currentTime().toString();

    ui->lbl_hora->setText(hora);
}
MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::on_pushButton_clicked()
{
    baseBanco->escogerTabla("registro_maestro");
    int resultadoBusqueda = baseBanco->busquedaLineal(ui->txt_usuario->text(),
                                                      ui->txt_contra->text());
    if(resultadoBusqueda){
        ui->lbl_resultadoLogin->setText("");
        hide();

        registroEmple = new RegistroEmpleados(this);
        registroEmple->pasarDatos(baseBanco);
        registroEmple->show();

        ui->txt_usuario->setText("");
        ui->txt_contra->setText("");

        return 1;
    }

    baseBanco->escogerTabla("registros_empleados");
    resultadoBusqueda = baseBanco->busquedaLineal(ui->txt_usuario->text(),
                                                      ui->txt_contra->text());
    if(resultadoBusqueda == 1){
        ui->lbl_resultadoLogin->setText("");
        hide();
        baseBanco->escogerTabla("registros_clientes");
        registroClient = new RegistroClientes(baseBanco->getId(),this);
        registroClient->pasarDatos(baseBanco);
        registroClient->show();

        ui->txt_usuario->setText("");
        ui->txt_contra->setText("");

        return 1;
    }
    else if(resultadoBusqueda == 0){
        ui->lbl_resultadoLogin->setText("<font color='red'>Usuario/contraseña incorrecta</font>");
        return 0;
    }
    else{
        ui->lbl_resultadoLogin->setText("<font color='red'>Su cargo no tiene permisos\n"
                                        " para modificar registros de clientes</font>");
        return 0;
    }
}
