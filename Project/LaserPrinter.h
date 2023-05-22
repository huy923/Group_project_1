#ifndef LASERPRINTER_H
#define LASERPRINTER_H
#include "Printer.h"
#include <string>
#include <vector>
#include <sstream>
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