lass Printer
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
	