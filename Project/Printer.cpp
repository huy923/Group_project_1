#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Printer
{
protected:
    int PrinterNumber{};
    string Color = "";
    double Speed{};
    double Intensity{};
    double Memory{};
    int NumverOfPrintersInStock{};

public:
    Printer() {}
    Printer(int, string, double, double, double, int);

    virtual void Print() = 0; // abstract function to be defined in derived classes

    void Input();

    void Output(vector<Printer>);
};

class LaserPrinter : public Printer
{
private:
    double DPI{};

public:
    LaserPrinter() {}
    LaserPrinter(int, string, double, double, double, int, double);
    double GetDPI() { return DPI; }
    void SetDPI(double DPI)
    {
        this->DPI = DPI;
    }
    void Print() override;

    void Input();

    void Output(vector<LaserPrinter>);
};

class ColorPrinter : public LaserPrinter
{
private:
    int NumberOfPrintableColors;

public:
    ColorPrinter() {}
    ColorPrinter(int, string, double, double, double, int, double, int);
    int GetNumberOfPrintableColors() { return NumberOfPrintableColors; }
    void SetNumberOfPrintableColors(int NumberOfPrintableColors)
    {
        this->NumberOfPrintableColors = NumberOfPrintableColors;
    }
    void Print() override;
    void Input();
    void Output(vector<ColorPrinter>);
    void Split(string line);
};

// main is here
int main(int argc, char const *argv[])
{

    // ifstream file("student management.txt");

    // if (!file.is_open())
    // {
    //     cerr << "Could not open your file" << endl;
    //     return 1;
    // }
    // vector<ColorPrinter> Data;
    // string Line;
    // while (getline(file, Line))
    // {
    //     ColorPrinter NewPrinterAll;
    //     NewPrinterAll.Split(Line);
    //     Data.push_back(NewPrinterAll);
    // }
    return 0;
}
void ColorPrinter::Split()
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
        NumverOfPrintersInStock = stoi(field);
    }
    break;
    case 2:
    {
        // read data from Laser printer warehouse.txt file
        ifstream inFile("Laser printer warehouse.txt");
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
        NumverOfPrintersInStock = stoi(field);
        getline(ss, field, '\n');
        int NumberDPI = stoi(field);
        SetDPI(NumberDPI);
    }

    break;
    case 3:
    {
        // read data from Color printer warehouse.txt file
        ifstream inFile("Color printer warehouse.txt");
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
        NumverOfPrintersInStock = stoi(field);
        getline(ss, field, ';');
        int NumberDPI = stoi(field);
        SetDPI(NumberDPI);
        getline(ss,field,'\n');
        int NumberOfPrintableColorsTemp = stoi(field);
        SetNumberOfPrintableColors(NumberOfPrintableColorsTemp);
    }
    break;
    default:
        cout << "Invalid selection. Please choose again." << endl;
        break;
    }
}

Printer::Printer(int num, string color, double speed, double intensity, double memory, int stock)
    : PrinterNumber(num), Color(color), Speed(speed), Intensity(intensity), Memory(memory), NumverOfPrintersInStock(stock) {}

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
    cin >> NumverOfPrintersInStock;
}
void Printer::Output(vector<Printer> data)
{
    cout << "+------------------------+---------+-------+-------------+--------+-------+" << endl;
    cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock |" << endl;
    cout << "+------------------------+---------+-------+-------------+--------+-------+" << endl;
    for (int i = 0; i < data.size(); i++)
    {
        cout << "| " << data[i].PrinterNumber << "| " << data[i].Color << "| " << data[i].Speed << "| " << data[i].Intensity << "| " << data[i].Memory << "| " << data[i].NumverOfPrintersInStock << " |\n";
    }
    cout << "+------------------------+---------+-------+-------------+--------+-------+" << endl;
}
LaserPrinter::LaserPrinter(int num, string color, double speed, double intensity, double memory, int stock, double dpi)
    : Printer(num, color, speed, intensity, memory, stock), DPI(dpi) {}
void LaserPrinter::Print()
{
    cout << "Printing with laser printer" << endl;
}
void LaserPrinter::Input()
{
    Printer::Input(); // call base class function
    cout << "Enter number of dots per inch (dpi): ";
    cin >> DPI;
}
void LaserPrinter::Output(vector<LaserPrinter> data)
{
    cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
    cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock | DPI +" << endl;
    cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
    for (int i = 0; i < data.size(); i++)
    {
        cout << "| " << data[i].PrinterNumber << "| " << data[i].Color << "| " << data[i].Speed << "| " << data[i].Intensity << "| " << data[i].Memory << "| " << data[i].NumverOfPrintersInStock << " | " << data[i].GetDPI() << " |\n";
    }
    cout << "+------------------------+---------+-------+-------------+--------+-------+-----+" << endl;
}

ColorPrinter::ColorPrinter(int num, string color, double speed, double intensity, double memory, int stock, double dpi, int numColors)
    : LaserPrinter(num, color, speed, intensity, memory, stock, dpi), NumberOfPrintableColors(numColors) {}

void ColorPrinter::Print()
{
    cout << "Printing with color printer" << endl;
}
void ColorPrinter::Input()
{
    LaserPrinter::Input(); // call base class function
    cout << "Enter number of printable colors: ";
    cin >> NumberOfPrintableColors;
}
void ColorPrinter::Output(vector<ColorPrinter> data)
{
    cout << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
    cout << "| Printer number         | Color   | Speed |  Intensity  | Memory | Stock | DPI | Number of colors |" << endl;
    cout << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
    for (int i = 0; i < data.size(); i++)
    {
        cout << "| " << data[i].PrinterNumber << "| " << data[i].Color << "| " << data[i].Speed << "| " << data[i].Intensity << "| " << data[i].Memory << "| " << data[i].NumverOfPrintersInStock << " | " << data[i].GetDPI() << " | " << data[i].GetNumberOfPrintableColors() << " |\n";
    }
    cout << "+------------------------+---------+-------+-------------+--------+-------+-----+------------------+" << endl;
}
