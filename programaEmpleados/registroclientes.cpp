#include "registroclientes.h"
#include "ui_registroclientes.h"

RegistroClientes::RegistroClientes(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistroClientes)
{
    ui->setupUi(this);
}

RegistroClientes::~RegistroClientes()
{
    delete ui;
}
