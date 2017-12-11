/*
NAME: KUMAR SIDDHANT
DATE: 12/11/2017
PROJECT: ACCOUNT MANAGEMENT SYSTEM
FILE: BANKACCOUNT_SIDDHANT.CPP
*/
#include "BankAccount_Siddhant.h"
#include <iostream>
#include <stdlib.h>
#include <iostream>
#include <string>
#include<time.h>
#include <iomanip>
#include <fstream>
using namespace std;

//IMPLEMENTATION OF THE CONSTRUCTOR
BankAccount::BankAccount()
{
	setBalance();
	depositAmount = 0.0;
	withdrawalAmount = 0.0;
}

//IMPLEMENTATION OF THE DESTRUCTOR
BankAccount::~BankAccount()
{
}

//SET CASH BALANCE
void BankAccount::setBalance() {
	ifstream cashFileStream;
	string content = "";
	double amount = 0.0;
	int i = 0;

	//OPEN THE CASHBALANCE.TXT FILE
	cashFileStream.open("cashBalance.txt");
	if (!cashFileStream) {
		cerr << "Unable to open the file!!" << endl;
	}

	//CASHBALANCE.TXT FILE STREAM ITERATION LETTER BY LETTER
	for (i = 0; cashFileStream.eof() != true; i++) {
		content += cashFileStream.get();
	}
	i--;
	content.erase(content.end() - 1);

	//SET THE CASH AMOUNT
	if ((content != "") || (content != " ")) {
		amount = ::atof(content.c_str());
		setCashBalance(amount);
	}
	else {
		setCashBalance(10000.0);
	}
	//CLOSE THE FILE
	cashFileStream.close();
}

//RETRIEVE CASH BALANCE
double BankAccount::getBalance() {
	return getCashBalance();
}

//DISPLAY THE CURRENT CASH AMOUNT BALANCE AVAILABLE IN THE ACCOUNT
void BankAccount::viewBalance() {

	setBalance();
	cout << "The present cash balance in your account is : $" << getBalance() << endl;
}

//METHOD TO DEPOSIT CASH
void BankAccount::depositCashAmount(){
	
	ofstream balanceOutputWriteStream;
	ofstream bankTransationOutputStream;

	cout << "Enter the amount in $ you want to deposit :";
	cin >> depositAmount;
	setCashBalance(getCashBalance() + depositAmount);
	cout << "Congrats! An amount of $" << depositAmount << " is deposited in your account!" << endl;

	//GENERATE THE TIME STAMP 
	time_t timev;
	struct tm now;
	char timeBuffer[100];
	time(&timev);
	localtime_s(&now, &timev);
	strftime(timeBuffer, 100, "%d-%m-%Y %I:%M:%S", &now);
	string strData(timeBuffer);

	//UPDATE THE CASHBALANCE.TXT FILE WITH THE CURRENT CASH AMOUNT
	balanceOutputWriteStream.open("cashBalance.txt");
	balanceOutputWriteStream << getCashBalance();
	balanceOutputWriteStream.close();

	//WRITE THE TRANSACTION TO BANK_TRANSACTION_HISTORY.TXT FILE
	bankTransationOutputStream.open("bank_transaction_history.txt", ios::app);
	bankTransationOutputStream << endl << left << setw(30) << "Deposit";
	bankTransationOutputStream << left << setw(1) << "$";
	bankTransationOutputStream << left << setw(15) << depositAmount;
	bankTransationOutputStream << left << setw(25) << strData;
	bankTransationOutputStream << left << setw(1) << "$" << getCashBalance();
	bankTransationOutputStream.close();

}

//METHOD TO WITHDRAW CASH
void BankAccount::withdrawCashAmount() {

	ofstream balanceOutputWriteStream;
	ofstream bankTransationOutputStream;

	cout << "Enter the amount $ to be withdrawn :";
	cin >> withdrawalAmount;

	setBalance();

	//RUN ALGORITHMS IF THERE IS SOME CASH IN THE ACCOUNT
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

			//UPDATE THE CASHBALANCE.TXT FILE WITH THE CURRENT CASH AMOUNT
			balanceOutputWriteStream.open("cashBalance.txt");
			balanceOutputWriteStream << getCashBalance();
			balanceOutputWriteStream.close();

			//WRITE THE TRANSACTION TO BANK_TRANSACTION_HISTORY.TXT FILE
			bankTransationOutputStream.open("bank_transaction_history.txt", ios::app);
			bankTransationOutputStream << endl << left << setw(30) << "Withdrawal";
			bankTransationOutputStream << left << setw(1) << "$";
			bankTransationOutputStream << left << setw(15) << withdrawalAmount;
			bankTransationOutputStream << left << setw(25) << strData;
			bankTransationOutputStream << left << setw(1) << "$" << getCashBalance();
			bankTransationOutputStream.close();

			return;
		}
	}
	else {
		cout << "Account balance is null... please deposit amounts!" << endl;
		return;
	}
}

//PRINT THE TRANSACTION HISTORY
void BankAccount::printHistory() {
	
	ifstream bankTransationInputStream;
	string historyData;

	cout << endl << left << setw(30) << "Transaction";
	cout << left << setw(18) << "Amount($)";
	cout << left << setw(22) << "Timestamp";
	cout << left << setw(10) << "Balance($)" << endl;

	bankTransationInputStream.open("bank_transaction_history.txt");

	if (bankTransationInputStream.is_open()) {
		while (!bankTransationInputStream.eof()) {
			while (getline(bankTransationInputStream, historyData)) {
				cout << historyData << endl;
			}
		}
	}
	cout << endl;
	bankTransationInputStream.close();
}