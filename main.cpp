//Katherine Hogue
//Applied HW1

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

        data.namespec(substr, fail);

        if(fail)                        //check if code failed
            return EXIT_FAILURE;
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
            try{
                QDate dateIn = QDate::fromString(test, "yyyy-MM-dd");
                data.deleteByDate(dateIn, fail);
                if(!dateIn.QDate::isValid())
                {
                    fail = true;
                    throw "Invalid Arguments(Date not Valid)";
                }
            }
            catch(const char* exc)
            {
                std::cerr << exc <<endl;
            }

            if(fail)                        //check if code failed
                return EXIT_FAILURE;
        }
        else
        {
            QString nameIn = argv[i];
            data.deleteByName(nameIn, fail);
            if(fail)                        //check if code failed
                return EXIT_FAILURE;
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

        if(fail)                        //check if code failed
            return EXIT_FAILURE;

        i++;
        int range = atoi(argv[i]);
        data.nextBdays(dayIn, range);

    }
    //Case with date range
    //chronilogical
    else if (QString::compare("-r", argv[i])==0)
    {
        try{
        i++;
        QDate day1 = QDate::fromString(argv[i],"yyyy-MM-dd");
        if(!day1.QDate::isValid()){
            throw "Invalid Input(Invalid Date)";
        }
        i++;
        QDate day2 = QDate::fromString(argv[i],"yyyy-MM-dd");
        if(!day2.QDate::isValid()){
            throw "Invalid Input(Invalid Date)";
        }
        int range = day1.daysTo(day2);

        data.nextBdays(day1, range);
        }
        catch(const char* exc)
        {
            std::cerr << exc << endl;
            return EXIT_FAILURE;
        }
    }
    //Case printing birthdays between name1 and name2's bday
    //alphabetical
    else if(QString::compare("-q",argv[i])==0)
    {
        i++;
        QString name = argv[i];
        QDate day1 = data.findBday(name, fail);

        if(fail)                        //check if code failed
            return EXIT_FAILURE;

        i++;
        name = argv[i];
        QDate day2 = data.findBday(name,fail);

        if(fail)                        //check if code failed
            return EXIT_FAILURE;

        int range = day1.daysTo(day2);

        data.nextBdays(day1, range);
    }


    return 0;
}





