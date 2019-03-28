#include "ProcessorRpn.h"



#define WRONG_STRING_INPUT_EXCEPTION 1

ProcessorRpn::ProcessorRpn(TCHAR* expression)
{
	rpnOperandList = converter.makeRpnOperandList(expression);
}



double ProcessorRpn::processRpnExpression(list<tstring> rpnOperandList) {

	stack<double> processingStack;

	for (tstring operand : rpnOperandList) {
		if (operationProcessor.isOperation(operand)) {
			makeOperation(processingStack, operand);
		}
		else {

			double res = 0;
			if (!isZeroString(operand)) {
				res = _ttof(operand.data());
				/*if (res == 0)
					throw WRONG_STRING_INPUT_EXCEPTION;*/
			}
			processingStack.push(res);
		}

	}
	if (processingStack.size() < 1)
		throw WRONG_STRING_INPUT_EXCEPTION;
	double res = processingStack.top();
	return res;
}

void ProcessorRpn::makeOperation(stack<double> &numberStack, tstring operation) {
	if (operationProcessor.isBinary(operation)) {
		if (numberStack.size() < 2)
			throw WRONG_STRING_INPUT_EXCEPTION;
		double secondOper = numberStack.top();
		numberStack.pop();
		double firstOper = numberStack.top();
		numberStack.pop();

		numberStack.push(makeBinOperation(firstOper, secondOper, operation));
	}
	else if (operationProcessor.isUnary(operation)) {
		if (numberStack.size() < 1)
			throw WRONG_STRING_INPUT_EXCEPTION;
		double firstOper = numberStack.top();
		numberStack.pop();

		numberStack.push(makeUnOperation(firstOper, operation));
	}
	else throw WRONG_STRING_INPUT_EXCEPTION;
}

void ProcessorRpn::changeChar(list<tstring> &rpnOperandList, tstring ch, double xNumber)
{
	for (list<tstring>::iterator iter = rpnOperandList.begin(); iter != rpnOperandList.end(); ++iter)
	{
		if (*iter == ch)
			*iter = to_tstring(xNumber);
	}

}


double ProcessorRpn::makeUnOperation(double firstOper, tstring operation) {
	if (!operation.compare(COS)) {
		return cos(firstOper);
	}
	else if (!operation.compare(SIN)) {
		return sin(firstOper);
	}
	else if (!operation.compare(TAN)) {
		return tan(firstOper);
	}
	else if (!operation.compare(LG)) {
		return log10(firstOper);
	}
	else if (!operation.compare(LN)) {
		return log(firstOper);
	}
	else if (!operation.compare(SQRT)) {
		return sqrt(firstOper);
	}
	else throw WRONG_STRING_INPUT_EXCEPTION;
}

double ProcessorRpn::makeBinOperation(double firstOper, double secondOper, tstring operation) {
	if (!operation.compare(PLUS)) {
		return firstOper + secondOper;
	}
	else if (!operation.compare(MINUS)) {
		return firstOper - secondOper;
	}
	else if (!operation.compare(MUL)) {
		return firstOper * secondOper;
	}
	else if (!operation.compare(DIV)) {
		return firstOper / secondOper;
	}
	else if (!operation.compare(POW)) {
		return pow(firstOper, secondOper);
	}
	else throw WRONG_STRING_INPUT_EXCEPTION;
}

double ProcessorRpn::function()
{
	double res = processRpnExpression(rpnOperandList);
	return res;
}

double ProcessorRpn::function(double x)
{
	return function({ { _T("x"), x } });
}

double ProcessorRpn::function(double x, double y)
{
	return function({ { _T("x"), x }, { _T("y"), y } });
}

double ProcessorRpn::function(double x, double y, double z)
{
	return function({ { _T("x"), x }, { _T("y"), y }, { _T("z"), z } });
}

double ProcessorRpn::function(map<tstring, double> operands)
{
	list<tstring> tmp = list<tstring>(rpnOperandList);
	for (auto operand = operands.begin(); operand != operands.end(); ++operand)
		changeChar(tmp, operand->first, operand->second);
	double res = processRpnExpression(tmp);
	return res;
}

bool  ProcessorRpn::isZeroString(tstring str) {
	if (str.at(0) == _T('.'))
		return false;
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) != _T('0') && str.at(i) != _T('.') && str.at(i) != _T('-'))
			return false;

	}
	return true;
}


ProcessorRpn::~ProcessorRpn()
{
}
