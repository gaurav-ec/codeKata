#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

class OCR
{
private:
	bool isA;
	bool isB;
	bool isC;
	bool isD;
	bool isE;
	bool isF;
	bool isG;
	
	char* fstLine;
	char* secLine;
	char* thrLine;
	
	int res[9];
	int resCnt;

	void setLCDSegments(char* fst, char* sec, char* thr);
    void setRes();
	void resetSeg();
	void parseChar();
	void setFst(char* ch);
	void setSec(char* ch);
	void setThr(char* ch);
	void showRes() const;
	bool isValidAccount(const int* acNum) const;// checksum function

public:
	OCR();
	virtual ~OCR();
	void readfile(string fl);
	

};


