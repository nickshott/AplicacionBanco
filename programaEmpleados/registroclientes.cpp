#include "registroclientes.h"
#include "ui_registroclientes.h"

RegistroClientes::RegistroClientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistroClientes)
{
    Parent = parent;
    ui->setupUi(this);
}

RegistroClientes::~RegistroClientes()
{
    delete ui;
}

void RegistroClientes::on_btn_buscar_clicked()
{
    BuscarUsuario *buscarUsu = new BuscarUsuario(this);
    buscarUsu->pasarDatos(baseBanco);
    buscarUsu->setModal(true);
    buscarUsu->exec();
    buscarUsu->setFila(datos);

    if(datos[0] != "NULL"){
        ui->txt_nombre->setText(datos[0]);
        ui->txt_apellido->setText(datos[1]);
        ui->txt_celular->setText(datos[2]);
        ui->txt_cedula->setText(datos[3]);
        ui->txt_cargo->setText(datos[4]);
        ui->txt_email->setText(datos[5]);
    }

}

QVector<QString> RegistroClientes::datosAVector(){
    QVector<QString> tmp;
    tmp.push_back(ui->txt_nombre->text());
    tmp.push_back(ui->txt_apellido->text());
    tmp.push_back(ui->txt_celular->text());
    tmp.push_back(ui->txt_cedula->text());
    tmp.push_back(ui->txt_cargo->text());
    tmp.push_back(ui->txt_email->text());

    QString usu = ui->txt_email->text();
    for(int i=0;i<usu.size();i++){
        if(usu[i] == '@'){
            usu = usu.mid(0,i);
        }
    }
    tmp.push_back(usu);
    return tmp;
}

void RegistroClientes::pasarDatos(BaseDeDatos * &base){
    baseBanco = base;
}

bool RegistroClientes::datosCompletos(){
    if(ui->txt_nombre->text() != "" && ui->txt_apellido->text() != "" &&
            ui->txt_celular->text() != "" && ui->txt_cedula->text() != ""
            && ui->txt_cargo->text() != "" &&  ui->txt_email->text() != ""){
        return true;
    }
    return false;
}

void RegistroClientes::vaciarRegistros(){
    ui->txt_nombre->setText("");
    ui->txt_apellido->setText("");
    ui->txt_celular->setText("");
    ui->txt_cedula->setText("");
    ui->txt_cargo->setText("");
    ui->txt_email->setText("");

}

void RegistroClientes::on_btn_cerrar_sesion_clicked()
{
    close();
    Parent->show();
}
