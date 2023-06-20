#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
#include <ctime>
using namespace std;

class Printer
{
protected:
	string PrinterNumber;		 // Printer number
	string Color;				 // Color of the printer
	double Speed;				 // Printing speed (pages per minute)
	double Intensity;			 // Intensity of the printer
	double Memory;				 // Memory capacity (in MB)
	int NumberOfPrintersInStock; // Number of printers in stock

public:
	Printer();											  // Default constructor
	Printer(string, string, double, double, double, int); // Constructor with parameters
	int GetNumberOfPrintersInStock() const;				  // Get the number of printers in stock
	void Split(string);									  // Split a line of text into individual attributes
	void Input();										  // Input printer information from user
	void Output(vector<Printer>) const;					  // Output printer information to file and console
	void GeneralImport();								  // General input function for printer attributes
	string getCurrentTime() const;						  // Get the current system time as a string
	void openFileExportInvoice() const;					  // Open the export invoice file
	void showExportInvoice() const;						  // Display the export invoice file
	double GetMemory() const;							  // Get the memory capacity
	double GetIntensity() const;						  // Get the intensity
	double GetSpeed() const;							  // Get the speed
	string GetColor() const;							  // Get the color
	string GetNumberPrinter() const;					  // Get the printer number
	virtual void Print();								  // Print function (virtual)
	void writeDataToVector(vector<Printer> &);			  // Write the data to the vector
};

// Print function implementation
void Printer::Print()
{
	cout << "Normal printer" << endl;
}
double Printer::GetMemory() const
{
	return Memory;
}
double Printer::GetIntensity() const
{
	return Intensity;
}
double Printer::GetSpeed() const
{
	return Speed;
}
string Printer::GetColor() const
{
	return Color;
}
string Printer::GetNumberPrinter() const
{
	return PrinterNumber;
}
// Get the number of printers in stock
int Printer::GetNumberOfPrintersInStock() const
{
	return NumberOfPrintersInStock;
}

// Default constructor
Printer::Printer()
{
	PrinterNumber = "";
	Color = "";
	Speed = 0.0;
	Intensity = 0.0;
	Memory = 0.0;
	NumberOfPrintersInStock = 0;
}

// Constructor with parameters
Printer::Printer(string num, string color, double speed, double intensity, double memory, int stock)
	: PrinterNumber(num), Color(color), Speed(speed), Intensity(intensity), Memory(memory), NumberOfPrintersInStock(stock) {}

// Split a line of text into individual attributes
void Printer::Split(string line)
{
	stringstream ss(line);
	string field;
	getline(ss, PrinterNumber, ';');
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

// Input printer information from user
void Printer::Input()
{
	GeneralImport();
	ofstream MyFile("Common printer warehouse.txt", ios::app);
	MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << "\n";
	MyFile.close();

	vector<Printer> data;
	Printer::writeDataToVector(data);
	Printer::Output(data);
	system("cls");
}

// Output printer information to file and console
void Printer::Output(vector<Printer> data) const
{
	openFileExportInvoice();
	ofstream file("Export invoice.txt", ios::app);
	file << "Normal printer " << endl;

	string displayTime = getCurrentTime();
	file << displayTime << endl;

	file << "+------------------------+---------+-------+-------------+--------+-------+" << endl;
	file << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock |" << endl;
	file << "+------------------------+---------+-------+-------------+--------+-------+" << endl;
	for (const auto &p : data)
	{
		file << "| " << setw(23) << left << p.PrinterNumber
			 << "| " << setw(8) << left << p.Color
			 << "|  " << setw(5) << left << p.Speed
			 << "| " << setw(12) << left << p.Intensity
			 << "| " << setw(7) << left << p.Memory
			 << "| " << setw(6) << left << p.NumberOfPrintersInStock << "|" << endl;
		file << "+------------------------+---------+-------+-------------+--------+-------+" << endl;
	}
	file.close();
	showExportInvoice();
}

// General input function for printer attributes
void Printer::GeneralImport()
{
	cout << "Enter printer number: ";
	cin >> PrinterNumber;
	while (cin.fail() or PrinterNumber.length() > 24)
	{
		cout << "Invalid input. Please enter a valid printer number: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> PrinterNumber;
	}

	cout << "Enter color: ";
	cin >> Color;
	while (cin.fail() or Color.length() > 9)
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

// Function to get the current time
string Printer::getCurrentTime() const
{
	time_t t = time(NULL);
	tm *now = localtime(&t);
	int day = now->tm_mday;
	int month = now->tm_mon + 1;
	int year = now->tm_year + 1900;
	int hour = now->tm_hour;
	int minute = now->tm_min;
	int second = now->tm_sec;
	string result;
	result = "Date " + to_string(day) + " Month " + to_string(month) + " Year " + to_string(year);
	result += "\nTime " + to_string(hour) + ":" + to_string(minute) + ":" + to_string(second);
	return result;
}

// Function to open the export invoice file
void Printer::openFileExportInvoice() const
{
	ofstream file("Export invoice.txt", ios::app);
	if (!file.is_open())
	{
		cout << "Error: Couldn't open the file";
		exit(1);
	}
	file << "\n\t\t\t\tExport invoice" << endl;
	file.close();
}

// Function to show the export invoice and prompt the user to open the file
void Printer::showExportInvoice() const
{
	cout << "Do you want to open the file? (y/n)" << endl;
	string choice;
	cin >> choice;
	cin.ignore();
	if (choice == "y" || choice == "Y")
	{
		system("start notepad.exe \"Export invoice.txt\"");
	}
}
void Printer::writeDataToVector(vector<Printer> &data)
{
	ifstream file("Common printer warehouse.txt");
	string line;
	while (getline(file, line))
	{
		Printer printer;
		printer.Split(line);
		data.push_back(printer);
	}
	file.close();
}
#endif