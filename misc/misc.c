#include "misc.h"
#include "string.h"
#include "math.h"
//--------------------------------------------------

char* utoa(uint64_t value, char buffer[21], char prev, uint8_t width)
{
  uint8_t i=0;
  char *pch=buffer;// 21 ������� char = 20 �������� max ������ � dec + 1 ������ ����������� 0
 
  pch+=20;//���������� ��������� �� ��������� ������ ������ (������� ������ ��� �������)
  *pch=0;//����������� ���������� �������� ������� ������ ��������� 0 - ������� ����� ������
  do 
	{
    *--pch=value%10+'0';//1)���������� ��������� �� ���������� ������ ������ 
		                     //2)������� �� ������� ���� �������� �������� ��� �������, �� ������� �� ������������� � 1)
		                     //3)��������� �������� �������� ���������� � 2) � ascii (���������� 0x30 ��� '0')
    value/=10;
    i++;
  } 
	while(value);
	
  if(width)
	{
	  while(i<width)//���� ���������� �������� ������, ������� �������� ����� ������ ��������� ������� ������
		{
		  *--pch=prev;//1)���������� ��������� �� ���������� (�� ������� ������) ������ ������
			            //2)����������� ����������� ��������(prev) �������, �� ������� �� ������������� � 1)
		  i++;
    }
  }
	
  if(i<20)//���� ���������� ����������� �������� ������ < max ������ � dec
	{
    for(i=0;*pch;pch++,i++)//�������� �������������� ������ � ������ ������ 
		    buffer[i]=*pch;
    buffer[i]=0;//����������� ���������� �������� ������� ������ ��������� 0 - ������� ����� ������
  }
	
  return buffer;
}
//--------------------------------------------------

char DecToHex(uint8_t i)
{
	char ch;
	if(i<10) 
		 ch='0'+i; 
	else 
		 ch='A'-10+i;
	return ch;
}
//--------------------------------------------------

uint8_t HexToDec(char ch)
{
	uint8_t i;
	if(ch>'9') 
		 i=ch-'A'+10; 
	else 
		 i=ch-'0';
  return i;	
}
//--------------------------------------------------

char* utoa_hex(uint64_t value, char buffer[17], char prev, uint8_t width)
{
  uint8_t i=0,d;
	char *pch=buffer;// 17 ��������� char = 16 �������� max ������ � hex + 1 ������ ����������� 0
	
	/*����� �� �������� � utoa() (��. ����)*/
  pch+=16;
  *pch=0;
	do
  {
	  d=value%16;
    *--pch=DecToHex(d);
    value/=16;
    i++;
  } 
  while(value);
 
  if(width)
  {
	  while(i<width)
		{
		  *--pch=prev;
		  i++;
	  }
  }
	
  if(i<16)
  {
    for(i=0;*pch;pch++,i++)
		    buffer[i]=*pch;
    buffer[i]=0;
  }
  return buffer;
}
//--------------------------------------------------

char* strnset(char* str1, char* str2, unsigned int count)
{
	memmove(str1,str2,count);
	str1[count]=0;
	return str1;
}
//--------------------------------------------------

char* stoa(int64_t value, char buffer[22], char prev, uint8_t width)
{
	char sign;
	
	/*���������� ����*/
	if(value<0)
	{
		sign='-';
		value = -value;
	} 
	else 
		sign='+';
	
	buffer=utoa(value,buffer,prev,width);//���������� ��������
	memmove(&buffer[1],buffer,21);//�������� ����� �� 1 ������; ����������� ����� ��� ������ �����
	buffer[0]=sign;//������� ������ ����� � �����(������)
	return buffer;
}
//--------------------------------------------------

char* dtoa(double n, char* buf, uint8_t width, uint8_t prec)
{
	uint8_t i=prec,j=0,t,d=0;
  char *pch=buf;
    
  if(n<0) 
	{
    *pch++='-';//������� ���� � ������ (�����)
		d++;//+1 �� ����
		n=-n;//���� '-' �� ���� ����� ����� �������� � ��������� ��������� (� �������)
  }
	
  do
	{
    n=n/10;
    i++;
  } 
	while((int)n>0);

	if(prec)d++;//+1 �� ����������� (.)
	while(width-i-j-d>0)//������� ��������� '0', � �������������� �������
	{
		*pch++='0';
		j++;
	}		
	
  while(i>0) 
	{
		/*���������� ��������� �������� �������� ������� ������*/
		n*=10;	
	  if(i-1) 
			 t=(int)n; 
		else 
			 t=(int)round(n);
		
		/*������ �������� ���������� ��� ������*/
		if(t>9) 
			 t=9;
		
		/*������� ������ '.' � ������*/
		if(i==prec) 
			 *pch++='.';
		
		/*������� ��������� � ��������������� ������ ������*/
		*pch++='0'+t;
		
    n-=(double)t;//������ t ������� � ������ ������� ��� �� n
		i--;//��������� �� ��������� ������
  }
  *pch=0;
	
	return buf;
}
//--------------------------------------------------

int summ(int a, int b, bool *overflow)
{
	if((a>0 && b>0) && (INT32_MAX-b < a))//����������� �����
	{
		if(overflow) *overflow=true;
		return INT32_MAX;
	}
	if((a<0 && b<0) && (INT32_MIN-b > a))//����������� �����
	{
		if(overflow) *overflow=true;
		return INT32_MIN;
	}
	if(overflow) *overflow=false;
	return a+b;	
}
//--------------------------------------------------
 
uint32_t power(uint32_t x, uint32_t y)
{
	uint32_t result=x; y--;
	while(y){result*=x;y--;}
	return result;
}
//--------------------------------------------------

