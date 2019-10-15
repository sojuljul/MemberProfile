#include "pch.h"
#include "HTMembers.h"


HTMembers::HTMembers()
{
	for (int i = 0; i < SIZE; i++)
	{
		table[i].head = NULL;
	}
}


HTMembers::~HTMembers()
{
}

bool HTMembers::deleteMember(string groupName, string stageName)
{
	int hashNumber = 0;
	for (int i = 0; i < groupName.length(); i++)
	{
		hashNumber += groupName[i];
	}
	hashNumber = hashNumber % HASH_NUM;

	if (table[hashNumber].head == NULL)
	{
		return false;
	}
	else if (stageName == table[hashNumber].head->data->getStageName())
	{
		HashNode* tempNode = table[hashNumber].head;
		table[hashNumber].head = table[hashNumber].head->next;
		delete tempNode;
		return true;
	}
	else
	{
		HashNode* current = table[hashNumber].head;

		while (current->next != NULL)
		{
			if (current->next->data->getStageName() == stageName)
			{
				HashNode* tempNode = current->next;
				current->next = current->next->next;
				delete tempNode;
				return true;
			}

			current = current->next;
		}

		return false;
		
	}

	
}

void HTMembers::updateMember(string groupName, string stageName, string newStageName, string birthName, string birthday, int height, int weight)
{
	int hashNumber = 0;
	for (int i = 0; i < groupName.length(); i++)
	{
		hashNumber += groupName[i];
	}
	hashNumber = hashNumber % HASH_NUM;

	HashNode* current = table[hashNumber].head;

	string tempStage = stageName;
	transform(tempStage.begin(), tempStage.end(), tempStage.begin(), ::tolower);

	while (current != NULL)
	{
		string tempCurrentName = current->data->getStageName();
		transform(tempCurrentName.begin(), tempCurrentName.end(), tempCurrentName.begin(), ::tolower);

		if (tempCurrentName == tempStage)
		{
			current->data->setStageName(newStageName);
			current->data->setBirthName(birthName);
			current->data->setBirthday(birthday);
			current->data->setHeight(height);
			current->data->setWeight(weight);
			return;
		}

		current = current->next;
	}
	
}

void HTMembers::displayAllGroups()
{
	cout << endl;
	cout << "-------------------------" << endl;
	cout << "GROUP NAMES:" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		if (table[i].head != NULL)
		{
			cout << table[i].head->data->getGroupName() << endl;
		}
	}
	cout << "-------------------------" << endl;
	cout << endl;
}

bool HTMembers::displayMember(string groupName, string stageName)
{
	int hashNumber = 0;
	for (int i = 0; i < groupName.length(); i++)
	{
		hashNumber += groupName[i];
	}
	hashNumber = hashNumber % HASH_NUM;

	HashNode* current = table[hashNumber].head;

	string tempStage = stageName;
	transform(tempStage.begin(), tempStage.end(), tempStage.begin(), ::tolower);

	while (current != NULL)
	{
		string tempCurrentName = current->data->getStageName();
		transform(tempCurrentName.begin(), tempCurrentName.end(), tempCurrentName.begin(), ::tolower);

		if (tempCurrentName == tempStage)
		{
			cout << endl;
			cout << "-------------------------" << endl;
			cout << "Group Name: " << current->data->getGroupName() << endl;
			cout << "Stage Name: " << current->data->getStageName() << endl;
			cout << "Birth Name: " << current->data->getBirthName() << endl;
			cout << "Birthday: " << current->data->getBirthday() << endl;
			cout << "Height(cm): " << current->data->getHeight() << endl;
			cout << "Weight(kg): " << current->data->getWeight() << endl;
			cout << "-------------------------" << endl;
			cout << endl;
			return true;
		}

		current = current->next;
	}
	
	return false;
}

void HTMembers::displayGroup(string groupName)
{
	int hashNumber = 0;
	for (int i = 0; i < groupName.length(); i++)
	{
		hashNumber += groupName[i];
	}
	hashNumber = hashNumber % HASH_NUM;

	HashNode* current = table[hashNumber].head;

	if (current == NULL)
	{
		cout << "Not found" << endl;
	}
	else
	{
		cout << endl;
		cout << "-------------------------" << endl;
		cout << "Group Name: " << groupName << endl;

		while (current != NULL)
		{
			cout << current->data->getStageName() << endl;
			current = current->next;
		}

		cout << "-------------------------" << endl;
		cout << endl;
	}

	
}

bool HTMembers::insertMember(Member* newMember)
{
	int hashNumber = 0;
	string groupName = newMember->getGroupName();

	for (int i = 0; i < groupName.length(); i++)
	{
		hashNumber += groupName[i];
	}

	hashNumber = hashNumber % HASH_NUM;

	HashNode* newNode = new HashNode;
	newNode->data = newMember;
	newNode->next = NULL;

	if (table[hashNumber].head == NULL)
	{
		newNode->next = table[hashNumber].head;
		table[hashNumber].head = newNode;
		return true;
	}
	else if (table[hashNumber].head->data->getStageName() == newMember->getStageName())
	{
		return false;
	}
	else
	{
		HashNode* current = table[hashNumber].head;

		while (current->next != NULL)
		{
			if (current->next->data->getStageName() == newMember->getStageName())
			{
				return false;
			}
			current = current->next;
		}

		current->next = newNode;
	}
	return true;
}