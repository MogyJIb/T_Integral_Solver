#pragma once

#include <string>
#include <winstring.h>
#include <map>
#include <math.h>
#include "Operation.h"
#include "Converter.h"

using namespace std;

class ProcessorRpn
{
private:
	list<tstring> rpnOperandList;

	Operation operationProcessor = Operation();
	Converter converter = Converter();
	void makeOperation(stack<double> &numberStack, tstring operation);
	void changeChar(list<tstring> &rpnOperandList, tstring ch, double xNumber);

	double processRpnExpression(list<tstring> rpnOperandList);
	bool isZeroString(tstring str);

public:
	ProcessorRpn(TCHAR* expression);
	~ProcessorRpn();

	double makeUnOperation(double firstOper, tstring operation);
	double makeBinOperation(double firstOper, double secondOper, tstring operation);
	double function();
	double function(double x);
	double function(double x, double y);
	double function(double x, double y, double z);
	double function(map<tstring, double> operands);
};

