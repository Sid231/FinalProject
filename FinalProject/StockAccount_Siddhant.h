#pragma once
#ifndef STOCKACCOUNT_SIDDHANT_H
#define STOCKACCOUNT_SIDDHANT_H

#include <iostream>
#include "Account_Siddhant.h"
#include "accountNode.h"
using namespace std;

class StockAccount_Siddhant : public Account_Siddhant
{

private:

public:
	StockAccount_Siddhant();
	~StockAccount_Siddhant();

	void displayStockPrice(accountNode *);

};

#endif