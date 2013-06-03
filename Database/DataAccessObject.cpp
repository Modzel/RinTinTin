#include "DataAccessObject.h"
#include <QString>
#include <vector>
#include "Logic/Server.h"
#include <QTextCodec>


int connectionName = 0;

DataAccessObject::DataAccessObject(void)
{

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QString login = "tin";
    QString password = "TYBv0kqRbnTF9XaE";

    db = new QSqlDatabase(  QSqlDatabase::addDatabase("QMYSQL"));

    db->setHostName("tin.jatokor.net");
    db->setDatabaseName("tin");
    db->setUserName(login);
    db->setPassword(password);


}


DataAccessObject::~DataAccessObject(void)
{
    delete db;
}

ResponseAddUserPacket DataAccessObject::addUser(AddUserPacket userToAdd) {
    ResponseAddUserPacket responsePacket;
    //TODO

    QSqlQuery query;
    db->open();

    query.prepare("INSERT INTO `tin`.`uzytkownik` (`nazwa`, `haslo`, `sesionID`, `admin`, `login_time`) VALUES (?, ?, ?,?, ?);");
    QString haslo = userToAdd.password;
    QString nazwa = userToAdd.login;

    query.bindValue(0, nazwa);
    query.bindValue(1, haslo);
    query.bindValue(2, 0);
    query.bindValue(3, 0);
    query.bindValue(4, "1000-01-01 00:00:00");


    query.exec();

    responsePacket.userId=query.lastInsertId().toInt();

     db->close();



    return responsePacket;
}

ResponseCheckRestaurantPacket DataAccessObject::findNewestRestaurant() {
    ResponseCheckRestaurantPacket responsePacket;

    GetRestaurantPacket packet;
    std::vector<ResponseGetRestaurantPacket> nowy = getRestaurant(packet);
    responsePacket.globalLastRestaurantId = nowy[nowy.size()-1].restaurantId;
    responsePacket.globalRestaurantSize = nowy.size();


    return responsePacket;
}

std::vector<ResponseGetRestaurantPacket> DataAccessObject::getRestaurant(GetRestaurantPacket packet) {
    //ResponseGetRestaurantPacket responsePacket;

    std::vector<ResponseGetRestaurantPacket> responsePacket;
    db->open();
    QSqlQuery query;

    query.prepare("SELECT * FROM restauracje");
    query.exec();


    for(int i=0;i<query.size();i++)
    {
        query.next();
       ResponseGetRestaurantPacket nowy;

       nowy.restaurantId = query.value(0).toInt();
       nowy.restaurantName = query.value(1).toString();
       nowy.restaurantAdress = query.value(2).toString();
       nowy.restaurantType = query.value(3).toString();
       responsePacket.push_back(nowy);
    }



    db->close();




    return responsePacket;
}

std::vector<ResponseGetCommentsPacket> DataAccessObject::getComment(GetCommentsPacket packet) {
    ResponseGetCommentsPacket responsePacket;

    std::vector<ResponseGetCommentsPacket> wynik;
    db->open();
    QSqlQuery query;

    if(packet.addedDate=="0")
    {
        query.prepare("SELECT komentarz.tekst, komentarz.data, uzytkownik.nazwa FROM  `uzytkownik` INNER JOIN  `komentarz` ON komentarz.iduzytkownik_fk = uzytkownik.iduzytkownik where idRestauracje_fk = ? ORDER BY DATA DESC limit 0,5;");

        query.bindValue(0, packet.restaurantId);
        query.exec();


        for(int i=0;i<query.size();i++)
        {
              query.next();
              ResponseGetCommentsPacket nowy;
              nowy.text=query.value(0).toString();
              nowy.date=query.value(1).toString();
              nowy.userLogin=query.value(2).toString();
              wynik.push_back(nowy);
        }
    }
    else
    {
        query.prepare("SELECT komentarz.tekst, komentarz.data, uzytkownik.nazwa FROM  `uzytkownik` INNER JOIN  `komentarz` ON komentarz.iduzytkownik_fk = uzytkownik.iduzytkownik where komentarz.data > ? and idRestauracje_fk = ? ORDER BY DATA DESC limit 0,5;");

        query.bindValue(0, packet.addedDate);
        query.bindValue(1, packet.restaurantId);


        query.exec();


        for(int i=0;i<query.size();i++)
        {
              query.next();
              ResponseGetCommentsPacket nowy;
              nowy.text=query.value(0).toString();
              nowy.date=query.value(1).toString();
              nowy.userLogin=query.value(2).toString();
              wynik.push_back(nowy);
        }
    }



    db->close();


    return wynik;
}

ResponseAddCommentPacket DataAccessObject::addComment(AddCommentPacket packet) {
    ResponseAddCommentPacket responsePacket;

    QSqlQuery query;
    db->open();

    query.prepare("INSERT INTO `tin`.`komentarz` (`idRestauracje_fk`, `iduzytkownik_fk`, `tekst`, `data`) VALUES (?,?, ?,?);");


    int idRes= packet.restaurantId;
    int idUser= packet.userId;
    QString tekst =packet.text;
    QString data = packet.date;


    query.bindValue(0, idRes);
    query.bindValue(1, idUser);
    query.bindValue(2, tekst);
    query.bindValue(3, data);

    query.exec();

    responsePacket.commentId=query.lastInsertId().toInt();
    query.lastInsertId().toInt();

     db->close();

    return responsePacket;
}

ResponseAddRestaurantPacket DataAccessObject::addRestaurant(AddRestaurantPacket packet) {
    ResponseAddRestaurantPacket responsePacket;

    QSqlQuery query;
    db->open();

    query.prepare("INSERT INTO `tin`.`restauracje` (`nazwa`, `adres`, `typ`) VALUES (?, ?, ?);");
    QString nazwa = packet.restaurantName;
    QString adres = packet.restaurantAdress;
    QString typ = packet.restaurantType;

    query.bindValue(0, nazwa);
    query.bindValue(1, adres);
    query.bindValue(2, typ);


    query.exec();
     responsePacket.restaurantId=query.lastInsertId().toInt();
     db->close();

    return responsePacket;
}

ReponseDeleteCommentPacket DataAccessObject::deleteComment(DeleteCommentPacket packet) {
    ReponseDeleteCommentPacket responsePacket;

    QSqlQuery query;
    db->open();

    query.prepare("DELETE FROM `tin`.`komentarz` WHERE `idkomentarz`= ?;");

    query.bindValue(0, packet.commentId);

    query.exec();



    db->close();
    return responsePacket;
}

/*void DataAccessObject::closeConn()
{
    QString connection;
    connection = db->connectionName();
    db->close();
    //db = QSqlDatabase();
    db->removeDatabase(connection);
}*/
