#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Printer.h"
#include "LaserPrinter.h"
#include "ColorPrinter.h"

// main is here
int main(int argc, char const *argv[])
{
	std::vector<Printer> DataPrinter;
	std::vector<ColorPrinter> DataColorPrinter;
	std::vector<LaserPrinter> DataLaserPrinter;
	ColorPrinter NewData;
	for (;;)
	{
		std::cout << "Enter 1: Add new data" << std::endl;
		std::cout << "Enter 2: Export data" << std::endl;
		std::cout << "Enter 3: Show missing data " << std::endl;

		int choice;
		std::cin >> choice;
		std::system("cls");
		switch (choice)
		{
		case 1:
			NewData.Options();
			break;
		case 2:
			NewData.PomegranateChooseToOpenFile(DataPrinter, DataColorPrinter, DataLaserPrinter);
			break;
		case 3:
			NewData.ShowPrinterStatistics();
			break;
		// case 4:

		// 	break;
		default:
			std::cout << "Bye! 💖💖💖" << std::endl;
			exit(1);
			break;
		}
	}

	DataPrinter.clear();
	DataLaserPrinter.clear();
	DataColorPrinter.clear();
	return 0;
}
