#pragma once
#ifndef STOCKACCOUNT_SIDDHANT_H
#define STOCKACCOUNT_SIDDHANT_H

#include <iostream>
#include "Account_Siddhant.h"
#include "accountNode_Siddhant.h"
#include<map>
using namespace std;

class StockAccount : public Account
{

private:

	accountNode *previousPointer = NULL;
	accountNode *tailPointer;
	accountNode *headPointer;

	string company;
	double amount;
	string date;

	double portValue;
	double portValue_array[100];
	string timeStamp_array[100];
	int sizeOfPortValueArray;

	int sizeOfList;

	map<string, double> stockDataMap;
	map<string, int> portfolioDataMap;

public:
	StockAccount();
	~StockAccount();

	void displayStockPrice();
	void setBalance();
	double getBalance(); 
	void displayCurrentPortfolio();
	void buyShares();
	void sellShares();
	bool sortLinkedListStockData();
	void retrieveDataToLinkedList();
	void savePortfolioDataToFile();
	void retrievePortfolioValue();
	void setPortfolioValue();

};

#endif