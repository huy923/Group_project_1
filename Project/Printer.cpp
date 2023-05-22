#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include "Printer.h"
#include "LaserPrinter.h"
#include "ColorPrinter.h"
using namespace std;

// main is here
int main(int argc, char const *argv[])
{
	vector<Printer> DataPrinter;
	vector<ColorPrinter> DataColorPrinter;
	vector<LaserPrinter> DataLaserPrinter;
	ColorPrinter NewData;
	for (;;)
	{
		cout << "Enter 1: Add new data" << endl;
		cout << "Enter 2: Export data" << endl;
		cout << "Enter 3: Show missing data " << endl;

		int choice;
		cin >> choice;
		system("cls");
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
			cout << "Bye! 💖💖💖" << endl;
			exit(1);
			break;
		}
	}

	DataPrinter.clear();
	DataLaserPrinter.clear();
	DataColorPrinter.clear();
	return 0;
}




LaserPrinter::LaserPrinter(int num, string color, double speed, double intensity, double memory, int stock, double dpi)
	: Printer(num, color, speed, intensity, memory, stock), DPI(dpi) {}
LaserPrinter::LaserPrinter()
{
	PrinterNumber = 0;
	Color = "";
	Speed = 0.0;
	Intensity = 0.0;
	Memory = 0.0;
	NumberOfPrintersInStock = 0;
	DPI = 0.0;
}

void LaserPrinter::Input()
{
	cout << "Enter printer number: ";
	cin >> PrinterNumber;
	cout << "Enter color: ";
	cin >> Color;
	cout << "Enter speed (pages per minute): ";
	cin >> Speed;
	cout << "Enter intensity : ";
	cin >> Intensity;
	cout << "Enter memory (MB): ";
	cin >> Memory;
	cout << "Enter number of printers in stock: ";
	cin >> NumberOfPrintersInStock;
	cout << "Enter number of dots per inch (dpi): ";
	cin >> DPI;
	ofstream MyFile("Laser printer warehouse.txt", ios::app);
	MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << ";" << DPI << "\n";
	system("cls");
	cout << "Added data do you want to see" << endl;
	MyFile.close();
	LaserPrinter();
}


ColorPrinter::ColorPrinter(int num, string color, double speed, double intensity, double memory, int stock, double dpi, int numColors)
	: LaserPrinter(num, color, speed, intensity, memory, stock, dpi), NumberOfPrintableColors(numColors) {}
void ColorPrinter::Input()
{
	cout << "Enter printer number: ";
	cin >> PrinterNumber;
	cout << "Enter color: ";
	cin >> Color;
	cout << "Enter speed (pages per minute): ";
	cin >> Speed;
	cout << "Enter intensity : ";
	cin >> Intensity;
	cout << "Enter memory (MB): ";
	cin >> Memory;
	cout << "Enter number of printers in stock: ";
	cin >> NumberOfPrintersInStock;
	cout << "Enter number of dots per inch (dpi): ";
	double DPI;
	cin >> DPI;
	cout << "Enter number of printable colors: ";
	cin >> NumberOfPrintableColors;
	ofstream MyFile("Color printer warehouse.txt", ios::app);
	if (MyFile.is_open())
	{
		MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << ";" << DPI << ";" << NumberOfPrintableColors << "\n";
	}
	else
	{
		cout << "Error";
	}
	std::cout << "Added data do you want to see (y,n) :";
    std::string choice;
    std::cin >> choice;
    std::cin.ignore();
    system("cls");
	    if (choice == "y" or choice == "Y") 
    {
        std::vector<Printer> data;
        std::ifstream file("Color printer warehouse.txt");
        std::string line;
        while (std::getline(file,line))
        {
            ColorPrinter printer;
            printer.ColorPrinter::Split(line);
            data.push_back(printer);
        }
        Printer::Output(data);
    }
	MyFile.close();
	system("cls");
}