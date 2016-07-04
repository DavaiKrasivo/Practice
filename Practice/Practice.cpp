// Practice.cpp: ���������� ����� ����� ��� ����������� ����������.
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

		if (list[curNum][1] == "�����")
			p = 0;
		if (list[curNum][1] == "�����16")
			p = 1;
		if (list[curNum][1] == "�����")
			p = 2;
		if (list[curNum][1] == "������")
			p = 3;
		if (list[curNum][1] == "�����")
			p = 4;
		if (list[curNum][1] == "�����" | list[curNum][1] == "����")
			p = 7;
		if (list[curNum][1] == "������")
			p = 6;
		if (list[curNum][1] == "������")
			p = 5;



		switch (automat[q][p])
		{

		case 1:
		{
			numLex++;
			list2[numLex][1] = "�������";
			break;
		}
		case 2:
		{
			numLex++;
			list2[numLex][1] = "������1";
			break;
		}
		case 3:
		{
			numLex++;
			list2[numLex][1] = "��";
			break;
		}
		case 4:
		{
			numLex++;
			list2[numLex][1] = "������2";
			break;
		}
		case 5:
		{
			numLex++;
			list2[numLex][1] = "�����";
			break;
		}
		case 6:
		{
			numLex++;
			list2[numLex][1] = "������3";
			break;
		}
		case 7:
		{
			numLex++;
			list2[numLex][1] = "����";
			break;
		}
		case 8:
		{
			numLex++;
			list2[numLex][1] = "�����1";
			break;
		}
		case 9:
		{
			numLex++;
			list2[numLex][1] = "�����2";
			break;
		}
		case 10:
		{
			numLex++;
			list2[numLex][1] = "������";
			break;
		}
		case 11:
		{
			numLex++;
			list2[numLex][1] = "�����1�";
			break;
		}
		case 12:
		{
			numLex++;
			list2[numLex][1] = "�����2�";
			break;
		}
		case 13:
		{
			numLex++;
			list2[numLex][1] = "������4";
			break;
		}
		case 14:
		{
			numLex++;
			list2[numLex][1] = "������";
			break;
		}
		case 15:
		{
			numLex++;
			list2[numLex][1] = "������5";
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
		list[i][1] = "������";
		if (((int)(s[i]) <= (int)('Z') && (int)(s[i]) >= (int)('A')) | ((int)(s[i]) <= (int)('z') && (int)(s[i]) >= (int)('a')))
			list[i][1] = "�����";
		if ((int)(s[i]) <= (int)('9') && (int)(s[i]) >= (int)('0'))
			list[i][1] = "�����";
		if ((int)(s[i]) == (int)(';'))
			list[i][1] = "������";
		if ((int)(s[i]) == (int)('='))
			list[i][1] = "�����";
		if ((int)(s[i]) == (int)(' '))
			list[i][1] = "������";
		if ((int)(s[i]) == (int)('+'))
			list[i][1] = "����";
		if ((int)(s[i]) == (int)('-'))
			list[i][1] = "�����";
		if ((int)(s[i]) == (int)('$'))
			list[i][1] = "������";
	}

	return list;
}

