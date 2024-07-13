
#ifndef OPERATOR_FUNCTIONS_H
#define OPERATOR_FUNCTIONS_H

#include <string>
#include <vector>
#include <stack>
#include <iostream>

#include "Var.h"
#include "variableFunctions.h"

const std::map<std::wstring, int> OPERATOR_PRECEDENCE_MAP =
{
	{ L"(",  0 },
	{ L")",  0 },
	{ L"<<", 1 },
	{ L">>", 1 },
	{ L"*",  2 },
	{ L"/",  2 },
	{ L"%",  2 },
	{ L"+",  3 },
	{ L"-",  3 },
	{ L"|",  4 },
	{ L"&",  4 },
	{ L"^",  4 },
	{ L"~",  4 },
	{ L">>>", 4 }
};

const std::map<std::wstring, int> OPERATOR_ID_MAP =
{
	{ L"(",  0 },
	{ L")",  0 },
	{ L"<<", 1 },
	{ L">>", 2 },
	{ L"*",  3 },
	{ L"/",  4 },
	{ L"%",  5 },
	{ L"+",  6 },
	{ L"-",  7 },
	{ L"|",  8 },
	{ L"&",  9 },
	{ L"^",  10 },
	{ L"~",  11 },
	{ L">>>", 12 }
};

bool execPlusOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execMinusOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execMultiplyOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execDivideOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execModuloOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execXorOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execAndOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execOrOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execBitwiseComplementOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execUnsignedRightShiftOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);

bool execLeftShiftOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);
bool execRightShiftOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs);

void execAssignOperator(Var* lhsVar, int& r1, Var* rhsVar, int& r2);
void execAssignOperator(Var* lhsVar, Var* rhsVar);
void execAssignOperator(const std::wstring& lhs, const std::wstring& rhs);
void execAssignOperator(const std::wstring& lhs, int r1, const std::wstring& rhs);

// Returns true if 'op2' has higher or same precedence as 'op1',
// otherwise returns false.
bool hasPrecedence(std::wstring& op1, std::wstring& op2)
{
	if (op2 == L"(")
	{
		return false;
	}

	const int op1Precedence = OPERATOR_PRECEDENCE_MAP.find(op1)->second;
	const int op2Precedence = OPERATOR_PRECEDENCE_MAP.find(op2)->second;

	if (op2Precedence >= op1Precedence)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// A utility method to apply an operator 'op' on operands 'a' 
// and 'b'. Return the result.
std::wstring applyOp(ReservedWord& assignmentType, const std::wstring& op, std::wstring& b, std::wstring& a)
{
	const int op1Id = OPERATOR_ID_MAP.find(op)->second;

	switch (op1Id)
	{
	case 1:
	{
		execLeftShiftOperator(assignmentType, a, b);
		return a;
	}
	case 2:
	{
		execRightShiftOperator(assignmentType, a, b);
		return a;
	}
	case 3:
	{
		execMultiplyOperator(assignmentType, a, b);
		return a;
	}
	case 4:
	{
		execDivideOperator(assignmentType, a, b);
		return a;
	}
	case 5:
	{
		execModuloOperator(assignmentType, a, b);
		return a;
	}
	case 6:
	{
		execPlusOperator(assignmentType, a, b);
		return a;
	}
	case 7:
	{
		execMinusOperator(assignmentType, a, b);
		return a;
	}
	case 8:
	{
		execOrOperator(assignmentType, a, b);
		return a;
	}
	case 9:
	{
		execAndOperator(assignmentType, a, b);
		return a;
	}
	case 10:
	{
		execXorOperator(assignmentType, a, b);
		return a;
	}
	case 11:
	{
		execBitwiseComplementOperator(assignmentType, a, b);
		return a;
	}
	case 12:
	{
		execUnsignedRightShiftOperator(assignmentType, a, b);
		return a;
	}
	}

	return nullptr;
}

std::wstring evaluate(ReservedWord& assignmentType, int startIndex, std::vector<std::wstring>& expressions)
{
	std::stack<std::wstring> values;

	std::stack<std::wstring> ops;

	bool lastWasOperator = false;
	bool appendNegative = false;

	for (int i = startIndex; i < expressions.size(); i++)
	{
		std::wstring expression = expressions[i];
		auto opId = OPERATOR_ID_MAP.find(expression);

		if (expression == L"(")
		{
			ops.push(expression);

			lastWasOperator = false;
		}

		else if (expression == L")")
		{
			std::wstring val1, val2;

			while (ops.top() != L"(")
			{
				val1 = values.top();
				values.pop();
				val2 = values.top();
				values.pop();

				values.push(applyOp(assignmentType, ops.top(), val1, val2));

				ops.pop();
			}

			ops.pop();

			lastWasOperator = false;
		}

		else if (lastWasOperator == false && opId != OPERATOR_ID_MAP.end())
		{
			std::wstring val1, val2;

			while (!ops.empty() && hasPrecedence(expression, ops.top()))
			{
				val1 = values.top();
				values.pop();
				val2 = values.top();
				values.pop();

				values.push(applyOp(assignmentType, ops.top(), val1, val2));

				ops.pop();
			}

			ops.push(expression);

			lastWasOperator = true;
		}

		else if (expression != L" ")
		{
			if (expression == L"-")
			{
				appendNegative = true;
			}
			else
			{
				if (appendNegative == true)
				{
					expression = L"-" + expression;

					appendNegative = false;
				}

				values.push(expression);
			}

			lastWasOperator = false;
		}
	}

	std::wstring val1, val2;

	while (!ops.empty())
	{
		val1 = values.top();
		values.pop();
		val2 = values.top();
		values.pop();

		values.push(applyOp(assignmentType, ops.top(), val1, val2));

		ops.pop();
	}

	std::wstring result = values.top();
	values.pop();

	return result;
}

void executeInitialization(const int& initializeVariableIndex, std::vector<std::wstring>& tokens)
{
	int r1;
	Var* lhsVar = getVar(tokens[1], r1);

	execAssignOperator(tokens[1], 0, evaluate(lhsVar->type, initializeVariableIndex, tokens));
}

void executeInitialization(const int& initializeVariableIndex, int size, std::vector<std::wstring>& tokens)
{
	int r1;
	Var* lhsVar = getVar(tokens[1], r1);

	std::wstring result = evaluate(lhsVar->type, initializeVariableIndex, tokens);

	for (int i = 0; i < size; ++i)
	{
		execAssignOperator(tokens[1], i, result);
	}
}

void executeAssignment(const int& tokensSize, std::vector<std::wstring>& tokens)
{
	Var* lhsVar;
	Var* rhsVar;
	ReservedWord lhsType;

	if (tokens[1] == L"=")
	{
		int r1;
		lhsVar = getVar(tokens[0], r1);

		execAssignOperator(tokens[0], evaluate(lhsVar->type, 2, tokens));
	}
	else if (tokens[1] == L"+=")
	{
		int r1, r2;
		lhsVar = getVar(tokens[0], r1);
		rhsVar = getVar(tokens[2], r2);

		lhsType = lhsVar->type;

		switch (lhsType)
		{
		case TYPE_INT:
		{
			if (rhsVar == nullptr)
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				pstr[r1] += std::stoi(tokens[2]);
			}
			else
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				int* rpstr = static_cast<int*>(rhsVar->data);
				pstr[r1] += rpstr[r2];
			}
			break;
		}
		case TYPE_LONG:
		{
			if (rhsVar == nullptr)
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				pstr[r1] += std::stoll(tokens[2]);
			}
			else
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				long long int* rpstr = static_cast<long long int*>(rhsVar->data);
				pstr[r1] += rpstr[r2];
			}
			break;
		}
		case TYPE_DOUBLE:
		{
			if (rhsVar == nullptr)
			{
				double* pstr = static_cast<double*>(lhsVar->data);
				pstr[r1] += std::stod(tokens[2]);
			}
			else
			{
				double* pstr = static_cast<double*>(lhsVar->data);
				double* rpstr = static_cast<double*>(rhsVar->data);
				pstr[r1] += rpstr[r2];
			}

			break;
		}
		case TYPE_STRING:
		{
			if (rhsVar == nullptr)
			{
				std::wstring temp = tokens[2];

				//findAndReplaceNewline(temp);
				//findAndReplaceQuoteEscape(temp);

				temp = temp.substr(1);
				temp = temp.substr(0, temp.length() - 1);

				std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
				//std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
				pstr[r1] += temp;
			}
			else
			{
				std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
				std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
				pstr[r1] += rpstr[r2];
			}

			break;
		}
		}
	}
	else if (tokens[1] == L"-=")
	{
		int r1, r2;
		lhsVar = getVar(tokens[0], r1);
		rhsVar = getVar(tokens[2], r2);

		lhsType = lhsVar->type;

		switch (lhsType)
		{
		case TYPE_INT:
		{
			if (rhsVar == nullptr)
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				pstr[r1] -= std::stoi(tokens[2]);
			}
			else
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				int* rpstr = static_cast<int*>(rhsVar->data);
				pstr[r1] -= rpstr[r2];
			}
			break;
		}
		case TYPE_LONG:
		{
			if (rhsVar == nullptr)
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				pstr[r1] -= std::stoll(tokens[2]);
			}
			else
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				long long int* rpstr = static_cast<long long int*>(rhsVar->data);
				pstr[r1] -= rpstr[r2];
			}
			break;
		}
		case TYPE_DOUBLE:
		{
			if (rhsVar == nullptr)
			{
				double* pstr = static_cast<double*>(lhsVar->data);
				pstr[r1] -= std::stod(tokens[2]);
			}
			else
			{
				double* pstr = static_cast<double*>(lhsVar->data);
				double* rpstr = static_cast<double*>(rhsVar->data);
				pstr[r1] -= rpstr[r2];
			}

			break;
		}
		}
	}
	else if (tokens[1] == L"*=")
	{
		int r1, r2;
		lhsVar = getVar(tokens[0], r1);
		rhsVar = getVar(tokens[2], r2);

		lhsType = lhsVar->type;

		switch (lhsType)
		{
		case TYPE_INT:
		{
			if (rhsVar == nullptr)
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				pstr[r1] *= std::stoi(tokens[2]);
			}
			else
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				int* rpstr = static_cast<int*>(rhsVar->data);
				pstr[r1] *= rpstr[r2];
			}
			break;
		}
		case TYPE_LONG:
		{
			if (rhsVar == nullptr)
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				pstr[r1] *= std::stoll(tokens[2]);
			}
			else
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				long long int* rpstr = static_cast<long long int*>(rhsVar->data);
				pstr[r1] *= rpstr[r2];
			}
			break;
		}
		case TYPE_DOUBLE:
		{
			if (rhsVar == nullptr)
			{
				double* pstr = static_cast<double*>(lhsVar->data);
				pstr[r1] *= std::stod(tokens[2]);
			}
			else
			{
				double* pstr = static_cast<double*>(lhsVar->data);
				double* rpstr = static_cast<double*>(rhsVar->data);
				pstr[r1] *= rpstr[r2];
			}

			break;
		}
		}
	}
	else if (tokens[1] == L"/=")
	{
		int r1, r2;
		lhsVar = getVar(tokens[0], r1);
		rhsVar = getVar(tokens[2], r2);

		lhsType = lhsVar->type;

		switch (lhsType)
		{
		case TYPE_INT:
		{
			if (rhsVar == nullptr)
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				pstr[r1] /= std::stoi(tokens[2]);
			}
			else
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				int* rpstr = static_cast<int*>(rhsVar->data);
				pstr[r1] /= rpstr[r2];
			}
			break;
		}
		case TYPE_LONG:
		{
			if (rhsVar == nullptr)
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				pstr[r1] /= std::stoll(tokens[2]);
			}
			else
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				long long int* rpstr = static_cast<long long int*>(rhsVar->data);
				pstr[r1] /= rpstr[r2];
			}
			break;
		}
		case TYPE_DOUBLE:
		{
			if (rhsVar == nullptr)
			{
				double* pstr = static_cast<double*>(lhsVar->data);
				pstr[r1] /= std::stod(tokens[2]);
			}
			else
			{
				double* pstr = static_cast<double*>(lhsVar->data);
				double* rpstr = static_cast<double*>(rhsVar->data);
				pstr[r1] /= rpstr[r2];
			}

			break;
		}
		}
	}
	else if (tokens[1] == L"~=")
	{
		int r1, r2;
		lhsVar = getVar(tokens[0], r1);
		rhsVar = getVar(tokens[2], r2);

		lhsType = lhsVar->type;

		switch (lhsType)
		{
		case TYPE_INT:
		{
			if (rhsVar == nullptr)
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				pstr[r1] = ~std::stoi(tokens[2]);
			}
			else
			{
				int* pstr = static_cast<int*>(lhsVar->data);
				int* rpstr = static_cast<int*>(rhsVar->data);
				pstr[r1] = ~rpstr[r2];
			}

			break;
		}
		case TYPE_LONG:
		{
			if (rhsVar == nullptr)
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				pstr[r1] = ~std::stoi(tokens[2]);
			}
			else
			{
				long long int* pstr = static_cast<long long int*>(lhsVar->data);
				long long int* rpstr = static_cast<long long int*>(rhsVar->data);
				pstr[r1] = ~rpstr[r2];
			}

			break;
		}
		}
	}
	else if (tokens[1] == L"^=")
	{
		int r1, r2;
		lhsVar = getVar(tokens[0], r1);
		rhsVar = getVar(tokens[2], r2);

		lhsType = lhsVar->type;

		switch (lhsType)
		{
			case TYPE_INT:
			{
				if (rhsVar == nullptr)
				{
					int* pstr = static_cast<int*>(lhsVar->data);
					pstr[r1] ^= std::stoi(tokens[2]);
				}
				else
				{
					int* pstr = static_cast<int*>(lhsVar->data);
					int* rpstr = static_cast<int*>(rhsVar->data);
					pstr[r1] ^= rpstr[r2];
				}

				break;
			}
			case TYPE_LONG:
			{
				if (rhsVar == nullptr)
				{
					long long int* pstr = static_cast<long long int*>(lhsVar->data);
					pstr[r1] ^= std::stoi(tokens[2]);
				}
				else
				{
					long long int* pstr = static_cast<long long int*>(lhsVar->data);
					long long int* rpstr = static_cast<long long int*>(rhsVar->data);
					pstr[r1] ^= rpstr[r2];
				}

				break;
			}
		}
	}
}

bool execPlusOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] + rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] + rpstr[r2]);

		break;
	}
	case TYPE_DOUBLE:
	{
		if (createdLhs == true)
		{
			double* pstr = static_cast<double*>(lhsVar->data);
			pstr[r1] = std::stod(lhs);
		}

		if (createdRhs == true)
		{
			double* rpstr = static_cast<double*>(rhsVar->data);
			rpstr[r2] = std::stod(rhs);
		}

		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] + rpstr[r2]);

		break;
	}
	case TYPE_STRING:
	{
		if (createdLhs == true)
		{
			std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
			pstr[r1] = lhs.substr(1, lhs.length() - 2);

			findAndReplaceNewline(pstr[r1]);
			findAndReplaceQuoteEscape(pstr[r1]);
		}

		if (createdRhs == true)
		{
			std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
			rpstr[r2] = rhs.substr(1, rhs.length() - 2);

			findAndReplaceNewline(rpstr[r2]);
			findAndReplaceQuoteEscape(rpstr[r2]);
		}

		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
		lhs = pstr[r1] + rpstr[r2];

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execMinusOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] - rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] - rpstr[r2]);

		break;
	}
	case TYPE_DOUBLE:
	{
		if (createdLhs == true)
		{
			double* pstr = static_cast<double*>(lhsVar->data);
			pstr[r1] = std::stod(lhs);
		}

		if (createdRhs == true)
		{
			double* rpstr = static_cast<double*>(rhsVar->data);
			rpstr[r2] = std::stod(rhs);
		}

		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] - rpstr[r2]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execLeftShiftOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] << rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] << rpstr[r2]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execRightShiftOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] >> rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] >> rpstr[r2]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execMultiplyOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] * rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] * rpstr[r2]);

		break;
	}
	case TYPE_DOUBLE:
	{
		if (createdLhs == true)
		{
			double* pstr = static_cast<double*>(lhsVar->data);
			pstr[r1] = std::stod(lhs);
		}

		if (createdRhs == true)
		{
			double* rpstr = static_cast<double*>(rhsVar->data);
			rpstr[r2] = std::stod(rhs);
		}

		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] * rpstr[r2]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execDivideOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] / rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] / rpstr[r2]);

		break;
	}
	case TYPE_DOUBLE:
	{
		if (createdLhs == true)
		{
			double* pstr = static_cast<double*>(lhsVar->data);
			pstr[r1] = std::stod(lhs);
		}

		if (createdRhs == true)
		{
			double* rpstr = static_cast<double*>(rhsVar->data);
			rpstr[r2] = std::stod(rhs);
		}

		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] / rpstr[r2]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execModuloOperator(ReservedWord& assignmentType, std::wstring& lhs, std::wstring rhs)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] % rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		lhs = std::to_wstring(pstr[r1] % rpstr[r2]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execXorOperator(ReservedWord& assignmentType, std::wstring& l, std::wstring r)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	std::wstring lhs = l, rhs = r;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		l = std::to_wstring(pstr[r1] ^ rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		l = std::to_wstring(pstr[r1] ^ rpstr[r2]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execUnsignedRightShiftOperator(ReservedWord& assignmentType, std::wstring& l, std::wstring r)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	std::wstring lhs = l, rhs = r;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		
		unsigned int lhs = pstr[r1];
		unsigned int result = lhs >> rpstr[r2];
		l = std::to_wstring(result);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		
		unsigned long long int lhs = pstr[r1];
		unsigned long long int result = lhs >> rpstr[r2];
		l = std::to_wstring(result);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execBitwiseComplementOperator(ReservedWord& assignmentType, std::wstring& l, std::wstring r)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	std::wstring lhs = l, rhs = r;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		pstr[r1] = ~rpstr[r2];
		l = std::to_wstring(pstr[r1]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		pstr[r1] = ~rpstr[r2];
		l = std::to_wstring(pstr[r1]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execAndOperator(ReservedWord& assignmentType, std::wstring& l, std::wstring r)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	std::wstring lhs = l, rhs = r;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		l = std::to_wstring(pstr[r1] & rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		l = std::to_wstring(pstr[r1] & rpstr[r2]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execOrOperator(ReservedWord& assignmentType, std::wstring& l, std::wstring r)
{
	int r1, r2;
	bool createdLhs, createdRhs;
	std::wstring lhs = l, rhs = r;
	Var* lhsVar = getVar(lhs, assignmentType, r1, createdLhs);
	Var* rhsVar = getVar(rhs, assignmentType, r2, createdRhs);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (createdLhs == true)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(lhs);
		}

		if (createdRhs == true)
		{
			int* rpstr = static_cast<int*>(rhsVar->data);
			rpstr[r2] = std::stoi(rhs);
		}

		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		l = std::to_wstring(pstr[r1] | rpstr[r2]);

		break;
	}
	case TYPE_LONG:
	{
		if (createdLhs == true)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(lhs);
		}

		if (createdRhs == true)
		{
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			rpstr[r2] = std::stoll(rhs);
		}

		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		l = std::to_wstring(pstr[r1] | rpstr[r2]);

		break;
	}
	}

	if (createdLhs == true)
	{
		delete lhsVar;
	}

	if (createdRhs == true)
	{
		delete rhsVar;
	}

	return false;
}

bool execGreaterThanOrEqualsOperator(Var* lhsVar, int& r1, Var* rhsVar, int& r2)
{
	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		return pstr[r1] >= rpstr[r2];
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		return pstr[r1] >= rpstr[r2];
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		return pstr[r1] >= rpstr[r2];
	}
	case TYPE_STRING:
	{
		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
		return pstr[r1] >= rpstr[r2];
	}
	}

	return false;
}

bool execGreaterThanOperator(Var* lhsVar, int& r1, Var* rhsVar, int& r2)
{
	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		return pstr[r1] > rpstr[r2];
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		return pstr[r1] > rpstr[r2];
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		return pstr[r1] > rpstr[r2];
	}
	case TYPE_STRING:
	{
		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
		return pstr[r1] > rpstr[r2];
	}
	}

	return false;
}

bool execLessThanOrEqualsOperator(Var* lhsVar, int& r1, Var* rhsVar, int& r2)
{
	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		return pstr[r1] <= rpstr[r2];
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		return pstr[r1] <= rpstr[r2];
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		return pstr[r1] <= rpstr[r2];
	}
	case TYPE_STRING:
	{
		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
		return pstr[r1] <= rpstr[r2];
	}
	}

	return false;
}

bool execLessThanOperator(Var* lhsVar, int& r1, Var* rhsVar, int& r2)
{
	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		return pstr[r1] < rpstr[r2];
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		return pstr[r1] < rpstr[r2];
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		return pstr[r1] < rpstr[r2];
	}
	case TYPE_STRING:
	{
		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
		return pstr[r1] < rpstr[r2];
	}
	}

	return false;
}

bool execNotEqualsOperator(Var* lhsVar, int& r1, Var* rhsVar, int& r2)
{
	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		return pstr[r1] != rpstr[r2];
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		return pstr[r1] != rpstr[r2];
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		return pstr[r1] != rpstr[r2];
	}
	case TYPE_STRING:
	{
		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
		return pstr[r1] != rpstr[r2];
	}
	}

	return false;
}

bool execEqualsOperator(Var* lhsVar, int& r1, Var* rhsVar, int& r2)
{
	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		return pstr[r1] == rpstr[r2];
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		return pstr[r1] == rpstr[r2];
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		return pstr[r1] == rpstr[r2];
	}
	case TYPE_STRING:
	{
		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
		return pstr[r1] == rpstr[r2];
	}
	}

	return false;
}

void execAssignOperator(Var* lhsVar, int& r1, Var* rhsVar, int& r2)
{
	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);
		pstr[r1] = rpstr[r2];

		break;
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);
		pstr[r1] = rpstr[r2];
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);
		pstr[r1] = rpstr[r2];

		break;
	}
	case TYPE_STRING:
	{
		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);

		pstr[r1] = std::wstring(rpstr[r2]);

		break;
	}
	case TYPE_OBJECT:
	{
		ObjectStore** objStore1 = static_cast<ObjectStore**>(lhsVar->data);

		for (int i = 0; i < lhsVar->size; ++i)
		{
			delete objStore1[i];
		}

		ObjectStore** objStore = new ObjectStore * [rhsVar->size];
		for (int i = 0; i < rhsVar->size; ++i)
		{
			objStore[i] = new ObjectStore();
		}
		objStore1 = objStore;
		lhsVar->data = objStore1;
		lhsVar->size = rhsVar->size;

		ObjectStore** objStore2 = static_cast<ObjectStore**>(rhsVar->data);

		for (int i = 0; i < rhsVar->size; ++i)
		{
			ObjectStore* obj1 = objStore1[i];
			ObjectStore* obj2 = objStore2[i];

			std::vector<std::wstring> keys = obj2->getKeys();
			for (int i = 0; i < keys.size(); ++i)
			{
				int toCopyIndex;
				Var* toCopyVar = obj2->getVar(keys.at(i), toCopyIndex);
				obj1->addVar(new Var(keys.at(i), toCopyVar[toCopyIndex].type, toCopyVar[toCopyIndex].size));

				int newIndex;
				Var* newVar = obj1->getVar(keys.at(i), newIndex);
				execAssignOperator(newVar, toCopyVar);
			}
		}

		break;
	}
	}
}

void execAssignOperator(Var* lhsVar, Var* rhsVar)
{
	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		int* pstr = static_cast<int*>(lhsVar->data);
		int* rpstr = static_cast<int*>(rhsVar->data);

		for (int i = 0; i < lhsVar->size; ++i)
			pstr[i] = rpstr[i];

		break;
	}
	case TYPE_LONG:
	{
		long long int* pstr = static_cast<long long int*>(lhsVar->data);
		long long int* rpstr = static_cast<long long int*>(rhsVar->data);

		for (int i = 0; i < lhsVar->size; ++i)
			pstr[i] = rpstr[i];

		break;
	}
	case TYPE_DOUBLE:
	{
		double* pstr = static_cast<double*>(lhsVar->data);
		double* rpstr = static_cast<double*>(rhsVar->data);

		for (int i = 0; i < lhsVar->size; ++i)
			pstr[i] = rpstr[i];

		break;
	}
	case TYPE_STRING:
	{
		std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
		std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);

		for (int i = 0; i < lhsVar->size; ++i)
			pstr[i] = std::wstring(rpstr[i]);

		break;
	}
	case TYPE_OBJECT:
	{
		ObjectStore** objStore1 = static_cast<ObjectStore**>(lhsVar->data);

		for (int i = 0; i < lhsVar->size; ++i)
		{
			delete objStore1[i];
		}

		ObjectStore** objStore = new ObjectStore * [rhsVar->size];
		for (int i = 0; i < rhsVar->size; ++i)
		{
			objStore[i] = new ObjectStore();
		}
		objStore1 = objStore;
		lhsVar->data = objStore1;
		lhsVar->size = rhsVar->size;

		ObjectStore** objStore2 = static_cast<ObjectStore**>(rhsVar->data);
		
		for (int i = 0; i < rhsVar->size; ++i)
		{
			ObjectStore* obj1 = objStore1[i];
			ObjectStore* obj2 = objStore2[i];

			std::vector<std::wstring> keys = obj2->getKeys();
			for (int i = 0; i < keys.size(); ++i)
			{
				int toCopyIndex;
				Var* toCopyVar = obj2->getVar(keys.at(i), toCopyIndex);
				obj1->addVar(new Var(keys.at(i), toCopyVar[toCopyIndex].type, toCopyVar[toCopyIndex].size));

				int newIndex;
				Var* newVar = obj1->getVar(keys.at(i), newIndex);
				execAssignOperator(newVar, toCopyVar);
			}
		}

		break;
	}
	}
}

void execAssignOperator(const std::wstring& lhs, const std::wstring& rhs)
{
	int r1, r2;
	Var* lhsVar = getVar(lhs, r1);
	Var* rhsVar = getVar(rhs, r2);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (rhsVar == nullptr)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(rhs);
		}
		else
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			int* rpstr = static_cast<int*>(rhsVar->data);
			pstr[r1] = rpstr[r2];
		}
		break;
	}
	case TYPE_LONG:
	{
		if (rhsVar == nullptr)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(rhs);
		}
		else
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			pstr[r1] = rpstr[r2];
		}
		break;
	}
	case TYPE_DOUBLE:
	{
		if (rhsVar == nullptr)
		{
			double* pstr = static_cast<double*>(lhsVar->data);
			pstr[r1] = std::stod(rhs);
		}
		else
		{
			double* pstr = static_cast<double*>(lhsVar->data);
			double* rpstr = static_cast<double*>(rhsVar->data);
			pstr[r1] = rpstr[r2];
		}

		break;
	}
	case TYPE_STRING:
	{
		if (rhsVar == nullptr)
		{
			std::wstring temp = rhs.substr(1);
			temp = temp.substr(0, temp.length() - 1);

			findAndReplaceNewline(temp);
			findAndReplaceQuoteEscape(temp);

			std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
			//std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
			pstr[r1] = temp;
		}
		else
		{
			std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
			std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
			pstr[r1] = std::wstring(rpstr[r2]);
		}

		break;
	}
	}
}

void execAssignOperator(const std::wstring& lhs, int r1, const std::wstring& rhs)
{
	int r2;
	int r1Temp;
	bool created = false;
	Var* lhsVar = getVar(lhs, r1Temp);
	Var* rhsVar = getVar(rhs, lhsVar->type, r2, created);

	ReservedWord lhsType = lhsVar->type;

	switch (lhsType)
	{
	case TYPE_INT:
	{
		if (rhsVar == nullptr)
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			pstr[r1] = std::stoi(rhs);
		}
		else
		{
			int* pstr = static_cast<int*>(lhsVar->data);
			int* rpstr = static_cast<int*>(rhsVar->data);
			pstr[r1] = rpstr[r2];
		}

		break;
	}
	case TYPE_LONG:
	{
		if (rhsVar == nullptr)
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			pstr[r1] = std::stoll(rhs);
		}
		else
		{
			long long int* pstr = static_cast<long long int*>(lhsVar->data);
			long long int* rpstr = static_cast<long long int*>(rhsVar->data);
			pstr[r1] = rpstr[r2];
		}
		break;
	}
	case TYPE_DOUBLE:
	{
		if (rhsVar == nullptr)
		{
			double* pstr = static_cast<double*>(lhsVar->data);
			pstr[r1] = std::stod(rhs);
		}
		else
		{
			double* pstr = static_cast<double*>(lhsVar->data);
			double* rpstr = static_cast<double*>(rhsVar->data);
			pstr[r1] = rpstr[r2];
		}

		break;
	}
	case TYPE_STRING:
	{
		if (rhsVar == nullptr)
		{
			std::wstring temp = rhs.substr(1);
			temp = temp.substr(0, temp.length() - 1);

			findAndReplaceNewline(temp);
			findAndReplaceQuoteEscape(temp);

			std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
			//std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
			pstr[r1] = temp;
		}
		else
		{
			std::wstring* pstr = static_cast<std::wstring*>(lhsVar->data);
			std::wstring* rpstr = static_cast<std::wstring*>(rhsVar->data);
			pstr[r1] = rpstr[r2];
		}

		break;
	}
	}

	if (created == true)
	{
		delete rhsVar;
	}
}

#endif
