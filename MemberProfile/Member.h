#pragma once

using namespace std;

#include <iostream>
#include <string>

class Member
{
public:

	Member();
	Member(string groupName, string stageName, string birthName, string birthday, int height, int weight);
	~Member();

	string getGroupName();
	string getStageName();
	string getBirthName();
	string getBirthday();
	int getHeight();
	int getWeight();

	void setGroupName(string groupName);
	void setStageName(string stageName);
	void setBirthName(string birthName);
	void setBirthday(string birthday);
	void setHeight(int height);
	void setWeight(int weight);

private:
	string groupName;
	string stageName;
	string birthName;
	string birthday;
	int height;
	int weight;
};

