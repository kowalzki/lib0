#include "chldlbr.h"
#include <iostream>
#include <time.h>

void remakeBk();
std::string generateRandString(int len = 0);
ChildrenBook generateBook(int minAge);
ChildrenLibraryHall generateHall(int minAge, int count = -1);
ChildrenLibrary generateLibrary(int hallsNum = -1, int maxMinAge = 21);


int main()
{
    srand(time(NULL));
    ChildrenLibrary libka;
    std::cout << "Library v1.0\n";
    libka = generateLibrary();
    libka.printLib();
    std::cout << "____________________________________\n" << std::endl;
    
    //Добавление книги в зал
    std::cout << "Library v1.1. Add book to the Hall\n";
    libka.getHallInd(1).add(generateBook(10), 1);
    libka.printLib();
    std::cout << "____________________________________\n" << std::endl;

    //Добавление книги в библиотеку
    std::cout << "Library v1.2. Add book to the library\n";
    libka.addBookInd(10, generateBook(8));
    libka.printLib();
    std::cout << "____________________________________\n" << std::endl;

    //Изменение книги
    std::cout << "Library v1.3. Change book to Pushkin\n";
    libka.getHallInd(2).remakeBook(1, "Pushkin", "CHANGED", 1998, 950, 12);
    libka.printLib();
    std::cout << "____________________________________\n" << std::endl;

    //Изменение зала
    std::cout << "Library v1.4. Change hall to something\n";
    ChildrenBook* newHall = new ChildrenBook[5];
    for (int i = 0; i < 5; i++)
    {
        newHall[i] = generateBook(9);
    }
    libka.changeHall(1, "9+", 5, newHall);
    libka.printLib();
    std::cout << "____________________________________\n" << std::endl;
    
    //Удаляем Пушкина
    std::cout << "Library v1.5. Say goodbye to Pushkin\n";
    libka.getHallInd(2).deleteBook(1);
    libka.printLib();
    std::cout << "Library v2.0 is ready|\n";
    std::cout << "_____________________| \n \n" << std::endl;

    //Лучшая книга
    std::cout << "Best book:" << std::endl;
    libka.getBestBook().printB();

    system("pause");
    return 0;
}


std::string generateRandString(int len)
{
    std::string t = "";
    if (!len) {
        len = rand() % 5 + 3;
    }
    for (int i = 0; i < len; i++) {
        t += char(rand() % 26 + 97);
    }
    return t;
}

ChildrenBook generateBook(int minAge)
{
    ChildrenBook cb;
    cb.setAthr(generateRandString());
    cb.setName(generateRandString());
    cb.setPrice(rand() % 100 + (rand() % 100 * 1. / 100));
    cb.setYear(1900 + rand() % 121);
    cb.setMinAge(minAge);
    return cb;
}

ChildrenLibraryHall generateHall(int minAge, int count)
{
    if (count == -1) {
        count = rand() % 3 + 3;
    }
    ChildrenLibraryHall clh;
    std::string name = "";
    if (minAge < 100)
    {
        if (minAge < 10)
        {
            name += char(minAge + 48);
        }
        else
        {
            name += char(minAge / 10 + 48);
            name += char(minAge % 10 + 48);
        }
        name += '+';
    }
    clh.setZName(name);
    for (int i = 0; i < count; i++)
    {
        clh.add(generateBook(minAge));
    }
    return clh;
}

ChildrenLibrary generateLibrary(int hallsNum, int maxMinAge)
{
    if (hallsNum == -1)
    {
        hallsNum = 3;// rand() % 4 + 3;
    }
    ChildrenLibrary cl;
    ChildrenLibraryHall hall;
    for (int i = 1, j = 0; j <= maxMinAge; i++, j = int((maxMinAge * 1.0 / hallsNum) * i))
    {
        hall = generateHall(j);
        cl.add(hall);
    }
    return cl;
}