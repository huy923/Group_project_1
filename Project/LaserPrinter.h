#ifndef LASERPRINTER_H
#define LASERPRINTER_H
#include ".\Printer.h"
class LaserPrinter : public Printer
{
private:
	double DPI;

public:
	LaserPrinter();//Default constructor
	LaserPrinter(string, string, double, double, double, int, double);
	double GetDPI() const;
	void SetDPI(double);
	void Input();
	void Output(vector<LaserPrinter>);
	void Split(string);
	void Print() override;
	void writeDataToVector(vector<LaserPrinter>&);
};
double LaserPrinter::GetDPI() const
{
	return DPI;
}
void LaserPrinter::SetDPI(double DPI)
{
	this->DPI = DPI;
}
void LaserPrinter::Print()
{
	cout << "LaserPrinter" << endl;
}
LaserPrinter::LaserPrinter(string num, string color, double speed, double intensity, double memory, int stock, double dpi)
	: Printer(num, color, speed, intensity, memory, stock), DPI(dpi) {}
LaserPrinter::LaserPrinter()
{
	PrinterNumber = "";
	Color = "";
	Speed = 0.0;
	Intensity = 0.0;
	Memory = 0.0;
	NumberOfPrintersInStock = 0;
	DPI = 0.0;
}

void LaserPrinter::Split(string line)
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
	getline(ss, field, ';');
	NumberOfPrintersInStock = stoi(field);
	getline(ss, field, '\n');
	double NumberDPI = stod(field);
	SetDPI(NumberDPI);
}

void LaserPrinter::Input()
{
	Printer::GeneralImport();
	cout << "Enter number of dots per inch (dpi) : ";
	cin >> DPI;
	while (cin.fail() or DPI > 0 or to_string(DPI).length() > 5)
	{
		cout << "Invalid input. Please enter a valid number of dots per inch: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> DPI;
	}
	// open file and write to it 
	ofstream MyFile("Laser printer warehouse.txt", ios::app);
	MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << ";" << DPI << "\n";
	MyFile.close();
	system("cls");

	vector<LaserPrinter> data;
	LaserPrinter::writeDataToVector(data);
	LaserPrinter::Output(data);
	system("cls");
}

void LaserPrinter::Output(vector<LaserPrinter> data)
{
	openFileExportInvoice();
	ofstream file("Export invoice.txt", ios::app);
	file << "Laser Printer" << endl;

	file << getCurrentTime() << endl;

	file << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
	file << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock | DPI |" << endl;
	file << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;

	for (const auto &p : data)
	{
		file << "| " << setw(23) << left << p.PrinterNumber
			 << "| " << setw(8) << left << p.Color
			 << "|  " << setw(5) << left << p.Speed
			 << "|\t" << setw(9) << left << p.Intensity
			 << "| " << setw(7) << left << p.Memory
			 << "| " << setw(6) << left << p.NumberOfPrintersInStock
			 << "| " << setw(4) << p.GetDPI() << "|" << endl;
		file << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
	}

	file.close();
	showExportInvoice();
}
void LaserPrinter::writeDataToVector(vector<LaserPrinter> &data){
	ifstream file("Laser printer warehouse.txt");
	string line;
	while (getline(file, line))
	{
		LaserPrinter printer;
		printer.LaserPrinter::Split(line);
		data.push_back(printer);
	}
	file.close();
}
#endif