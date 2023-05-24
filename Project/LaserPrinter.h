#ifndef LASERPRINTER_H
#define LASERPRINTER_H
#include "Printer.h"
#include <string>
#include <vector>
#include <sstream>
#include <limits>
class LaserPrinter : public Printer
{
private:
	double DPI;

public:
	LaserPrinter();
	LaserPrinter(int, std::string, double, double, double, int, double);
	double GetDPI() const { return DPI; }
	void SetDPI(double DPI) { this->DPI = DPI; }
	void Input();
	void Split(std::string);
	void Output(std::vector<LaserPrinter>);
};
LaserPrinter::LaserPrinter(int num, std::string color, double speed, double intensity, double memory, int stock, double dpi)
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

void LaserPrinter::Split(std::string line)
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
	std::getline(ss, field, '\n');
	double NumberDPI = std::stod(field);
	SetDPI(NumberDPI);
}

void LaserPrinter::Input()
{
	GeneralImport();
	std::cout << "Enter number of dots per inch (dpi): ";
	std::cin >> DPI;
	while (std::cin.fail())
	{
		std::cout << "Invalid input. Please enter a valid number of dots per inch: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> DPI;
	}

	std::ofstream MyFile("Laser printer warehouse.txt", std::ios::app);
	MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << ";" << DPI << "\n";
	std::system("cls");
	std::cout << "Added data. Do you want to see (y/n): ";
	std::string choice;
	std::cin >> choice;
	std::cin.ignore();
	std::system("cls");
	if (choice == "y" || choice == "Y")
	{
		std::vector<LaserPrinter> data;
		std::ifstream file("Laser printer warehouse.txt");
		std::string line;
		while (std::getline(file, line))
		{
			LaserPrinter printer;
			printer.LaserPrinter::Split(line);
			data.push_back(printer);
		}
		LaserPrinter::Output(data);
	}
	MyFile.close();
	std::system("cls");
}

void LaserPrinter::Output(std::vector<LaserPrinter> data)
{
	std::cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << std::endl;
	std::cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock | DPI |" << std::endl;
	std::cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << std::endl;
	for (const auto &p : data)
	{
		std::cout << "| " << std::setw(23) << std::left << p.PrinterNumber
				  << "| " << std::setw(8) << std::left << p.Color
				  << "|  " << std::setw(5) << std::left << p.Speed
				  << "|\t" << std::setw(9) << std::left << p.Intensity
				  << "| " << std::setw(7) << std::left << p.Memory
				  << "| " << std::setw(6) << std::left << p.NumberOfPrintersInStock
				  << "| " << std::setw(4) << p.GetDPI() << "|" << std::endl;
	}
	std::cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << std::endl;
}
#endif