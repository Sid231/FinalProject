/*
NAME: KUMAR SIDDHANT
DATE: 12/11/2017
PROJECT: ACCOUNT MANAGEMENT SYSTEM
FILE: STOCKACCOUNT_SIDDHANT.CPP
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
			cout << endl << left << setw(20) << "Company-Symbol";
			cout << left << setw(20) << "Price per Share"<<endl;
			cout << left << setw(20) << it->first;
			cout << left << setw(20) << it->second << endl << endl;
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
	
	//LOOP THROUGH THE LINKED LIST AND GE THE DATA BY LOOPING THROUGH THE STOCK DATA MAP
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

	//IF THE LINKEDLIST IS NOT EMPTY
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

		//UPDATE THE TOTAL PORTFOLIO VALUE
		portValue = getCashBalance() + stockValue;
		cout << "Cash Balance is : $" << getCashBalance() << endl;
		cout << "Stock Balance is : $" << stockValue << endl;
		cout << "Total Portfolio value is : $" << portValue << endl << endl;
	
		//UPDATE THE PORTFOLIO VALUES IN AN ARRAY AND INCREASE THE SIZE OF ARRAY BY 1
		portValue_array[sizeOfPortValueArray] = portValue;
		sizeOfPortValueArray++;
	}

	//NO DATA IN THE LINKEDLIST SO NOTHING TO SHOW
	if (sizeOfList == 0) {
		portValue = getCashBalance();
		cout << "Shares are not available!!" << endl;
	}
}

//BUY SHARES
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

	//CHECK IF THE STOCK TO BE PURCHASED EXISTS IN THE ACCOUNT SYSTEM
	for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {
		if (companySymbol == it->first) {
			validCompanySymbolData = true;
			break;
		}
	}

	//STOCK EXISTS IN THE SYSTEM
	if (validCompanySymbolData == true) {
		cout << "Enter the number of shares you want to buy" << endl;
		cin >> numberOfShares;
		cout << "Enter the maximum limit you are willing to pay per share" << endl;
		cin >> maxAmtPay;

		//UPDATE THE CASH BALANCE AMOUNT
		setBalance();

		//GET HTE STOCK DATA INFO
		for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {
			if (companySymbol == it->first) {
				shareValueOfCompany = it->second;
				break;
			}
		}

		//MAX PAY SHOULD BE GREATER THAN THE STOCK VALUE. IF NOT THEN THE USER CANT BUY THE STOCK
		if (maxAmtPay >= shareValueOfCompany) {
			totalAmount = numberOfShares * shareValueOfCompany;
		}
		else {
			cout << "The max limit value entered is less than the value of the stock. Sorry you cant buy the stock with this amount!" << endl;
			return;
		}

		//CONDITION TO CHECK IF THERE IS ENOUGH MONEY IN THE ACCOUNT TO BUY THE STOCKS
		if (totalAmount > getCashBalance()) {
			cout << "Insufficient balance in your account! Please check again later!" << endl;
			return;
		}
		else {
			
			//STOCKS PURCHASING SUCCESS STATEMENTS
			cout << endl << "Thanks for purchasing the stocks of " << companySymbol << endl;
			cout << "The number of shares you purchased are " << numberOfShares << " and the total amount you paid for those number of shares is " << totalAmount << endl << endl;

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

			//WRITE THE TRANSACTION TO BANK_TRANSACTION_HISTORY.TXT FILE
			bankTransationOutputStream.open("bank_transaction_history.txt", ios::app);
			bankTransationOutputStream << endl << left << setw(30) << "Debited to Stock Account";
			bankTransationOutputStream << left << setw(1) << "$";
			bankTransationOutputStream << left << setw(15) << totalAmount;
			bankTransationOutputStream << left << setw(25) << str;
			bankTransationOutputStream << left << setw(1) << "$" << getCashBalance();
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
	//UPDATE THE SIZE OF THE LINKEDLIST IN port_value_data.txt FILE
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

	//CHECK IF HEADPOINTER IS NOT NULL AND THE STOCK TO BE SOLD HAS BEEN PURCHASED BEFORE
 	while (tempNode != NULL) {
		if (tempNode->company == companySymbol) {
			validCompanySymbolData = true;
			break;
		}
		tempNode = tempNode->next;
	}

	//STOCK HAS BEEN PURCHASED BEFORE AND CAN BE SOLD
	if (validCompanySymbolData == true) {
		
		cout << "Enter the number of shares you want to sell" << endl;
		cin >> numberOfShares;
		cout << "Enter the minimum limit you are willing to pay per share" << endl;
		cin >> minAmtPay;

		//THE LINKEDLIST IS NOT EMPTY
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
						cout << endl << "You sold the stocks of " << companySymbol << endl;
						cout << "The number of shares you sold are " << numberOfShares << " and the total amount you earned for those number of shares is " << totalAmount << endl << endl;

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
						bankTransationOutputStream << left << setw(25) << str;
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
									//UPDATE THE SIZE OF THE LINKEDLIST IN port_value_data.txt FILE
									updateSizeOfList(sizeOfList);
									return;
								}
								accountNode *temporaryPointer1 = traversalNode->next;
								headPointer = traversalNode->next;
								temporaryPointer1->prev = NULL;
								delete traversalNode;
								sizeOfList--;
								//UPDATE THE SIZE OF THE LINKEDLIST IN port_value_data.txt FILE
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
									//UPDATE THE SIZE OF THE LINKEDLIST IN port_value_data.txt FILE
									updateSizeOfList(sizeOfList);
									return;
								}
								accountNode *temporaryPointer2 = traversalNode->prev;
								tailPointer = traversalNode->prev;
								temporaryPointer2->next = NULL;
								delete traversalNode;
								sizeOfList--;
								//UPDATE THE SIZE OF THE LINKEDLIST IN port_value_data.txt FILE
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
								//UPDATE THE SIZE OF THE LINKEDLIST IN port_value_data.txt FILE
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
	//THE STOCK HAS NOT BEEN PURCHASED BEFORE OR DOESNT EXIST AT ALL!
	else {
		cout << "The ticker symbol of the stock you entered is invalid!" << endl;
		return;
	}
	//UPDATE THE SIZE OF THE LINKEDLIST IN port_value_data.txt FILE
	updateSizeOfList(sizeOfList);
}

//SORT THE LINKED LIST
bool StockAccount::sortLinkedListStockData() {

	accountNode *traversalNode1 = headPointer;

	//CHECK IF HEAD POINTER IS NOT NULL
	while (traversalNode1 != NULL) {

		//SET THE NODE DATA REQUIRED FOR SORTING
		for (std::map<string, double>::iterator it = stockDataMap.begin(); it != stockDataMap.end(); it++) {
			if(traversalNode1 != NULL) {
				if (traversalNode1->company == it->first) {
					traversalNode1->amountPerShareForSorting = it->second;
					traversalNode1->currentPortfolioNodeVal = traversalNode1->numberOfShares * traversalNode1->amountPerShareForSorting;
				}
				traversalNode1 = traversalNode1->next;
			}
		}

		//THE NODE(traversalNode2) WILL TRAVERSE THROUGH THE LIST 
		//AND SORT THE LINKED LIST USING BUBBLE SORTING
		accountNode  *traversalNode2 = headPointer;

		if (traversalNode2 != NULL) {
			
			//ASSIGN PREVIOUS POINTER AS 0
			accountNode *prevTempPointer = 0;
			//TEMPORARY POINTER
			accountNode *nextTempPointer = NULL;
			//VALUE TO CHECK IF SWAPPING IS REQUIRED
			bool isSwapNeeded = false;

			//INITIATION OF BUBBLE SORT
			for (int i = 0; i < sizeOfList; i++) {

				//STOP IF THE TRAVELLING NODE REACHES THE TAIL POINTER
				while (traversalNode2->next != 0) {
					
					//ASSIGN THE NEXT POINTER TO A TEMPORARY POINTER
					nextTempPointer = traversalNode2->next;

					//SWAP IS DONE OF THE PORTFOLIO VALUE ON THE LEFT IS SMALLER THAN THE ONE ON RIGHT
					if (traversalNode2->currentPortfolioNodeVal < nextTempPointer->currentPortfolioNodeVal) {
						
						nextTempPointer->prev = traversalNode2->prev;
						traversalNode2->prev = nextTempPointer;
						isSwapNeeded = true;
						traversalNode2->next = nextTempPointer->next;

						//CHECK IF TAIL POINTER IS NOT NULL
						if (traversalNode2->next != NULL) {
							traversalNode2->next->prev = traversalNode2;
						}
						//AFTER SWAPPING THE TEMPORARY POINTER SHOULD BECOME THE CURRENT POINTER
						nextTempPointer->next = traversalNode2;

						//CHECK IF THE POINTER BEFORE THE CURRENT ONE IS NOT NULL
						if (prevTempPointer != 0) {
							prevTempPointer->next = nextTempPointer;
						}

						//FOR NEXT ITERATION THE PREVIOUS POINTER TO CURRENT SHOULD BE THE TEMPORARY POINTER
						prevTempPointer = nextTempPointer;

						//IF HEADPOINTER IS CURRENT THEN AFTER SWAPPING THE HEADPOINTER SHOULD BE THE CURRENT POINTER
						if (headPointer == traversalNode2) {
							headPointer = nextTempPointer;
						}

						//CHECK IF THE NEXT POINTER TO XURRENT IS TAIL.
						//IF YES, THEN TAILPOINTER SHOULD BE CURRENT POINTER
						if (traversalNode2->next == 0) {
							tailPointer = traversalNode2;
						}
					}

					//CONDITION IF THERE IS NO SWAPPING
					//PREVIOUS POINTER SHOULD BE THE NODE WHICH THE TRAVERSAL NODE IS POINTING TO CURRENTLY
					else {
						prevTempPointer = traversalNode2;
						traversalNode2 = traversalNode2->next;
					}
				}
				//LIST SORTED
				if (isSwapNeeded = false) {
					break;
				}

				//BEGIN AGAIN FROM THE HEAD POINTER
				else {
					prevTempPointer = 0;
					traversalNode2 = headPointer;
					isSwapNeeded = false;
				}
			}
		}
		//EMPTY LIST... NOTHING CAN BE DONE
		else {
			cout << "Empty list!! Sorry cannot sort at this moment!" << endl;
			return false;
		}
	}
	return true;
}

//SAVE THE PORTFOLIO VALUE TO A FILE
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

//GET VALUE FROM THE PORTFOLIO TXT FILE TO THE LINKEDLIST
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

//SAVE THE PORTFOLIO VALUE
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

	//UPDATE THE CASHBALANCE IF THE PORTFOLIO IS EMPTY
	if (sizeOfList == 0) {
		portValue = getCashBalance();
	}
	savePortfolioOutputStream.open("port_value_data.txt");
	savePortfolioOutputStream << portValue << "\t" << str << endl;
	savePortfolioOutputStream.close();

}

//GET THE PORTFOLIO VALUE
void StockAccount::retrievePortfolioValue() {
	
	//OPEN THE FILE port_value_data.txt AND GET THE HISTORICAL DATA
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
				//APPEND THE TIME WITH DATA
				timeStamp_array[sizeOfPortValueArray].append(" ");
				timeStamp_array[sizeOfPortValueArray].append(tempData);
			}
			sizeOfPortValueArray++;
			stream.clear();
		}
	}
	savePortfolioInputStream.close();
}

//PRINT THE TRANSACTION HISTORY
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

//PLOT THE GRAPH IN MATLAB
void StockAccount::viewGraph() {
	
	//POINTER TO THE ENGINE
	Engine *matlabPlotNode;
	matlabPlotNode = engOpen(NULL);

	if (matlabPlotNode == NULL) {
		cout << "Error in matlab plotting" << endl;
		exit(1);
	}
	//CREATE MXARRAY AND COPY THE C++ DOUBLE ARRAY OF PORTFOLIO IN IT
	cout << "Plotting MATLAB graph..." << endl;
	mxArray *MXA;
	MXA = mxCreateDoubleMatrix(1, sizeOfPortValueArray, mxREAL);
	//ALLOCATE MEMORY SPACE
	memcpy((void *)mxGetPr(MXA), (void*)portValue_array, sizeOfPortValueArray * sizeof(double));
	engPutVariable(matlabPlotNode, "set", MXA);
	//PLOT THE DATA
	engEvalString(matlabPlotNode, "plot(set);");
	engEvalString(matlabPlotNode, "title('Change in Portfolio Value');");
	//DEALLOCATE THE MATRIX
	mxDestroyArray(MXA);
}

//UPDATE THE SIZE OF THE LINKEDLIST IN THE FILE stock_list_size_data.txt
void StockAccount::updateSizeOfList(int sizeOfList) {
	ofstream listSizeOutputStream;
	listSizeOutputStream.open("stock_list_size_data.txt");
	listSizeOutputStream << sizeOfList;
	listSizeOutputStream.close();
}

