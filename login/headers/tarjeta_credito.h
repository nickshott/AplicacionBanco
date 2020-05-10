#ifndef TARJETA_CREDITO_H
#define TARJETA_CREDITO_H

#include <QDialog>
#include "basededatos.h"

namespace Ui {
class tarjeta_Credito;
}

class tarjeta_Credito : public QDialog
{
    Q_OBJECT

public:
    void pasarDatos(BaseDeDatos * &base);
    explicit tarjeta_Credito(QWidget *parent = 0);
    ~tarjeta_Credito();

private:
    Ui::tarjeta_Credito *ui;
    BaseDeDatos *baseBanco;
};

#endif // TARJETA_CREDITO_H
