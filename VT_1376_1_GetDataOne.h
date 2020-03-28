#ifndef  VT_1376_1_GETDATAONE_H
#define  VT_1376_1_GETDATAONE_H
#include "VT1376_1_Frame.h"


#define user_String  1

#define BufferMax    100
#if user_String
#include <iostream>
#include <string>
using namespace std;
#endif
typedef enum Fn
{
	F2 = 2,

}Fn;

class VT_1376_1_GetDataOne :	public userFormat
{
private:
	 unsigned int Fn;
	 unsigned int Pn;
	 unsigned char dataBuffer[BufferMax];
	 unsigned int   lenght;
	 unsigned int  offset;

	 bool getFnAndPn();
	 void copyDatatoBuffer(unsigned char* src,unsigned int len);

	bool functionForF2(unsigned char* dataout);
	string functionForF2();
public:
	
	string getData();

	VT_1376_1_GetDataOne();
	VT_1376_1_GetDataOne(unsigned char* dataIn, unsigned int   lenghtIn);
	~VT_1376_1_GetDataOne();
};

#endif //VT_1376_1_GETDATAONE_H


