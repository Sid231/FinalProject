#include "StockAccount_Siddhant.h"
#include "accountNode_Siddhant.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<map>
using namespace std;

StockAccount::StockAccount(){

	tailPointer = NULL;
	headPointer = NULL;
	ifstream file;
	string data;
	stringstream stream;
	ifstream listSizeInputStream;
	string content = "";
	double amount = 0.0;
	int i = 0;

	//Setting the cash balance
	setBalance();
	
	if (rand()%2 == 0) {
		file.open("Result_1.txt");
	}
	else {
		file.open("Result_2.txt");
	}

	if (file.is_open()) {
		while (!file.eof()) {
			getline(file, data);
			stream << data;
			stream >> company >> amount;
			stockDataMap.insert(pair<string, double>(company, amount));
			stream.str("");
			stream.clear();
		}
	}
	file.close();

	listSizeInputStream.open("stock_list_size_data.txt");
	for (i = 0; listSizeInputStream.eof() != true; i++) {
		content += listSizeInputStream.get();
	}
	i--;
	content.erase(content.end() - 1);
	if ((content != "") || (content != " ")) {
		sizeOfList = stoi(content);
	}
	listSizeInputStream.close();
	if (sizeOfList != 0) {
		//TODO
	}
}


StockAccount::~StockAccount()
{
}

void StockAccount::displayStockPrice() {

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
	cashFileStream.close();
}