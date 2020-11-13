#pragma once
#include <string>
#include <iostream>
#include "chldlbrhl.h"

class ChildrenLibrary
{
private:
	ChildrenLibraryHall* pCH;
	int amountOfHalls;
	
public:
	ChildrenLibrary()
	{
		this->pCH = nullptr;
		this->amountOfHalls = 0;
	}

	ChildrenLibrary(int amountOH, int* pAmountOB)
	{
		this->amountOfHalls = amountOH;
		this->pCH = new ChildrenLibraryHall[amountOfHalls];
		
		for (int i = 0; i < amountOH; i++)
		{
			ChildrenBook* ptm = new ChildrenBook[pAmountOB[i]];
			pCH[i].setPointer(ptm);
			pCH[i].setAmount(pAmountOB[i]);
		}

	}

	ChildrenLibrary(ChildrenLibraryHall* phalls, int amount)
	{
		this->amountOfHalls = amount;
		for (int i = 0; i < amount; i++)
		{
			this->pCH[i] = phalls[i];
		}
	}

	ChildrenLibrary(const ChildrenLibrary& copy)
	{
		this->amountOfHalls = copy.getAOH();
		this->pCH = new ChildrenLibraryHall[this->amountOfHalls];

		for (int i = 0; i < this->amountOfHalls; i++) {
			this->pCH[i] = copy.pCH[i];
		}
	}

	~ChildrenLibrary()
	{
		delete[] pCH;
		pCH = 0;
	}

	void add(ChildrenLibraryHall added)
	{	
		if (!pCH)
		{
			pCH = new ChildrenLibraryHall[amountOfHalls];
		}

        ChildrenLibraryHall* copy = new ChildrenLibraryHall[++amountOfHalls];

		for (int i = 0; i < amountOfHalls-1; i++) {
			copy[i] = pCH[i];
		}
		copy[amountOfHalls-1] = added;
        pCH = copy;
	}

	void changeHall(int ind, std::string newnme, int newamnt, ChildrenBook* newptr)
	{
		if (!pCH) {
			std::cout << "Error nullptr\n"; return;
		}
		this->pCH[ind].setAmount(newamnt);
		this->pCH[ind].setZName(newnme);
		this->pCH[ind].setPointer(newptr);
	}

	int getAOH() const
	{
		return this->amountOfHalls;
	}


	int getFAOB() // Сумма всех книг в либке
	{
		if (!pCH) {
			std::cout << "Error nullptr\n"; return 0;
		}
		int FAOB = 0;
		for (int i = 0; i < amountOfHalls; i++)
		{
			FAOB += pCH[i].getAmount();
		}
		return FAOB;
	}

	ChildrenLibraryHall getHalls()
	{
		return *pCH;
	}

	ChildrenLibraryHall& getHallInd(int ind) const
	{
		if (!pCH) {
			std::cout << "Error nullptr\n"; 
			ChildrenLibraryHall nwObj;
			return nwObj;
		}
		if (ind >= this->amountOfHalls) {
			ChildrenLibraryHall newH;
			return newH;
		}
		return this->pCH[ind];
	}


	ChildrenBook getBookInd(int index)
	{
		if (!pCH) {
			std::cout << "Error nullptr\n"; return ChildrenBook();
		}
		for (int i = 0; i < amountOfHalls; i++)
		{
			int lgh = pCH[i].getAmount();
			if (index >= lgh) {
				index -= lgh;
			}
			else {
				return pCH[i].getBook(index);
			}
		}
	}

	void printHallNames()
	{
		if (!pCH) {
			std::cout << "Error nullptr\n"; return;
		}
		for (int i = 0; i <= amountOfHalls; i++)
		{
			std::cout << std::endl << "Зал №1: " << pCH[i].getZName() 
				<< ". Количество книг в зале: " << pCH[i].getAmount() << std::endl;
		}
	}

	void addBookInd(int ind, ChildrenBook added)
	{
		for (int i = 0; i < amountOfHalls; i++)
		{
			int lgh = pCH[i].getAmount();
			if (ind >= lgh) {
				ind -= lgh;
			}
			else {
				pCH[i].add(added, ind);
			}
		}
	}

	void addBookInd(int ind)
	{
		for (int i = 0; i < amountOfHalls; i++)
		{
			int lgh = pCH[i].getAmount();
			if (ind >= lgh) {
				ind -= lgh;
			}
			else {
				pCH[i].deleteBook(ind);
			}
		}
	}

	ChildrenBook getBestBook()
	{
		if (!pCH) {
			std::cout << "Error nullptr\n"; return ChildrenBook();
		}
		ChildrenBook bb;
		for (int i = 0; i < amountOfHalls; i++)
		{
			if (bb.getPrice() < pCH[i].getBestBook().getPrice())
			{
				bb = pCH[i].getBestBook();
			}
		}
		return bb;
	}

	ChildrenLibrary operator= (const ChildrenLibrary copy)
	{
		if (this == &copy) return *this;
		if (copy.pCH == nullptr) {
			this->pCH = nullptr;
			this->amountOfHalls = 0;
			return *this;
		}
		this->amountOfHalls = copy.amountOfHalls;
		delete[] pCH;
		pCH = new ChildrenLibraryHall[copy.amountOfHalls];
		for (int i = 0; i < copy.amountOfHalls; i++)
		{
			this->pCH[i] = copy.pCH[i];
		}

		return *this;
	}

	void printLib()
	{
		if (!pCH) {
			std::cout << "Error nullptr\n"; return;
		}
		for (int i = 0; i < amountOfHalls; i++)
		{
			pCH[i].printHl();
			std::cout << std::endl;
		}
	}
};