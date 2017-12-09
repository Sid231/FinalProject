#pragma once

#ifndef ACCOUNTNODE_H
#define ACCOUNTNODE_H

#include <iostream>
using namespace std;

class accountNode {

private:
	string company;
	int numberOfShares;
	double amount;
	double amountPerShare;
	double currentPortfolioNodeVal;
	string date;
	accountNode *prev;
	accountNode *next;

public:
	friend class StockAccount;
	accountNode(string, double, string);
};

#endif