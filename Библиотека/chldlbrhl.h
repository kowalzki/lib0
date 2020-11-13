#ifndef CHLDLBRHL_H
#define CHLDLBRHL_H
#include <string>
#include <iostream>
#include "chldbk.h"
#include <time.h>
#include <iomanip>

class ChildrenLibraryHall
{
private:
    std::string z_name;
    ChildrenBook *pCB;
    int amount;

public:
    ChildrenLibraryHall()
    {
        this->z_name = "Not Defined";
        this->pCB = nullptr;
        amount = 0;
    }
    ChildrenLibraryHall(std::string z_name, int amount)
    {
        this->z_name = z_name;
        this->amount = amount;
        this->pCB = new ChildrenBook[amount];
    }

    ChildrenLibraryHall(std::string z_name, int amount, ChildrenBook *pbooks)
    {
        this->z_name = z_name;
        this->amount = amount;
        this->pCB = new ChildrenBook[amount];
        for (int i=0; i<amount; i++)
        {
            this->pCB[i] = pbooks[i];
        }
    }

    ChildrenLibraryHall(const ChildrenLibraryHall&  copy)
    {
        this->z_name = copy.getZName();
        this->amount = copy.getAmount();
        this->pCB = new ChildrenBook[this->amount];

        for (int i=0; i<this->amount; i++)
        {
            this->pCB[i] = copy.pCB[i];
        }
    }
    
    ~ChildrenLibraryHall()
    {
        delete[] pCB;
        pCB = nullptr;
    }

   
    void setPointer(ChildrenBook* p)
    {
        this->pCB = p;
    }

    void add(ChildrenBook book)
    {
        ChildrenBook* arr = new ChildrenBook[getAmount()+1];
        for (int i = 0; i <= this->amount - 1; i++)
        {
            arr[i] = pCB[i];
        }
        arr[this->amount] = book;
        delete[] pCB;
        pCB = arr;
        this->amount++;
    }

    void deleteBook(int ind)
    {
        if (ind < 0 || ind >= amount || !pCB) {
            return;
        }
        ChildrenBook* copy = new ChildrenBook[amount - 1];
        for (int iWr = 0, iRd = 0; iRd < this->amount; iWr++, iRd++) {
            if (iRd != ind) {
                copy[iWr] = this->pCB[iRd];
            }
            else {
                iWr--;
            }
        }

        this->amount--;
        delete[] this->pCB;
        this->pCB = copy;
        if (this->amount == 0) {
            pCB = nullptr;
        }
    }

    void add(ChildrenBook book, int ind)
    {
        this->amount++;
        ChildrenBook* copy = new ChildrenBook[amount];
        for (int i = 0, k = 0; k < this->amount; i++, k++)
        {
            if (k != ind)
            {
                copy[k] = this->pCB[i];
            }
            else
            {
                copy[k] = book;
                i--;
            }
        }
        delete[] this->pCB;
        this->pCB = copy;
    }

    ChildrenBook getBook(int ind) const
    {
        if (!pCB) {
            std::cout << "Error nullptr\n"; return ChildrenBook();
        }
        if (ind >= this->amount)
        {
            ChildrenBook t;
            return t;
        }
        return this->pCB[ind];
    }

    
    void remakeBook(int n, std::string athr, std::string name, int year, int price, int minAge)
    {
        if (!pCB) {
            std::cout << "Error nullptr\n"; return;
        }
        pCB[n].setAthr(athr);
        pCB[n].setName(name);
        pCB[n].setYear(year);
        pCB[n].setPrice(price);
        pCB[n].setMinAge(minAge);
    }

    int getAmount() const
    {
        return this->amount;
    }

    std::string getZName() const
    {
        return this->z_name;
    }

    void setAmount(int amount)
    {
        this->amount = amount;
    }

    void setZName(std::string z_name)
    {
        this->z_name = z_name;
    }

    void showAllNames()
    {
        if (!pCB) {
            std::cout << "Error nullptr\n"; return;
        }
        for (int i = 0; i < this->amount; i++)
        {
            std::cout << pCB[i].getName() << ', ';
        }
    }

    double getFullPrice()
    {
        if (!pCB) {
            std::cout << "Error nullptr\n"; return 0;
        }
        double full = 0;
        for (int i = 0; i < this->amount; i++)
        {
            full += pCB[i].getPrice();
        }
        return full;
    }

    ChildrenLibraryHall operator= (const ChildrenLibraryHall copy)
    {
        if (this == &copy) return *this;
        if (copy.pCB == nullptr) {
            this->pCB = nullptr;
            this->amount = 0;
            return *this;
        }
        this->z_name = copy.z_name;
        this->amount = copy.amount;
        delete[] pCB;
        pCB = nullptr;
        pCB = new ChildrenBook[amount];
        
        for (int i = 0; i < amount; i++)
        {
            this->pCB[i] = copy.getBook(i);
        }
        return *this;
    }

    ChildrenBook getBestBook()
    {
        if (!pCB) {
            std::cout << "Error nullptr\n"; return ChildrenBook();
        }
        ChildrenBook bb;
        for (int i = 0; i < amount-1; i++)
        {
            if (bb.getPrice() < pCB[i].getPrice())
            {
                bb = pCB[i];
            }
        }
        return bb;
    }

    ChildrenBook& operator[](const int index)
    {
        return this->pCB[index];
    }

    void printHl()
    {        
        if (!pCB) {
            std::cout << "Error nullptr\n"; return;
        }
        std::cout << "Hall: " << z_name << "\n Amount of books: " << this->amount << std::endl;
        for (int i = 0; i < this->amount; i++)
        {
            std::cout << " Book #" << i << " author: " << std::setw(7) << this->pCB[i].getAthr() 
                << " name: " << std::setw(7) << this -> pCB[i].getName() 
                << " price: " << std::setw(7) << pCB[i].getPrice() << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif // CHLDLBRHL_H