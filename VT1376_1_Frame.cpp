#include "VT1376_1_Frame.h"
#include "VT_1376_1_GetDataOne.h"
#include <iostream>
//#include <string>

/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 类构造函数
 *输入参数： 无
 *说明：     无
****************************************************/
VT1376_1_Format::VT1376_1_Format()
{
    valueInit();
}
void VT1376_1_Format::valueInit()
{
   lenght = NULL;//数据长度
   contorllerRegion = NULL;//控制域
   addressRegionA1 = NULL;//地址域A1      行政区域划码
   addressRegionA2 = NULL;//地址域A2		  终端地址
   addressRegionA3 = NULL;//地址域A3      主站地址与终端地址标识
   checkCode = NULL;//校验码 

}
/***************************************************
 *函数名：   ~VT1376_1_Format
 *函数功能： VT1376_1_Layout 类构析函数
 *输入参数： 无
 *说明：     无
****************************************************/
VT1376_1_Format::~VT1376_1_Format()
{

}
/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 返回合成数据长度
 *输入参数： 无
 *说明：     无
****************************************************/
unsigned int VT1376_1_Format::getLeght()
{
    return lenght;
}

/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 拷贝databuffer中数据到外部中去
 *输入参数： 无
 *说明：     无
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 返回dataBuffer地址
 *输入参数： 无
 *说明：     无
****************************************************/
unsigned char VT1376_1_Format::getDataBuffer(unsigned int i)
{
    return dataBuffer[i];
}


/***************************************************
 *函数名：   userFormat
 *函数功能： userFormat 类构析函数
 *输入参数： 无
 *说明：     无
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
 *函数名：   ~userFormat
 *函数功能： userFormat 类构析函数
 *输入参数： 无
 *说明：     无
****************************************************/
userFormat::~userFormat()
{
}

/***************************************************
 *函数名：   setAFNData
 *函数功能： userFormat 设置应用层功能码 AFN
 *输入参数： 无
 *说明：     无
****************************************************/
void userFormat::setAFNData(unsigned char dataIn)
{
    AFN = dataIn;
}
/***************************************************
 *函数名：   setSEQData
 *函数功能： userFormat 设置应用层帧序列  SEQ
 *输入参数： 无
 *说明：     无
****************************************************/
void userFormat::setSEQData(unsigned char dataIn)
{
    SEQ = dataIn;
}
/***************************************************
 *函数名：   getAFNData
 *函数功能： userFormat 获取应用层功能码 AFN
 *输入参数： 无
 *说明：     无
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
 *函数名：  isTpV
 *函数功能： userFormat 有无时间标识 TpV
 *输入参数： 无
 *说明：     无
****************************************************/
bool userFormat::isTpV(void) 
{
    return ((SEQ&(1<<7)) ==(1<< 7));
}
/***************************************************
 *函数名：   getFI
 *函数功能： userFormat 帧标识  FIR  FIN
 *输入参数： 无
 *说明：     无
****************************************************/
unsigned char  userFormat::getFI(void)//获取帧标识
{

    return (SEQ & (3 << 5)) >> 5;
}

bool userFormat::isCON(void)// 请求确认标识
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
 *函数名：   dataManage
 *函数功能： userFormat 信息处理函数
 *输入参数： 无
 *说明：     无
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout CS校验
 *输入参数： data  输入16 进制数据
 *说明：     无
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 获取数据长度
 *输入参数： data  输入16 进制数据
 *说明：     无
****************************************************/
bool VT1376_1_Format::getLenght(unsigned char* data)
{
    bool ret = false;
    unsigned int tempLenght = 0; 
    dataBufferClear();//清除缓存
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 传输方向
 *输入参数： data  输入16 进制数据
 *说明：     无
****************************************************/
bool VT1376_1_Format::isDIR(unsigned char contorllerValue)
{
    
    return ((contorllerRegion & (1 << 7)) == (1 << 7));
}
/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 启动标识位
 *输入参数： data  输入16 进制数据
 *说明：     无
****************************************************/
bool VT1376_1_Format::isPRM(unsigned char contorllerValue)
{
   
    return ((contorllerRegion & (1 << 6)) == (1 << 6));
}
/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 帧计数位
 *输入参数： data  输入16 进制数据
 *说明：     无
****************************************************/
bool VT1376_1_Format::isFCB(unsigned char contorllerValue)
{
   
    return ((contorllerRegion & (1 << 5)) == (1 << 5));
}
/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 帧计数有效位
 *输入参数： data  输入16 进制数据
 *说明：     无
****************************************************/
bool VT1376_1_Format::isFCV(unsigned char contorllerValue)
{
    
    return ((contorllerRegion & (1 << 4)) == (1 << 4));
}
/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 功能码
 *输入参数： data  输入16 进制数据
 *说明：     无
****************************************************/
unsigned char VT1376_1_Format::getFunctionCode(unsigned char contorllerValue)
{
   
    return (contorllerRegion&0x0f);

}
/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 获取地址
 *输入参数： data  输入16 进制数据
 *说明：     无
****************************************************/
bool VT1376_1_Format::getAddress(unsigned char* Region)
{
    bool ret = false;

    return ret;
}



/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 输入数据总长度
 *输入参数： data  输入16 进制数据
 *说明：     如果查找数据长度大于 bufferMax 则返回0 
****************************************************/
unsigned int VT1376_1_Format::getDataLenght(unsigned char* data)
{
    unsigned char ret = 0;
    while (*data++ != endChar)
    {
        ret++;
        if (ret > bufferMax)//超出范围后直接退出，并返回0
        {
            return  NULL;
        }
            
    }      
    return ret;
}


/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Format 返回两个数字之间的数据 拷贝到缓存区中，并返回数据长度
 *输入参数： *data  16 进制输入数据   head  头   tail尾  datalenght  总的数据长度
 *说明：     无
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
                dataBuffer[temp++] = data[i++];//拷贝数据 

                if (i > datalenght)
                    return  false;
            }
            if (data[i] == tail) //返回数据长度
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 小端模式转换
 *输入参数： 无
 *说明：     无
****************************************************/
unsigned int VT1376_1_Format::smallEndChange(unsigned int dataIn)
{
    unsigned int temp = 0;
    temp   =  (dataIn&0xff00) >> 8;
    temp    |= (dataIn&0xff) << 8;
    return temp;
}

/***************************************************
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 字符串转16 进制
 *输入参数： 无
 *说明：     无
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 字符串 转十进制
 *输入参数： 无
 *说明：     无
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 计算CS
 *输入参数： 无
 *说明：     无
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 清除缓存区
 *输入参数： 无
 *说明：     无
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 传入数据长度是否正确
 *输入参数： data  输入16 进制数据
 *说明：     无
****************************************************/
bool  VT1376_1_Format::checkLenght(unsigned char* data)
{
    bool ret = false;
    if (getLenght(data))//获取长度
    {
        if ((getFormatData(data, startChar, endChar, getDataLenght(data))-1) == lenght)//比较长度是否正确
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 分解传入数据
 *输入参数： data  输入16 进制数据
 *说明：     无
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
        
        /*设置数据单元标识起始位置，并设定长度*/       
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
 *函数名：   VT1376_1_Format
 *函数功能： VT1376_1_Layout 数据合成
 *输入参数： data  输入16 进制数据
 *说明：     无
****************************************************/
unsigned char* VT1376_1_Format::postFormat(unsigned char funcCode, const char* addres, 
                                           unsigned char appFuncCode, const char* Fn,
                                             const char* Pn,unsigned char Dir,unsigned char PRM,
                                            unsigned char FI, unsigned char needAck,unsigned char data)
{
    dataBufferClear();//清除缓存
    /*功能码*/
    contorllerRegion = funcCode|(Dir<<7)|(PRM << 6);
    /*地址域*/
    if (strToHex(addres))
    {
        addressRegionA1 =  smallEndChange(addressRegionA1);//转换位小端模式
        addressRegionA2 = smallEndChange(addressRegionA2);//转换位小端模式
        addressRegionA3 = smallEndChange(addressRegionA3);//转换位小端模式
    }
    /*应用层功能码*/
    setAFNData(appFuncCode);

    /*应用层SEQ*/
    setSEQData((FI <<5) | (needAck <<4) );

    /*计算Pn*/
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
    /*计算Fn*/
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
    /*计算CS*/
    //checkCode = getCS();
    /*生成报文*/
    dataBufferClear();
   // if ((appFuncCode != 0x04) && (appFuncCode != 0x05))//04 为设置命令   05 为控制命令    其余为数据请求命令
    {
        unsigned int temp = 0;
        /*起始头*/
        dataBuffer[temp++] = startChar;
        dataBuffer[temp++] = 0x32;
        dataBuffer[temp++] = 0x00;
        dataBuffer[temp++] = 0x32;
        dataBuffer[temp++] = 0x00;
        dataBuffer[temp++] = startChar;
        
        /*功能码*/
        dataBuffer[temp++] = contorllerRegion;
        /*地址域*/
        dataBuffer[temp++] = addressRegionA1 >> 8;
        dataBuffer[temp++] = addressRegionA1 &  0xff;
        dataBuffer[temp++] = addressRegionA2 >> 8;
        dataBuffer[temp++] = addressRegionA2 & 0xff;     
        dataBuffer[temp++] = addressRegionA3 & 0xff;
        /*应用层功能码*/
        dataBuffer[temp++] = getAFNData();
        /*应用层SEQ*/
        dataBuffer[temp++] = getSEQData();
        /*Pn*/
        dataBuffer[temp++] = getDataIdenPn() >> 8;
        dataBuffer[temp++] = getDataIdenPn() & 0xff;
        /*Fn*/
        dataBuffer[temp++] = getDataIdenFn() >> 8;
        dataBuffer[temp++] = getDataIdenFn() & 0xff;
        /*校验码*/
        dataBuffer[temp++] = getCS(&dataBuffer[6],temp-6);
        checkCode = dataBuffer[temp - 1];
        /*结束*/
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








