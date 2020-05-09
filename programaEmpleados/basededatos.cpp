#include "basededatos.h"

BaseDeDatos::BaseDeDatos()
{
    hostName = "db4free.net";
    userName = "jlukas01";
    password = "lukas1000579449";
    dataBaseName = "datos_banco_aed";

    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(hostName);
    db.setUserName(userName);
    db.setPassword(password);
    db.setDatabaseName(dataBaseName);

    if(!db.open()){
        qDebug() << "Error al iniciar base de datos";
    }
    else{
        qDebug() << "Base de datos iniciada correctamente";
    }

    dbModel = new QSqlTableModel();
    dbModel->setTable("registro_maestro");
    dbModel->select();

}

void BaseDeDatos::escogerTabla(QString tabla){
    dbModel->setTable(tabla);
    dbModel->select();
}

bool BaseDeDatos::busquedaLineal(QString usu, QString con){
    //METER ENCRIPTACION
    for(int i=0;i<dbModel->rowCount();i++){
        QString usuario = dbModel->record(i).value("Usuario").toString();
        QString clave = dbModel->record(i).value("Contraseña").toString();
        if(usuario == usu && clave == con)
            return true;
    }
    return false;
}

QVector<QString> BaseDeDatos::busquedaLineal(QString cedula){
    QVector<QString> datos;
    for(int i=0;i<dbModel->rowCount();i++){
        QString ced = dbModel->record(i).value("Cedula").toString();

        if(ced == cedula){
            datos.push_back(dbModel->record(i).value("Nombre").toString());
            datos.push_back(dbModel->record(i).value("Apellido").toString());
            datos.push_back(dbModel->record(i).value("Celular").toString());
            datos.push_back(dbModel->record(i).value("Cedula").toString());
            datos.push_back(dbModel->record(i).value("Cargo").toString());
            datos.push_back(dbModel->record(i).value("Email").toString());
            datos.push_back(QString::number(i+1));

            return datos;
        }
    }
    datos.push_back("NULL");
    return datos;
}

bool BaseDeDatos::insertarFila(QVector<QString> datos){
    QSqlRecord tmpRecord = dbModel->record();
    //PASAR datos[3] POR PROCESO DE ENCRIPTACION
    tmpRecord.remove(tmpRecord.indexOf("id"));

    tmpRecord.setValue("Nombre", datos[0]);
    tmpRecord.setValue("Apellido", datos[1]);
    tmpRecord.setValue("Celular", datos[2]);
    tmpRecord.setValue("Cedula", datos[3]);
    tmpRecord.setValue("Cargo", datos[4]);
    tmpRecord.setValue("Email", datos[5]);
    tmpRecord.setValue("Usuario",datos[6]);
    tmpRecord.setValue("Contraseña",datos[3]);

    if(dbModel->insertRecord(-1, tmpRecord)){
        dbModel->submitAll();
        return true;
    }
    else{
        db.rollback();
        return false;
    }
}

bool BaseDeDatos::modificarFila(QVector<QString> datos){
    QSqlRecord tmpRecord = dbModel->record(datos[3].toInt()-1);
    tmpRecord.remove(tmpRecord.indexOf("id"));

    tmpRecord.setValue("Celular", datos[0]);
    tmpRecord.setValue("Cargo", datos[1]);
    tmpRecord.setValue("Email", datos[2]);

    if(dbModel->setRecord(datos[3].toInt()-1, tmpRecord)){
        dbModel->submitAll();
        return true;
    }
    else{
        db.rollback();
        return false;
    }
}

bool BaseDeDatos::eliminarFila(int indice){
    if(dbModel->removeRow(indice-1)){
        dbModel->submitAll();
        return true;
    }
    else
        return false;
}
