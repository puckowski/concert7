
#ifndef WORKSPACE_STORE_H
#define WORKSPACE_STORE_H

#include <vector>
#include <string>
#include <set>
#include <unordered_map>

class WorkspaceStore;

extern thread_local std::vector<std::wstring> workspaceStack;

#include "VarStore.h"

class WorkspaceStore
{
	std::list < std::pair<const std::wstring, VarStore*>, std::allocator<std::pair<const std::wstring, VarStore*>>>::iterator mBackIterator;
	std::unordered_map<std::wstring, VarStore*> mVars;
	VarStore* mBack;
	std::set<long long> deletedDataSet;

public:
	WorkspaceStore();

	~WorkspaceStore();

	void print();
	std::set<long long>& getDeletedDataSet();
	void setDeletedDataSet(std::set<long long>& set);

	VarStore* getStore(const std::wstring &name);

	void addStore(const std::wstring &name, VarStore* varStore);

	void addGlobalStore(VarStore* varStore);

	void addGlobalStoreWithoutStackEntry(VarStore* varStore);

	VarStore* getStore();

	void removeStore();

	void setBack();

	int count();
	std::pair<std::wstring, VarStore*> removeStoreAndReturn();
	void addStoreSimple(const std::wstring &name, VarStore* varStore);
	void removeStore(const std::wstring &name);
	bool hasStore(const std::wstring &name);
	void reassignVar(Var* toReassign, Var* newVar);
};

#endif