/*----------------------------------------------------------------
 * Copyright (C) 2011 ���մ�ѧ ����ѧԺ416 ����ԭ
 * ��Ȩ���С� 
 * 
 * �ļ����� main.c
 * 
 * �ļ�����������   
 *          MSP430F16x,MSP430F14X�ⲿAD��������(SPI�ӿ�)ʾ������
 *      ˵����  
 *          AD7708.c���빤�̣�����AD7708.h����ʹ�ã���������ļ���
 *          �ĳ���ʹ�������
 *
 * ������ʶ��   ����ԭ20110816
 * 
 * �޸ı�ʶ��   
 * �޸�������   
**----------------------------------------------------------------*/

#include "msp430x14x.h"     //430�Ĵ���ͷ�ļ�
#include "AD7708.h"         //ad7708����ͷ�ļ�

/****************************************************************************
* ��    �ƣ�ClkInit
* ��    �ܣ�ʱ��ϵͳ��ʼ��  MCLKΪ8MHz��SMCLKΪ1MHz
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
void ClkInit()
{
    char i;
    BCSCTL1 &= ~XT2OFF;             //��XT2����
    IFG1&=~OFIFG;                   //����񵴴����־
    while((IFG1&OFIFG)!=0)
    {
        for(i=0;i<0xff;i++);
        IFG1&=~OFIFG;               //����񵴴����־
    }
    BCSCTL2 |= SELM_2+SELS+DIVS_3;  //MCLKΪ8MHz��SMCLKΪ1MHz
}

/****************************************************************************
* ��    �ƣ�main������
* ��    �ܣ�����AD7708��������
* ��ڲ�������
* ���ڲ�������
****************************************************************************/
long a;
void main()
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    ClkInit();
    AD7708Init(0);  //��ֹն�� 1ʱ����ն��
    
    _EINT();        //���жϣ�������Ҫ�õ�SPI���жϣ���ͻ�����Ը���SPI����
    
    while(1)                    //���ڲ���
    {
        AD7708Start(0);
        a = AD7708ReadResultData();         //��ȡAD������Ľ��
        //��ѹ���㷽����a*1.024*2.5(�ο���ѹ)/65535
        a = AD7708ReadRegister(0);          //ȥ״ֵ̬���˴���������Ҫ��
        
    }
}
