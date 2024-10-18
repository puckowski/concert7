
#ifndef WORKSPACE_STORE_CPP
#define WORKSPACE_STORE_CPP

#include "WorkspaceStore.h"

WorkspaceStore::WorkspaceStore()
{
}

WorkspaceStore::~WorkspaceStore()
{
	for (auto it = mVars.begin(); it != mVars.end(); ) {
		const VarStore* vs = it->second;
		it = mVars.erase(it);
		delete vs;
		vs = nullptr;
	}
}

void WorkspaceStore::print() {
	for (auto it = mVars.begin(); it != mVars.end(); ++it) {
		std::wcout << L"Store: " << it->first << std::endl;
		it->second->print();
		std::cout << std::endl;
	}
}

VarStore* WorkspaceStore::getStore(const std::wstring &name)
{
	return mVars.find(name)->second;
}

void WorkspaceStore::addStoreSimple(const std::wstring &name, VarStore* varStore)
{
	mVars.insert({ name, varStore });
}

void WorkspaceStore::addStore(const std::wstring &name, VarStore* varStore)
{
	mVars.insert({ name, varStore });

	mBack = varStore;
}

void WorkspaceStore::addGlobalStore(VarStore* varStore)
{
	workspaceStack.push_back(L"global");
	mVars.insert({ L"global", varStore });

	mBack = varStore;
}

void WorkspaceStore::addGlobalStoreWithoutStackEntry(VarStore* varStore)
{
	mVars.insert({ L"global", varStore });

	mBack = varStore;
}

VarStore* WorkspaceStore::getStore()
{
	return mBack;
}

void WorkspaceStore::reassignVar(Var* toReassign, Var* newVar)
{
	for (auto it = mVars.begin(); it != mVars.end();) 
	{
		it->second->reassignAllVar(toReassign, newVar);
	}
}

void WorkspaceStore::removeStore()
{
	VarStore* vs = getStore(workspaceStack.back());
	mVars.erase(workspaceStack.back());
	delete vs;
	vs = nullptr;
}

void WorkspaceStore::removeStore(const std::wstring &name)
{
	mVars.erase(name);
}

bool WorkspaceStore::hasStore(const std::wstring &name)
{
	return mVars.find(name) != mVars.end();
}

std::pair<std::wstring, VarStore*> WorkspaceStore::removeStoreAndReturn()
{
	std::pair<std::wstring, VarStore*> lastStore;

	lastStore = std::make_pair(workspaceStack.back(), mVars.find(workspaceStack.back())->second);

	mVars.erase(workspaceStack.back());

	return lastStore;
}

void WorkspaceStore::setBack() {
	mBackIterator = mVars.find(workspaceStack.back());
	mBack = mBackIterator->second;
}

int WorkspaceStore::count()
{
	return mVars.size();
}

std::set<long long>& WorkspaceStore::getDeletedDataSet() {
	return deletedDataSet;
}

void WorkspaceStore::setDeletedDataSet(std::set<long long>& set) {
	deletedDataSet.clear();
	deletedDataSet = set;
}

#endif