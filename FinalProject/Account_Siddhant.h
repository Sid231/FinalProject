/*
NAME: KUMAR SIDDHANT
DATE: 12/11/2017
PROJECT: ACCOUNT MANAGEMENT SYSTEM
FILE: ACCOUNT_SIDDHANT.H
*/
#pragma once

#ifndef ACCOUNT_SIDDHANT_H
#define ACCOUNT_SIDDHANT_H

#include<iostream>
using namespace std;

//ABSTRACT BASE CLASS ACCOUNT
class Account
{

private:
	//CASH BALANCE
	double cashBalance;
public:
	//CASHBALANCE CONSTRUCTOR
	Account(double = 0.0);

	//CASHBALANCE DESTRUCTOR
	~Account();

	//CASH BALANCE GETTER
	double getCashBalance() {
		return cashBalance;
	}

	//CASH BALANCE SETTER
	void setCashBalance(double balance) {
		cashBalance = balance;
	}

};

#endif