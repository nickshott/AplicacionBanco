#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H

#include <QObject>

#include<QSql>
#include<QSqlDatabase>
#include<QSqlTableModel>
#include<QSqlError>
#include<QSqlRecord>
#include<QSqlQuery>
#include<QFile>
#include<QDebug>
#include<QVector>
#include<QMessageBox>
#include<QTextStream>
class BaseDeDatos
{
public:
    BaseDeDatos();
    bool insercionTransaccion(QVector<QString>&datos);
    void escogerTabla(QString tabla);
    QVector<QString> busquedaLineal(QString usu, QString con);
    //bool busquedaLineal(QString usu);
    QString readPrint(QString k);
    QVector<QString> busquedaLinealtd(QString td);
    QVector<QString> getDatos();
    QSqlTableModel* getModel();
    QVector<QString> busquedaLineal1_2(QString conv);
    QVector<QString> busquedaLineal1_1(QString cedula);
    QVector<QString> busquedaLineal1_1_2(QString cedula);
    QVector<QString> busquedaLineal1_3(QString cedula);
    bool insertarFila(QVector<QString> &datos);
    bool modificarFila(QVector<QString> datos);
    bool modificarFila1(QVector<QString> datos);
    bool modificarFila2(QVector<QString> datos);
    bool modificarFila1_1(QVector<QString> datos);

    bool cambiarUsuarioContra(QVector<QString> datos);
    //bool eliminarFila(int indice);

private:
    QString hostName;
    QString userName;
    QString password;
    QString dataBaseName;

    QSqlTableModel *dbModel;
    QSqlDatabase db;
    int indice;
};

#endif // BASEDEDATOS_H
