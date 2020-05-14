#include "registroclientes.h"
#include "ui_registroclientes.h"

#define TARJETADEBITO 132600000000
#define TARJETACREDITO 829100000000

RegistroClientes::RegistroClientes(int ultimoNumero, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistroClientes)
{
    Parent = parent;
    ui->setupUi(this);


    long long int numeroTarjeta = TARJETADEBITO + ultimoNumero;
    ui->lbl_numeroTarjjeta->setText(QString::number(numeroTarjeta));
}

RegistroClientes::~RegistroClientes()
{
    delete ui;
}

void RegistroClientes::on_btn_buscar_clicked()
{
    BuscarUsuario *buscarUsu = new BuscarUsuario(this);
    baseBanco->escogerTabla("registros_clientes");
    buscarUsu->pasarDatos(baseBanco);
    buscarUsu->setModal(true);
    buscarUsu->exec();
    buscarUsu->setFila(datos);

    if(datos[0] != "NULL"){
        vaciarRegistros();

        ui->txt_nombre->setText(datos[0]);
        ui->txt_apellido->setText(datos[1]);
        ui->txt_celular->setText(datos[2]);
        ui->txt_cedula->setText(datos[3]);
        ui->txt_cargo->setText(datos[4]);
        ui->txt_email->setText(datos[5]);

        if(datos[7][0] == "0"){
            ui->rbtn_tarjeta_debito->setChecked(true);
            ui->lbl_monto_cupo_inicial->setText("Monto:  ");

            QString numeroTarjeta = "1326" + datos[8].mid(4,-1);
            ui->lbl_numeroTarjjeta->setText(numeroTarjeta);
            habilitar(false);
        }
        else if(datos[8][0] == "0"){
            ui->rbtn_tarjeta_credito->setChecked(true);
            ui->lbl_monto_cupo_inicial->setText("Cupo:   ");

            QString numeroTarjeta = "8291" + datos[7].mid(4,-1);
            ui->lbl_numeroTarjjeta->setText(numeroTarjeta);
            habilitar(false);
        }
        else{
            QMessageBox::critical(this,"Cuentas maximas", "El usuario ya tiene en su historial"
                                                          "\nTarjeta de credito y tarjeta debito "
                                                          "\nCualquier cambio de datos, hagalo en"
                                                          "\nLa aplicacion de clientes");
            datos.clear();
            vaciarRegistros();
        }
    }

}

void RegistroClientes::habilitar(bool habilitar){
    ui->txt_nombre->setEnabled(habilitar);
    ui->txt_apellido->setEnabled(habilitar);
    ui->txt_celular->setEnabled(habilitar);
    ui->txt_cedula->setEnabled(habilitar);
    ui->txt_cargo->setEnabled(habilitar);
    ui->txt_email->setEnabled(habilitar);
    ui->rbtn_tarjeta_credito->setEnabled(habilitar);
    ui->rbtn_tarjeta_debito->setEnabled(habilitar);
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
    tmp.push_back(ui->lbl_numeroTarjjeta->text());

    if(ui->lbl_numeroTarjjeta->text().mid(0,4) == "1326"){
        if(ui->txt_monto_cupo->text() == ""){
            tmp.push_back("0");
        }
        else{
            tmp.push_back(ui->txt_monto_cupo->text());
        }
    }
    else{
        if(ui->txt_monto_cupo->text() == ""){
            tmp.push_back("6000");
        }
        else{
            tmp.push_back(ui->txt_monto_cupo->text());
        }
    }

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
    ui->txt_monto_cupo->setText("");
}

void RegistroClientes::on_btn_cerrar_sesion_clicked()
{
    close();
    Parent->show();
}

void RegistroClientes::on_btn_user_clicked()
{
    baseBanco->escogerTabla("registros_empleados");
    cambiarDatos *cambiarUsu = new cambiarDatos(baseBanco->getDatos(), this);
    cambiarUsu->pasarDatos(baseBanco);
    cambiarUsu->setModal(true);
    cambiarUsu->exec();
    baseBanco->escogerTabla("registros_clientes");
}



void RegistroClientes::on_rbtn_tarjeta_debito_clicked(bool checked)
{
    if(checked){
        long long int numeroTarjeta = TARJETADEBITO + baseBanco->getId();
        ui->lbl_numeroTarjjeta->setText(QString::number(numeroTarjeta));
        ui->lbl_monto_cupo_inicial->setText("Monto:  ");
    }
}

void RegistroClientes::on_rbtn_tarjeta_credito_clicked(bool checked)
{
    if(checked){
        long long int numeroTarjeta = TARJETACREDITO + baseBanco->getId();
        ui->lbl_numeroTarjjeta->setText(QString::number(numeroTarjeta));
        ui->lbl_monto_cupo_inicial->setText("Cupo:   ");
    }
}

void RegistroClientes::on_btn_registtro_clicked()
{
    if(datosCompletos()){
        baseBanco->escogerTabla("registros_clientes");
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
                int numero = ui->lbl_numeroTarjjeta->text().mid(3,-1).toInt() + 1;
                ui->lbl_numeroTarjjeta->setText(ui->lbl_numeroTarjjeta->text().mid(0,3) + QString::number(numero));
            }
            else{
                QMessageBox::critical(this,"Error en registro", "Intente nuevamente");
            }
        }
        else{
            habilitar(false);
            QString indice = datos[6];

            if(ui->rbtn_tarjeta_debito->isChecked() && datos[7][0] == "0"){
                datos.clear();
                datos.push_back("Tarjeta debito");
                datos.push_back(ui->lbl_numeroTarjjeta->text());
                datos.push_back("Monto");

                if(ui->txt_monto_cupo->text() == ""){
                    datos.push_back("0");
                }
                else{
                    datos.push_back(ui->txt_monto_cupo->text());
                }
                datos.push_back(indice);

                if(baseBanco->crearTarjeta(datos)){
                    QMessageBox::information(this,"Cambio correcto",
                                             "Tarjeta debito creada correctamente");

                    long long int numeroTarjeta = TARJETADEBITO + baseBanco->getId();
                    ui->lbl_numeroTarjjeta->setText(QString::number(numeroTarjeta));
                    ui->lbl_monto_cupo_inicial->setText("Monto:  ");

                    vaciarRegistros();
                    habilitar(true);
                }
                else{
                    QMessageBox::critical(this,"Error en cambio",
                                          "Ha ocurrido un error, por favor intente nuevamente");
                }
            }
            else if(ui->rbtn_tarjeta_credito->isChecked() && datos[8][0] == "0"){
                datos.clear();
                datos.push_back("Tarjeta credito");
                datos.push_back(ui->lbl_numeroTarjjeta->text());
                datos.push_back("Cupo");

                if(ui->txt_monto_cupo->text() == ""){
                    datos.push_back("6000");
                }
                else{
                    datos.push_back(ui->txt_monto_cupo->text());
                }
                datos.push_back(indice);

                if(baseBanco->crearTarjeta(datos)){
                    QMessageBox::information(this,"Cambio correcto",
                                             "Tarjeta de credito creada correctamente");

                    long long int numeroTarjeta = TARJETACREDITO + baseBanco->getId();
                    ui->lbl_numeroTarjjeta->setText(QString::number(numeroTarjeta));
                    ui->lbl_monto_cupo_inicial->setText("Cupo:   ");

                    vaciarRegistros();
                    habilitar(true);
                }
                else{
                    QMessageBox::critical(this,"Erro en cambio",
                                          "Ha ocurrido un error, por favor intente nuevamente");
                }
            }
            else{
                QMessageBox::critical(this,"Usuario existente", "Para crear una cuenta diferente "
                                                                " \nseleccione el tipo de tarjeta");
            }
        }
    }
    else{
        QMessageBox::critical(this,"Faltan datos", "Por favor llene los campos obligatorios");
    }
}
