#pragma once

#ifndef ACCOUNTNODE_H
#define ACCOUNTNODE_H

#include <iostream>
using namespace std;

class accountNode {

private:
	string company;
	double amount;
	string date;
	accountNode *prev;
	accountNode *next;

public:
	accountNode(string, double, string);
};

#endif