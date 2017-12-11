/*
NAME: KUMAR SIDDHANT
DATE: 12/11/2017
PROJECT: ACCOUNT MANAGEMENT SYSTEM
FILE: BANKACCOUNT_SIDDHANT.H
*/
#pragma once
#ifndef STOCKACCOUNT_SIDDHANT_H
#define STOCKACCOUNT_SIDDHANT_H

#include <iostream>
#include "Account_Siddhant.h"
#include "accountNode_Siddhant.h"
#include<map>
using namespace std;

//DERIVED CLASS STOCKACCOUNT
class StockAccount : public Account
{

private:

	//LINKEDLIST NODE POINTERS
	accountNode *previousPointer = NULL;
	accountNode *tailPointer;
	accountNode *headPointer;

	//STOCK DATA
	string company;
	double amount;
	string date;

	//PORTFOLIO DATA
	double portValue;
	double portValue_array[100];
	string timeStamp_array[100];
	int sizeOfPortValueArray;
	int sizeOfList;

	//MAPS TO STORE THE DATA FROM THE FILES
	map<string, double> stockDataMap;
	map<string, int> portfolioDataMap;

public:

	//CONSTRUCTOR
	StockAccount();

	//DESTRUCTOR
	~StockAccount();

	//METHOD THAT DISPLAYS THE PRICE OF THE STOCK
	void displayStockPrice();

	//METHOD THAT SETS THE CASH BALANCE AMOUNT
	void setBalance();

	//METHOD THAT FETCHES THE CASH BALANCE AMOUNT
	double getBalance(); 

	//METHOD THAT DISPLAYS THE CURRENT PORTFOLIO DETAILS
	void displayCurrentPortfolio();

	//METHOD TO BUY SHARES
	void buyShares();

	//METHOD TO SELL SHARES
	void sellShares();

	//METHOD TO SORRT THE LINKEDLIST DATA
	bool sortLinkedListStockData();

	//METHOD TO RETRIEVE DATA FROM THE FILE TO THE LINKEDLIST
	void retrieveDataToLinkedList();

	//METHOD TO SAVE THE PORTFOLIO DATA TO THE FILE
	void savePortfolioDataToFile();

	//METHOD TO RETRIEVE THE PORTFOLIO DATA FROM THE FILE
	void retrievePortfolioValue();

	//METHOD TO SET THE PORTFOLIO VALUE
	void setPortfolioValue();

	//METHOD TO PRINT THE HISTORY OF TRANSACTION
	void printHistory();

	//METHOD TO UPDATE THE LIST SIZE OF THE PORTFOLIO
	void updateSizeOfList(int);

	//METHOD TO PLOT THE GRAPH
	void viewGraph();
};

#endif