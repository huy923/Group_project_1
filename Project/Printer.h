#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <vector>
#include <sstream>
class Printer
{
protected:
    int PrinterNumber;
    std::string Color;
    double Speed;
    double Intensity;
    double Memory;
    int NumberOfPrintersInStock;

public:
    Printer();
    Printer(int, std::string, double, double, double, int);
    int GetNumberOfPrintersInStock() { return NumberOfPrintersInStock; }
    void Split(std::string);
    void Input();
    void Output(std::vector<Printer>);
};

Printer::Printer()
{
	PrinterNumber = 0;
	Color = "";
	Speed = 0.0;
	Intensity = 0.0;
	Memory = 0.0;
	NumberOfPrintersInStock = 0;
}
Printer::Printer(int num, std::string color, double speed, double intensity, double memory, int stock)
	: PrinterNumber(num), Color(color), Speed(speed), Intensity(intensity), Memory(memory), NumberOfPrintersInStock(stock) {}
void Printer::Split(std::string line)
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
	std::getline(ss, field, '\n');
	NumberOfPrintersInStock = std::stoi(field);
}
void Printer::Output(std::vector<Printer> data)
{
	std::cout << "+------------------------+---------+-------+-------------+--------+-------+" << std::endl;
	std::cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock |" << std::endl;
	std::cout << "+------------------------+---------+-------+-------------+--------+-------+" << std::endl;
	for (const auto &p : data)
	{
		std::cout << "| " << std::setw(23) << std::left << p.PrinterNumber
			 << "| " << std::setw(8) << std::left << p.Color
			 << "|  " << std::setw(5) << std::left << p.Speed
			 << "|\t" << std::setw(9) << std::left << p.Intensity
			 << "| " <<std::setw(7) << std::left << p.Memory
			 << "| " << std::setw(6) << std::left << p.NumberOfPrintersInStock << "|" << std::endl;
	}
	std::cout << "+------------------------+---------+-------+-------------+--------+-------+" << std::endl;
}
#endif