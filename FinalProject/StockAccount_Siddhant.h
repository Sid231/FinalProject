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
	accountNode *tailPointer = NULL;
	accountNode *headPointer = NULL;

	string company;
	double amount;
	string date;

	int sizeOfList;

	map<string, double> stockDataMap;

public:
	StockAccount();
	~StockAccount();

	void displayStockPrice();
	void setBalance();
	double getBalance(); 
	void displayCurrentPortfolio();

};

#endif