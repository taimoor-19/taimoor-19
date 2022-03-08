#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
class user
{
	int rollno;
	char name[15];
	int salary;
public:
	void getitem(void);
	void putitem();
	int  getrollno(void) {
		return rollno;
	}
	void updatesalary(int num)
	{
		salary = salary - num;
	}
};
void user::getitem()
{
	cout << "enter roll no." << "\n";
	cin >> rollno;
	cout << "enter name :" << "\n";
	cin >> name;
	cout << "enter salary" << "\n";
	cin >> salary;
}
void user::putitem()
{
	cout << setw(6) << rollno;
	cout << setw(10) << name;
	cout << setw(6) << salary;
}
void addrecord();
void showall();
void deleterecord();
void showrecord();
user us;
fstream fit;

int main() {
	int option;
	while (1)
	{
		system("cls");
		cout << "**********MENU**************" << "\n";
		cout << "1. show all records " << "\n";
		cout << "2. add a new record " << "\n";
		cout << "3. delete a particular record " << "\n";
		cout << "4.show a particular record " << "\n";
		cout << "5.exit" << "\n";
		cout << "enter any option" << "\n";
		cin >> option;
		switch (option)
		{
		case 1:
		{
			cout << "----------------------------------------------" << "\n";
			cout << setw(6) << "ROLL NUMBER " << setw(10) << "NAME " << setw(6) << "SALARY" << "\n";
			cout << "-----------------------------------------------------" << "\n";
			showall();
			cout << "---------------------------------------------------------" << "\n";
			cout << "press any key to see main menu " << "\n";
			_getch;
			break;
		}
		case 2:
		{
			addrecord();
			cout << "press any key to continue " << "\n";
			_getch;
			break;
		}
		case 3:
		{
			deleterecord();
			cout << "press any key to see main menu" << "\n";
			_getch;
			break;
		}
		case 4:
		{
			showrecord();
			cout << "press any key to see menu " << "\n"; \
				_getch;
			break;
		}
		case 5:
		{
			exit(0);
		}
		default:
		{
			cout << "incorrect option press any key to continue" << "\n";
			_getch;
			break;
		}
		}

	}
	system("pause");
	return 0;
}
void addrecord()
{
	char ch = 'y';
	fit.open("dope.txt", ios::app | ios::binary | fstream::out);
	while (ch == 'y' || ch == 'Y')
	{
		us.getitem();
		//witing object into file
		fit.write((char*)&us, sizeof(us));
		cout << "add more recordss?(y/n)";
		cin >> ch;
	}
	fit.close();
}

void showall()
{
	fit.open("dope.txt", ios::in | ios::binary);
	if (!fit)
	{
		cout << "file not found" << "\n";
		exit(0);
	}
	else
	{//reading a file from file into object
		fit.read((char*)&us, sizeof(us));
		while (!fit.eof())
		{
			us.putitem();
			fit.read((char*)&us, sizeof(us));
		}
	}
	fit.close();
}
void deleterecord()
{
	int no;
	cout << "enter user id to delete " << "\n";
	cin >> no;
	ofstream f2;
	f2.open("newstd.txt", ios::out | ios::binary);
	fit.open("dope.txt", ios::in || ios::binary);
	if (!fit)
	{
		cout << "file not found" << "\n";
	}
	else
	{
		fit.read((char*)&us, sizeof(us));
		while (!fit.eof())
		{
			if (no != us.getrollno())
			{
				f2.write((char*)&us, sizeof(us));
			}
			fit.read((char*)&us, sizeof(us));
		}
	}
	f2.close();
	fit.close();
	remove("dope.txt");
	rename("newstd.txt", "dope.txt");

}
void showrecord()
{
	int no;
	bool flag = 0;
	fit.open("dope.txt", ios::in | ios::binary);
	if (!fit)
	{
		cout << "file not found" << "\n";
		exit(0);
	}
	else
	{
		cout << "enter item code to search" << "\n";
		cin >> no;
		fit.read((char*)&us, sizeof(us));
		while (!fit.eof())
		{
			if (no == us.getrollno())
			{
				flag = 1;
				cout << "--------------------------------------" << "\n";
				cout << setw(6) << "ROLL NUMBER " << setw(10) << "NAME " << setw(6) << "SALARY" << "\n";
				cout << "------------------------------------------" << "\n";
				us.putitem();
				cout << "---------------------------------------------" << "\n";
				break;
			}
		}
		fit.read((char*)&us, sizeof(us));

		if (flag == 0)
		{
			cout << "iten not found" << "\n";
		}
	}
	fit.close();
}
