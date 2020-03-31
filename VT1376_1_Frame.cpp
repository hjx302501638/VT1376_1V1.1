#include "VT1376_1_Frame.h"
#include "VT_1376_1_GetDataOne.h"
#include <iostream>
//#include <string>

/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout �๹�캯��
 *��������� ��
 *˵����     ��
****************************************************/
VT1376_1_Format::VT1376_1_Format()
{
    valueInit();
}
void VT1376_1_Format::valueInit()
{
   lenght = NULL;//���ݳ���
   contorllerRegion = NULL;//������
   addressRegionA1 = NULL;//��ַ��A1      ����������
   addressRegionA2 = NULL;//��ַ��A2		  �ն˵�ַ
   addressRegionA3 = NULL;//��ַ��A3      ��վ��ַ���ն˵�ַ��ʶ
   checkCode = NULL;//У���� 

}
/***************************************************
 *��������   ~VT1376_1_Format
 *�������ܣ� VT1376_1_Layout �๹������
 *��������� ��
 *˵����     ��
****************************************************/
VT1376_1_Format::~VT1376_1_Format()
{

}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ���غϳ����ݳ���
 *��������� ��
 *˵����     ��
****************************************************/
unsigned int VT1376_1_Format::getLeght()
{
    return lenght;
}

/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ����databuffer�����ݵ��ⲿ��ȥ
 *��������� ��
 *˵����     ��
****************************************************/
void VT1376_1_Format::strcopy(unsigned char* sre, unsigned int len)
{
    if (len < bufferMax)
    {
        for (unsigned int i = 0; i < len; i++)
        {
            sre[i] = dataBuffer[i];//Test.getDataBuffer(i);
        }
    }
    
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ����dataBuffer��ַ
 *��������� ��
 *˵����     ��
****************************************************/
unsigned char VT1376_1_Format::getDataBuffer(unsigned int i)
{
    return dataBuffer[i];
}


/***************************************************
 *��������   userFormat
 *�������ܣ� userFormat �๹������
 *��������� ��
 *˵����     ��
****************************************************/
userFormat::userFormat()
{
    valueInit();
}

void userFormat::valueInit()
{
    AFN = NULL;
    SEQ = NULL;
    dataIdenDA = NULL;//Pn
    dataIdenDT = NULL;//Fn

}
/***************************************************
 *��������   ~userFormat
 *�������ܣ� userFormat �๹������
 *��������� ��
 *˵����     ��
****************************************************/
userFormat::~userFormat()
{
}

/***************************************************
 *��������   setAFNData
 *�������ܣ� userFormat ����Ӧ�ò㹦���� AFN
 *��������� ��
 *˵����     ��
****************************************************/
void userFormat::setAFNData(unsigned char dataIn)
{
    AFN = dataIn;
}
/***************************************************
 *��������   setSEQData
 *�������ܣ� userFormat ����Ӧ�ò�֡����  SEQ
 *��������� ��
 *˵����     ��
****************************************************/
void userFormat::setSEQData(unsigned char dataIn)
{
    SEQ = dataIn;
}
/***************************************************
 *��������   getAFNData
 *�������ܣ� userFormat ��ȡӦ�ò㹦���� AFN
 *��������� ��
 *˵����     ��
****************************************************/
unsigned char userFormat::getAFNData()
{
    return AFN;
}

unsigned char userFormat::getSEQData()
{
    return SEQ;
}

unsigned int userFormat::getDataIdenPn()
{
    return dataIdenDA;
}

unsigned int userFormat::getDataIdenFn()
{
    return dataIdenDT;
}


void userFormat::setDataIdenPn(unsigned int Pn)
{
    dataIdenDA = Pn;
}

void userFormat::setDataIdenFn(unsigned int Fn)
{
    dataIdenDT = Fn;
}

/***************************************************
 *��������  isTpV
 *�������ܣ� userFormat ����ʱ���ʶ TpV
 *��������� ��
 *˵����     ��
****************************************************/
bool userFormat::isTpV(void) 
{
    return ((SEQ&(1<<7)) ==(1<< 7));
}
/***************************************************
 *��������   getFI
 *�������ܣ� userFormat ֡��ʶ  FIR  FIN
 *��������� ��
 *˵����     ��
****************************************************/
unsigned char  userFormat::getFI(void)//��ȡ֡��ʶ
{

    return (SEQ & (3 << 5)) >> 5;
}

bool userFormat::isCON(void)// ����ȷ�ϱ�ʶ
{
    return ((SEQ & (1 << 4)) == (1 << 4));
}


unsigned int userFormat::getNowDataLenght()
{
    return nowDataLenght;
}
void   userFormat::setNowDataLenght(unsigned int dataIn)
{
    nowDataLenght = dataIn;
}
unsigned char* userFormat::getNowData()
{
    return nowData;
}
void   userFormat::setNowData(unsigned char* dataIn)
{
     nowData = dataIn;
}
/***************************************************
 *��������   dataManage
 *�������ܣ� userFormat ��Ϣ������
 *��������� ��
 *˵����     ��
****************************************************/
 bool userFormat::dataManage(unsigned char* data, unsigned int lenght)
{
     bool ret = false;
     if (AFN == AFN_GetDataOne)
     {
         VT_1376_1_GetDataOne Test = VT_1376_1_GetDataOne(data, lenght);
#if ifDebug
         std::cout << Test.getData() << std::endl;
#endif 
     }
     return  ret;
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout CSУ��
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
bool VT1376_1_Format::checkCS(unsigned char* data)
{
    bool ret = false;
    unsigned char cs = 0;
    unsigned int  i = 0;
    for (i = 0; i < lenght; i++)
    {
        cs += data[i];
    }
    if (cs == data[lenght])
    {
        checkCode = data[lenght];
        ret = true;
    }
        
    return ret;
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ��ȡ���ݳ���
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
bool VT1376_1_Format::getLenght(unsigned char* data)
{
    bool ret = false;
    unsigned int tempLenght = 0; 
    dataBufferClear();//�������
    if (getFormatData(data, startChar, startChar, getDataLenght(data)))
    {
        tempLenght = dataBuffer[1] << 8 | dataBuffer[0];
        tempLenght >>= 2;
        lenght = tempLenght;
        ret = true;
        #if  ifDebug
        std::cout << tempLenght<< std::endl;
        #endif
    }

    return ret;
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ���䷽��
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
bool VT1376_1_Format::isDIR(unsigned char contorllerValue)
{
    
    return ((contorllerRegion & (1 << 7)) == (1 << 7));
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ������ʶλ
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
bool VT1376_1_Format::isPRM(unsigned char contorllerValue)
{
   
    return ((contorllerRegion & (1 << 6)) == (1 << 6));
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ֡����λ
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
bool VT1376_1_Format::isFCB(unsigned char contorllerValue)
{
   
    return ((contorllerRegion & (1 << 5)) == (1 << 5));
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ֡������Чλ
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
bool VT1376_1_Format::isFCV(unsigned char contorllerValue)
{
    
    return ((contorllerRegion & (1 << 4)) == (1 << 4));
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ������
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
unsigned char VT1376_1_Format::getFunctionCode(unsigned char contorllerValue)
{
   
    return (contorllerRegion&0x0f);

}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ��ȡ��ַ
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
bool VT1376_1_Format::getAddress(unsigned char* Region)
{
    bool ret = false;

    return ret;
}



/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ���������ܳ���
 *��������� data  ����16 ��������
 *˵����     ����������ݳ��ȴ��� bufferMax �򷵻�0 
****************************************************/
unsigned int VT1376_1_Format::getDataLenght(unsigned char* data)
{
    unsigned char ret = 0;
    while (*data++ != endChar)
    {
        ret++;
        if (ret > bufferMax)//������Χ��ֱ���˳���������0
        {
            return  NULL;
        }
            
    }      
    return ret;
}


/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Format ������������֮������� �������������У����������ݳ���
 *��������� *data  16 ������������   head  ͷ   tailβ  datalenght  �ܵ����ݳ���
 *˵����     ��
****************************************************/
unsigned int   VT1376_1_Format::getFormatData(unsigned char* data, unsigned char head, unsigned char tail, unsigned char datalenght)
{
    unsigned   ret = false;
     int temp = 0;
    unsigned int i = 0;
    for (i = 0; i < datalenght; i++)
    {
        if (data[i] == head)
        {
            i++;
            while (data[i] != tail)
            {
                if (data[i] == head)
                    temp = -1;
                dataBuffer[temp++] = data[i++];//�������� 

                if (i > datalenght)
                    return  false;
            }
            if (data[i] == tail) //�������ݳ���
            {
#if  ifDebug
                std::cout << temp << std::endl;
#endif
                return temp;
            }
               
        }
    }
    return  ret;
}

/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout С��ģʽת��
 *��������� ��
 *˵����     ��
****************************************************/
unsigned int VT1376_1_Format::smallEndChange(unsigned int dataIn)
{
    unsigned int temp = 0;
    temp   =  (dataIn&0xff00) >> 8;
    temp    |= (dataIn&0xff) << 8;
    return temp;
}

/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout �ַ���ת16 ����
 *��������� ��
 *˵����     ��
****************************************************/
bool VT1376_1_Format::strToHex(const char* dataIn)
{
    unsigned  int ret = 0;
    int i=0;

    addressRegionA1 = 0;
    addressRegionA2 = 0;
    addressRegionA3 = 0;
    for ( i = 0; i < 10; i++)
    {
        if (( dataIn[i] >47) && (dataIn[i] < 58))
        {
            ret++;
            if (i < 4)
            {
                addressRegionA1 <<= 4;
                addressRegionA1 += (dataIn[i] - (48));
            }
            else if ((i >= 4) && (i < 8))
            {
                addressRegionA2 <<= 4;
                addressRegionA2 += (dataIn[i] - (48));
            }
            else
            {
                addressRegionA3 <<= 4;
                addressRegionA3 += (dataIn[i] - (48));
            }
            
            
           
        }
        else if (( dataIn[i]>96)&& (dataIn[i] <103 ))
        {
            ret++;
            if (i < 4)
            {
                addressRegionA1 <<= 4;
                addressRegionA1 += (dataIn[i] - (87));
            }
            else if ((i >= 4) && (i < 8))
            {
                addressRegionA2 <<= 4;
                addressRegionA2 += (dataIn[i] - (87));
            }
            else
            {
                addressRegionA3 <<= 4;
                addressRegionA3 += (dataIn[i] - (87));
            }
           
        }
           
        else if (( dataIn[i] >64) && (dataIn[i]<71))
        {
            ret++;
            if (i < 4)
            {
                addressRegionA1 <<= 4;
                addressRegionA1 += (dataIn[i] - (55));
            }
            else if ((i >= 4) && (i < 8))
            {
                addressRegionA2 <<= 4;
                addressRegionA2 += (dataIn[i] - (55));
            }
            else
            {
                addressRegionA3 <<= 4;
                addressRegionA3 += (dataIn[i] - (55));
            }
            
        }
            

    }
    return (ret==i);
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout �ַ��� תʮ����
 *��������� ��
 *˵����     ��
****************************************************/
unsigned int VT1376_1_Format::strToNumber(const  char* dataIn)
{
    unsigned int ret = 0;
    while (*dataIn++)
    {
        if ((*dataIn > 47) && (*dataIn < 58))
        {
            ret *= 10;
            ret += (*dataIn - (48));
        }

    }
    return ret;
}



/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ����CS
 *��������� ��
 *˵����     ��
****************************************************/
unsigned char VT1376_1_Format::getCS(unsigned char* dataIn,unsigned int dataLenght)
{
    unsigned char ret = 0;
    for (unsigned int i = 0; i < dataLenght; i++)
    {
        ret += dataIn[i];
    }

    //ret += contorllerRegion;
    //ret += addressRegionA1;
    //ret += addressRegionA2;
    //ret += addressRegionA3;

    //ret += getAFNData();
    //ret += getSEQData();
    //ret += getDataIdenPn();
    //ret += getDataIdenFn();
    return (ret&0xff);
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ���������
 *��������� ��
 *˵����     ��
****************************************************/
void VT1376_1_Format::dataBufferClear(void)
{
    unsigned int i = 0;
    for (i = 0; i < bufferMax; i++)
    {
        dataBuffer[i] = NULL;
    }
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout �������ݳ����Ƿ���ȷ
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
bool  VT1376_1_Format::checkLenght(unsigned char* data)
{
    bool ret = false;
    if (getLenght(data))//��ȡ����
    {
        if ((getFormatData(data, startChar, endChar, getDataLenght(data))-1) == lenght)//�Ƚϳ����Ƿ���ȷ
        {
            ret = true;
#if  ifDebug
            std::cout << ret << std::endl;
#endif
        }
           
    }
    return  ret;
}
/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout �ֽ⴫������
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
bool VT1376_1_Format::formatResolve(unsigned char* data) 
{
    bool ret = false;    
    if (checkLenght(data) && checkCS(dataBuffer))
    {
        ret = true;
        contorllerRegion = dataBuffer[0];
        addressRegionA1 = dataBuffer[2] << 8 | dataBuffer[1];
        addressRegionA2 = dataBuffer[4] << 8 | dataBuffer[3];
        addressRegionA3 = dataBuffer[5];
        setAFNData(dataBuffer[6]);
        setSEQData(dataBuffer[7]);
        
        /*�������ݵ�Ԫ��ʶ��ʼλ�ã����趨����*/       
        dataManage(&dataBuffer[8], lenght - 8);
#if  ifDebug
        std::cout << "data check ok" << std::endl;
        printf("lenght:%.2d\n", lenght);
        printf("DIR:0x%.2x\n", isDIR());
        printf("PRM:0x%.2x\n", isPRM());
        printf("FCB:0x%.2x\n", isFCB());
        printf("FCV:0x%.2x\n", isFCV());
        printf("FuncCode:0x%.2x\n", getFunctionCode());
        printf("addressRegionA1:0x%.2x\n", addressRegionA1);
        printf("addressRegionA2:0x%.2x\n", addressRegionA2);
        printf("addressRegionA3:0x%.2x\n", addressRegionA3);
        printf("AFNData:0x%.2x\n", getAFNData());
        printf("TpV:0x%.2x\n", isTpV());
        printf("FI:0x%.2x\n", getFI());
        printf("CON:0x%.2x\n", isCON());
        printf("CS:0x%.2x\n", checkCode);
#endif  
    }
  
    return ret;
}


/***************************************************
 *��������   VT1376_1_Format
 *�������ܣ� VT1376_1_Layout ���ݺϳ�
 *��������� data  ����16 ��������
 *˵����     ��
****************************************************/
unsigned char* VT1376_1_Format::postFormat(unsigned char funcCode, const char* addres, 
                                           unsigned char appFuncCode, const char* Fn,
                                             const char* Pn,unsigned char Dir,unsigned char PRM,
                                            unsigned char FI, unsigned char needAck,unsigned char data)
{
    dataBufferClear();//�������
    /*������*/
    contorllerRegion = funcCode|(Dir<<7)|(PRM << 6);
    /*��ַ��*/
    if (strToHex(addres))
    {
        addressRegionA1 =  smallEndChange(addressRegionA1);//ת��λС��ģʽ
        addressRegionA2 = smallEndChange(addressRegionA2);//ת��λС��ģʽ
        addressRegionA3 = smallEndChange(addressRegionA3);//ת��λС��ģʽ
    }
    /*Ӧ�ò㹦����*/
    setAFNData(appFuncCode);

    /*Ӧ�ò�SEQ*/
    setSEQData((FI <<5) | (needAck <<4) );

    /*����Pn*/
    if (Pn == "P0" ||(Pn == "p0"))
    {
        
        setDataIdenPn(0);
    }
    else
    {
        unsigned int temp = strToNumber(Pn);
        unsigned char  DA1 = 1 << ((temp -1)%8);
        unsigned char  DA2 = (temp - 1) / 8+1;
        setDataIdenPn((DA1 << 8) | DA2);
    }
    /*����Fn*/
    if (Fn == "F0")
    {

    }
    else
    {
        unsigned int temp = strToNumber(Fn);
        unsigned char DT1 = 1 << ((temp - 1) % 8);
        unsigned char DT2 = (temp - 1) / 8;
        setDataIdenFn((DT1 << 8) | DT2);
    }
    /*����CS*/
    //checkCode = getCS();
    /*���ɱ���*/
    dataBufferClear();
   // if ((appFuncCode != 0x04) && (appFuncCode != 0x05))//04 Ϊ��������   05 Ϊ��������    ����Ϊ������������
    {
        unsigned int temp = 0;
        /*��ʼͷ*/
        dataBuffer[temp++] = startChar;
        dataBuffer[temp++] = 0x32;
        dataBuffer[temp++] = 0x00;
        dataBuffer[temp++] = 0x32;
        dataBuffer[temp++] = 0x00;
        dataBuffer[temp++] = startChar;
        
        /*������*/
        dataBuffer[temp++] = contorllerRegion;
        /*��ַ��*/
        dataBuffer[temp++] = addressRegionA1 >> 8;
        dataBuffer[temp++] = addressRegionA1 &  0xff;
        dataBuffer[temp++] = addressRegionA2 >> 8;
        dataBuffer[temp++] = addressRegionA2 & 0xff;     
        dataBuffer[temp++] = addressRegionA3 & 0xff;
        /*Ӧ�ò㹦����*/
        dataBuffer[temp++] = getAFNData();
        /*Ӧ�ò�SEQ*/
        dataBuffer[temp++] = getSEQData();
        /*Pn*/
        dataBuffer[temp++] = getDataIdenPn() >> 8;
        dataBuffer[temp++] = getDataIdenPn() & 0xff;
        /*Fn*/
        dataBuffer[temp++] = getDataIdenFn() >> 8;
        dataBuffer[temp++] = getDataIdenFn() & 0xff;
        /*У����*/
        dataBuffer[temp++] = getCS(&dataBuffer[6],temp-6);
        checkCode = dataBuffer[temp - 1];
        /*����*/
        dataBuffer[temp++] = endChar;

        lenght = temp;
    }
#if  ifDebug
    printf("*************************postFormat***************************************\n");
    printf("contorllerRegion:0x%x\n", contorllerRegion);
    printf("addressRegionA1:0x%x\n", addressRegionA1);
    printf("addressRegionA2:0x%x\n", addressRegionA2);
    printf("addressRegionA3:0x%x\n", addressRegionA3);
    printf("AFN:0x%x\n", getAFNData());
    printf("SEQ:0x%x\n", getSEQData());
    printf("setDataIdenPn:0x%x\n", getDataIdenPn());
    printf("setDataIdenFn:0x%x\n", getDataIdenFn());
    for (unsigned int  i = 0; i < lenght; i++)
    {
        printf("%.2x\t", dataBuffer[i]);
    }
#endif


    return dataBuffer;
}








