#include "stdafx.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
using namespace std;
typedef string arr[255][1];
string** transliteration(string s, bool err);
string** lexicalBlock(string** list, int& n);
bool keywordRecognize(string** list, int& n);
bool syntaxBlock(string** list, int& n);
string input(bool err);
void tolower(string& str);
void output(bool result);

int main()
{
	setlocale(LC_CTYPE, "rus");
	string** list;
	bool err = false;
	string s = input(err);
	tolower(s);
	if (err)
		exit;
	list = transliteration(s, err);
	if (err)
		exit;
	int n = s.length();
	list = lexicalBlock(list, n);
	if (keywordRecognize(list, n))
	{
	output(syntaxBlock(list, n));
	}
	else
	output(keywordRecognize(list, n));
	system("pause");
	return 0;
}

string ** transliteration(string s, bool err)//���� ��������������
{
	string** list = new string*[255];
	for (int i = 0; i < 255; ++i)
	{
		list[i] = new string[2];
	}
	for (int i = 0; i < s.length(); i++)
	{
		list[i][0] = s[i];
		if (((int)(s[i]) <= (int)('Z') && (int)(s[i]) >= (int)('A')) | ((int)(s[i]) <= (int)('z') && (int)(s[i]) >= (int)('a'))) {
			list[i][1] = "�����"; continue;
		}
		if ((int)(s[i]) <= (int)('9') && (int)(s[i]) >= (int)('0')) {
			list[i][1] = "�����"; continue;
		}
		if ((int)(s[i]) == (int)(';')) {
			list[i][1] = "������"; continue;
		}
		if ((int)(s[i]) == (int)(' ')) {
			list[i][1] = "������"; continue;
		}
		if ((int)(s[i]) == (int)('+')) {
			list[i][1] = "����"; continue;
		}
		if ((int)(s[i]) == (int)('-')) {
			list[i][1] = "�����"; continue;
		}
		if ((int)(s[i]) == (int)(',')) {
			list[i][1] = "���"; continue;
		}
		if ((int)(s[i]) == (int)('(')) {
			list[i][1] = "��.����.��."; continue;
		}
		if ((int)(s[i]) == (int)(')')) {
			list[i][1] = "��.����.��."; continue;
		}
		else
		{
			(list[i][1] == "err");
			err = true;
		}
	}
	if (err)
	{
		cout << "runtime error : unexpected symbol" << endl;
		exit;
	}
	else
		return list;
}

string ** lexicalBlock(string ** list, int & n)//����������� ����
{
	string** list2 = new string*[255];
	for (int i = 0; i < 255; ++i)
	{
		list2[i] = new string[2];
	}
	bool error = false;
	string status = "���";
	int i = 0;
	int j = 0;
	while (j != n) {
		if (error) break;
		if (status == "���")
		{
			if (list[j][1] == "�����")
			{
				status = "��_�����_1";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "���";
				continue;
			}
		}
		if (status == "��_�����_1")
		{
			if (list[j][1] == "�����")
			{
				status = "��_�����_1";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				list2[i][1] = "��_�����_1";
				i++;
				status = "������1";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
		}
		if (status == "������1")
		{
			if (list[j][1] == "�����")
			{
				status = "��_1";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "������1";
				j++;
				continue;
			}
		}
		if (status == "��_1")
		{
			if (list[j][1] == "�����" || list[j][1] == "�����")
			{
				status = "��_1";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "������")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "��.����.��.")
			{
				list2[i][1] = "�����";
				i++;
				status = "1(";
				list2[i][0] += list[j][0];
				list2[i][1] = "��.����.��";
				j++;
				i++;
				continue;
			}
		}
		if (status == "1(")
		{
			if (list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "1(";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "�����")
			{
				status = "�����";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "����" || list[j][1] == "�����")
			{
				status = "����";
				list2[i][0] += list[j][0];
				list2[i][1] = "����";
				j++;
				i++;
				continue;
			}
		}
		if (status == "����")
		{
			if (list[j][1] == "�����")
			{
				status = "�����";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "������" || list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
		}
		if (status == "�����")
		{
			if (list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "�����")
			{
				status = "�����";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if(list[j][1] == "������")
			{
				list2[i][1] = "�����";
				i++;
				status = "������3";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "��.����.��.")
			{
				list2[i][1] = "�����";
				i++;
				status = "1)";
				list2[i][0] += list[j][0];
				list2[i][1] = "��.����.��";
				j++;
				i++;
				continue;
			}
		}
		if (status == "������3")
		{
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if(list[j][1] == "������")
			{
				status = "������3";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "��.����.��.")
			{
				status = "1)";
				list2[i][0] += list[j][0];
				list2[i][1] = "��.����.��";
				j++;
				i++;
				continue;
			}
		}
		if (status == "1)")
		{
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "������4";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
		}
		if (status == "������4")
		{
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "������4";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "�����")
			{
				status = "��_�����_2";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
		}
		if (status == "��_�����_2")
		{
			if (list[j][1] == "�����")
			{
				status = "��_�����_2";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				list2[i][1] = "��_�����_2";
				i++;
				status = "������5";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
		}
		if (status == "������5")
		{
			if (list[j][1] == "�����")
			{
				status = "��_2";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "������5";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
		}
		if (status == "��_2")
		{
			if (list[j][1] == "�����" || list[j][1] == "�����")
			{
				status = "��_2";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "������")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "��.����.��.")
			{
				list2[i][1] = "�����";
				i++;
				status = "2(";
				list2[i][0] += list[j][0];
				list2[i][1] = "��.����.��";
				j++;
				i++;
				continue;
			}
		}
		if (status == "2(")
		{
			if (list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "2(";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "�����")
			{
				status = "��_3";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
		}
		if (status == "��_3")
		{
			if (list[j][1] == "��.����.��.")
			{
				list2[i][1] = "�����";
				i++;
				status = "2)";
				list2[i][0] += list[j][0];
				list2[i][1] = "��.����.��";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "�����" || list[j][1] == "�����")
			{
				status = "��_3";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "��.����.��." || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "������" || list[j][1] == "��.����.��." || list[j][1] == "������")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "���")
			{
				list2[i][1] = "�����";
				i++;
				status = "���";
				list2[i][0] += list[j][0];
				list2[i][1] = "���";
				j++;
				i++;
				continue;
			}
		}
		if (status == "���")
		{
			if (list[j][1] == "�����" || list[j][1] == "�����" || list[j][1] == "��.����.��." || list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "������" || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "������7";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}

		}
		if (status == "������7")
		{
			if (list[j][1] == "�����" || list[j][1] == "��.����.��." || list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "������")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "������7";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "�����")
			{
				status = "��_3";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "��.����.��.")
			{
				status = "2)";
				list2[i][0] += list[j][0];
				list2[i][1] = "��.����.��";
				j++;
				i++;
				continue;
			}
		}
		if (status == "2)")
		{
			if (list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				status = "2)";
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "������")
			{
				list2[i][0] += list[j][0];
				list2[i][1] = "������";
				i++;
				status = "������";
				j++;
				continue;
			}
		}
		if (status == "������")
		{
			if (list[j][1] == "������" || list[j][1] == "�����" || list[j][1] == "����" || list[j][1] == "�����" || list[j][1] == "�����" || list[j][1] == "���" || list[j][1] == "��.����.��." || list[j][1] == "��.����.��.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "������")
			{
				j++;
				continue;
			}
		}
	}
	return list2;
}

bool keywordRecognize(string ** list, int & n)//���� ������������� �������� ����
{
	ifstream fin;
	string word;
	fin.open("keyword.txt");
	int i = 0;
	for (int i = 0; i <= n; i++)
	{
		
		if (((list[i][1] == "��_�����_1") && (list[i][0] != "repeat")))
		{
			return false;
		}
		if (((list[i][1] == "��_�����_2") && (list[i][0] != "until")))
		{
			return false;
		}
		if (list[i][1] == "�����")
		{
			while (!fin.eof())
			{
				fin >> word;
				if (word == list[i][0])
				{
					return false;
				}
			}
		}
	}
	
	return true;
}

bool syntaxBlock(string ** list, int & n)//�������������� ����
{
	string status = "���";
	int i = 0;
	while (true)
	{
		if (list[i][1] == "������") {
			i++;
			continue;
		}
		if (status == "���")
		{
			if (list[i][1] == "��_�����_1")
			{
				status = "�������_1";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "�������_1")
		{
			if (list[i][1] == "�����")
			{
				status = "�����_1";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "�����_1")
		{
			if (list[i][1] == "��.����.��")
			{
				status = "(1";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "(1")
		{
			if (list[i][1] == "����")
				i++;
			if (list[i][1] == "�����")
			{
				status = "�����";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "�����")
		{
			if (list[i][1] == "��.����.��")
			{
				status = "1)";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "1)")
		{
			if (list[i][1] == "��_�����_2")
			{
				status = "��_�����_2";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "��_�����_2")
		{
			if (list[i][1] == "�����")
			{
				status = "�����_2";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "�����_2")
		{
			if (list[i][1] == "��.����.��")
			{
				status = "(2";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "(2")
		{
			if (list[i][1] == "�����")
			{
				status = "�����_3";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "�����_3")
		{
			if (list[i][1] == "���")
			{
				status = "�����_3";
				i++;
				continue;
			}
			if (list[i][1] == "�����")
			{
				status = "�����_3";
				i++;
				continue;
			}
			if (list[i][1] == "��.����.��")
			{
				status = ")2";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == ")2")
		{
			if (list[i][1] == "������")
			{
				status = "���";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "���")
			return true;
	}
	return false;
}

string input(bool err)//���� ������ (������) �� �����
{
	char str[81];
	ifstream fin;
	fin.open("input.txt");
	fin.getline(str, 80);
	fin.close();
	if (str[0] == '\0')
	{
		err = true;
		cout << "runtime error: empty string" << endl;
		exit;
	}
	return str;
}

void tolower(string& str)//������� ���� � ������ �������
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' &&  str[i] <= 'Z') {
			str[i] = char(str[i] + 32);
		}
		i++;
	}
}

void output(bool result) //����� ������ (����������) � ����
{
	ofstream fout;
	fout.open("output.txt");
	if (result)
	{
		fout << "ACCEPT";
	}
	else
	{
		fout << "REJECT";
	}
	fout.close();
}
