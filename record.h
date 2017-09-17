//Katherine Hogue, 9/7/17 In Class Assignment
#ifndef RECORD_H
#define RECORD_H
#include <QString>
#include <QDate>
#include <QFile>
#include <QTextStream>
#include <iostream>

class Record
{
public:
    Record();
    Record(QString name, QDate date);
    void setName(QString name);
    void setDate(QDate date);
    QString getName();
    QDate getDate();

private:
    QDate m_date;
    QString m_name;
};

#endif // RECORD_H
