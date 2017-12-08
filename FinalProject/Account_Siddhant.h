#pragma once

#ifndef ACCOUNT_SIDDHANT_H
#define ACCOUNT_SIDDHANT_H

#include<iostream>
using namespace std;

class Account_Siddhant
{

private:
	double cashBalance;
public:
	Account_Siddhant(double = 10000.0);
	~Account_Siddhant();

	double getCashBalance() const;
	void setCashBalance(double balance) {
		cashBalance = balance;
	}

};

#endif