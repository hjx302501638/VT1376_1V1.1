#ifndef VT1376_1_FRAME_H
#define VT1376_1_FRAME_H
//#pragma once


#define VT1376_Disable    0
#define VT1376_WEB        1
#define VT1376_Hard       2

#define  startChar     0x68
#define  endChar       0x16
#define  bufferMax     100
#define  NULL          0


#define  ifDebug     1   //���Ժ�

/*ö�ٹ�����*/
typedef enum PRMisOneFuncCode
{  
    PRMisOne_resetCMD                =1,
    PRMisOne_userData                =4,
    PRMisOne_conncetTest             =9,
    PRMisOne_requseLVOneData         =10,
    PRMisOne_requseLVTowData         =11
    
}PRMisOneFuncCode;

typedef enum PRMisZeroFuncCode
{
    PRMisZero_affirm                 = 0,
    PRMisZero_ackUserData            = 8,
    PRMisZero_ontAffirm              = 9,
    PRMisZero_connectState           = 11
}PRMisZeroFuncCode;


typedef enum  AFNFuncCode
{
    AFN_Affirm            = 0x00,
    AFN_Reset             = 0x01,
    AFN_ConnectCheck      = 0x02,
    AFN_RelayStation      = 0x03,
    AFN_SetParameter      = 0x04,
    AFN_ContorllerCmd     = 0x05,
    AFN_Auten             = 0x06,
    AFN_OnUser            = 0x07,
    AFN_Report            = 0x08,
    AFN_TerminalSet       = 0x09,
    AFN_QueryParameter    = 0x0a,
    AFN_GetTaskData       = 0x0b,
    AFN_GetDataOne        = 0x0c,
    AFN_GetDataTow        = 0x0d,
    AFN_GetDataThree      = 0x0e,
    AFN_FileTransfer      = 0x0f,
    AFN_DataTransmit      = 0x10
}AFNFuncCode;


typedef enum  ACK
{
    noACK               = 0x00,
    NeendACK            = 0x01
}ACK;
typedef enum  FI
{
    FI_Middle = 0x00,
    FI_End    = 0x01,
    FI_Start  = 0x02,
    FI_One    = 0x03
}FI;


typedef enum outStata
{
    OFF = 0x00,
    ON   = 0x01
}outStata;

typedef enum DIR
{
    DIR_down = 0x00,
    DIR_UP   = 0x01
}DIR;

typedef enum PRM
{
    PRM_Sever  = 0x00,
    PRM_Terminal=0x01
}PRM;
/*�ඨ��*/
class  userFormat 
{

private:
    unsigned char AFN;
    unsigned char SEQ;
    unsigned  int dataIdenDA;//Pn
    unsigned  int dataIdenDT;//Fn
    unsigned  char* nowData;
    unsigned  int   nowDataLenght;
    void valueInit();
protected:
    //virtual bool dataManage(unsigned char* data = 0,unsigned int lenght = 0);
public:
    void setAFNData(unsigned char dataIn);
    void setSEQData(unsigned char dataIn);

    unsigned char getAFNData();//��ȡ������
    unsigned char getSEQData();//��ȡ֡���� SEQ

    unsigned int getDataIdenPn();
    unsigned int getDataIdenFn();
    void         setDataIdenPn(unsigned int Pn);
    void         setDataIdenFn(unsigned int Fn);

    bool isTpV(void);
    unsigned char  getFI(void);//��ȡ֡��ʶ
    bool isCON(void);// ����ȷ�ϱ�ʶ

    unsigned int getNowDataLenght();
    void   setNowDataLenght(unsigned int dataIn);
    unsigned char* getNowData();
    void   setNowData(unsigned char* dataIn);

    bool dataManage(unsigned char* data = 0, unsigned int lenght = 0);

    userFormat();
    ~userFormat();
};

class VT1376_1_Format :public userFormat
{

private:
    unsigned int  lenght;//���ݳ���
    unsigned char contorllerRegion;//������
    unsigned int  addressRegionA1;//��ַ��A1      ����������
    unsigned int  addressRegionA2;//��ַ��A2		  �ն˵�ַ
    unsigned char addressRegionA3;//��ַ��A3      ��վ��ַ���ն˵�ַ��ʶ
    unsigned char checkCode;//У����   
    unsigned char dataBuffer[bufferMax];

    bool checkCS(unsigned char* data);
    bool checkLenght(unsigned char* data);
    bool getLenght(unsigned char* data);

    bool isDIR(unsigned char contorllerValue = 0);
    bool isPRM(unsigned char contorllerValue = 0);
    bool isFCB(unsigned char contorllerValue = 0);
    bool isFCV(unsigned char contorllerValue = 0);
    unsigned char getFunctionCode(unsigned char contorllerValue = 0);

    void dataBufferClear(void);
    void valueInit();
    unsigned int getDataLenght(unsigned char* data);//��ȡ�ܳ���
    unsigned int  getFormatData(unsigned char* data, unsigned char head, unsigned char tail, unsigned char datalenght);//��ȡ���������м������ ������dataBufer��
    unsigned int  smallEndChange(unsigned int dataIn);
    bool strToHex(const char* dataIn);
    unsigned int strToNumber(const  char* dataIn);
    unsigned char getCS(unsigned char* dataIn, unsigned int dataLenght);
protected:

public:
    VT1376_1_Format();
    ~VT1376_1_Format();
    unsigned int getLeght();//���غϳ����ݳ���
    void strcopy(unsigned char* sre, unsigned int len = bufferMax);
    
    unsigned char getDataBuffer(unsigned int i = 0);
    bool getAddress(unsigned char* Region);
    bool formatResolve(unsigned char* data);
    unsigned char* postFormat(unsigned char funcCode,const char* addres,unsigned char appFuncCode,
                                 const char* Fn, const char* Pn = NULL,  
                                unsigned char Dir = 0, unsigned char PRM = 0,unsigned char FI = FI_One,
                                unsigned char needAck = NULL, unsigned char data = 0);
};




#endif
