/*
NAME: KUMAR SIDDHANT
DATE: 12/11/2017
PROJECT: ACCOUNT MANAGEMENT SYSTEM
FILE: MAIN_SIDDHANT.CPP
*/
#include <iostream>
#include "Account_Siddhant.h"
#include "BankAccount_Siddhant.h"
#include "StockAccount_Siddhant.h"
#include "accountNode_Siddhant.h"
using namespace std;

int main() {
	//USER CHOICE VARIABLES IN THE MENU
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;

	//INIT HEAD POINTER AND THE BANK AND STOCK ACCOUNT OBJECTS
	accountNode *head = NULL;
	BankAccount bankAccount;
	StockAccount stockAccount;

	//MAIN MENU
	cout << "Welcome to the Account Management System!!" << endl;

	while (choice1 != 3) {

		cout << endl << endl << "Please select the account to access" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		cout << "Please Select Account to Access : " << endl;

		cin >> choice1;

		cout << endl << "Option " << choice1 << endl;

		switch (choice1) {

		case 1:
			//STOCK ACCOUNT MENU
			cout << endl << "Stock Portfolio Account" << endl;
			while (choice2 != 7) {
				cout << "1. Display the price for a Stock Symbol" << endl;
				cout << "2. Display Current Portfolio" << endl;
				cout << "3. Buy Shares" << endl;
				cout << "4. Sell Shares" << endl;
				cout << "5. View a Graph for the Portfolio Value" << endl;
				cout << "6. View Transaction History" << endl;
				cout << "7. Return to the Previous Menu" << endl;
				cout << "Enter Your Choice : ";

				cin >> choice2;
				cout << endl << "Option " << choice2 << endl;
				switch (choice2)
				{
				case 1:
					//DISPLAY STOCK PRICE
					stockAccount.displayStockPrice(); 
					break;
				case 2:
					//DISPLAY THE CURRENT PORTFOLIO INFO
					stockAccount.displayCurrentPortfolio();
					break;
				case 3:
					//BUY SHARES
					stockAccount.buyShares();
					break;
				case 4:
					//SELL SHARES
					stockAccount.sellShares();
					break;
				case 5:
					//VIEW GRAPH
					stockAccount.viewGraph();
					break;
				case 6:
					//PRINT TRANSACTION HISTORY
					stockAccount.printHistory();
					break;
				case 7:
					//SORT LINKEDLIST AND GO BAK TO MAIN MENU
					stockAccount.sortLinkedListStockData();
					break;
				default:
					cout << "Please Enter a Valid Option!" << endl;
				}
			}
			choice2 = 0;
			break;

		case 2:
			while (choice3 != 5) {
				//BANK ACCOUNT MENU
				cout << endl << "Bank Account" << endl;
				cout << "Please select an option:" << endl;
				cout << "1. View Account Balance" << endl;
				cout << "2. Deposit Money" << endl;
				cout << "3. Withdraw Money" << endl;
				cout << "4. Print out History" << endl;
				cout << "5. Return to Previous Menu" << endl;
				cout << "Please Enter Your Choice : " << endl;
				cin >> choice3;
				cout << endl << "Option " << choice3 << endl;

				switch (choice3) {

				case 1:
					//VIEW BALANCE
					bankAccount.viewBalance();
					break;
				case 2:
					//DEPOSIT CASH
					bankAccount.depositCashAmount();
					break;
				case 3:
					//WITHDRAW CASH
					bankAccount.withdrawCashAmount();
					break;
				case 4:
					//PRINT TRANSACTION HISTORY
					bankAccount.printHistory();
					break;
				case 5:
					//RETURN TO PREVIOUS MENU
					break;
				default:
					cout << "Please Enter Valid Option!" << endl;
				}
			}
			choice3 = 0;
			break;

		case 3:
			//SAVE PORTFOLIO DATA TO THE FILE BEFORE EXITING
			stockAccount.savePortfolioDataToFile(); 

			//SET THE PORTFOLIO VALUE AMOUNT BEFORE EXITING
			stockAccount.setPortfolioValue();
			break;

		default:
			cout << "Please Enter Valid Option!" << endl;
		}
	}
	return 0;
}