#pragma once

#ifndef ACCOUNT_SIDDHANT_H
#define ACCOUNT_SIDDHANT_H

#include<iostream>
using namespace std;

class Account
{

private:
	double cashBalance;
public:
	Account(double = 0.0);
	~Account();

	double getCashBalance() {
		return cashBalance;
	}
	void setCashBalance(double balance) {
		cashBalance = balance;
	}

};

#endif