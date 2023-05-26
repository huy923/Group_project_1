#ifndef PRINTER_H
#define PRINTER_H 

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;
class Printer
{
protected:
	int PrinterNumber;
	string Color;
	double Speed;
	double Intensity;
	double Memory;
	int NumberOfPrintersInStock;

public:
	Printer();
	Printer(int, string, double, double, double, int);
	int GetNumberOfPrintersInStock();
	void Split(string);
	void Input();
	void Output(vector<Printer>) const;
	void GeneralImport();
	virtual void Print();
};
void Printer::Print(){
	cout << "Printer\n";
}
int Printer::GetNumberOfPrintersInStock()
{
	return NumberOfPrintersInStock;
}

Printer::Printer()
{
	PrinterNumber = 0;
	Color = "";
	Speed = 0.0;
	Intensity = 0.0;
	Memory = 0.0;
	NumberOfPrintersInStock = 0;
}
Printer::Printer(int num, string color, double speed, double intensity, double memory, int stock)
	: PrinterNumber(num), Color(color), Speed(speed), Intensity(intensity), Memory(memory), NumberOfPrintersInStock(stock) {}
void Printer::Split(string line)
{
	stringstream ss(line);
	string field;
	getline(ss, field, ';');
	PrinterNumber = stoi(field);
	getline(ss, Color, ';');
	getline(ss, field, ';');
	Speed = stod(field);
	getline(ss, field, ';');
	Intensity = stod(field);
	getline(ss, field, ';');
	Memory = stod(field);
	getline(ss, field, '\n');
	NumberOfPrintersInStock = stoi(field);
}

void Printer::Input()
{
	GeneralImport();
	ofstream MyFile("Common printer warehouse.txt", ios::app);
	MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << "\n";
	MyFile.close();

	cout << "\nAdded data. Do you want to see the data (y/n): ";
	string choice;
	cin >> choice;
	cin.ignore();
	cout << endl;

	if (choice == "y" || choice == "Y")
	{
		ifstream file("Common printer warehouse.txt");
		if (file)
		{
			vector<Printer> data;
			string line;
			while (getline(file, line))
			{
				Printer printer;
				printer.Split(line);
				data.push_back(printer);
			}
			Printer::Output(data);
		}
		else
		{
			cout << "No data available." << endl;
		}
		file.close();
	}
}

void Printer::Output(vector<Printer> data) const
{
	cout << "+------------------------+---------+-------+-------------+--------+-------+" << endl;
	cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock |" << endl;
	cout << "+------------------------+---------+-------+-------------+--------+-------+" << endl;
	for (const auto &p : data)
	{
		cout << "| " << setw(23) << left << p.PrinterNumber
				  << "| " << setw(8) << left << p.Color
				  << "|  " << setw(5) << left << p.Speed
				  << "|\t" << setw(9) << left << p.Intensity
				  << "| " << setw(7) << left << p.Memory
				  << "| " << setw(6) << left << p.NumberOfPrintersInStock << "|" << endl;
	}
	cout << "+------------------------+---------+-------+-------------+--------+-------+" << endl;
}
void Printer::GeneralImport()
{
	cout << "Enter printer number: ";
	cin >> PrinterNumber;
	while (cin.fail() or PrinterNumber < 0)
	{
		cout << "Invalid input. Please enter a valid printer number: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> PrinterNumber;
	}

	cout << "Enter color: ";
	cin >> Color;
	while (cin.fail())
	{
		cout << "Invalid input. Please enter a valid color: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> Color;
	}

	cout << "Enter speed (pages per minute): ";
	cin >> Speed;
	while (cin.fail() or Speed < 0)
	{
		cout << "Invalid input. Please enter a valid speed: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> Speed;
	}

	cout << "Enter intensity: ";
	cin >> Intensity;
	while (cin.fail() or Intensity < 0)
	{
		cout << "Invalid input. Please enter a valid intensity: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> Intensity;
	}

	cout << "Enter memory (MB): ";
	cin >> Memory;
	while (cin.fail() or Memory < 0)
	{
		cout << "Invalid input. Please enter a valid memory: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> Memory;
	}

	cout << "Enter number of printers in stock: ";
	cin >> NumberOfPrintersInStock;
	while (cin.fail() or NumberOfPrintersInStock < 0)
	{
		cout << "Invalid input. Please enter a valid number of printers in stock: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> NumberOfPrintersInStock;
	}
}
#endif