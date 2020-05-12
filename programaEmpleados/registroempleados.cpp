#include "registroempleados.h"
#include "ui_registroempleados.h"

RegistroEmpleados::RegistroEmpleados(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistroEmpleados)
{
    Parent = parent;
    ui->setupUi(this);
    ui->txt_cedula->setValidator(new QIntValidator());
    ui->txt_celular->setValidator(new QIntValidator());
}

RegistroEmpleados::~RegistroEmpleados()
{
    delete ui;
}

void RegistroEmpleados::on_btn_cerrar_sesion_clicked()
{
    hide();
    Parent->show();
}

void RegistroEmpleados::vaciarRegistros(){
    ui->txt_nombre->setText("");
    ui->txt_apellido->setText("");
    ui->txt_celular->setText("");
    ui->txt_cedula->setText("");
    ui->txt_cargo->setCurrentIndex(0);
    ui->txt_email->setText("");

}
void RegistroEmpleados::on_rbtn_agregar_clicked(bool checked)
{
    if(checked){
        ui->btn_buscar->setEnabled(false);
        ui->lbl_nombre->setEnabled(true);
        ui->txt_nombre->setEnabled(true);
        ui->lbl_apellido->setEnabled(true);
        ui->txt_apellido->setEnabled(true);
        ui->lbl_cedula->setEnabled(true);
        ui->txt_cedula->setEnabled(true);
        ui->lbl_celular->setEnabled(true);
        ui->txt_celular->setEnabled(true);
        ui->lbl_cargo->setEnabled(true);
        ui->txt_cargo->setEnabled(true);
        ui->lbl_email->setEnabled(true);
        ui->txt_email->setEnabled(true);

        vaciarRegistros();
        ui->btn_agregar_registro->setText("Agregar nuevo empleado al registro");
    }
}

void RegistroEmpleados::on_rbtn_editar_clicked(bool checked)
{
    if(checked){
        ui->btn_buscar->setEnabled(true);
        ui->lbl_nombre->setEnabled(false);
        ui->txt_nombre->setEnabled(false);
        ui->lbl_apellido->setEnabled(false);
        ui->txt_apellido->setEnabled(false);
        ui->lbl_cedula->setEnabled(false);
        ui->txt_cedula->setEnabled(false);
        ui->lbl_celular->setEnabled(true);
        ui->txt_celular->setEnabled(true);
        ui->lbl_cargo->setEnabled(true);
        ui->txt_cargo->setEnabled(true);
        ui->lbl_email->setEnabled(true);
        ui->txt_email->setEnabled(true);

        vaciarRegistros();
        ui->btn_agregar_registro->setText("Editar datos del empleado");
    }
}

void RegistroEmpleados::on_rbtn_eliminar_clicked(bool checked)
{
    if(checked){
        ui->btn_buscar->setEnabled(true);
        ui->lbl_nombre->setEnabled(false);
        ui->txt_nombre->setEnabled(false);
        ui->lbl_apellido->setEnabled(false);
        ui->txt_apellido->setEnabled(false);
        ui->lbl_cedula->setEnabled(false);
        ui->txt_cedula->setEnabled(false);
        ui->lbl_celular->setEnabled(false);
        ui->txt_celular->setEnabled(false);
        ui->lbl_cargo->setEnabled(false);
        ui->txt_cargo->setEnabled(false);
        ui->lbl_email->setEnabled(false);
        ui->txt_email->setEnabled(false);

        vaciarRegistros();
        ui->btn_agregar_registro->setText("Borrar empleado del registro");
    }
}

void RegistroEmpleados::on_btn_buscar_clicked()
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
        ui->txt_cargo->setCurrentText(datos[4]);
        ui->txt_email->setText(datos[5]);
    }
    else{
        QMessageBox::critical(this,"Cliente no encontrado", "Lo sentimos, el cliente \n"
                                                            "no registra en nuestra base de datos");
    }

}

void RegistroEmpleados::pasarDatos(BaseDeDatos * &base){
    baseBanco = base;
}

bool RegistroEmpleados::datosCompletos(){
    if(ui->txt_nombre->text() != "" && ui->txt_apellido->text() != "" &&
            ui->txt_celular->text() != "" && ui->txt_cedula->text() != ""
            && ui->txt_cargo->currentText() != "" &&  ui->txt_email->text() != ""){
        return true;
    }
    return false;
}
void RegistroEmpleados::on_btn_agregar_registro_clicked(){
    if(ui->rbtn_agregar->isChecked()){
        if(datosCompletos()){
            baseBanco->escogerTabla("registros_empleados");
            datos = baseBanco->busquedaLineal(ui->txt_cedula->text());

            if(datos[0] == "NULL"){
                QVector<QString> datosInsercion;
                datosInsercion = datosAVector();
                bool insercion = baseBanco->insertarFila(datosInsercion);

                QString informacion = "El usuario es: " + datosInsercion[6] + "\n contraseña: "
                        + datosInsercion[3];
                if(insercion){
                    QMessageBox::information(this,"Registro exitoso", informacion);
                    vaciarRegistros();
                }
                else{
                    QMessageBox::critical(this,"Error en registro", "Intente nuevamente");
                }
            }
            else{
                QMessageBox::critical(this,"El usuario existe", "Si quiere editar, cambie el modo");
            }
        }
        else{
            QMessageBox::critical(this,"Faltan datos", "Por favor llene los campos obligatorios");
        }
    }

    else if(ui->rbtn_editar->isChecked()){
        if(ui->txt_nombre->text() != ""){
            QString indice = datos[6];
            datos.clear();
            datos.push_back(ui->txt_celular->text());
            datos.push_back(ui->txt_cargo->currentText());
            datos.push_back(ui->txt_email->text());
            datos.push_back(indice);

            bool resultado = baseBanco->modificarFila(datos);
            if(resultado){
                vaciarRegistros();
                QMessageBox::information(this,"Correcto","Registro editado correctamente");
            }
            else{
                vaciarRegistros();
                QMessageBox::critical(this,"Error","Error al editar registro");
            }
        }
        else{
            QMessageBox::critical(this,"Error","Para editar la informacion de un empleado \n primero busquelo");
        }
    }
    else if(ui->rbtn_eliminar->isChecked()){
        if(ui->txt_nombre->text() != ""){
            bool resultado = baseBanco->eliminarFila(datos[6].toInt());
            if(resultado){
                vaciarRegistros();
                QMessageBox::information(this,"Correcto","Empleado eliminado correctamente");
            }
            else{
                vaciarRegistros();
                QMessageBox::critical(this,"Error","Error al eliminar registro");
            }
        }
        else{
            QMessageBox::critical(this,"Error","Para eliminar un empleado \n primero busquelo");
        }
    }
}

QVector<QString> RegistroEmpleados::datosAVector(){
    QVector<QString> tmp;
    tmp.push_back(ui->txt_nombre->text());
    tmp.push_back(ui->txt_apellido->text());
    tmp.push_back(ui->txt_celular->text());
    tmp.push_back(ui->txt_cedula->text());
    tmp.push_back(ui->txt_cargo->currentText());
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
