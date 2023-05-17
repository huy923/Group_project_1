#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iomanip>

using namespace std;
// ========================================

// ========================================

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
	void Split(string);
	void Input();
	void Output(vector<Printer>);
};

class LaserPrinter : public Printer
{
private:
	double DPI;

public:
	LaserPrinter();
	LaserPrinter(int, string, double, double, double, int, double);
	double GetDPI() const { return DPI; }
	void SetDPI(double DPI) { this->DPI = DPI; }
	void Input();
	void Split(string);
	void Output(vector<LaserPrinter>);
};

class ColorPrinter : public LaserPrinter
{
private:
	int NumberOfPrintableColors;

public:
	ColorPrinter();
	ColorPrinter(int, string, double, double, double, int, double, int);
	int GetNumberOfPrintableColors() const { return NumberOfPrintableColors; }
	void SetNumberOfPrintableColors(int NumberOfPrintableColors) { this->NumberOfPrintableColors = NumberOfPrintableColors; }
	void Split(string);
	void Input();
	void PomegranateChooseToOpenFile(vector<Printer> &, vector<ColorPrinter> &, vector<LaserPrinter> &);
	void Output(vector<ColorPrinter>);
	void GetFileData(string, vector<Printer> &, vector<ColorPrinter> &, vector<LaserPrinter> &);
};

// main is here
int main(int argc, char const *argv[])
{
	vector<Printer> DataPrinter;
	vector<ColorPrinter> DataColorPrinter;
	vector<LaserPrinter> DataLaserPrinter;
	ColorPrinter NewData;
	NewData.PomegranateChooseToOpenFile(DataPrinter, DataColorPrinter, DataLaserPrinter);
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
void LaserPrinter::Split(string line)
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
	getline(ss, field, ';');
	NumberOfPrintersInStock = stoi(field);
	getline(ss, field, '\n');
	int NumberDPI = stoi(field);
	SetDPI(NumberDPI);
}
void ColorPrinter::Split(string line)
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
	getline(ss, field, ';');
	NumberOfPrintersInStock = stoi(field);
	getline(ss, field, ';');
	int NumberDPI = stoi(field);
	SetDPI(NumberDPI);
	getline(ss, field, '\n');
	int NumberOfPrintableColorsTemp = stoi(field);
	SetNumberOfPrintableColors(NumberOfPrintableColorsTemp);
}
void Printer::Input()
{
	cout << "Enter printer number: ";
	cin >> PrinterNumber;
	cout << "Enter color: ";
	cin >> Color;
	cout << "Enter speed (pages per minute): ";
	cin >> Speed;
	cout << "Enter intensity (dpi): ";
	cin >> Intensity;
	cout << "Enter memory (GB): ";
	cin >> Memory;
	cout << "Enter number of printers in stock: ";
	cin >> NumberOfPrintersInStock;
	ofstream MyFile("Common printer warehouse.txt", ios::app);
	MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << "\n";
	MyFile.close();
}
void Printer::Output(vector<Printer> data)
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
	Printer::Input(); // call base class function
	cout << "Enter number of dots per inch (dpi): ";
	cin >> DPI;
	ofstream MyFile("Laser printer warehouse.txt", ios::app);
	MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << ";" << DPI << "\n";
	MyFile.close();
}
void LaserPrinter::Output(vector<LaserPrinter> data)
{
	cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
	cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock | DPI +" << endl;
	cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
	for (const auto &p : data)
	{
		cout << "| " << setw(23) << left << p.PrinterNumber
			 << "| " << setw(8) << left << p.Color
			 << "|  " << setw(5) << left << p.Speed
			 << "|\t" << setw(9) << left << p.Intensity
			 << "| " << setw(7) << left << p.Memory
			 << "| " << setw(6) << left << p.NumberOfPrintersInStock
			 << "| " << setw(4) << left << p.GetDPI() << "|" << endl;
	}
	cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
}
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
ColorPrinter::ColorPrinter(int num, string color, double speed, double intensity, double memory, int stock, double dpi, int numColors)
	: LaserPrinter(num, color, speed, intensity, memory, stock, dpi), NumberOfPrintableColors(numColors) {}
void ColorPrinter::Input()
{
	LaserPrinter::Input(); // call base class function
	cout << "Enter number of printable colors: ";
	cin >> NumberOfPrintableColors;
	ofstream MyFile("Color printer warehouse.txt", ios::app);
	MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << ";" << GetDPI() << ";" << NumberOfPrintableColors<< "\n";
	MyFile.close();
}
void ColorPrinter::Output(vector<ColorPrinter> data)
{
	cout << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
	cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock | DPI | Number of colors |" << endl;
	cout << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
	for (const auto &p : data)
	{
		cout << "| " << setw(23) << left << p.PrinterNumber
			 << "| " << setw(8) << left << p.Color
			 << "|  " << setw(5) << left << p.Speed
			 << "|\t" << setw(9) << left << p.Intensity
			 << "| " << setw(7) << left << p.Memory
			 << "| " << setw(6) << left << p.NumberOfPrintersInStock
			 << "| " << setw(3) << left << p.GetDPI()
			 << " | " << setw(17) << left << p.GetNumberOfPrintableColors() << "|" << endl;
	}
	cout << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
}
void ColorPrinter::GetFileData(string NameFile, vector<Printer> &DataPrinter, vector<ColorPrinter> &DataColorPrinter, vector<LaserPrinter> &DataLaserPrinter)
{
	string check1 = "Common printer warehouse.txt";
	string check2 = "Laser printer warehouse.txt";
	string check3 = "Color printer warehouse.txt";
	if (NameFile == check1)
	{
		ifstream file("Common printer warehouse.txt");
		string Line;
		while (getline(file, Line))
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
		ifstream file("Laser printer warehouse.txt");
		string Line;
		while (getline(file, Line))
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
		ifstream file("Color printer warehouse.txt");
		string Line;
		while (getline(file, Line))
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
		cerr << "Can't open file" << endl;
	}
}