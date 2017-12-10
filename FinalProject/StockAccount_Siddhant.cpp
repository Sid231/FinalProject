#include "StockAccount_Siddhant.h"
#include "accountNode_Siddhant.h"
#include <stdlib.h>
#include <iostream>
#include<time.h>
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
			cout << left << setw(20) << currentNode->company;									//print symbol
			cout << left << setw(20) << currentNode->numberOfShares;							//print number of shares
			cout << left << setw(20) << currentNode->amountPerShare;							//print price per share
			cout << left << setw(20) << currentNode->currentPortfolioNodeVal << endl;			//print total value of the stock

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

void StockAccount::buyShares() {

	string companySymbol;
	bool validCompanySymbolData = false;
	int numberOfShares;
	double maxAmtPay;
	double shareValueOfCompany;
	double totalAmount;
	ofstream cashFileOutputStream;
	ofstream bankTransationOutputStream;
	ofstream stockTransactionOutputStream;

	cout << "Enter the ticker symbol of the stock you want to buy" << endl;
	cin >> companySymbol;

	for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); ++it) {
		if (companySymbol == it->first) {
			validCompanySymbolData = true;
			break;
		}
	}

	if (validCompanySymbolData == true) {
		cout << "Enter the number of shares you want to buy" << endl;
		cin >> numberOfShares;
		cout << "Enter the maximum limit you are willing to pay per share" << endl;
		cin >> maxAmtPay;

		setBalance();

		for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); ++it) {
			if (companySymbol == it->first) {
				shareValueOfCompany = it->second;
			}
		}

		if (maxAmtPay >= shareValueOfCompany) {
			totalAmount = numberOfShares * shareValueOfCompany;
		}
		else {
			cout << "The max limit value entered is less than the value of the stock. Sorry you cant buy the stock with this amount!" << endl;
		}

		if (totalAmount > getCashBalance()) {
			cout << "Insufficient balance in your account! Please check again later!" << endl;
			return;
		}
		else {
			
			//STOCKS PURCHASING SUCCESS STATEMENTS
			cout << "Thanks for purchasing the stocks of " << companySymbol << endl;
			cout << "The number of shares you purchased are " << numberOfShares << " and the total amount you paid for those number of shares is " << totalAmount << endl;

			//GENERATE THE TIME STAMP OF THE PURCHASE OF STOCKS
			time_t timev;
			struct tm now;
			char timeBuffer[100];
			time(&timev);
			localtime_s(&now,&timev);
			strftime(timeBuffer, 100, "%d-%m-%Y %I:%M:%S", &now);
			string str(timeBuffer);


			//UPDATING THE AMOUNT BACK IN THE CASHBALANCE.TXT FILE
			setCashBalance(getCashBalance() - totalAmount);
			cashFileOutputStream.open("cashBalance.txt");
			cashFileOutputStream << getCashBalance();
			cashFileOutputStream.close();

			//WRITE THE TRANSACTION TO STOCK_TRANSACTION_HISTORY.TXT FILE
			stockTransactionOutputStream.open("stock_transaction_history.txt");
			stockTransactionOutputStream << left << setw(25) << "Purchase";
			stockTransactionOutputStream << left << setw(25) << companySymbol;
			stockTransactionOutputStream << left << setw(25) << numberOfShares;
			stockTransactionOutputStream << left << setw(25) << shareValueOfCompany;
			stockTransactionOutputStream << left << setw(25) << totalAmount;
			stockTransactionOutputStream << left << setw(25) << str;
			stockTransactionOutputStream.close();

			//WRITE THE TRANSACTION TO BANK_TRANSACTION_HISTORY.TXT FILE
			bankTransationOutputStream.open("bank_transaction_history.txt");
			bankTransationOutputStream << left << setw(25) << "Debited to Stock Account";
			bankTransationOutputStream << left << setw(25) << "$";
			bankTransationOutputStream << left << setw(25) << totalAmount;
			bankTransationOutputStream << left << setw(25) << str;
			bankTransationOutputStream << left << setw(25) << "$" << getCashBalance();
			bankTransationOutputStream.close();

			//UPDATE LINKEDLIST
			accountNode *newNode;
			if ((headPointer == NULL) && (tailPointer == NULL)) {
				//CREATE THE FIRST NODE : POINT HEAD AND TAIL TO THE SAME NODE
				tailPointer = newNode;
				headPointer = newNode;
				newNode->company = companySymbol;
				newNode->numberOfShares = numberOfShares;
				newNode->amountPerShare = shareValueOfCompany;
			}
			else {
				//UPDATE EXISTING NODES
				accountNode *tempNode = headPointer;
				while (tempNode != NULL) {
					//CHECK IF STOCK ALREADY ADDED BY THE USER IN THE PAST
					if (companySymbol == tempNode->company) {
						//THE STOCK WAS ALREADY EXISTING IN THE PAST
						//UPDATE THE NUMBER OF SHARES
						tempNode->numberOfShares = tempNode->numberOfShares + numberOfShares;
						return;
					}
					tempNode = tempNode->next;
				}

				//NEW NODE ADDITION AT THE END OF THE LIST
				accountNode *tempTailPointer;
				tempTailPointer = tailPointer;
				tailPointer->next = newNode;
				tailPointer = newNode;
				tailPointer->prev = tempTailPointer;
				newNode->company = companySymbol;
				newNode->numberOfShares = numberOfShares;
				newNode->amountPerShare = shareValueOfCompany;
			}
			//UPDATE THE SIZE OF THE LINKED LIST
			sizeOfList++;
		}

	}
	else{
		cout << "The ticker symbol of the stock you entered is invalid!" << endl;
		return;
	}


}