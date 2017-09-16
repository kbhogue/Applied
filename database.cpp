#include "database.h"

//Default constructor
Database::Database()
{

}

//opens file and reads names and dates into a database
//inputs: filename
void Database::openFile(QString fileIn)
{
    QTextStream out(stdout);
    QFile file(fileIn);
    file.open(QFile::ReadOnly);
    while (!file.atEnd())
    {
        QString nameIn = file.readLine();
        nameIn = nameIn.remove('\r');
        nameIn = nameIn.remove('\n');
        QString dateIn = file.readLine();
        QDate qDateIn = QDate::fromString(dateIn);
        Record r;
        r.setName(nameIn);
        r.setDate(qDateIn);
        addPerson(r);
    }
}

//Writes a database to a file
//inputs: filename
void Database::writeFile(QString fileIn)
{
    QFile file(fileIn);
    QTextStream out(&file);
    file.open(QFile::WriteOnly);
    for(int i = 0;i<m_db.length(); i++)
    {
        out<<m_db[i].getName() << endl;
        out << m_db[i].getDate().QDate::toString() << endl;
    }
}

//adds a person to a database
//if person already exists, it overwrites their birthday
//inputs: person to be added
void Database::addPerson(Record personIn)
{
    int i;
    for(i = 0; i<m_db.length(); i++)
    {
        if (m_db[i].getName() == personIn.getName())
            m_db[i].getDate() = personIn.getDate();
    }
    if(i==m_db.length())
    {
        m_db.append(personIn);
    }
}

//deletes a person from the database
//checks for name and deletes person of same name
//inputs: person to be deleted
void Database::deleteByName(QString nameIn)
{
    for(int i = 0; i<m_db.length(); i++)
    {
        if (QString::compare(nameIn,m_db[i].getName())==0)
        {
            m_db.removeAt(i);
            break;
        }
    }
}

//deletes a person from the database
//checks for birthday and deletes person with same birthday
//inputs: date to be deleted
void Database::deleteByDate(QDate dateIn)
{
    for(int i = 0; i<m_db.length(); i++)
    {
        QDate dateCur = m_db[i].getDate();
        if (dateIn == dateCur)
        {
            m_db.removeAt(i);
        }
    }
}

//Takes in a name and finds the birthday associated with the name
//Inputs: QString name
//Outputs: QDate birthday
QDate Database::findBday(QString nameIn)
{
    QTextStream out(stdout);
    QString nameCur;
    nameIn = nameIn.remove('\r');
    nameIn = nameIn.remove('\n');
    out << nameIn << endl;
    for(int i = 0; i<m_db.length(); i++)
    {
        nameCur = m_db[i].getName();
        out << nameCur;
        if(QString::compare(nameCur, nameIn)==0)
            return m_db[i].getDate();
    }
   throw "invalid argument(Name not found)";
}

QDate Database::namespec(QString substr)
{
    QTextStream out(stdout);
    out << "Name            Birthday" << endl;
    out << "===========     ===========" << endl;

    int i;
    for(i = 0; i < m_db.size(); i++)
    {
        if(m_db[i].getName().contains(substr))
        {
           out << m_db[i].getName()<< "\t" << m_db[i].getDate().QDate::toString() << endl;
        }
    }
}

/*
//Sorts the database by name alphabetically
bool compareName(Record &person1, Record &person2)
{
    int c = QString::compare(person1.getName(),person2.getName());
    if (c == 1)
        return true;
    else
        return false;
}

//sorts the database by birthday chronologically
bool compareDate(Record &person1, Record &person2))
{
    int c = QString::compare(person1.getDate().toString(),person2.getDate().toString());
    if (c == 1)
        return true;
    else
        return false;
} */

//lists the next birthdays occuring in range
void Database::nextBdays(QDate date,int range)
{
    QTextStream out(stdout);
    out.setPadChar(0x20);

    //qSort(m_db.begin(), m_db.end(),compareDate);

    out << "Name            Birthday" << endl;
    out << "===========     ===========" << endl;
    for(int i=0; i< m_db.length(); i++){
        {
            if (date.daysTo(m_db[i].getDate())<=range&& date.daysTo(m_db[i].getDate())>=0)
                out << m_db[i].getName()<< "\t" << m_db[i].getDate().QDate::toString() << endl;
        }

    }
}

//For testing
QString Database::getName(int i)
{
    return m_db[i].Record::getName();
}

//for testing
QDate Database::getDate(int i)
{
    return m_db[i].Record::getDate();
}
