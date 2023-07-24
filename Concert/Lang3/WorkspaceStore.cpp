
#ifndef WORKSPACE_STORE_CPP
#define WORKSPACE_STORE_CPP

#include "WorkspaceStore.h"

WorkspaceStore::WorkspaceStore()
{
}

WorkspaceStore::~WorkspaceStore()
{
	for (auto it = mVars.begin(); it != mVars.end(); ) {
		it = mVars.erase(it);
	}
}

void WorkspaceStore::print() {
	for (auto it = mVars.begin(); it != mVars.end(); ++it) {
		std::cout << "Store: " << it->first << std::endl;
		it->second->print();
		std::cout << std::endl;
	}
}

VarStore* WorkspaceStore::getStore(const std::string &name)
{
	return mVars.find(name)->second;
}

void WorkspaceStore::addStoreSimple(const std::string &name, VarStore* varStore)
{
	mVars.insert({ name, varStore });
}

void WorkspaceStore::addStore(const std::string &name, VarStore* varStore)
{
	mVars.insert({ name, varStore });

	mBack = varStore;
}

void WorkspaceStore::addGlobalStore(VarStore* varStore)
{
	workspaceStack.push_back("global");
	mVars.insert({ "global", varStore });

	mBack = varStore;
}

void WorkspaceStore::addGlobalStoreWithoutStackEntry(VarStore* varStore)
{
	mVars.insert({ "global", varStore });

	mBack = varStore;
}

VarStore* WorkspaceStore::getStore()
{
	return mBack;
}

void WorkspaceStore::removeStore()
{
	mVars.erase(workspaceStack.back());
}

void WorkspaceStore::removeStore(const std::string &name)
{
	mVars.erase(name);
}

bool WorkspaceStore::hasStore(const std::string &name)
{
	return mVars.find(name) != mVars.end();
}

std::pair<std::string, VarStore*> WorkspaceStore::removeStoreAndReturn()
{
	std::pair<std::string, VarStore*> lastStore;

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

#endif