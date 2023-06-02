#include ".\Printer.h"
#include ".\LaserPrinter.h"
#include ".\ColorPrinter.h"
#include <iostream>
using namespace std;
int main(int argc, char const *argv[])
{
	vector<Printer> DataPrinter;
	vector<ColorPrinter> DataColorPrinter;
	vector<LaserPrinter> DataLaserPrinter;
	ColorPrinter NewData;
	for (;;)
	{
		cout << "\n***********************************" << endl;
		cout << "* 👉 Enter 1: Add new data        *" << endl;
		cout << "* 👉 Enter 2: Export data         *" << endl;
		cout << "* 👉 Enter 3: Show missing data   *" << endl;
		cout << "***********************************" << endl;
		cout << " 😁 Your choice is : ";
		int choice;
		cin >> choice;
		system("cls");
		switch (choice)
		{
		case 1:
		{
			NewData.Options();
			break;
		}
		case 2:
		{
			NewData.PomegranateChooseToOpenFile(DataPrinter, DataColorPrinter, DataLaserPrinter);
			break;
		}
		case 3:
		{
			NewData.ShowPrinterStatistics();
			break;
		}
		case 4:
		{
			NewData.search();
			break;
		}
		default:
		{
			cout << "Bye! 💖💖💖" << endl;
			exit(1);
			break;
		}
		}
	}
	DataPrinter.clear();
	DataLaserPrinter.clear();
	DataColorPrinter.clear();
	return 0;
}