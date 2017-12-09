#pragma once
#ifndef STOCKACCOUNT_SIDDHANT_H
#define STOCKACCOUNT_SIDDHANT_H

#include <iostream>
#include "Account_Siddhant.h"
#include "accountNode_Siddhant.h"
using namespace std;

class StockAccount : public Account
{

private:

	accountNode *previousPointer = NULL;
	accountNode *tailPointer = NULL;
	accountNode *headPointer = NULL;

public:
	StockAccount(accountNode *);
	~StockAccount();

	void displayStockPrice(accountNode *);
	void retrieveCashBalanceFromFile();

};

#endif