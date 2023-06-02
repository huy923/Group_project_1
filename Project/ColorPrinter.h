#ifndef COLORPRINTER_H
#define COLORPRINTER_H

#include ".\Printer.h"
#include ".\LaserPrinter.h"


class ColorPrinter : public LaserPrinter
{
private:
	int NumberOfPrintableColors;

public:
	ColorPrinter();
	ColorPrinter(int, string, double, double, double, int, double, int);
	int GetNumberOfPrintableColors() const;
	void SetNumberOfPrintableColors(int);
	void Split(string);
	void Input();
	void CheckOpenFile();
	void PomegranateChooseToOpenFile(vector<Printer> &, vector<ColorPrinter> &, vector<LaserPrinter> &);
	void Output(vector<ColorPrinter>) const;
	void GetFileData(string, vector<Printer> &, vector<ColorPrinter> &, vector<LaserPrinter> &);
	void MoreData(string);
	void Options();
	void ShowPrinterStatistics();
	void Print() override;
	void search();
};
void ColorPrinter::Print()
{
	cout << "Color Printer" << endl;
}
int ColorPrinter::GetNumberOfPrintableColors() const
{
	return NumberOfPrintableColors;
}
void ColorPrinter::SetNumberOfPrintableColors(int NumberOfPrintableColors) { this->NumberOfPrintableColors = NumberOfPrintableColors; }

ColorPrinter::ColorPrinter(int num, string color, double speed, double intensity, double memory, int stock, double dpi, int numColors)
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
	double NumberDPI = stod(field);
	SetDPI(NumberDPI);
	getline(ss, field, '\n');
	int NumberOfPrintableColorsTemp = stoi(field);
	SetNumberOfPrintableColors(NumberOfPrintableColorsTemp);
}
void ColorPrinter::Output(vector<ColorPrinter> data) const
{
	openFileExportInvoice();
	ofstream file("Export invoice.txt", ios::app);
	file << "Color printer" << endl;
	
	string displayTime = getCurrentTime();
	file << displayTime << endl;

	file << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
	file << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock | DPI | Number of colors |" << endl;
	file << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
	for (const auto &p : data)
	{
		file << "| " << setw(23) << left << p.PrinterNumber
			 << "| " << setw(8) << left << p.Color
			 << "|  " << setw(5) << left << p.Speed
			 << "|\t" << setw(9) << left << p.Intensity
			 << "| " << setw(7) << left << p.Memory
			 << "| " << setw(6) << left << p.NumberOfPrintersInStock
			 << "| " << setw(3) << left << p.GetDPI()
			 << " | " << setw(17) << left << p.GetNumberOfPrintableColors() << "|" << endl;
	}
	file << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
	file.close();
	showExportInvoice();
}
void ColorPrinter::MoreData(string NameFile)
{
	string check1 = "Common printer warehouse.txt";
	string check2 = "Laser printer warehouse.txt";
	string check3 = "Color printer warehouse.txt";
	if (NameFile == check1)
	{
		ifstream file("Common printer warehouse.txt");
		Printer::Input();
		file.close();
	}
	else if (NameFile == check2)
	{
		ifstream File("Laser printer warehouse.txt");
		LaserPrinter::Input();
		File.close();
	}
	else if (NameFile == check3)
	{
		ifstream file("Color printer warehouse.txt");
		ColorPrinter::Input();
		file.close();
	}
}
void ColorPrinter::Options()
{
	cout << "**************************************************************" << endl;
	cout << "* 😉 In which file do you want to add data  (´･ω･`)?         *" << endl;
	cout << "* 👉 Enter 1 : Add data to the file Common printer warehouse *" << endl;
	cout << "* 👉 Enter 2 : Add data to the file Laser printer warehouse  *" << endl;
	cout << "* 👉 Enter 3 : Add data to the file Color printer warehouse  *" << endl;
	cout << "**************************************************************" << endl;
	cout << " 😊 Your choose the number : ";
	int choice;
	cin >> choice;
	cin.ignore();
	system("cls");
	switch (choice)
	{
	case 1:
	{
		MoreData("Common printer warehouse.txt");
		break;
	}
	case 2:
	{
		MoreData("Laser printer warehouse.txt");
		break;
	}
	case 3:
	{
		MoreData("Color printer warehouse.txt");
		break;
	}
	default:
		cout << "Unknown choice" << endl;
		break;
	}
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

void ColorPrinter::CheckOpenFile()
{
	ifstream file("Common printer warehouse.txt");
	ifstream file2("Laser printer warehouse.txt");
	ifstream file3("Color printer warehouse.txt");
	if (!file.is_open() or !file2.is_open() or !file3.is_open())
	{
		cout << "You need to download file" << endl;
	}
	file.close();
	file2.close();
	file3.close();
}
void ColorPrinter::ShowPrinterStatistics()
{
	vector<Printer> data1;
	vector<LaserPrinter> data2;
	vector<ColorPrinter> data3;
	cout << "*******************************************************" << endl;
	cout << "* 🤗 What printer stats do you want to see (´･ω･`)?   *" << endl;
	cout << "* 👉 Enter 1: Printer                                 *" << endl;
	cout << "* 👉 Enter 2: Laser printer                           *" << endl;
	cout << "* 👉 Enter 3: Color printer                           *" << endl;
	cout << "*******************************************************" << endl;
	cout << " 😎 Your choose the number : ";
	int choice;
	cin >> choice;
	cin.ignore();
	ofstream FileExportInvoice("Export invoice.txt",ios::app);
	switch (choice)
	{
	case 1:
	{
		ifstream file("Common printer warehouse.txt");
		string Line;
		bool success = false;
		while (getline(file, Line))
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
			system("cls");
			FileExportInvoice << "\t\t\t------------------- Missing Printer ------------------ \n";
			
			Printer::Output(data1);
		}
		else
		{
			cout << "No printer is messing" << endl;
		}
		file.close();
		break;
	}
	case 2:
	{
		ifstream file("Laser printer warehouse.txt");
		string Line;
		bool success = false;
		while (getline(file, Line))
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
			system("cls");
			FileExportInvoice << "\t\t\t------------------- Missing Printer ------------------ \n";
			LaserPrinter::Output(data2);
		}
		else
		{
			cout << "No printer is messing" << endl;
		}
		file.close();
		break;
	}
	case 3:
	{
		ifstream file("Color printer warehouse.txt");
		string Line;
		bool success = false;
		while (getline(file, Line))
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
			system("cls");
			FileExportInvoice << "\t\t\t------------------- Missing Printer ------------------ \n";
			ColorPrinter::Output(data3);
		}
		else
		{
			cout << "No printer is messing" << endl;
		}
		file.close();
		break;
	}
	default:
		cout << "ERROR: Unknown" << endl;
		break;
	}
	FileExportInvoice.close();
}
void ColorPrinter::PomegranateChooseToOpenFile(vector<Printer> &DataPrinter, vector<ColorPrinter> &DataColorPrinter, vector<LaserPrinter> &DataLaserPrinter)
{
	cout << "*************************************" << endl;
	cout << "* 😃 Enter your selection           *\n";
	cout << "* 👉 1. Common printer warehouse    *\n";
	cout << "* 👉 2. Laser printer warehouse     *\n";
	cout << "* 👉 3. Color printer warehouse     *\n";
	cout << "*************************************" << endl;
	cout << " 😎 Your choose the number : ";
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
		break;
	}
	case 2:
	{
		// read data from Laser printer warehouse.txt file
		ifstream inFile("Laser printer warehouse.txt");
		system("cls");
		GetFileData("Laser printer warehouse.txt", DataPrinter, DataColorPrinter, DataLaserPrinter);
		inFile.close();
		break;
	}

	case 3:
	{
		// read data from Color printer warehouse.txt file
		ifstream inFile("Color printer warehouse.txt");
		system("cls");
		GetFileData("Color printer warehouse.txt", DataPrinter, DataColorPrinter, DataLaserPrinter);
		inFile.close();
		break;
	}
	default:
		cout << "Invalid selection. Please choose again." << endl;
		break;
	}
}
void ColorPrinter::Input()
{
	GeneralImport();
	cout << "Enter number of dots per inch (dpi): ";
	double DPI;
	cin >> DPI;
	while (cin.fail())
	{
		cout << "Invalid input. Please enter a valid number of dots per inch: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> DPI;
	}
	cout << "Enter number of printable colors: ";
	cin >> NumberOfPrintableColors;
	while (cin.fail() or NumberOfPrintableColors < 0)
	{
		cout << "Invalid input. Please enter a valid number of printable color: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> NumberOfPrintableColors;
	}

	ofstream MyFile("Color printer warehouse.txt", ios::app);
	if (MyFile.is_open())
	{
		MyFile << PrinterNumber << ";" << Color << ";" << Speed << ";" << Intensity << ";" << Memory << ";" << NumberOfPrintersInStock << ";" << DPI << ";" << NumberOfPrintableColors << "\n";
	}
	else
	{
		cout << "Error opening file " << endl;
	}
	cout << "Added data do you want to see (y,n) :";
	string choice;
	cin >> choice;
	cin.ignore();
	system("cls");
	if (choice == "y" or choice == "Y")
	{
		vector<ColorPrinter> data;
		ifstream file("Color printer warehouse.txt");
		string line;
		while (getline(file, line))
		{
			ColorPrinter printer;
			printer.ColorPrinter::Split(line);
			data.push_back(printer);
		}
		ColorPrinter::Output(data);
	}
	MyFile.close();
	system("cls");
}
void showFileSearch()
{
	cout << "****************************************************" << endl;
	cout << "* 🤗 What do you want to search for (´･ω･`)?  		*" << endl;
	cout << "* 👉 Enter 1️⃣: Search printer number         		*" << endl;
	cout << "* 👉 Enter 2️⃣: Search color                  		*" << endl;
	cout << "* 👉 Enter 3️⃣: Search speed                  		*" << endl;
	cout << "* 👉 Enter 4️⃣: Search intensity              		*" << endl;
	cout << "* 👉 Enter 5️⃣: Search memory                 		*" << endl;
	cout << "* 👉 Enter 6️⃣: Search number of printers in stock *" << endl;
}
void ColorPrinter::search()
{

	cout << "********************************************************" << endl;
	cout << "* What do you want open file to search ❓   	 	   *" << endl;
	cout << "* Enter 1️⃣ : Common printer warehouse     		     *" << endl;
	cout << "* Enter 2️⃣ : Laser printer warehouse          		 *" << endl;
	cout << "* Enter 3️⃣ : Color printer warehouse                   *" << endl;
	cout << "********************************************************" << endl;
	cout << " 😝 You choose the number : ";
	int choice;
	cin >> choice;
	cin.ignore();
	switch (choice)
	{
	case 1:
	{
		showFileSearch();
		cout << "********************************************************" << endl;
		cout << "😊 Your choice the number : ";
		int choice;
		cin >> choice;
		cin.ignore();
		system("cls");
		switch (choice)
		{
		case 1:

			break;

		default:
			break;
		}

		break;
	}
	case 2:
	{
		showFileSearch();
		cout << "* 👉 Enter 7️⃣: Search number of print points per unit *" << endl;
		cout << "********************************************************" << endl;
		cout << "😊 Your choice the number : ";
		int choice;
		cin >> choice;
		cin.ignore();
		system("cls");
		break;
	}
	case 3:
	{

		break;
	}
	default:
		break;
	}
}
#endif