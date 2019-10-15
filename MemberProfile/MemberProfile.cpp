// MemberProfile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm> 

#include "HTMembers.h"

using namespace std;

HTMembers memberTable;

void insertMember();
void loadMembers();
void displayGroup();
void displayMember();
void displayAllGroups();
void editMember();
void deleteMember();

int main()
{
	system("title KPOP MEMBER PROFILE SYSTEM");
	system("color 0f");

	loadMembers();
	int selection;

	do
	{		
		cout << "Select an option" << endl;
		cout << "1. Insert a member" << endl;
		cout << "2. Display all groups" << endl;
		cout << "3. Display group members" << endl;
		cout << "4. Display member info" << endl;
		cout << "5. Edit a member" << endl;
		cout << "6. Delete a member" << endl;
		cout << "7. Exit" << endl;

		cin >> selection;

		switch (selection)
		{
		case 1:
			insertMember();
			break;
		case 2:
			displayAllGroups();
			break;
		case 3:
			displayGroup();
			break;
		case 4:
			displayMember();
			break;
		case 5:
			editMember();
			break;
		case 6:
			deleteMember();
			break;
		default:
			cout << "Invalid selection" << endl;
			cout << endl;
			break;
		}
	} while (selection != 7);
}

bool checkBirthday(string birthday)
{
	// MM / DD / YYYY
	// 01 2 34 5 6789
	if (birthday.length() != 10)
	{
		cout << "Invalid length" << endl;
		return false;
	}

	if (birthday[2] != '/' || birthday[5] != '/')
	{
		cout << "Invalid no slash" << endl;
		return false;
	}

	for (int i = 0; i < birthday.length(); i++)
	{
		if (i == 2 || i == 5)
		{
			continue;
		}

		if (birthday[i] >= 48 && birthday[i] <= 57)
		{
			continue;
		}
		else
		{
			cout << "Invalid not number" << endl;
			return false;
		}
	}

	int month = stoi(birthday.substr(0, 2));
	int day = stoi(birthday.substr(3, 2));
	int year = stoi(birthday.substr(6, 4));

	if (month < 1 || month > 12)
	{
		cout << "Invalid month" << endl;
		return false;
	}

	if (month == 2)
	{
		int leapYear = (year % 4);
		if (leapYear == 0)
		{
			if (day < 1 || day > 29)
			{
				cout << "Invalid day" << endl;
				return false;
			}
		}
		else
		{
			if (day < 1 || day > 28)
			{
				cout << "Invalid day" << endl;
				return false;
			}
		}
		
	}
	else
	{
		int remMonth = (month % 7) % 2;
		if (remMonth == 0)
		{
			if (day < 1 || day > 30)
			{
				cout << "Invalid day" << endl;
				return false;
			}
		}
		else
		{
			if (day < 1 || day > 31)
			{
				cout << "Invalid day" << endl;
				return false;
			}
		}
	}

	if (year >= 2019)
	{
		cout << "Invalid year" << endl;
		return false;
	}

	return true;
}

void deleteMember()
{
	cin.ignore();

	string groupName;
	string stageName;

	cout << "Enter group name: ";
	getline(cin, groupName);

	cout << "Enter stage name (case sensitive): ";
	getline(cin, stageName);

	transform(groupName.begin(), groupName.end(), groupName.begin(), ::toupper);

	if (memberTable.deleteMember(groupName, stageName))
	{
		cout << "Successfully deleted a member" << endl;
		cout << endl;

		ifstream inFile("members.txt");
		string line;
		ofstream outFile("updated.txt", ios::trunc);

		if (inFile.is_open())
		{
			while (getline(inFile, line))
			{
				stringstream linestream(line);
				string fileGroupName;
				string fileStageName;
				string fileBirthName;
				string fileBirthday;
				string fileHeight;
				string fileWeight;

				getline(linestream, fileGroupName, ',');
				getline(linestream, fileStageName, ',');
				getline(linestream, fileBirthName, ',');
				getline(linestream, fileBirthday, ',');
				getline(linestream, fileHeight, ',');
				getline(linestream, fileWeight, ',');

				if (groupName == fileGroupName && stageName == fileStageName)
				{
					continue;
				}
				else
				{
					outFile << fileGroupName << "," << fileStageName << "," << fileBirthName << "," << fileBirthday << "," << fileHeight << "," << fileWeight << endl;
				}
			}

			inFile.close();
			outFile.close();
		}

		ifstream inFileNew("updated.txt");
		ofstream outFileNew("members.txt", ios::trunc);

		if (inFileNew.is_open())
		{
			outFileNew << inFileNew.rdbuf();
			inFileNew.close();
			outFileNew.close();
		}
		else
		{
			cout << "Unable to open file" << endl;
			cout << endl;
		}

	}
	else
	{
		cout << "Not found" << endl;
		cout << endl;
	}

}

void editMember()
{
	cin.ignore();

	string groupName;
	string stageName;

	cout << "Enter group name: ";
	getline(cin, groupName);

	cout << "Enter stage name: ";
	getline(cin, stageName);

	transform(groupName.begin(), groupName.end(), groupName.begin(), ::toupper);

	if (memberTable.displayMember(groupName, stageName))
	{
		string newStageName;
		string newBirthName;
		string newBirthday;
		string newHeight;
		string newWeight;

		cout << "UPDATING" << endl;
		cout << "Enter new stage name: ";
		getline(cin, newStageName);
		cout << "Enter new birth name: ";
		getline(cin, newBirthName);
		cout << "Enter new birthday: ";
		getline(cin, newBirthday);

		if (!checkBirthday(newBirthday))
		{
			cout << "ERROR: Birthday input" << endl;
			cout << endl;
			return;
		}

		cout << "Enter new height: ";
		getline(cin, newHeight);
		cout << "Enter new weight: ";
		getline(cin, newWeight);

		int heightConvert = stoi(newHeight);
		int weightConvert = stoi(newWeight);

		memberTable.updateMember(groupName, stageName, newStageName, newBirthName, newBirthday, heightConvert, weightConvert);

		ifstream inFile("members.txt");
		string line;

		ofstream outFile("updated.txt", ios::trunc);

		if (inFile.is_open())
		{
			while (getline(inFile, line))
			{
				stringstream linestream(line);
				string fileGroupName;
				string fileStageName;
				string fBirthName;
				string fBirthday;
				string fHeight;
				string fWeight;

				getline(linestream, fileGroupName, ',');
				getline(linestream, fileStageName, ',');
				getline(linestream, fBirthName, ',');
				getline(linestream, fBirthday, ',');
				getline(linestream, fHeight, ',');
				getline(linestream, fWeight, ',');

				string tempFStageName = fileStageName;
				transform(tempFStageName.begin(), tempFStageName.end(), tempFStageName.begin(), ::tolower);

				string tempRegStage = stageName;
				transform(tempRegStage.begin(), tempRegStage.end(), tempRegStage.begin(), ::tolower);

				if (fileGroupName == groupName && tempFStageName == tempRegStage)
				{
					outFile << groupName << "," << newStageName << "," << newBirthName << "," << newBirthday << "," << heightConvert << "," << weightConvert << endl;
				}
				else
				{
					outFile << fileGroupName << "," << fileStageName << "," << fBirthName << "," << fBirthday << "," << fHeight << "," << fWeight << endl;
				}



			}
			
			cout << "Successfully updated a member" << endl;
			cout << endl;

			inFile.close();
			outFile.close();
		}
		else
		{
			cout << "Unable to open file" << endl;
		}


		ifstream inFileNew("updated.txt");
		ofstream outFileNew("members.txt", ios::trunc);

		if (inFileNew.is_open())
		{
			outFileNew << inFileNew.rdbuf();
			inFileNew.close();
			outFileNew.close();
		}
		else
		{
			cout << "Unable to open file" << endl;
			cout << endl;
		}
	}
	else
	{
		cout << "Not found" << endl;
		cout << endl;
	}	

}

void displayAllGroups()
{
	memberTable.displayAllGroups();
}

void displayMember()
{
	string groupName;
	string stageName;

	cin.ignore();

	cout << "Enter group name: ";
	getline(cin, groupName);

	cout << "Enter stage name: ";
	getline(cin, stageName);

	transform(groupName.begin(), groupName.end(), groupName.begin(), ::toupper);
	if (!memberTable.displayMember(groupName, stageName))
	{
		cout << "Not found" << endl;
		cout << endl;
	};
}

void displayGroup()
{
	string groupName;
	cin.ignore();

	cout << "Enter group name: ";
	getline(cin, groupName);

	transform(groupName.begin(), groupName.end(), groupName.begin(), ::toupper);

	memberTable.displayGroup(groupName);
}

void loadMembers()
{
	ifstream inFile("members.txt");
	string line;

	if (inFile.is_open())
	{
		while (getline(inFile, line))
		{
			stringstream linestream(line);
			
			string groupName;
			string stageName;
			string birthName;
			string birthday;
			string height;
			string weight;

			getline(linestream, groupName, ',');
			getline(linestream, stageName, ',');
			getline(linestream, birthName, ',');
			getline(linestream, birthday, ',');
			getline(linestream, height, ',');
			getline(linestream, weight, ',');

			int heightConvert = stoi(height);
			int weightConvert = stoi(weight);

			Member* newMember = new Member(groupName, stageName, birthName, birthday, heightConvert, weightConvert);
			memberTable.insertMember(newMember);

		}

		inFile.close();
	}
	else
	{
		cout << "Unnable to open file" << endl;
	}
}

void insertMember()
{
	string groupName;
	string stageName;
	string birthName;
	string birthday;
	int height;
	int weight;

	cin.ignore();

	cout << endl;
	cout << "-------------------------" << endl;
	cout << "INSERTING A MEMBER" << endl;
	cout << "-------------------------" << endl;

	cout << "Enter group name: ";
	getline(cin, groupName);

	cout << "Enter stage name: ";
	getline(cin, stageName);

	cout << "Enter birth name: ";
	getline(cin, birthName);

	cout << "Enter birthday(MM/DD/YYYY): ";
	getline(cin, birthday);

	if (!checkBirthday(birthday))
	{
		cout << "ERROR: Birthday input" << endl;
		cout << endl;
		return;
	}

	cout << "Enter height(cm) (-1 if n/a): ";
	cin >> height;

	cout << "Enter weight(kg) (-1 if n/a): ";
	cin >> weight;

	transform(groupName.begin(), groupName.end(), groupName.begin(), ::toupper);

	Member* newMember = new Member(groupName, stageName, birthName, birthday, height, weight);

	if (memberTable.insertMember(newMember))
	{
		cout << "Successfully inserted a member" << endl;
		cout << endl;
		ofstream directory("members.txt", ios::app);
		directory << groupName << "," << stageName << "," << birthName << "," << birthday << "," << height << "," << weight << endl;
		directory.close();
	}
	else
	{
		cout << "ERROR: Duplicate member" << endl;
	}
	

}