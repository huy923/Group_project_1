#ifndef COLORPRINTER_H
#define COLORPRINTER_H
#include "Printer.h"
#include "LaserPrinter.h"
#include <iostream>
#include <vector>
#include <string>
#include <istream>
class ColorPrinter : public LaserPrinter
{
private:
	int NumberOfPrintableColors;

public:
	ColorPrinter();
	ColorPrinter(int, std::string, double, double, double, int, double, int);
	int GetNumberOfPrintableColors() const { return NumberOfPrintableColors; }
	void SetNumberOfPrintableColors(int NumberOfPrintableColors) { this->NumberOfPrintableColors = NumberOfPrintableColors; }
	void Split(std::string);
	void Input();
	void CheckOpenFile();
	void PomegranateChooseToOpenFile(std::vector<Printer> &, std::vector<ColorPrinter> &, std::vector<LaserPrinter> &);
	void Output(std::vector<ColorPrinter>);
	void GetFileData(std::string, std::vector<Printer> &, std::vector<ColorPrinter> &, std::vector<LaserPrinter> &);
	void MoreData(std::string);
	void Options();
	void ShowPrinterStatistics();
};

ColorPrinter::ColorPrinter(int num, std::string color, double speed, double intensity, double memory, int stock, double dpi, int numColors)
	: LaserPrinter(num, color, speed, intensity, memory, stock, dpi), NumberOfPrintableColors(numColors) {}

ColorPrinter::ColorPrinter()
{
	PrinterNumber = 0;
	Color = "";
	Speed = 0.0;
	Intensity = 0.0;
	Memory = 0.0;
	NumberOfPrintersInStock = 0;
	this->SetDPI(0.0);
	NumberOfPrintableColors = 0;
}
void ColorPrinter::Split(std::string line)
{
	std::stringstream ss(line);
	std::string field;
	std::getline(ss, field, ';');
	PrinterNumber = std::stoi(field);
	std::getline(ss, Color, ';');
	std::getline(ss, field, ';');
	Speed = std::stod(field);
	std::getline(ss, field, ';');
	Intensity = std::stod(field);
	std::getline(ss, field, ';');
	Memory = std::stod(field);
	std::getline(ss, field, ';');
	NumberOfPrintersInStock = std::stoi(field);
	std::getline(ss, field, ';');
	double NumberDPI = std::stod(field);
	SetDPI(NumberDPI);
	std::getline(ss, field, '\n');
	int NumberOfPrintableColorsTemp = std::stoi(field);
	SetNumberOfPrintableColors(NumberOfPrintableColorsTemp);
}
void ColorPrinter::Output(std::vector<ColorPrinter> data)
{
	std::cout << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << std::endl;
	std::cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock | DPI | Number of colors |" << std::endl;
	std::cout << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << std::endl;
	for (const auto &p : data)
	{
		std::cout << "| " << std::setw(23) << std::left << p.PrinterNumber
				  << "| " << std::setw(8) << std::left << p.Color
				  << "|  " << std::setw(5) << std::left << p.Speed
				  << "|\t" << std::setw(9) << std::left << p.Intensity
				  << "| " << std::setw(7) << std::left << p.Memory
				  << "| " << std::setw(6) << std::left << p.NumberOfPrintersInStock
				  << "| " << std::setw(3) << std::left << p.GetDPI()
				  << " | " << std::setw(17) << std::left << p.GetNumberOfPrintableColors() << "|" << std::endl;
	}
	std::cout << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << std::endl;
}
void ColorPrinter::MoreData(std::string NameFile)
{
	std::string check1 = "Common printer warehouse.txt";
	std::string check2 = "Laser printer warehouse.txt";
	std::string check3 = "Color printer warehouse.txt";
	if (NameFile == check1)
	{
		std::ifstream file("Common printer warehouse.txt");
		Printer::Input();
		file.close();
	}
	else if (NameFile == check2)
	{
		std::ifstream File("Laser printer warehouse.txt");
		LaserPrinter::Input();
		File.close();
	}
	else if (NameFile == check3)
	{
		std::ifstream file("Color printer warehouse.txt");
		ColorPrinter::Input();
		file.close();
	}
}
void ColorPrinter::Options()
{
	std::cout << "In which file do you want to add data? " << std::endl;
	std::cout << "Enter 1 : Add data to the file Common printer warehouse" << std::endl;
	std::cout << "Enter 2 : Add data to the file Laser printer warehouse" << std::endl;
	std::cout << "Enter 3 : Add data to the file Color printer warehouse" << std::endl;
	int choice;
	std::cin >> choice;
	std::cin.ignore();
	switch (choice)
	{
	case 1:
	{
		MoreData("Common printer warehouse.txt");
	}
	break;
	case 2:
	{
		MoreData("Laser printer warehouse.txt");
	}
	break;
	case 3:
	{
		MoreData("Color printer warehouse.txt");
	}
	break;
	default:
		std::cout << "Unknown choice" << std::endl;
		break;
	}
}

void ColorPrinter::GetFileData(std::string NameFile, std::vector<Printer> &DataPrinter, std::vector<ColorPrinter> &DataColorPrinter, std::vector<LaserPrinter> &DataLaserPrinter)
{
	std::string check1 = "Common printer warehouse.txt";
	std::string check2 = "Laser printer warehouse.txt";
	std::string check3 = "Color printer warehouse.txt";
	if (NameFile == check1)
	{
		std::ifstream file("Common printer warehouse.txt");
		std::string Line;
		while (std::getline(file, Line))
		{
			Printer NewPrinter;
			NewPrinter.Printer::Split(Line);
			DataPrinter.push_back(NewPrinter);
		}
		Printer::Output(DataPrinter);
		file.close();
	}
	else if (NameFile == check2)
	{
		std::ifstream file("Laser printer warehouse.txt");
		std::string Line;
		while (std::getline(file, Line))
		{
			LaserPrinter NewLaserPrinter;
			NewLaserPrinter.LaserPrinter::Split(Line);
			DataLaserPrinter.push_back(NewLaserPrinter);
		}
		LaserPrinter::Output(DataLaserPrinter);
		file.close();
	}
	else if (NameFile == check3)
	{
		std::ifstream file("Color printer warehouse.txt");
		std::string Line;
		while (std::getline(file, Line))
		{
			ColorPrinter NewColorPrinter;
			NewColorPrinter.ColorPrinter::Split(Line);
			DataColorPrinter.push_back(NewColorPrinter);
		}
		ColorPrinter::Output(DataColorPrinter);
		file.close();
	}
	else
	{
		std::cerr << "Can't open file" << std::endl;
	}
}

void ColorPrinter::CheckOpenFile()
{
	std::ifstream file("Common printer warehouse.txt");
	std::ifstream file2("Laser printer warehouse.txt");
	std::ifstream file3("Color printer warehouse.txt");
	if (!file.is_open() or !file2.is_open() or !file3.is_open())
	{
		std::cout << "You need to download file" << std::endl;
	}
	file.close();
	file2.close();
	file3.close();
}
void ColorPrinter::ShowPrinterStatistics()
{
	std::vector<Printer> data1;
	std::vector<LaserPrinter> data2;
	std::vector<ColorPrinter> data3;

	std::cout << "What printer stats do you want to see? " << std::endl;
	std::cout << "Enter 1: Printer" << std::endl;
	std::cout << "Enter 2: Laser printer" << std::endl;
	std::cout << "Enter 3: Color printer" << std::endl;
	int choice;
	std::cin >> choice;
	std::cin.ignore();
	switch (choice)
	{
	case 1:
	{
		std::ifstream file("Common printer warehouse.txt");
		std::string Line;
		bool success = false;
		while (std::getline(file, Line))
		{
			Printer NewPrinter;
			NewPrinter.Printer::Split(Line);
			if (NewPrinter.GetNumberOfPrintersInStock() < 5)
			{
				success = true;
				data1.push_back(NewPrinter);
			}
		}
		if (success)
		{
			std::system("cls");
			std::cout << "\t\t\t------------------- Missing Printer ------------------ \n";
			Printer::Output(data1);
		}
		else
		{
			std::cout << "No printer is messing" << std::endl;
		}
		file.close();
	}
	break;
	case 2:
	{
		std::ifstream file("Laser printer warehouse.txt");
		std::string Line;
		bool success = false;
		while (std::getline(file, Line))
		{
			LaserPrinter NewPrinter;
			NewPrinter.LaserPrinter::Split(Line);
			if (NewPrinter.GetNumberOfPrintersInStock() < 5)
			{
				success = true;
				data2.push_back(NewPrinter);
			}
		}
		if (success)
		{
			std::system("cls");
			std::cout << "\t\t\t------------------- Missing Printer ------------------ \n";
			LaserPrinter::Output(data2);
		}
		else
		{
			std::cout << "No printer is messing" << std::endl;
		}
		file.close();
	}
	break;
	case 3:
	{
		std::ifstream file("Color printer warehouse.txt");
		std::string Line;
		bool success = false;
		while (std::getline(file, Line))
		{
			ColorPrinter NewPrinter;
			NewPrinter.ColorPrinter::Split(Line);
			if (NewPrinter.GetNumberOfPrintersInStock() < 5)
			{
				success = true;
				data3.push_back(NewPrinter);
			}
		}
		if (success)
		{
			std::system("cls");
			std::cout << "\t\t\t------------------- Missing Printer ------------------ \n";
			ColorPrinter::Output(data3);
		}
		else
		{
			std::cout << "No printer is messing" << std::endl;
		}
		file.close();
	}
	break;
	default:
		std::cout << "ERROR: Unknown" << std::endl;
		break;
	}
}
void ColorPrinter::PomegranateChooseToOpenFile(std::vector<Printer> &DataPrinter, std::vector<ColorPrinter> &DataColorPrinter, std::vector<LaserPrinter> &DataLaserPrinter)
{
	std::cout << "Enter your selection\n";
	std::cout << "1. Common printer warehouse\n";
	std::cout << "2. Laser printer warehouse\n";
	std::cout << "3. Color printer warehouse\n";
	int Select;
	std::cin >> Select;
	std::cin.ignore();
	switch (Select)
	{
	case 1:
	{
		// read data from Common printer warehouse.txt file
		std::ifstream inFile("Common printer warehouse.txt");
		std::system("cls");
		GetFileData("Common printer warehouse.txt", DataPrinter, DataColorPrinter, DataLaserPrinter);
		inFile.close();
	}
	break;
	case 2:
	{
		// read data from Laser printer warehouse.txt file
		std::ifstream inFile("Laser printer warehouse.txt");
		std::system("cls");
		GetFileData("Laser printer warehouse.txt", DataPrinter, DataColorPrinter, DataLaserPrinter);
		inFile.close();
	}

	break;
	case 3:
	{
		// read data from Color printer warehouse.txt file
		std::ifstream inFile("Color printer warehouse.txt");
		std::system("cls");
		GetFileData("Color printer warehouse.txt", DataPrinter, DataColorPrinter, DataLaserPrinter);
		inFile.close();
	}
	break;
	default:
		std::cout << "Invalid selection. Please choose again." << std::endl;
		break;
	}
}
void ColorPrinter::Input()
{
	GeneralImport();
	std::cout << "Enter number of dots per inch (dpi): ";
	double DPI;
	std::cin >> DPI;
	while (std::cin.fail())
	{
		std::cout << "Invalid input. Please enter a valid number of dots per inch: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> DPI;
	}
	std::cout << "Enter number of printable colors: ";
	std::cin >> NumberOfPrintableColors;
	while (std::cin.fail() or NumberOfPrintableColors < 0)
	{
		std::cout << "Invalid input. Please enter a valid number of printable color: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> NumberOfPrintableColors;
	}
	
	std::ofstream MyFile("Color printer warehouse.txt", std::ios::app);
	if (MyFile.is_open())
	{
		MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << ";" << DPI << ";" << NumberOfPrintableColors << "\n";
	}
	else
	{
		std::cout << "Error opening file " << std::endl;
	}
	std::cout << "Added data do you want to see (y,n) :";
	std::string choice;
	std::cin >> choice;
	std::cin.ignore();
	std::system("cls");
	if (choice == "y" or choice == "Y")
	{
		std::vector<ColorPrinter> data;
		std::ifstream file("Color printer warehouse.txt");
		std::string line;
		while (std::getline(file, line))
		{
			ColorPrinter printer;
			printer.ColorPrinter::Split(line);
			data.push_back(printer);
		}
		ColorPrinter::Output(data);
	}
	MyFile.close();
	std::system("cls");
}
#endif