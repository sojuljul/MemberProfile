#pragma once

using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <algorithm>

#include "Member.h"

class HTMembers
{

	static const int SIZE = 100;
	static const int HASH_NUM = 100;

public:
	HTMembers();
	~HTMembers();

	bool insertMember(Member* newMember);
	void displayGroup(string groupName);
	bool displayMember(string groupName, string stageName);
	void displayAllGroups();
	void updateMember(string groupName, string stageName, string newStageName, string birthName, string birthday, int height, int weight);
	bool deleteMember(string groupName, string stageName);

private:
	struct HashNode;

	struct HashList
	{
		HashNode* head;
	};

	struct HashNode
	{
		Member* data;
		HashNode* next;
	};

	HashList table[SIZE];
};

