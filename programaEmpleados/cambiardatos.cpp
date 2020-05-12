#include "cambiardatos.h"
#include "ui_cambiardatos.h"

cambiarDatos::cambiarDatos(QVector<QString> d, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cambiarDatos)
{
    ui->setupUi(this);
    datos = d;

    QString nombreCompleto = datos[0] + " " + datos[1];
    QString cargo = datos[2];

    ui->lbl_nombre->setText(nombreCompleto);
    ui->lbl_cargo->setText(cargo);
}

cambiarDatos::~cambiarDatos()
{
    delete ui;
}

void cambiarDatos::pasarDatos(BaseDeDatos * &base){
    baseBanco = base;
}



void cambiarDatos::on_btn_cambiar_datos_clicked()
{
    QString indice = datos[5];
    QString usuarioAnt = datos[3];
    QString contraAnt = datos[4];

    if(ui->txt_usuario_nuevo->text() != "" || ui->txt_contra_nueva->text() != "")
    {
        if(usuarioAnt == ui->txt_usuario_ant->text() && contraAnt == ui->txt_contra_ant->text()){
            datos.clear();
            if(ui->txt_usuario_nuevo->text() == ""){
                datos.push_back(usuarioAnt);
                datos.push_back(ui->txt_contra_nueva->text());
                datos.push_back(indice);
            }
            else if(ui->txt_contra_nueva->text() == ""){
                datos.push_back(ui->txt_usuario_nuevo->text());
                datos.push_back(contraAnt);
                datos.push_back(indice);
            }
            else{
                datos.push_back(ui->txt_usuario_nuevo->text());
                datos.push_back(ui->txt_contra_nueva->text());
                datos.push_back(indice);
            }

            if(baseBanco->cambiarUsuarioContra(datos)){
                QMessageBox::information(this,"Cambio exitoso","Se ha actualizado correctamente la informacion");
                close();
            }
            else{
                QMessageBox::critical(this,"Error en cambio","Ha ocurrido un error, intente nuevamente");
                ui->txt_usuario_nuevo->setText("");
                ui->txt_contra_nueva->setText("");
                ui->txt_usuario_ant->setText("");
                ui->txt_contra_ant->setText("");
            }
        }
        else{
            QMessageBox::critical(this,"Datos incorrectos", "Usuario o contraseña \nanterior"
                                                            " incorrectos");
        }
    }
    else{
        close();
    }

}
