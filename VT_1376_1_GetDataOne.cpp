#include "VT_1376_1_GetDataOne.h"




VT_1376_1_GetDataOne::VT_1376_1_GetDataOne()
{
	Fn = 0;
	Pn = 0;
	offset = 0;
	lenght = NULL;
	for (int i = 0; i < BufferMax; i++)
		dataBuffer[i] = 0;
}

VT_1376_1_GetDataOne::VT_1376_1_GetDataOne(unsigned char* dataIn, unsigned int   lenghtIn)
{
	Fn = 0;
	Pn = 0;
	offset = 0;
	copyDatatoBuffer(dataIn,lenghtIn);
	lenght = lenghtIn;
	for (int i = 0; i < BufferMax; i++)
		dataBuffer[i] = 0;
}
VT_1376_1_GetDataOne::~VT_1376_1_GetDataOne()
{

}
bool VT_1376_1_GetDataOne::functionForF2(unsigned char* dataout)
{
	bool ret = false;
	return ret;
}
string VT_1376_1_GetDataOne::functionForF2()
{
	string ret = "begin ";
	if (Pn == 0 && Fn == F2)
	{
		ret += "year:" + to_string((dataBuffer[offset + 5] & 0xf0) >> 4) + to_string(dataBuffer[offset + 5] & 0x0f) + ' ';
		ret += "week:" + to_string(dataBuffer[offset + 4] >> 5) + ' ';
		ret += "month:" + to_string((dataBuffer[offset + 4] & 0x1f) >> 4) + to_string(dataBuffer[offset + 4] & 0x0f) + ' ';
		ret += "day:" + to_string((dataBuffer[offset + 3] & 0xf0) >> 4) + to_string(dataBuffer[offset + 3] & 0x0f) + ' ';
		ret += "hour:" + to_string((dataBuffer[offset + 2] & 0xf0) >> 4) + to_string(dataBuffer[offset + 2] & 0x0f) + ' ';
		ret += "minute:" + to_string((dataBuffer[offset + 1] & 0xf0) >> 4) + to_string(dataBuffer[offset + 1] & 0x0f) + ' ';
		ret += "second:" + to_string((dataBuffer[offset + 0] & 0xf0) >> 4) + to_string(dataBuffer[offset + 0] & 0x0f) + ' ';
		ret += "end;";
	}
	else ret = "erro";
	
	return ret;

}

void VT_1376_1_GetDataOne::copyDatatoBuffer(unsigned char* src, unsigned int len)
{
	for (unsigned int i = 0; i < len; i++)
	{
		dataBuffer[i] = src[i];
	}
}
bool VT_1376_1_GetDataOne::getFnAndPn()
{
	bool ret = false;
	/*
	userFormat user;
	 data = user.getNowData();
	lenght = user.getNowDataLenght();
	*/
	
	if (lenght != NULL)
	{
		Pn = dataBuffer[1] << 8 | dataBuffer[0];
		Fn = dataBuffer[3] << 8 | dataBuffer[2];
		offset += 4;
		lenght -= 4;		
		ret = true;
	}
	return ret;
}
string VT_1376_1_GetDataOne::getData()
{
	string ret="";
	if (getFnAndPn())
	{
		ret=functionForF2();

	}
	return  ret;
}
