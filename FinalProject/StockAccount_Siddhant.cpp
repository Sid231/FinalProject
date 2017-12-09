#include "StockAccount_Siddhant.h"
#include "accountNode_Siddhant.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

StockAccount::StockAccount(accountNode *head){

	tailPointer = NULL;
	headPointer = NULL;
	ifstream file;

	//Setting the cash balance
	setBalance();
	
	if (rand()%2 == 0) {
		file.open("Result_1.txt");
	}
	else {
		file.open("Result_2.txt");
	}

	if (file.is_open) {

	}

}


StockAccount::~StockAccount()
{
}

void StockAccount::displayStockPrice(accountNode *head) {

}

//TO GET THE CASH AMOUNT BALANCE
double StockAccount::getBalance() {
	return getCashBalance();
}

//TO SET THE CASH AMOUNT BALANCE
void StockAccount::setBalance() {

	ifstream cashFileStream;
	string content = "";
	double amount = 0.0;
	int i=0;

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
	
}