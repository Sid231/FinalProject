#include "BankAccount_Siddhant.h"
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include<time.h>
#include <iomanip>
#include <fstream>
using namespace std;

BankAccount::BankAccount()
{
	setBalance();
	depositAmount = 0.0;
	withdrawalAmount = 0.0;
}


BankAccount::~BankAccount()
{
}

void BankAccount::setBalance() {
	ifstream cashFileStream;
	string content = "";
	double amount = 0.0;
	int i = 0;

	cashFileStream.open("cashBalance.txt");
	if (!cashFileStream) {
		cerr << "Unable to open the file!!" << endl;
	}

	for (i = 0; cashFileStream.eof() != true; i++) {
		content += cashFileStream.get();
	}
	i--;
	content.erase(content.end() - 1);

	if ((content != "") || (content != " ")) {
		amount = ::atof(content.c_str());
		setCashBalance(amount);
	}
	else {
		setCashBalance(10000.0);
	}
	cashFileStream.close();
}

double BankAccount::getBalance() {
	return getCashBalance();
}

void BankAccount::viewBalance() {

	setBalance();
	cout << "The present cash balance in your account is : $" << getBalance << endl;
}

void BankAccount::depositCashAmount(){
	
	ofstream balanceOutputWriteStream;

	cout << "Enter the amount in $ you want to deposit :";
	cin >> depositAmount;
	setCashBalance(getCashBalance() + depositAmount);
	cout << "Congrats! An amount of $" << depositAmount << "is deposited in your account!" << endl;

	//GENERATE THE TIME STAMP 
	time_t timev;
	struct tm now;
	char timeBuffer[100];
	time(&timev);
	localtime_s(&now, &timev);
	strftime(timeBuffer, 100, "%d-%m-%Y %I:%M:%S", &now);
	string str(timeBuffer);

	balanceOutputWriteStream.open("balance_file.txt");
	balanceOutputWriteStream << getCashBalance();
	balanceOutputWriteStream.close();

}

void BankAccount::withdrawCashAmount() {

	cout << "Enter the amount to be withdrawn :";
	cin >> withdrawalAmount;



}