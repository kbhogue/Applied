#include <QCoreApplication>
#include "database.h"
#include "record.h"
#include <QTextStream>
#include <iostream>
#include <exception>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream out(stdout);
    Database data;
    bool fail = false;
    data.openFile("birthdays.dat");

    int i = 1;

    //Default case with no arguments
    //Return any birthdays in next 30 days
    if (argc == 1)
    {
        QDate currDate = QDate::currentDate();
        data.nextBdays(currDate, 30);
    }

    //Namespec
    if (argc == 2)
    {
        QString substr = argv[i];
        //try
        {
            data.namespec(substr, fail);
        }
    }
    //Case to add or set birthday
    else if(QString::compare("-a",argv[i])==0)
    {
        try{
        i++;
        QString dateIn = argv[i];
        QDate date = QDate::fromString(dateIn, "yyyy-MM-dd");
        if (!date.QDate::isValid())
            throw "Invalid Argument(Invalid date)";
        i++;
        QString name = argv[i];
        Record humanIn(name,date);

        data.addPerson(humanIn);

        data.writeFile("birthdays.dat");
        }
        catch(const char* exc)
        {
            std::cerr << exc <<endl;
            return EXIT_FAILURE;
        }
    }
    //Case printing birthdays coming up in next xx days
    //chronilogical
    else if(QString::compare("-n",argv[i])==0)
    {
        i++;
        int range = atoi(argv[i]);
        QDate currDate = QDate::currentDate();
        data.nextBdays(currDate,range);
    }
    //Case deleting entries with certain bday
    else if(QString::compare("-d",argv[i])==0)
    {
        i++;
        QString test = argv[i];
        if (test[0].isDigit())
        {
            QDate dateIn = QDate::fromString(test, "yyyy-MM-dd");
            data.deleteByDate(dateIn, fail);
        }
        else
        {
            QString nameIn = argv[i];
            data.deleteByName(nameIn, fail);
        }

       data.writeFile("birthdays.dat");

    }
    //Case printing birthdays coming up in next xx days of name's bday
    //chronilogical
    else if(QString::compare("-m",argv[i])==0)
    {
        i++;
        QString name = argv[i];
        QDate dayIn = data.findBday(name, fail);

        i++;
        int range = atoi(argv[i]);
        data.nextBdays(dayIn, range);

    }
    //Case with date range
    //chronilogical
    else if (QString::compare("-r", argv[i])==0)
    {
       i++;
       QDate day1 = QDate::fromString(argv[i],"yyyy-MM-dd");
       i++;
       QDate day2 = QDate::fromString(argv[i],"yyyy-MM-dd");

       int range = day1.daysTo(day2);

       data.nextBdays(day1, range);
    }
    //Case printing birthdays between name1 and name2's bday
    //alphabetical
    else if(QString::compare("-q",argv[i])==0)
    {
        i++;
        QString name = argv[i];
        QDate day1 = data.findBday(name, fail);
        i++;
        name = argv[i];
        QDate day2 = data.findBday(name,fail);

        if(fail)                        //check if code failed
            return EXIT_FAILURE;

        int range = day1.daysTo(day2);

        data.nextBdays(day1, range);
    }

    //catch(const std::invalid_argument& ia)
    //{
    //    out << "invalid argument" << endl;
    //}

    return 0;
}





