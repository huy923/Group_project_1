#ifndef COLORPRINTER_H
#define COLORPRINTER_H
#include "Printer.h"
#include "LaserPrinter.h"
#include <vector>
#include <string>
class ColorPrinter : public LaserPrinter
{
private:
	int NumberOfPrintableColors;

public:
	ColorPrinter();
	ColorPrinter(int, std::string, double, double, double, int, double, int);
	int GetNumberOfPrintableColors() const { return NumberOfPrintableColors; }
	void SetNumberOfPrintableColors(int NumberOfPrintableColors) { this->NumberOfPrintableColors = NumberOfPrintableColors; }
	void Split(std::string);
	void Input();
	void CheckOpenFile();
	void PomegranateChooseToOpenFile(std::vector<Printer> &, std::vector<ColorPrinter> &, std::vector<LaserPrinter> &);
	void Output(std::vector<ColorPrinter>);
	void GetFileData(std::string, std::vector<Printer> &, std::vector<ColorPrinter> &, std::vector<LaserPrinter> &);
	void MoreData(std::string);
	void Options();
	void ShowPrinterStatistics();
};
void ColorPrinter::Split(std::string line)
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
	std::getline(ss, field, ';');
	double NumberDPI = std::stod(field);
	SetDPI(NumberDPI);
	std::getline(ss, field, '\n');
	int NumberOfPrintableColorsTemp = std::stoi(field);
	SetNumberOfPrintableColors(NumberOfPrintableColorsTemp);
}
#endif