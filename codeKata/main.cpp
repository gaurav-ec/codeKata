#include "firstRun.h"

int main()
{
	string fileName;
	cout<<"enter .txt file name, e.g OCR.txt "; 
	cin>>fileName;

	OCR obj;
	obj.readfile(fileName);
	
	cout<<"\n press any key to exit";
	getche();


}