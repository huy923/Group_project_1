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
		file << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
	}
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
	cout << "* In which file do you want to add data ?\t\t     *" << endl;
	cout << "* Enter 1 : Add data to the file Common printer warehouse    *" << endl;
	cout << "* Enter 2 : Add data to the file Laser printer warehouse     *" << endl;
	cout << "* Enter 3 : Add data to the file Color printer warehouse     *" << endl;
	cout << "**************************************************************" << endl;
	cout << " Your choose the number : ";
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
	cout << "****************************************************" << endl;
	cout << "* What printer stats do you want to see ?          *" << endl;
	cout << "* Enter 1: Printer                                 *" << endl;
	cout << "* Enter 2: Laser printer                           *" << endl;
	cout << "* Enter 3: Color printer                           *" << endl;
	cout << "****************************************************" << endl;
	cout << " Your choose the number : ";
	int choice;
	cin >> choice;
	cin.ignore();
	ofstream FileExportInvoice("Export invoice.txt", ios::app);
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
			FileExportInvoice << "\t\t\t------------------- Missing Printer ------------------ \n";
			system("cls");
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
			FileExportInvoice.close();
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
			FileExportInvoice.close();
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
	cout << "* Enter your selection              *\n";
	cout << "* 1. Common printer warehouse       *\n";
	cout << "* 2. Laser printer warehouse        *\n";
	cout << "* 3. Color printer warehouse        *\n";
	cout << "*************************************" << endl;
	cout << " Your choose the number : ";
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
	MyFile.close();

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
	file.close();
	system("cls");
}
void showFileSearch()
{
	cout << "********************************************************" << endl;
	cout << "* What do you want to search for ?                     *" << endl;
	cout << "* Enter 1 : Search printer number                      *" << endl;
	cout << "* Enter 2 : Search color                               *" << endl;
	cout << "* Enter 3 : Search speed                               *" << endl;
	cout << "* Enter 4 : Search intensity                           *" << endl;
	cout << "* Enter 5 : Search memory                              *" << endl;
	cout << "* Enter 6 : Search number of printers in stock         *" << endl;
}
void ColorPrinter::search()
{
	ofstream fileOutput("Export invoice.txt", ios::app);

	ifstream filePrinter("Common printer warehouse.txt");
	vector<Printer> dataPrinter;
	string linePrinter;
	while (getline(filePrinter, linePrinter))
	{
		Printer printer;
		printer.Split(linePrinter);
		dataPrinter.push_back(printer);
	}
	filePrinter.close();

	vector<ColorPrinter> dataColorPrinter;
	ifstream fileColorPrinter("Color printer warehouse.txt");
	string lineColorPrinter;
	while (getline(fileColorPrinter, lineColorPrinter))
	{
		ColorPrinter printer;
		printer.ColorPrinter::Split(lineColorPrinter);
		dataColorPrinter.push_back(printer);
	}
	fileColorPrinter.close();
	// read file Laser printer warehouse.txt and push it to dataLaserPrinter
	vector<LaserPrinter> dataLaserPrinter;
	ifstream fileLaserPrinter("Laser printer warehouse.txt");
	string lineLaserPrinter;
	while (getline(fileLaserPrinter, lineLaserPrinter))
	{
		LaserPrinter printer;
		printer.LaserPrinter::Split(lineLaserPrinter);
		dataLaserPrinter.push_back(printer);
	}
	fileLaserPrinter.close();

	cout << "********************************************************" << endl;
	cout << "* What file do you want to open for searching?         *" << endl;
	cout << "* Enter 1: Common printer warehouse                    *" << endl;
	cout << "* Enter 2: Laser printer warehouse                     *" << endl;
	cout << "* Enter 3: Color printer warehouse                     *" << endl;
	cout << "********************************************************" << endl;
	cout << "Your choice: ";
	int fileChoice;
	cin >> fileChoice;
	cin.ignore();
	system("cls");

	switch (fileChoice)
	{
	case 1:
	{
		showFileSearch();
		cout << "********************************************************" << endl;
		cout << "Your choice: ";
		int searchChoice1;
		cin >> searchChoice1;
		cin.ignore();
		system("cls");
		switch (searchChoice1)
		{
		case 1:
		{
			cout << "Enter the number of printers to search for: ";
			int numOfPrinters;
			cin >> numOfPrinters;
			cin.ignore();
			vector<Printer> temp;
			bool check = false;
			for (const auto &printer : dataPrinter)
			{
				if (printer.GetNumberPrinter() == numOfPrinters)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				Printer::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 2:
		{
			cout << "Enter the color to search for: ";
			string color;
			cin >> color;
			cin.ignore();
			vector<Printer> temp;
			bool check = false;
			for (const auto &printer : dataPrinter)
			{
				if (printer.GetColor() == color)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				Printer::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 3:
		{
			cout << "Enter the speed to search for: ";
			double speed;
			cin >> speed;
			cin.ignore();
			vector<Printer> temp;
			bool check = false;
			for (const auto &printer : dataPrinter)
			{
				if (printer.GetSpeed() == speed)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				Printer::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 4:
		{
			cout << "Enter the intensity to search for: ";
			double intensity;
			cin >> intensity;
			cin.ignore();
			vector<Printer> temp;
			bool check = false;
			for (const auto &printer : dataPrinter)
			{
				if (printer.GetIntensity() == intensity)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				Printer::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 5:
		{
			cout << "Enter the memory to search for: ";
			double memory;
			cin >> memory;
			cin.ignore();
			vector<Printer> temp;
			bool check = false;
			for (const auto &printer : dataPrinter)
			{
				if (printer.GetMemory() == memory)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				Printer::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 6:
		{
			cout << "Enter the number of printers in stock to search for: ";
			int numOfPrinters;
			cin >> numOfPrinters;
			cin.ignore();
			vector<Printer> temp;
			bool check = false;
			for (int i = 0; i < dataPrinter.size(); i++)
			{
				if (dataPrinter[i].GetNumberOfPrintersInStock() == numOfPrinters)
				{
					check = true;
					temp.push_back(dataPrinter[i]);
				}
			}
			if (check)
			{
				Printer::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}

		break;
		default:
			cout << "Invalid selection. Please choose again." << endl;
			break;
		}
		break;
	}
	case 2:
	{
		showFileSearch();
		cout << "* Enter 7 : Search number of print points per unit(DPI)*" << endl;
		cout << "********************************************************" << endl;
		cout << "Your choice: ";
		int searchChoice2;
		cin >> searchChoice2;
		cin.ignore();
		system("cls");
		switch (searchChoice2)
		{
		case 1:
		{
			cout << "Enter the number of printers to search for: ";
			int numOfPrinters;
			cin >> numOfPrinters;
			cin.ignore();
			vector<LaserPrinter> temp;
			bool check = false;
			for (const auto &printer : dataLaserPrinter)
			{
				if (printer.GetNumberPrinter() == numOfPrinters)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				LaserPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 2:
		{
			cout << "Enter the color to search for: ";
			string color;
			cin >> color;
			cin.ignore();
			vector<LaserPrinter> temp;
			bool check = false;
			for (const auto &printer : dataLaserPrinter)
			{
				if (printer.GetColor() == color)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				LaserPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 3:
		{
			cout << "Enter the speed to search for: ";
			double speed;
			cin >> speed;
			cin.ignore();
			vector<LaserPrinter> temp;
			bool check = false;
			for (const auto &printer : dataLaserPrinter)
			{
				if (printer.GetSpeed() == speed)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				LaserPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 4:
		{
			cout << "Enter the intensity to search for: ";
			double intensity;
			cin >> intensity;
			cin.ignore();
			vector<LaserPrinter> temp;
			bool check = false;
			for (const auto &printer : dataLaserPrinter)
			{
				if (printer.GetIntensity() == intensity)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				LaserPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 5:
		{
			cout << "Enter the memory to search for: ";
			double memory;
			cin >> memory;
			cin.ignore();
			vector<LaserPrinter> temp;
			bool check = false;
			for (const auto &printer : dataLaserPrinter)
			{
				if (printer.GetMemory() == memory)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				LaserPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 6:
		{
			cout << "Enter the number of printers in stock to search for: ";
			int numOfPrinters;
			cin >> numOfPrinters;
			cin.ignore();
			vector<LaserPrinter> temp;
			bool check = false;
			for (const auto &printer : dataLaserPrinter)
			{
				if (printer.GetNumberOfPrintersInStock() == numOfPrinters)
				{
					check = true;
					temp.push_back(printer);
				}
			}
			if (check)
			{
				LaserPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		case 7:
		{
			cout << "Enter the number of print points per unit of printer : ";
			double numberDPI;
			cin >> numberDPI;
			cin.ignore();
			vector<LaserPrinter> temp;
			bool check = false;
			for (const auto &printer : dataLaserPrinter)
			{
				if (printer.GetDPI() == numberDPI)
				{
					check = true;
					temp.push_back(printer);
				}
			}
			if (check)
			{
				LaserPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found " << endl;
			}
			temp.clear();
		}
		break;
		default:
			cout << "Invalid selection. Please choose again." << endl;
			break;
		}
		break;
	}
	case 3:
	{
		showFileSearch();
		cout << "* Enter 7 : Search number of print points per unit     *" << endl;
		cout << "* Enter 8 : Search number of printable colors          *" << endl;
		cout << "********************************************************" << endl;
		cout << "Your choice: ";
		int searchChoice3;
		cin >> searchChoice3;
		cin.ignore();
		system("cls");
		switch (searchChoice3)
		{
		case 1:
		{
			cout << "Enter the number of printers to search for: ";
			int numOfPrinters;
			cin >> numOfPrinters;
			cin.ignore();
			vector<ColorPrinter> temp;
			bool check = false;
			for (const auto &printer : dataColorPrinter)
			{
				if (printer.GetNumberPrinter() == numOfPrinters)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				ColorPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 2:
		{
			cout << "Enter the color to search for: ";
			string color;
			cin >> color;
			cin.ignore();
			vector<ColorPrinter> temp;
			bool check = false;
			for (const auto &printer : dataColorPrinter)
			{
				if (printer.GetColor() == color)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				ColorPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 3:
		{
			cout << "Enter the speed to search for: ";
			double speed;
			cin >> speed;
			cin.ignore();
			vector<ColorPrinter> temp;
			bool check = false;
			for (const auto &printer : dataColorPrinter)
			{
				if (printer.GetSpeed() == speed)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				ColorPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 4:
		{
			cout << "Enter the intensity to search for: ";
			double intensity;
			cin >> intensity;
			cin.ignore();
			vector<ColorPrinter> temp;
			bool check = false;
			for (const auto &printer : dataColorPrinter)
			{
				if (printer.GetIntensity() == intensity)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				ColorPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 5:
		{
			cout << "Enter the memory to search for: ";
			double memory;
			cin >> memory;
			cin.ignore();
			vector<ColorPrinter> temp;
			bool check = false;
			for (const auto &printer : dataColorPrinter)
			{
				if (printer.GetMemory() == memory)
				{
					check = true;
					temp.push_back(printer);
				}
			}

			if (check)
			{
				ColorPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		break;

		case 6:
		{
			cout << "Enter the number of printers in stock to search for: ";
			int numOfPrinters;
			cin >> numOfPrinters;
			cin.ignore();
			vector<ColorPrinter> temp;
			bool check = false;
			for (const auto &printer : dataColorPrinter)
			{
				if (printer.GetNumberOfPrintersInStock() == numOfPrinters)
				{
					check = true;
					temp.push_back(printer);
				}
			}
			if (check)
			{
				ColorPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found	" << endl;
			}
			temp.clear();
		}
		case 7:
		{
			cout << "Enter the number of print points per unit of printer : ";
			double numberDPI;
			cin >> numberDPI;
			cin.ignore();
			vector<ColorPrinter> temp;
			bool check = false;
			for (const auto &printer : dataColorPrinter)
			{
				if (printer.GetDPI() == numberDPI)
				{
					check = true;
					temp.push_back(printer);
				}
			}
			if (check)
			{
				ColorPrinter::Output(temp);
			}
			else
			{
				fileOutput << "\tNo results found " << endl;
			}
			temp.clear();
		}
		break;
		case 8:
		{
			cout << "Enter the number of printable colors" << endl;
			bool check = false;
			int Number;
			cin >> Number;
			cin.ignore();
			vector<ColorPrinter> temp;
			for (const auto &printer : dataColorPrinter)
			{
				if (printer.GetDPI() == Number)
				{
					check = true;
					temp.push_back(printer);
				}
			}
			if (check)
			{
				ColorPrinter::Output(temp);
			}
			else
			{
				fileOutput << "No results found " << endl;
			}
			temp.clear();
		}
		break;
		default:
			cout << "Invalid selection. Please choose again." << endl;
			break;
		}
	}
	default:
		cout << "Invalid file selection. Please choose again." << endl;
		break;
	}
	dataPrinter.clear();
	dataLaserPrinter.clear();
	dataColorPrinter.clear();
}
#endif