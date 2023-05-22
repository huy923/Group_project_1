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

void ColorPrinter::PomegranateChooseToOpenFile(vector<Printer> &DataPrinter, vector<ColorPrinter> &DataColorPrinter, vector<LaserPrinter> &DataLaserPrinter)
{
	cout << "Enter your selection\n";
	cout << "1. Common printer warehouse\n";
	cout << "2. Laser printer warehouse\n";
	cout << "3. Color printer warehouse\n";
	int Select;
	cin >> Select;
	cin.ignore();
	switch (Select)
	{
	case 1:
	{
		// read data from Common printer warehouse.txt file
		ifstream inFile("Common printer warehouse.txt");
		system("cls");
		GetFileData("Common printer warehouse.txt", DataPrinter, DataColorPrinter, DataLaserPrinter);
		inFile.close();
	}
	break;
	case 2:
	{
		// read data from Laser printer warehouse.txt file
		ifstream inFile("Laser printer warehouse.txt");
		system("cls");
		GetFileData("Laser printer warehouse.txt", DataPrinter, DataColorPrinter, DataLaserPrinter);
		inFile.close();
	}

	break;
	case 3:
	{
		// read data from Color printer warehouse.txt file
		ifstream inFile("Color printer warehouse.txt");
		system("cls");
		GetFileData("Color printer warehouse.txt", DataPrinter, DataColorPrinter, DataLaserPrinter);
		inFile.close();
	}
	break;
	default:
		cout << "Invalid selection. Please choose again." << endl;
		break;
	}
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
void LaserPrinter::Output(vector<LaserPrinter> data)
{
	cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
	cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock | DPI |" << endl;
	cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
	for (const auto &p : data)
	{
		cout << "| " << setw(23) << left << p.PrinterNumber
			 << "| " << setw(8) << left << p.Color
			 << "|  " << setw(5) << left << p.Speed
			 << "|\t" << setw(9) << left << p.Intensity
			 << "| " << setw(7) << left << p.Memory
			 << "| " << setw(6) << left << p.NumberOfPrintersInStock
			 << "| " << setw(4) << p.GetDPI() << "|" << endl;
	}
	cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
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