#include <iostream>
#include "Account_Siddhant.h"
#include "BankAccount_Siddhant.h"
#include "StockAccount_Siddhant.h"
#include "accountNode_Siddhant.h"
using namespace std;

int main() {
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;

	accountNode *head = NULL;
	BankAccount bankAccount;
	StockAccount stockAccount;


	cout << "Welcome to the Account Management System!!" << endl;

	while (choice1 != 3) {

		cout << "Please select the account to access" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		cout << "Please Select Account to Access : " << endl;

		cin >> choice1;

		cout << "Option " << choice1 << endl;

		switch (choice1) {

		case 1:
			cout << "Stock Portfolio Account" << endl;
			while (choice2 != 7) {
				cout << "Stock Portfolio account";
				cout << "1. Display the price for a Stock Symbol" << endl;
				cout << "2. Display Current Portfolio" << endl;
				cout << "3. Buy Shares" << endl;
				cout << "4. Sell Shares" << endl;
				cout << "5. View a Graph for the Portfolio Value" << endl;
				cout << "6. View Transaction History" << endl;
				cout << "7. Return to the Previous Menu" << endl;
				cout << "Enter Your Choice : ";

				cin >> choice2;
				cout << "Option " << choice2 << endl;
				switch (choice2)
				{
				case 1:
					stockAccount.displayStockPrice(); 
					break;
				case 2:
					stockAccount.displayCurrentPortfolio();
					break;
				case 3:
					stockAccount.buyShares();
					break;
				case 4:
					//stockAccount.sellShares();
					break;
				case 5:
					//stockAccount.viewGraph();
					break;
				case 6:
					//stockAccount.printHistory();
					break;

				case 7:
					break;
				default:
					cout << "Please Enter a Valid Option!" << endl;
				}
			}
			choice2 = 0;
			break;

		case 2:
			while (choice3 != 5) {

				cout << "Bank Account" << endl << endl;
				cout << "Please select an option:" << endl;
				cout << "1. View Account Balance" << endl;
				cout << "2. Deposit Money" << endl;
				cout << "3. Withdraw Money" << endl;
				cout << "4. Print out History" << endl;
				cout << "5. Return to Previous Menu" << endl;
				cout << "Please Enter Your Choice : " << endl;
				cin >> choice3;
				cout << "Option " << choice3 << endl;

				switch (choice3) {

				case 1:
					//bankAccount.viewBalance();
					break;
				case 2:
					//bankAccount.depositAmount();
					//bankAccount.savePortValue();
					break;
				case 3:
					//bankAccount.withdrawAmount();
					//bankAccount.savePortValue();
					break;
				case 4:
					//bankAccount.printHistory();
					break;
				case 5:
					break;
				default:
					cout << "Please Enter Valid Option!" << endl;
				}
			}

			choice3 = 0;
			break;

		case 3:
			//stockAccount.savePortValue(); 
			//bankAccount.savePortValue(); 
			break;

		default:
			cout << "Please Enter Valid Option!" << endl;
		}
	}
	return 0;
}