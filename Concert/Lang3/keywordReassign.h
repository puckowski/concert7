
#ifndef KEYWORD_REASSIGN_H
#define KEYWORD_REASSIGN_H

#include <string>
#include <vector>

#include "sourceFunctions.h"

void executeKeywordReassign(std::vector<std::string>& tokens)
{
	int index;
	bool createdVar = false;

	Var* toReassignVar = getVar(tokens[1], index, createdVar);

	int index2;
	bool createdVar2 = false;

	Var* nameVar = getVar(tokens[2], index2, createdVar2);

	if (toReassignVar->data != nameVar->data) {
		VarStore* vs = gWorkspaceStore->getStore();
		std::set<long long> deletedDataSet = gWorkspaceStore->getDeletedDataSet();
		vs->reassignVar(toReassignVar, nameVar, deletedDataSet);
		gWorkspaceStore->setDeletedDataSet(deletedDataSet);
	}

	if (createdVar)
		delete toReassignVar;

	if (createdVar2)
		delete nameVar;
}

#endif