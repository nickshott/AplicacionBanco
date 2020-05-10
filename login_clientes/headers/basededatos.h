#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H

#include <QObject>

#include<QSql>
#include<QSqlDatabase>
#include<QSqlTableModel>
#include<QSqlError>
#include<QSqlRecord>

#include<QDebug>
#include<QVector>

class BaseDeDatos
{
public:
    BaseDeDatos();
    void escogerTabla(QString tabla);
    bool busquedaLineal(QString usu, QString con);
    //bool busquedaLineal(QString usu);
    QVector<QString> busquedaLineal1(QString cedula);
    bool insertarFila(QVector<QString> datos);
    bool modificarFila(QVector<QString> datos);
    bool eliminarFila(int indice);
private:
    QString hostName;
    QString userName;
    QString password;
    QString dataBaseName;

    QSqlTableModel *dbModel;
    QSqlDatabase db;
};

#endif // BASEDEDATOS_H
