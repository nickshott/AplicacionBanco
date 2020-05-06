#ifndef REGISTROCLIENTES_H
#define REGISTROCLIENTES_H

#include <QDialog>

namespace Ui {
class RegistroClientes;
}

class RegistroClientes : public QDialog
{
    Q_OBJECT

public:
    explicit RegistroClientes(QWidget *parent = 0);
    ~RegistroClientes();

private:
    Ui::RegistroClientes *ui;
};

#endif // REGISTROCLIENTES_H
