#ifndef DATABASE_H
#define DATABASE_H
#include "record.h"

class Database
{
public:
    Database();
    void openFile(QString fileIn);
    void writeFile(QString fileIn);
    void addPerson(Record personIn);
    void deleteByName(QString nameIn);
    void deleteByDate(QDate dateIn);
    QDate findBday(QString nameIn);
    //QDate findBday(QDate d1, QDate d2);
    void nextBdays(QDate date, int range);
    QDate namespec(QString substr);
    QString getName(int i);
    QDate getDate(int i);

private:
    QList<Record> m_db;
};

//bool compareName(Record &person1, Record &person2);
//bool compareDate(Record &person1, Record &person2);

#endif // DATABASE_H
