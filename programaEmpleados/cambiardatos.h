#ifndef CAMBIARDATOS_H
#define CAMBIARDATOS_H

#include <QDialog>
#include <QMessageBox>

#include"basededatos.h"

namespace Ui {
class cambiarDatos;
}

class cambiarDatos : public QDialog
{
    Q_OBJECT

public:
    explicit cambiarDatos(QVector<QString> d, QWidget *parent = 0);
    void pasarDatos(BaseDeDatos * &base);
    ~cambiarDatos();

private slots:

    void on_btn_cambiar_datos_clicked();

private:
    Ui::cambiarDatos *ui;
    BaseDeDatos *baseBanco;
    QVector<QString> datos;
};

#endif // CAMBIARDATOS_H
