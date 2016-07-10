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

string ** transliteration(string s, bool err)//блок транслитерации
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
			list[i][1] = "буква"; continue;
		}
		if ((int)(s[i]) <= (int)('9') && (int)(s[i]) >= (int)('0')) {
			list[i][1] = "цифра"; continue;
		}
		if ((int)(s[i]) == (int)(';')) {
			list[i][1] = "тчкзпт"; continue;
		}
		if ((int)(s[i]) == (int)(' ')) {
			list[i][1] = "пробел"; continue;
		}
		if ((int)(s[i]) == (int)('+')) {
			list[i][1] = "плюс"; continue;
		}
		if ((int)(s[i]) == (int)('-')) {
			list[i][1] = "минус"; continue;
		}
		if ((int)(s[i]) == (int)(',')) {
			list[i][1] = "зап"; continue;
		}
		if ((int)(s[i]) == (int)('(')) {
			list[i][1] = "кр.откр.ск."; continue;
		}
		if ((int)(s[i]) == (int)(')')) {
			list[i][1] = "кр.закр.ск."; continue;
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

string ** lexicalBlock(string ** list, int & n)//лексический блок
{
	string** list2 = new string*[255];
	for (int i = 0; i < 255; ++i)
	{
		list2[i] = new string[2];
	}
	bool error = false;
	string status = "нач";
	int i = 0;
	int j = 0;
	while (j != n) {
		if (error) break;
		if (status == "нач")
		{
			if (list[j][1] == "буква")
			{
				status = "кл_слово_1";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "нач";
				continue;
			}
		}
		if (status == "кл_слово_1")
		{
			if (list[j][1] == "буква")
			{
				status = "кл_слово_1";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				list2[i][1] = "кл_слово_1";
				i++;
				status = "пробел1";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
		}
		if (status == "пробел1")
		{
			if (list[j][1] == "буква")
			{
				status = "ид_1";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "пробел1";
				j++;
				continue;
			}
		}
		if (status == "ид_1")
		{
			if (list[j][1] == "буква" || list[j][1] == "цифра")
			{
				status = "ид_1";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "пробел")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "кр.откр.ск.")
			{
				list2[i][1] = "идент";
				i++;
				status = "1(";
				list2[i][0] += list[j][0];
				list2[i][1] = "кр.откр.ск";
				j++;
				i++;
				continue;
			}
		}
		if (status == "1(")
		{
			if (list[j][1] == "буква" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "1(";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "цифра")
			{
				status = "число";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "плюс" || list[j][1] == "минус")
			{
				status = "знак";
				list2[i][0] += list[j][0];
				list2[i][1] = "знак";
				j++;
				i++;
				continue;
			}
		}
		if (status == "знак")
		{
			if (list[j][1] == "цифра")
			{
				status = "число";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "пробел" || list[j][1] == "буква" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
		}
		if (status == "число")
		{
			if (list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "буква" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "цифра")
			{
				status = "число";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if(list[j][1] == "пробел")
			{
				list2[i][1] = "число";
				i++;
				status = "пробел3";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "кр.закр.ск.")
			{
				list2[i][1] = "число";
				i++;
				status = "1)";
				list2[i][0] += list[j][0];
				list2[i][1] = "кр.закр.ск";
				j++;
				i++;
				continue;
			}
		}
		if (status == "пробел3")
		{
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "буква" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
			if(list[j][1] == "пробел")
			{
				status = "пробел3";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "кр.закр.ск.")
			{
				status = "1)";
				list2[i][0] += list[j][0];
				list2[i][1] = "кр.закр.ск";
				j++;
				i++;
				continue;
			}
		}
		if (status == "1)")
		{
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "буква" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.откр.ск." || list[j][1] == "кр.закр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "пробел4";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
		}
		if (status == "пробел4")
		{
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.откр.ск." || list[j][1] == "кр.закр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "пробел4";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "буква")
			{
				status = "кл_слово_2";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
		}
		if (status == "кл_слово_2")
		{
			if (list[j][1] == "буква")
			{
				status = "кл_слово_2";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				list2[i][1] = "кл_слово_2";
				i++;
				status = "пробел5";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
		}
		if (status == "пробел5")
		{
			if (list[j][1] == "буква")
			{
				status = "ид_2";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "пробел5";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
		}
		if (status == "ид_2")
		{
			if (list[j][1] == "буква" || list[j][1] == "цифра")
			{
				status = "ид_2";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "пробел")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "кр.откр.ск.")
			{
				list2[i][1] = "идент";
				i++;
				status = "2(";
				list2[i][0] += list[j][0];
				list2[i][1] = "кр.откр.ск";
				j++;
				i++;
				continue;
			}
		}
		if (status == "2(")
		{
			if (list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "цифра" || list[j][1] == "зап" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "кр.откр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "2(";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "буква")
			{
				status = "ид_3";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
		}
		if (status == "ид_3")
		{
			if (list[j][1] == "кр.закр.ск.")
			{
				list2[i][1] = "идент";
				i++;
				status = "2)";
				list2[i][0] += list[j][0];
				list2[i][1] = "кр.закр.ск";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "буква" || list[j][1] == "цифра")
			{
				status = "ид_3";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "кр.откр.ск." || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск." || list[j][1] == "пробел")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "зап")
			{
				list2[i][1] = "идент";
				i++;
				status = "зап";
				list2[i][0] += list[j][0];
				list2[i][1] = "зап";
				j++;
				i++;
				continue;
			}
		}
		if (status == "зап")
		{
			if (list[j][1] == "буква" || list[j][1] == "цифра" || list[j][1] == "кр.откр.ск." || list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "тчкзпт" || list[j][1] == "кр.закр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "пробел7";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}

		}
		if (status == "пробел7")
		{
			if (list[j][1] == "цифра" || list[j][1] == "кр.откр.ск." || list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "тчкзпт")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "пробел7";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "буква")
			{
				status = "ид_3";
				list2[i][0] += list[j][0];
				j++;
				continue;
			}
			if (list[j][1] == "кр.закр.ск.")
			{
				status = "2)";
				list2[i][0] += list[j][0];
				list2[i][1] = "кр.закр.ск";
				j++;
				i++;
				continue;
			}
		}
		if (status == "2)")
		{
			if (list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "буква" || list[j][1] == "зап" || list[j][1] == "кр.откр.ск." || list[j][1] == "кр.закр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				status = "2)";
				list2[i][0] += list[j][0];
				list2[i][1] = "пробел";
				j++;
				i++;
				continue;
			}
			if (list[j][1] == "тчкзпт")
			{
				list2[i][0] += list[j][0];
				list2[i][1] = "тчкзпт";
				i++;
				status = "тчкзпт";
				j++;
				continue;
			}
		}
		if (status == "тчкзпт")
		{
			if (list[j][1] == "тчкзпт" || list[j][1] == "цифра" || list[j][1] == "плюс" || list[j][1] == "минус" || list[j][1] == "буква" || list[j][1] == "зап" || list[j][1] == "кр.откр.ск." || list[j][1] == "кр.закр.ск.")
			{
				error = true;
				continue;
			}
			if (list[j][1] == "пробел")
			{
				j++;
				continue;
			}
		}
	}
	return list2;
}

bool keywordRecognize(string ** list, int & n)//блок идентификации ключевых слов
{
	ifstream fin;
	string word;
	fin.open("keyword.txt");
	int i = 0;
	for (int i = 0; i <= n; i++)
	{
		
		if (((list[i][1] == "кл_слово_1") && (list[i][0] != "repeat")))
		{
			return false;
		}
		if (((list[i][1] == "кл_слово_2") && (list[i][0] != "until")))
		{
			return false;
		}
		if (list[i][1] == "идент")
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

bool syntaxBlock(string ** list, int & n)//синтаксический блок
{
	string status = "нач";
	int i = 0;
	while (true)
	{
		if (list[i][1] == "пробел") {
			i++;
			continue;
		}
		if (status == "нач")
		{
			if (list[i][1] == "кл_слово_1")
			{
				status = "клслово_1";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "клслово_1")
		{
			if (list[i][1] == "идент")
			{
				status = "идент_1";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "идент_1")
		{
			if (list[i][1] == "кр.откр.ск")
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
			if (list[i][1] == "знак")
				i++;
			if (list[i][1] == "число")
			{
				status = "число";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "число")
		{
			if (list[i][1] == "кр.закр.ск")
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
			if (list[i][1] == "кл_слово_2")
			{
				status = "кл_слово_2";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "кл_слово_2")
		{
			if (list[i][1] == "идент")
			{
				status = "идент_2";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "идент_2")
		{
			if (list[i][1] == "кр.откр.ск")
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
			if (list[i][1] == "идент")
			{
				status = "идент_3";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "идент_3")
		{
			if (list[i][1] == "зап")
			{
				status = "идент_3";
				i++;
				continue;
			}
			if (list[i][1] == "идент")
			{
				status = "идент_3";
				i++;
				continue;
			}
			if (list[i][1] == "кр.закр.ск")
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
			if (list[i][1] == "тчкзпт")
			{
				status = "вых";
				i++;
				continue;
			}
			else
			{
				return false;
				break;
			}
		}
		if (status == "вых")
			return true;
	}
	return false;
}

string input(bool err)//ввод данных (строки) из файла
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

void tolower(string& str)//перевод букв в нижний регистр
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

void output(bool result) //вывод данных (результата) в файл
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
