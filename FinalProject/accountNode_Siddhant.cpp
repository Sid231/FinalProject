#include <iostream>
#include "accountNode_Siddhant.h"
using namespace std;

accountNode::accountNode(string companyData, double amountData, string dateData) {
	company = companyData;
	amount = amountData;
	date = dateData;
	prev = NULL;
	next = NULL;
}