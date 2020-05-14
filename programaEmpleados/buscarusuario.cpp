#include "buscarusuario.h"
#include "ui_buscarusuario.h"


BuscarUsuario::BuscarUsuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuscarUsuario)
{
    ui->setupUi(this);
}

BuscarUsuario::~BuscarUsuario()
{
    datos.push_back("NULL");
    delete ui;
}

void BuscarUsuario::on_pushButton_2_clicked()
{
    datos.push_back("NULL");
    close();
}


void BuscarUsuario::on_pushButton_clicked()
{
    datos = baseBanco->busquedaLineal(ui->lineEdit->text());

    if(datos[0] == "NULL"){
        QMessageBox::critical(this,"Cedula No encontrada",
                              "El usuario no existe, intente de nuevo");
        ui->lineEdit->setText("");
    }
    else{
        close();
    }
}

void BuscarUsuario::pasarDatos(BaseDeDatos * &base){
    baseBanco = base;
}

void BuscarUsuario::setFila(QVector<QString> &d){
    d = datos;
}



void BuscarUsuario::on_BuscarUsuario_finished(int result)
{
    datos.push_back("NULL");
}
