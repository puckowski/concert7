
#ifndef WORKSPACE_STORE_H
#define WORKSPACE_STORE_H

#include <vector>
#include <string>
#include <unordered_map>

class WorkspaceStore;

extern thread_local std::vector<std::string> workspaceStack;

#include "VarStore.h"

class WorkspaceStore
{
	std::list < std::pair<const std::string, VarStore*>, std::allocator<std::pair<const std::string, VarStore*>>>::iterator mBackIterator;
	std::unordered_map<std::string, VarStore*> mVars;
	VarStore* mBack;

public:
	WorkspaceStore();

	~WorkspaceStore();

	void print();

	VarStore* getStore(const std::string &name);

	void addStore(const std::string &name, VarStore* varStore);

	void addGlobalStore(VarStore* varStore);

	void addGlobalStoreWithoutStackEntry(VarStore* varStore);

	VarStore* getStore();

	void removeStore();

	void setBack();

	int count();
	std::pair<std::string, VarStore*> removeStoreAndReturn();
	void addStoreSimple(const std::string &name, VarStore* varStore);
	void removeStore(const std::string &name);
	bool hasStore(const std::string &name);
};

#endif