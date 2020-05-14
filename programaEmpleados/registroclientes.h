#ifndef REGISTROCLIENTES_H
#define REGISTROCLIENTES_H

#include <QDialog>
#include"buscarusuario.h"
#include"cambiardatos.h"

namespace Ui {
class RegistroClientes;
}

class RegistroClientes : public QDialog
{
    Q_OBJECT

public:
    explicit RegistroClientes(int ultimoNumero, QWidget *parent = 0);
    void pasarDatos(BaseDeDatos * &base);
    void habilitar(bool habilitar);
    void vaciarRegistros();
    bool datosCompletos();
    QVector<QString> datosAVector();
    ~RegistroClientes();

private slots:
    void on_btn_buscar_clicked();

    void on_btn_cerrar_sesion_clicked();

    void on_btn_user_clicked();


    void on_rbtn_tarjeta_debito_clicked(bool checked);

    void on_rbtn_tarjeta_credito_clicked(bool checked);

    void on_btn_registtro_clicked();

private:
    Ui::RegistroClientes *ui;
    QWidget *Parent;
    BaseDeDatos *baseBanco;
    QVector<QString> datos;
};

#endif // REGISTROCLIENTES_H
