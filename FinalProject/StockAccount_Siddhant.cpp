#include "StockAccount_Siddhant.h"
#include <iostream>
#include <fstream>
#include "accountNode.h"
using namespace std;

StockAccount::StockAccount(accountNode *head){

	string company = "";
	double amount = 0.0;
	string date = "";
	string filename = "Result_1.txt";
	ifstream din;
	din.open(filename.c_str());
	if (din.fail()){
		cerr << "Could not open file \n";
	}
	while (!din.eof()){
		din >> company >> amount >> date;
		accountNode *temp = new accountNode(company, amount, date);
		temp->setNext(head);
		head = temp;
	}

}


StockAccount::~StockAccount()
{
}

void StockAccount::displayStockPrice(accountNode *head) {

}