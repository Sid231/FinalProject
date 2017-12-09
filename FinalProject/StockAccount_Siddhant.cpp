#include "StockAccount_Siddhant.h"
#include "accountNode_Siddhant.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
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

	string companySymbol;
	cout << "Enter the company symbol of the stock you want to check" << endl;
	cin >> companySymbol;
	bool symbolFound = false;

	for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); ++it) {
		if (companySymbol == it->first) {
			cout << left << setw(20) << "Company-Symbol";
			cout << left << setw(20) << "Price per Share"<<endl;
			cout << left << setw(20) << it->first;
			cout << left << setw(20) << it->second << endl;
			symbolFound = true;
		}
	}

	if (symbolFound == false) {
		cout << "Data not found in the database of the Stock data" << endl;
	}
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

void StockAccount::displayCurrentPortfolio() {
	accountNode *currentNode = headPointer;
	setBalance();
	double stockValue = 0.0;
	
	while (currentNode != NULL) {
		for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); ++it) {
			if (currentNode->company == it->first) {
				currentNode->amountPerShare = it->second;
				currentNode->currentPortfolioNodeVal = currentNode->numberOfShares * currentNode->amountPerShare;
			}
		}
		currentNode = currentNode->next;
	}
	this->sortList();

	if (sizeOfList > 0) {
		cout << left << setw(20) << "Company-Symbol";
		cout << left << setw(20) << "Shares";
		cout << left << setw(20) << "Price per Share (in $)";
		cout << left << setw(20) << "Total value (in $)" << endl;

		currentNode = headPointer;
		while (currentNode != NULL) {
			cout << left << setw(20) << currentNode->company;
			cout << left << setw(20) << currentNode->numberOfShares;
			cout << left << setw(20) << currentNode->amountPerShare;
			cout << left << setw(20) << currentNode->currentPortfolioNodeVal << endl;

			stockValue = stockValue + currentNode->currentPortfolioNodeVal;
			currentNode = currentNode->next;
		}

		portValue = getCashBalance() + stockValue;
		cout << "Cash Balance is : $" << getCashBalance() << endl;
		cout << "Stock Balance is : $" << stockValue << endl;
		cout << "Total Portfolio value is : $" << portValue << endl;
	
		portValue_array[sizeOfPortValueArray] = portValue;
		sizeOfPortValueArray++;
	}

	if (sizeOfList == 0) {
		portValue = getCashBalance();
		cout << "Shares are not available!!" << endl;
	}
}

void StockAccount::sortList() {

}