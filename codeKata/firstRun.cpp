#include "firstRun.h"

   OCR::OCR()
   {
	 isA = isB = isC = isD = isE = isF = isG = false;
	 resCnt = 0;
   }
   OCR::~OCR()
   {}
 
	void OCR::setFst(char* ch)
	{
		fstLine = ch;
	}
	void OCR::setSec(char* ch)
	{
	   secLine = ch;
	}
	void OCR::setThr(char* ch)
	{
	   thrLine = ch;
	}

	

	void OCR::parseChar()  // pass first line to this function
	{
		
		for(int j=0; j<27; j+=3)// 
			setLCDSegments(&fstLine[j],&secLine[j],&thrLine[j]);
	}

	void OCR::setLCDSegments(char* fst, char* sec, char* thr)  // the display segments are named as per the 7 segment LCD convention
	{
		if(fst[1]=='_')
			isA = true;
		
		if(sec[0]=='|')
			isF = true;
		if(sec[1]=='_')
			isG = true;
		if(sec[2]=='|')
			isB = true;

		if(thr[0]=='|')
			isE = true;
		if(thr[1]=='_')
			isD = true;
		if(thr[2]=='|')
			isC = true;
		
		setRes();
	}
	void OCR::setRes()
	{
		if(resCnt > 8)
			resCnt=0;
		if(isC == false)// result should be 2
		{
			res[resCnt]=2;
			resCnt++;
			resetSeg();
			return;
		}
		
		if(isA == false)// reult is either 4 or 1
		{
			if(isF == true)
				res[resCnt] = 4;
			else
				res[resCnt] = 1;
			
			resCnt++;
			resetSeg();
			return;
		}

		if(isB == false)// result is either 5 or 6
		{
			if(isE ==  true)
				res[resCnt] = 6;
			else
				res[resCnt] = 5;

			resCnt++;
			resetSeg();
			return;
		}

		if(isG == false)// result is either 0 or 1 or 7  The 1 is already being taken care of so we wont worry about it
		{
			if(isD == true)
				res[resCnt] = 0;
			else
				res[resCnt] = 7;
			
			resCnt++;
			resetSeg();
			return;
		}
		/* following code checks for 8, 9 or 3*/
		if( isE == true) 
		{
			res[resCnt] = 8;
			resCnt++;
			resetSeg();
			return;
		}
		else if(isF == true)
		{
			res[resCnt] = 9;
			resCnt++;
			resetSeg();
			return;
		}
		else
		{
			res[resCnt] = 3;
			resCnt++;
			resetSeg();
			return;
		}
	}
	
	void OCR::showRes() const
	{
		
		for(int j=0; j<resCnt; j++)
			cout<< res[j];
	  
		
		if(isValidAccount(res))
			cout<<"\nAcount number is valid and passes checksum\n";
		else
			cout<<"\nAcount number is not valid  checksum error\n";
	}

	void OCR::resetSeg()
	{
		isA=isB=isC=isD=isE=isF=isG= false;
	}

	void OCR::readfile(string fl)
	{

		char line1[28];
		char line2[28];
		char line3[28];

		ifstream infile(fl);
		while(1)
		{
			infile.getline(line1,28);
			setFst(line1);
			if(!infile)
				break;

			infile.getline(line2,28);
			setSec(line2);
			infile.getline(line3,28);
			setThr(line3);
			parseChar();
			showRes();
	    }
	}

	bool OCR::isValidAccount(const int* acNum) const
	{
		int sum=0;
		for(int j=0,k=9;j<9;j++,k--)
			sum = sum + (k)*acNum[j];
		if(sum==0)
			return false;
		if(sum % 11 == 0)
			return true;
		else 
			return false;
	}
	