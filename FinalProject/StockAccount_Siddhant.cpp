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

	//Setting the cash balance
	retrieveCashBalanceFromFile();

}


StockAccount::~StockAccount()
{
}

void StockAccount::displayStockPrice(accountNode *head) {

}

void StockAccount::retrieveCashBalanceFromFile() {

	ifstream inFileStream;
	char *stringBal;
	char *tempData;
	inFileStream.open("cashBalance.txt");

	if (!inFileStream) {
		cerr << "Unable to open the file!!" << endl;
	}

	while (inFileStream >> tempData) {
		strcat(stringBal, tempData);
	}

	if ((stringBal != "") && (stringBal != " ")) {
		setCashBalance(atof(stringBal));
	}
	else {
		setCashBalance(10000.0);
	}
	


}