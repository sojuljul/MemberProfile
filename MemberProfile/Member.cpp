#include "pch.h"
#include "Member.h"


Member::Member()
{
	this->groupName = "";
	this->stageName = "";
	this->birthName = "";
	this->birthday = "";
	this->height = -1;
	this->weight = -1;
}

Member::Member(string groupName, string stageName, string birthName, string birthday, int height, int weight)
{
	this->groupName = groupName;
	this->stageName = stageName;
	this->birthName = birthName;
	this->birthday = birthday;
	this->height = height;
	this->weight = weight;
}


Member::~Member()
{
}

string Member::getGroupName()
{
	return this->groupName;
}


string Member::getStageName()
{
	return this->stageName;
}
string Member::getBirthName()
{
	return this->birthName;
}

string Member::getBirthday()
{
	return this->birthday;
}

int Member::getHeight()
{
	return this->height;
}

int Member::getWeight()
{
	return this->weight;
}

void  Member::setGroupName(string groupName)
{
	this->groupName = groupName;
}
void  Member::setStageName(string stageName)
{
	this->stageName = stageName;
}
void  Member::setBirthName(string birthName)
{
	this->birthName = birthName;
}
void  Member::setBirthday(string birthday)
{
	this->birthday = birthday;
}
void  Member::setHeight(int height)
{
	this->height = height;
}
void  Member::setWeight(int weight)
{
	this->weight = weight;
}