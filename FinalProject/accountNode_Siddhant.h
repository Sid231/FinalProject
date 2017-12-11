/*
NAME: KUMAR SIDDHANT
DATE: 12/11/2017
PROJECT: ACCOUNT MANAGEMENT SYSTEM
FILE: ACCOUNT_NODE.H
*/
#pragma once

#ifndef ACCOUNTNODE_H
#define ACCOUNTNODE_H

#include <iostream>
using namespace std;

class accountNode {

private:
	string company;											//company symbol
	int numberOfShares;										//number of shares
	double amountPerShareForSorting;						//price per share for sorting
	double amountPerShare;									//price per share
	double currentPortfolioNodeVal;							//total value of the stock
	string date;											//store the timestamp
	accountNode *prev;										//pointer to the previous node
	accountNode *next;										//pointer to the next node

public:
	friend class StockAccount;
	accountNode();
};

#endif