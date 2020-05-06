#ifndef REGISTROEMPLEADOS_H
#define REGISTROEMPLEADOS_H

#include <QDialog>
#include<QWidget>

#include<QDebug>
#include<QVector>

#include"basededatos.h"

#include"buscarusuario.h"

namespace Ui {
class RegistroEmpleados;
}

class RegistroEmpleados : public QDialog
{
    Q_OBJECT

public:
    explicit RegistroEmpleados(QWidget *parent = 0);
    void pasarDatos(BaseDeDatos * &base);
    void vaciarRegistros();
    bool datosCompletos();
    QVector<QString> datosAVector();
    ~RegistroEmpleados();

private slots:
    void on_btn_cerrar_sesion_clicked();

    void on_rbtn_agregar_clicked(bool checked);

    void on_rbtn_editar_clicked(bool checked);

    void on_rbtn_eliminar_clicked(bool checked);

    void on_btn_buscar_clicked();

    void on_btn_agregar_registro_clicked();

private:
    Ui::RegistroEmpleados *ui;
    QWidget *Parent;

    BaseDeDatos *baseBanco;
    QVector<QString> datos;

};

#endif // REGISTROEMPLEADOS_H
