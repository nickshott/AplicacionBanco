#ifndef BUSCARUSUARIO_H
#define BUSCARUSUARIO_H

#include <QDialog>
#include<QDebug>
#include<QVector>

#include<QMessageBox>

#include"basededatos.h"

namespace Ui {
class BuscarUsuario;
}

class BuscarUsuario : public QDialog
{
    Q_OBJECT

public:
    explicit BuscarUsuario(QWidget *parent = 0);
    void pasarDatos(BaseDeDatos * &base);
    void setFila(QVector<QString> & d);
    ~BuscarUsuario();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_BuscarUsuario_finished(int result);

private:
    Ui::BuscarUsuario *ui;
    BaseDeDatos *baseBanco;
    QVector<QString> datos;
};

#endif // BUSCARUSUARIO_H
