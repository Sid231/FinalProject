/*
NAME: KUMAR SIDDHANT
DATE: 12/11/2017
PROJECT: ACCOUNT MANAGEMENT SYSTEM
FILE: BANKACCOUNT_SIDDHANT.CPP
*/


//MATLAB LIBS START
#pragma comment(lib,"libmx.lib")
#pragma comment(lib,"libmex.lib")
#pragma comment(lib,"libeng.lib")
#include<yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include<engine.h>
//MATLAB LIBS END

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

//CONSTRUCTOR
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

	//SET THE CASH BALANCE
	setBalance();
	
	//RANDOMLY SELECT A FILE TO DO ALL THE OPERATIONS
	if (rand()%2 == 0) {
		file.open("Result_1.txt");
	}
	else {
		file.open("Result_2.txt");
	}

	//CHECK IF THE FILE IS OPEN
	if (file.is_open()) {
		while (!file.eof()) {
			//READ THE LINE FROM THE FILE
			getline(file, data);
			//STORE THE READ DATA IN A STREAM
			stream << data;
			//STORE INTO THE COMPANY AND THE AMOUNT VARIABLES
			stream >> company >> amount;
			//STORE THE PAIR IN A MAP
			stockDataMap.insert(pair<string, double>(company, amount));
			//ALLOCATE A STRING VARIABLE
			stream.str("");
			//CLEAR THE STREAM
			stream.clear();
		}
	}
	//CLOSE THE FILES
	file.close();

	//GET THE SIZE OF LIST DATA FROM THE stock_list_size_data.txt FILE
	listSizeInputStream.open("stock_list_size_data.txt");
	for (i = 0; listSizeInputStream.eof() != true; i++) {
		content += listSizeInputStream.get();
	}
	i--;
	//ERASE GARBAGE ELEMENT AT THE END
	content.erase(content.end() - 1);
	if ((content != "") || (content != " ")) {
		sizeOfList = stoi(content);
	}
	
	listSizeInputStream.close();
	if (sizeOfList != 0) {
		//RETRIEVE DATA FROM FILE TO LINKED LIST IF THERE IS SOME HISTORY
		this->retrieveDataToLinkedList();

		//RETRIEVE PORTFOLIO DATA VALUES
		this->retrievePortfolioValue();
	}
}

//DESTRUCTOR
StockAccount::~StockAccount()
{
}

//DISPLAY THE STOCK PRICES
void StockAccount::displayStockPrice() {

	string companySymbol;
	cout << "Enter the company symbol of the stock you want to check" << endl;
	cin >> companySymbol;

	//ITERATE THROUGH THE MAP OF STOCK DATA
	for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {
		if (companySymbol == it->first) {
			cout << left << setw(20) << "Company-Symbol";
			cout << left << setw(20) << "Price per Share"<<endl;
			cout << left << setw(20) << it->first;
			cout << left << setw(20) << it->second << endl;
			return;
		}
	}
	//STOCK DATAASKED FOR IS NOT FOUND
	cout << "Data not found in the database of the Stock data" << endl << endl;
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

	//OPEN cashBalance.txt TO GE THE UPDATED CASH BALANCE AMOUNT IN THE ACCOUNT
	cashFileStream.open("cashBalance.txt");
	if (!cashFileStream) {
		cerr << "Unable to open the file!!" << endl;
	}

	for (i = 0; cashFileStream.eof() != true; i++) {
		content += cashFileStream.get();
	}
	i--;
	content.erase(content.end() - 1);

	//IF VALID DATA IS FOUND THEN STORE IT ELSE SET THE CASH BALANCE TO $10000.00
	if ((content != "") || (content != " ")) {
		amount = ::atof(content.c_str());
		setCashBalance(amount);
	}
	else {
		setCashBalance(10000.0);
	}
	cashFileStream.close();
}

//DISPLAY THE CURRENT PORTFOLIO
void StockAccount::displayCurrentPortfolio() {
	accountNode *currentNode = headPointer;
	setBalance();
	double stockValue = 0.0;
	
	while (currentNode != NULL) {
		for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {
			if (currentNode->company == it->first) {
				currentNode->amountPerShare = it->second;
				currentNode->currentPortfolioNodeVal = currentNode->numberOfShares * currentNode->amountPerShare;
				break;
			}
		}
		currentNode = currentNode->next;
	}
	this->sortLinkedListStockData();

	if (sizeOfList > 0) {
		cout << left << setw(20) << "Company-Symbol";
		cout << left << setw(20) << "Shares";
		cout << left << setw(20) << "Price per Share($)";
		cout << left << setw(20) << "Total value($)" << endl;

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

	for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {
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

		for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {
			if (companySymbol == it->first) {
				shareValueOfCompany = it->second;
				break;
			}
		}

		if (maxAmtPay >= shareValueOfCompany) {
			totalAmount = numberOfShares * shareValueOfCompany;
		}
		else {
			cout << "The max limit value entered is less than the value of the stock. Sorry you cant buy the stock with this amount!" << endl;
			return;
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
			stockTransactionOutputStream.open("stock_transaction_history.txt",ios::app);
			stockTransactionOutputStream << endl << left << setw(15) << "Buy";
			stockTransactionOutputStream << left << setw(15) << companySymbol;
			stockTransactionOutputStream << left << setw(7) << numberOfShares;
			stockTransactionOutputStream << left << setw(15) << shareValueOfCompany;
			stockTransactionOutputStream << left << setw(10) << totalAmount;
			stockTransactionOutputStream << left << setw(15) << str;
			stockTransactionOutputStream.close();

			if (sizeOfList > 0) {

			}

			//WRITE THE TRANSACTION TO BANK_TRANSACTION_HISTORY.TXT FILE
			bankTransationOutputStream.open("bank_transaction_history.txt", ios::app);
			bankTransationOutputStream << endl << left << setw(30) << "Debited to Stock Account";
			bankTransationOutputStream << left << setw(1) << "$";
			bankTransationOutputStream << left << setw(15) << totalAmount;
			bankTransationOutputStream << left << setw(15) << str;
			bankTransationOutputStream << left << setw(5) << "$" << getCashBalance();
			bankTransationOutputStream.close();

			//UPDATE LINKEDLIST
			accountNode *newNode = new accountNode();;
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
	updateSizeOfList(sizeOfList);
}

void StockAccount::sellShares() {

	string companySymbol;
	bool validCompanySymbolData = false;
	int numberOfShares;
	double minAmtPay;
	double shareValueOfCompany;
	double totalAmount;
	ofstream cashFileOutputStream;
	ofstream bankTransationOutputStream;
	ofstream stockTransactionOutputStream;
	accountNode *tempNode = headPointer;

	cout << "Enter the ticker symbol of the stock you want to sell" << endl;
	cin >> companySymbol;

 	while (tempNode != NULL) {
		if (tempNode->company == companySymbol) {
			validCompanySymbolData = true;
			break;
		}
		tempNode = tempNode->next;
	}

	if (validCompanySymbolData == true) {
		
		cout << "Enter the number of shares you want to sell" << endl;
		cin >> numberOfShares;
		cout << "Enter the minimum limit you are willing to pay per share" << endl;
		cin >> minAmtPay;

		if (sizeOfList > 0) {
			accountNode *traversalNode = headPointer;
			while (traversalNode != NULL) {
				if (traversalNode -> company == companySymbol) {
					if (numberOfShares <= traversalNode->numberOfShares) {
						traversalNode->numberOfShares = traversalNode->numberOfShares - numberOfShares;
						for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {
							if (companySymbol == it->first) {
								if (minAmtPay > it->second) {
									cout << "Minimum limit is more than the current stock share value!" << endl;
									return;
								}
								shareValueOfCompany = it->second;
							}
						}

						setBalance();
						totalAmount = numberOfShares * shareValueOfCompany;
						setCashBalance(getCashBalance() + totalAmount);

						//STOCKS PURCHASING SUCCESS STATEMENTS
						cout << "You sold the stocks of " << companySymbol << endl;
						cout << "The number of shares you sold are " << numberOfShares << " and the total amount you earned for those number of shares is " << totalAmount << endl;

						//GENERATE THE TIME STAMP OF THE PURCHASE OF STOCKS
						time_t timev;
						struct tm now;
						char timeBuffer[100];
						time(&timev);
						localtime_s(&now, &timev);
						strftime(timeBuffer, 100, "%d-%m-%Y %I:%M:%S", &now);
						string str(timeBuffer);

						//UPDATING THE AMOUNT BACK IN THE CASHBALANCE.TXT FILE
						cashFileOutputStream.open("cashBalance.txt");
						cashFileOutputStream << getCashBalance();
						cashFileOutputStream.close();

						//WRITE THE TRANSACTION TO STOCK_TRANSACTION_HISTORY.TXT FILE
						stockTransactionOutputStream.open("stock_transaction_history.txt", ios::app);
						stockTransactionOutputStream << endl << left << setw(15) << "Sell";
						stockTransactionOutputStream << left << setw(15) << companySymbol;
						stockTransactionOutputStream << left << setw(7) << numberOfShares;
						stockTransactionOutputStream << left << setw(15) << shareValueOfCompany;
						stockTransactionOutputStream << left << setw(10) << totalAmount;
						stockTransactionOutputStream << left << setw(15) << str;
						stockTransactionOutputStream.close();

						//WRITE THE TRANSACTION TO BANK_TRANSACTION_HISTORY.TXT FILE
						bankTransationOutputStream.open("bank_transaction_history.txt", ios::app);
						bankTransationOutputStream << endl << left << setw(30) << "Debited to Stock Account";
						bankTransationOutputStream << left << setw(1) << "$";
						bankTransationOutputStream << left << setw(15) << totalAmount;
						bankTransationOutputStream << left << setw(15) << str;
						bankTransationOutputStream << left << setw(1) << "$" << getCashBalance();
						bankTransationOutputStream.close();

						//UPDATE LINKED LIST
						//THE LINKEDLIST ITEM NEEDS TO BE DELETED IF THE NUMBER OF SHARES BECOME 0 ELSE NO UPDATE IS REQUIRED

						if (traversalNode->numberOfShares == 0) {
							//CASE 1: IF CURRENT NODE IS HEAD
							if (traversalNode == headPointer) {
								//IF THERE IS ONLY ONE NODE
								if (traversalNode == tailPointer) {
									headPointer = NULL;
									tailPointer = NULL;
									delete traversalNode;
									sizeOfList--;
									updateSizeOfList(sizeOfList);
									return;
								}
								accountNode *temporaryPointer1 = traversalNode->next;
								headPointer = traversalNode->next;
								temporaryPointer1->prev = NULL;//temporaryPointer->prev = NULL;?? TODO
								delete traversalNode;
								sizeOfList--;
								updateSizeOfList(sizeOfList);
								return;
							}
							//CASE 2: IF CURRENT NODE IS TAIL
							else if (traversalNode == tailPointer) {
								//IF THERE IS ONLY ONE NODE
								if (traversalNode == headPointer) {
									headPointer = NULL;
									tailPointer = NULL;
									delete traversalNode;
									sizeOfList--;
									updateSizeOfList(sizeOfList);
									return;
								}
								accountNode *temporaryPointer2 = traversalNode->prev;
								tailPointer = traversalNode->prev;
								temporaryPointer2->next = NULL;//temporaryPointer->next = NULL;?? TODO
								delete traversalNode;
								sizeOfList--;
								updateSizeOfList(sizeOfList);
								return;
							}
							//CASE 3: IF CURRENT NODE IS ANYWHERE IN BETWEEN
							else {
								accountNode *temporaryPointer3 = traversalNode->prev;
								accountNode *temporaryPointer4 = traversalNode->next;
								temporaryPointer3->next = traversalNode->next;
								temporaryPointer4->prev = traversalNode->prev;
								delete traversalNode;
								sizeOfList--;
								updateSizeOfList(sizeOfList);
								return;
							}
						}

					}
					else {
						cout << "Number of shares entered is more than what is purchased!" << endl;
						return;
					}
				}
				traversalNode = traversalNode->next;
			}
		}


	}
	else {
		cout << "The ticker symbol of the stock you entered is invalid!" << endl;
		return;
	}
	updateSizeOfList(sizeOfList);
}

bool StockAccount::sortLinkedListStockData() {

	accountNode *traversalNode1 = headPointer;

	while (traversalNode1 != NULL) {

		for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {
			if(traversalNode1 != NULL) {
				if (traversalNode1->company == it->first) {
					traversalNode1->amountPerShareForSorting = it->second;
					traversalNode1->currentPortfolioNodeVal = traversalNode1->numberOfShares * traversalNode1->amountPerShareForSorting;
				}
				traversalNode1 = traversalNode1->next;
			}
		}

		accountNode  *traversalNode2 = headPointer;

		if (traversalNode2 != NULL) {
			
			accountNode *prevTempPointer = 0;
			accountNode *nextTempPointer = NULL;
			bool isSwapNeeded = false;

			for (int i = 0; i < sizeOfList; i++) {

				while (traversalNode2->next != 0) {
					
					nextTempPointer = traversalNode2->next;
					if (traversalNode2->currentPortfolioNodeVal < nextTempPointer->currentPortfolioNodeVal) {
						
						nextTempPointer->prev = traversalNode2->prev;
						traversalNode2->prev = nextTempPointer;
						isSwapNeeded = true;
						traversalNode2->next = nextTempPointer->next;

						if (traversalNode2->next != NULL) {
							traversalNode2->next->prev = traversalNode2;
						}
						nextTempPointer->next = traversalNode2;
						if (prevTempPointer != 0) {
							prevTempPointer->next = nextTempPointer;
						}
						prevTempPointer = nextTempPointer;
						if (headPointer == traversalNode2) {
							headPointer = nextTempPointer;
						}
						if (traversalNode2->next == 0) {
							tailPointer = traversalNode2;
						}
					}
					else {
						prevTempPointer = traversalNode2;
						traversalNode2 = traversalNode2->next;
					}
				}
				if (isSwapNeeded = false) {
					break;
				}
				else {
					prevTempPointer = 0;
					traversalNode2 = headPointer;
					isSwapNeeded = false;
				}
			}
		}
		else {
			cout << "Empty list!! Sorry cannot sort at this moment!" << endl;
			return false;
		}
	}
	return true;
}

void StockAccount::savePortfolioDataToFile() {
	
	accountNode *traversalNode = headPointer;
	ofstream savePortfolioOutputStream;
	savePortfolioOutputStream.open("portfolioFile.txt");
	if (savePortfolioOutputStream.is_open()) {
		while (traversalNode != NULL) {
			savePortfolioOutputStream << traversalNode->company << "\t" << traversalNode->numberOfShares << endl;
			traversalNode = traversalNode->next;
		}
	}
	savePortfolioOutputStream.close();
}

void StockAccount::retrieveDataToLinkedList(){
	
	ifstream savePortfolioInputStream;
	stringstream stream;
	string data;
	string comapnyNameTextData;
	int numOfSharesTextData;

	savePortfolioInputStream.open("portfolioFile.txt");

	if (savePortfolioInputStream.is_open()) {
		while (!savePortfolioInputStream.eof()) {
			getline(savePortfolioInputStream, data);
			stream << data;
			stream >> comapnyNameTextData >> numOfSharesTextData;
			portfolioDataMap.insert(pair<string,int>(comapnyNameTextData, numOfSharesTextData));
			stream.clear();
		}
	}
	savePortfolioInputStream.close();

	for (std::map<string, int>::iterator it = portfolioDataMap.begin(); it != portfolioDataMap.end(); ++it) {
		accountNode *newNode = new accountNode();
		newNode->company = it->first;
		newNode->numberOfShares = it->second;

		//IF THE NEW NODE IS THE FIRST NODE
		if (previousPointer == NULL) {
			newNode->prev = NULL;
			newNode->next = NULL;
			headPointer = newNode;
			tailPointer = newNode;
		}
		//UPDATE THE ENTRY AT THE END OF THE LIST
		else {
			newNode->prev = previousPointer;
			previousPointer->next = newNode;
		}
		previousPointer = newNode;
		tailPointer = previousPointer;
	}

	//UPDATE OTHER CONTENTS OF THE LINKEDLIST
	accountNode *traversalNode = headPointer;
	while (traversalNode != NULL) {
		
		for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {

			if (traversalNode->company == it->first) {
				traversalNode->amountPerShareForSorting = it->second;
				traversalNode->currentPortfolioNodeVal = traversalNode->numberOfShares * traversalNode->amountPerShareForSorting;
			}
		}

		portValue = portValue + traversalNode->currentPortfolioNodeVal;
		traversalNode = traversalNode->next;
	}
	portValue += getCashBalance();
}

void StockAccount::setPortfolioValue() {

	ofstream savePortfolioOutputStream;

	//CAPTURE TIMESTAMP
	time_t timev;
	struct tm now;
	char timeBuffer[100];
	time(&timev);
	localtime_s(&now, &timev);
	strftime(timeBuffer, 100, "%d-%m-%Y %I:%M:%S", &now);
	string str(timeBuffer);

	if (sizeOfList == 0) {
		portValue = getCashBalance();
	}
	savePortfolioOutputStream.open("port_value_data.txt");
	savePortfolioOutputStream << portValue << "\t" << str << endl;
	savePortfolioOutputStream.close();

}

void StockAccount::retrievePortfolioValue() {
	
	ifstream savePortfolioInputStream;
	string portfolioData, tempData;
	stringstream stream;

	savePortfolioInputStream.open("port_value_data.txt");
	if (savePortfolioInputStream.is_open()) {
		while (!savePortfolioInputStream.eof()) {
			getline(savePortfolioInputStream, portfolioData);
			stream << portfolioData;
			stream >> portValue_array[sizeOfPortValueArray] >> timeStamp_array[sizeOfPortValueArray] >> tempData;
			if (timeStamp_array[sizeOfPortValueArray] == "") {
				continue;
			}
			else {
				timeStamp_array[sizeOfPortValueArray].append(" ");
				timeStamp_array[sizeOfPortValueArray].append(tempData);
			}
			sizeOfPortValueArray++;
			stream.clear();
		}
	}
	savePortfolioInputStream.close();
}

void StockAccount::printHistory() {
	
	ifstream stockTransactionInputStream;
	string historyData;

	cout << left << setw(15) << "Transaction";
	cout << left << setw(12) << "Symbol";
	cout << left << setw(7) << "Shares";
	cout << left << setw(15) << "Price per Share($)";
	cout << left << setw(10) << "Value($)";
	cout << left << setw(15) << "Timestamp" << endl;

	stockTransactionInputStream.open("stock_transaction_history.txt");

	if (stockTransactionInputStream.is_open()) {
		while (!stockTransactionInputStream.eof()) {
			while (getline(stockTransactionInputStream,historyData)) {
				cout << historyData << endl;
			}
		}
	}
	cout << endl;
	stockTransactionInputStream.close();
}

void StockAccount::viewGraph() {
	
	Engine *matlabPlotNode;
	matlabPlotNode = engOpen(NULL);

	if (matlabPlotNode == NULL) {
		cout << "Error in matlab plotting" << endl;
		exit(1);
	}

	cout << "Plotting MATLAB graph..." << endl;
	mxArray *MXA;
	MXA = mxCreateDoubleMatrix(1, sizeOfPortValueArray, mxREAL);
	memcpy((void *)mxGetPr(MXA), (void*)portValue_array, sizeOfPortValueArray * sizeof(double));
	engPutVariable(matlabPlotNode, "set", MXA);
	engEvalString(matlabPlotNode, "plot(set);");
	engEvalString(matlabPlotNode, "title('Change in Portfolio Value');");
	mxDestroyArray(MXA);
}

void StockAccount::updateSizeOfList(int sizeOfList) {
	ofstream listSizeOutputStream;
	listSizeOutputStream.open("stock_list_size_data.txt");
	listSizeOutputStream << sizeOfList;
	listSizeOutputStream.close();
}

