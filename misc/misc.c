#include "misc.h"
#include "string.h"
#include "math.h"
//--------------------------------------------------

char* utoa(uint64_t value, char buffer[21], char prev, uint8_t width)
{
  uint8_t i=0;
  char *pch=buffer;// 21 элемент char = 20 символов max размер в dec + 1 символ завершающий 0
 
  pch+=20;//перемещаем указатель на последний символ строки (элемент буфера или массива)
  *pch=0;//присваиваем последниму элементу символу строки заначение 0 - признак конца строки
  do 
	{
    *--pch=value%10+'0';//1)перемещаем указатель на предыдущий символ строки 
		                     //2)остаток от деления дает числовое значение для символа, на который мы переместились в 1)
		                     //3)переводим числовое значение полученное в 2) в ascii (прибавляем 0x30 или '0')
    value/=10;
    i++;
  } 
	while(value);
	
  if(width)
	{
	  while(i<width)//пока количество символов строки, которое занимает число меньше заданного размера строки
		{
		  *--pch=prev;//1)перемещаем указатель на предыдущий (не занятый числом) символ строки
			            //2)присваиваем заполняющие значение(prev) символу, на который мы переместились в 1)
		  i++;
    }
  }
	
  if(i<20)//если количество заполненных символов строки < max размер в dec
	{
    for(i=0;*pch;pch++,i++)//сдвигаем сформированную строку в начало буфера 
		    buffer[i]=*pch;
    buffer[i]=0;//присваиваем последниму элементу символу строки заначение 0 - признак конца строки
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
	char *pch=buffer;// 17 элементов char = 16 символов max размер в hex + 1 символ завершающий 0
	
	/*далее по аналогии с utoa() (см. выше)*/
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
	
	/*определяем знак*/
	if(value<0)
	{
		sign='-';
		value = -value;
	} 
	else 
		sign='+';
	
	buffer=utoa(value,buffer,prev,width);//определяем значение
	memmove(&buffer[1],buffer,21);//сдвигаем буфер на 1 символ; освобождаем место под символ знака
	buffer[0]=sign;//заносим символ знака в буфер(строку)
	return buffer;
}
//--------------------------------------------------

char* dtoa(double n, char* buf, uint8_t width, uint8_t prec)
{
	uint8_t i=prec,j=0,t,d=0;
  char *pch=buf;
    
  if(n<0) 
	{
    *pch++='-';//заносим знак в строку (буфер)
		d++;//+1 на знак
		n=-n;//знак '-' мы учли далее будем работать с численным значением (с модулем)
  }
	
  do
	{
    n=n/10;
    i++;
  } 
	while((int)n>0);

	if(prec)d++;//+1 на назделитель (.)
	while(width-i-j-d>0)//заносим начальные '0', в неиспользуемые разряды
	{
		*pch++='0';
		j++;
	}		
	
  while(i>0) 
	{
		/*определяем численное значение текущего символа строки*/
		n*=10;	
	  if(i-1) 
			 t=(int)n; 
		else 
			 t=(int)round(n);
		
		/*потеря точности округления при выводе*/
		if(t>9) 
			 t=9;
		
		/*заносим символ '.' в строку*/
		if(i==prec) 
			 *pch++='.';
		
		/*заносим численное в соответствующий символ строки*/
		*pch++='0'+t;
		
    n-=(double)t;//разряд t занесен в строку убираем его из n
		i--;//переходим на следующий символ
  }
  *pch=0;
	
	return buf;
}
//--------------------------------------------------

int summ(int a, int b, bool *overflow)
{
	if((a>0 && b>0) && (INT32_MAX-b < a))//переплнение суммы
	{
		if(overflow) *overflow=true;
		return INT32_MAX;
	}
	if((a<0 && b<0) && (INT32_MIN-b > a))//переплнение суммы
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

