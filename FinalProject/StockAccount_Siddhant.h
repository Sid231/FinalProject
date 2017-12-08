#pragma once
#ifndef STOCKACCOUNT_SIDDHANT_H
#define STOCKACCOUNT_SIDDHANT_H

#include <iostream>
#include "Account_Siddhant.h"
#include "accountNode.h"
using namespace std;

class StockAccount : public Account
{

private:

public:
	StockAccount(accountNode *);
	~StockAccount();

	void displayStockPrice(accountNode *);

};

#endif