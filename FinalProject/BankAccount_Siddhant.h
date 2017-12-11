/*
NAME: KUMAR SIDDHANT
DATE: 12/11/2017
PROJECT: ACCOUNT MANAGEMENT SYSTEM
FILE: BANKACCOUNT_SIDDHANT.H
*/
#pragma once

#ifndef BANKACCOUNT_SIDDHANT_H
#define BANKACCOUNT_SIDDHANT_H

#include <iostream>
#include "Account_Siddhant.h"
using namespace std;

//DERIVED CLASS BANKACCOUNT
class BankAccount : public Account
{

private:
	//VARIABLE TO STORE THE AMOUNT DEPOSITTED
	double depositAmount = 0.0;

	//VARIABLE TP STORE THE AMOUNT TO BE WITHDRAWN
	double withdrawalAmount = 0.0;

public:

	//CONSTRUCTOR
	BankAccount();

	//DESTRUCTOR
	~BankAccount();

	//SETTER TO SET THE CASH BALANCE 
	void setBalance();
	
	//GETTER TO GET THE CASH BALANCE 
	double getBalance();
	
	//METHOD TO VIEW THE BALANCE
	void viewBalance();

	//METHOD TO DEPOSIT CASH AMOUNT TO THE BANK SYSTEM
	void depositCashAmount();
	
	//METHOD TO WITHDRAW CASH AMOUNT FROM THE BANK SYSTEM
	void withdrawCashAmount();
	
	//METHOD TO PRINT THE HISTORY OF THE TRANSACTION
	void printHistory();
};

#endif