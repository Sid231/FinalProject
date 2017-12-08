#include <iostream>
using namespace std;

struct accountNode
{
	string company;
	double amount;
	string date;
	accountNode *prev;
	accountNode *next;
};