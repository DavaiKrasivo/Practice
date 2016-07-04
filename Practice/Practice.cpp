// Practice.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
using namespace std;
string** translate(string s);
string** lexicalBlock(string** list, int& n);
int main()
{
    return 0;
}
string** lexicalBlock(string** list, int& n)
{
	string** list2 = new string*[255];
	for (int i = 0; i < 255; ++i)
	{
		list2[i] = new string[2];
	}

	int automat[30][30] =
	{ {{ 1 },{ 1 },{ -1 },{ 0 },{ -1 },{ -1 },{ -1 },{ -1 }},
	{ { 1 },{ 1 },{ -1 },{ 2 },{ -1 },{ -1 },{ -1 },{ -1 } },
	{ { 3 },{ 3 },{ -1 },{ 2 },{ -1 },{ -1 },{ -1 },{ -1 } },
	{ { 3 },{ 3 },{ 3 },{ 4 },{ 5 },{ -1 },{ -1 },{ -1 } },
	{ { -1 },{ -1 },{ -1 },{ 4 },{ 5 },{ -1 },{ -1 },{ -1 } },
	{ { -1 },{ -1 },{ 8 },{ 6 },{ -1 },{ -1 },{ 10 },{ 7 } },
	{ { -1 },{ -1 },{ 8 },{ 6 },{ -1 },{ -1 },{ 10 },{ 7 } },
	{ { -1 },{ -1 },{ 8 },{ -1 },{ -1 },{ -1 },{ -1 },{ -1 } },
	{ { -1 },{ -1 },{ 9 },{ -1 },{ -1 },{ -1 },{ -1 },{ -1 } },
	{ { -1 },{ -1 },{ 9 },{ 13 },{ -1 },{ 14 },{ -1 },{ -1 } },
	{ { -1 },{ 11 },{ 11 },{ -1 },{ -1 },{ -1 },{ -1 },{ -1 } },
	{ { -1 },{ 12 },{ 12 },{ -1 },{ -1 },{ -1 },{ -1 },{ -1 } },
	{ { -1 },{ 12 },{ 12 },{ 13 },{ -1 },{ 14 },{ -1 },{ -1 } },
	{ { -1 },{ -1 },{ -1 },{ 13 },{ -1 },{ 14 },{ -1 },{ -1 } },
	{ { -1 },{ -1 },{ -1 },{ 15 },{ -1 },{ 15 },{ -1 },{ -1 } },
	{ { -1 },{ -1 },{ -1 },{ 15 },{ -1 },{ 15 },{ -1 },{ -1 } },
	{ { -1 },{ -1 },{ -1 },{ -1 },{ -1 },{ -1 },{ -1 },{ -1 } } };
	int q = 0;
	int p = -1;
	int numLex = -1;
	int curNum = 0;
	bool error = false;
	while (error == false && n > curNum)
	{

		if (list[curNum][1] == "буква")
			p = 0;
		if (list[curNum][1] == "буква16")
			p = 1;
		if (list[curNum][1] == "цыфра")
			p = 2;
		if (list[curNum][1] == "пробел")
			p = 3;
		if (list[curNum][1] == "равно")
			p = 4;
		if (list[curNum][1] == "минус" | list[curNum][1] == "плюс")
			p = 7;
		if (list[curNum][1] == "доллар")
			p = 6;
		if (list[curNum][1] == "тчкзпт")
			p = 5;



		switch (automat[q][p])
		{

		case 1:
		{
			numLex++;
			list2[numLex][1] = "клслово";
			break;
		}
		case 2:
		{
			numLex++;
			list2[numLex][1] = "пробел1";
			break;
		}
		case 3:
		{
			numLex++;
			list2[numLex][1] = "ид";
			break;
		}
		case 4:
		{
			numLex++;
			list2[numLex][1] = "пробел2";
			break;
		}
		case 5:
		{
			numLex++;
			list2[numLex][1] = "равно";
			break;
		}
		case 6:
		{
			numLex++;
			list2[numLex][1] = "пробел3";
			break;
		}
		case 7:
		{
			numLex++;
			list2[numLex][1] = "знак";
			break;
		}
		case 8:
		{
			numLex++;
			list2[numLex][1] = "число1";
			break;
		}
		case 9:
		{
			numLex++;
			list2[numLex][1] = "число2";
			break;
		}
		case 10:
		{
			numLex++;
			list2[numLex][1] = "доллар";
			break;
		}
		case 11:
		{
			numLex++;
			list2[numLex][1] = "число1б";
			break;
		}
		case 12:
		{
			numLex++;
			list2[numLex][1] = "число2б";
			break;
		}
		case 13:
		{
			numLex++;
			list2[numLex][1] = "пробел4";
			break;
		}
		case 14:
		{
			numLex++;
			list2[numLex][1] = "тчкзпт";
			break;
		}
		case 15:
		{
			numLex++;
			list2[numLex][1] = "пробел5";
			break;
		}
		default:
			error = true;

		}
		list2[numLex][0] += list[curNum][0];
		q = p;
		curNum++;
	}
	n = numLex;
	return list2;
}
string** translate(string s)
{
	string** list = new string*[255];
	for (int i = 0; i < 255; ++i)
	{
		list[i] = new string[2];
	}

	for (int i = 0; i < s.length(); i++)
	{
		list[i][0] = s[i];
		list[i][1] = "ошибка";
		if (((int)(s[i]) <= (int)('Z') && (int)(s[i]) >= (int)('A')) | ((int)(s[i]) <= (int)('z') && (int)(s[i]) >= (int)('a')))
			list[i][1] = "буква";
		if ((int)(s[i]) <= (int)('9') && (int)(s[i]) >= (int)('0'))
			list[i][1] = "цифра";
		if ((int)(s[i]) == (int)(';'))
			list[i][1] = "тчкзпт";
		if ((int)(s[i]) == (int)('='))
			list[i][1] = "равно";
		if ((int)(s[i]) == (int)(' '))
			list[i][1] = "пробел";
		if ((int)(s[i]) == (int)('+'))
			list[i][1] = "плюс";
		if ((int)(s[i]) == (int)('-'))
			list[i][1] = "минус";
		if ((int)(s[i]) == (int)('$'))
			list[i][1] = "доллар";
	}

	return list;
}

