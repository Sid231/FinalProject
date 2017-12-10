#pragma once

#ifndef ACCOUNTNODE_H
#define ACCOUNTNODE_H

#include <iostream>
using namespace std;

class accountNode {

private:
	string company;											//symbol
	int numberOfShares;										//number of shares
	double amountPerShareForSorting;						//price per share for sorting
	double amountPerShare;									//price per share
	double currentPortfolioNodeVal;							//total value of the stock
	string date;
	accountNode *prev;
	accountNode *next;

public:
	friend class StockAccount;
	accountNode(string, double, string);
};

#endif