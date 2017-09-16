//Katherine Hogue, 9/7/17 In Class Assignment

#include "record.h"

//Default constructor
Record::Record()
{

}

//Constructor
//inputs: name and date of the person being entered into "record"
 Record::Record(QString name, QDate date)
 {
     m_name = name;
     m_date = date;
 }

 //Sets name
 //inputs: string name
 void Record::setName(QString name)
 {
     m_name = name;
 }

 //Sets the date
 //inputs: Qdate date
 void Record::setDate(QDate date)
 {
     m_date = date;
 }

 //returns name
 QString Record::getName()
 {
     return m_name;
 }

 //returns date
 QDate Record::getDate()
 {
     return m_date;
 }
