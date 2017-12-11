#pragma once

#ifndef BANKACCOUNT_SIDDHANT_H
#define BANKACCOUNT_SIDDHANT_H

#include <iostream>
#include "Account_Siddhant.h"
using namespace std;

class BankAccount : public Account
{

private:
	double depositAmount = 0.0;
	double withdrawalAmount = 0.0;

public:
	BankAccount();
	~BankAccount();
	void setBalance();
	double getBalance();
	void viewBalance();
	void depositCashAmount();
	void withdrawCashAmount();
	void printHistory();
};

#endif