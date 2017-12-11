#include "BankAccount_Siddhant.h"
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <string>
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
	cout << "The present cash balance in your account is : $" << getBalance() << endl;
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

	balanceOutputWriteStream.open("cashBalance.txt");
	balanceOutputWriteStream << getCashBalance();
	balanceOutputWriteStream.close();

}

void BankAccount::withdrawCashAmount() {

	ofstream balanceOutputWriteStream;
	ofstream bankTransationOutputStream;

	cout << "Enter the amount $ to be withdrawn :";
	cin >> withdrawalAmount;

	setBalance();

	if (getCashBalance() > 0) {
		if (withdrawalAmount > getCashBalance()) {
			cout << "Sorry you dont have this much amount in your account!" << endl;
			return;
		}
		else {
			setCashBalance(getCashBalance() - withdrawalAmount);
			cout << "The amount withdrawn successfully from your account is $" << withdrawalAmount << " and the amount available in your account is $" << getCashBalance() << endl;

			//GENERATE THE TIME STAMP 
			time_t timev;
			struct tm now;
			char timeBuffer[100];
			time(&timev);
			localtime_s(&now, &timev);
			strftime(timeBuffer, 100, "%d-%m-%Y %I:%M:%S", &now);
			string strData(timeBuffer);

			balanceOutputWriteStream.open("cashBalance.txt");
			balanceOutputWriteStream << getCashBalance();
			balanceOutputWriteStream.close();

			//WRITE THE TRANSACTION TO BANK_TRANSACTION_HISTORY.TXT FILE
			bankTransationOutputStream.open("bank_transaction_history.txt", ios::app);
			bankTransationOutputStream << endl << left << setw(25) << "Withdrawal";
			bankTransationOutputStream << left << setw(25) << "$";
			bankTransationOutputStream << left << setw(25) << withdrawalAmount;
			bankTransationOutputStream << left << setw(25) << strData;
			bankTransationOutputStream << left << setw(25) << "$" << getCashBalance();
			bankTransationOutputStream.close();

			return;
		}
	}
	else {
		cout << "Account balance is null... please deposit amounts!" << endl;
		return;
	}
}

void BankAccount::printHistory() {
	
	ifstream bankTransationInputStream;
	string historyData;

	cout << endl << left << setw(10) << "Transaction";
	cout << left << setw(10) << "Amount";
	cout << left << setw(10) << "Price per Share (in $)";
	cout << left << setw(10) << "Value (in $)";
	cout << left << setw(10) << "Timestamp" << endl;

	bankTransationInputStream.open("bank_transaction_history.txt");

	if (bankTransationInputStream.is_open()) {
		while (!bankTransationInputStream.eof()) {
			while (getline(bankTransationInputStream, historyData)) {
				cout << historyData << endl;
			}
		}
	}
	bankTransationInputStream.close();
}