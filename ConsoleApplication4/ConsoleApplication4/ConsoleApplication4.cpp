#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>

#include <fstream>
using namespace std;
string lib; 
string encrypt(string str, string key, int language)
{
	string file = "C:\\Users\\User\\source\\repos\\ConsoleApplication4\\ConsoleApplication4\\O.txt";
	fstream fileOu(file, ios::out | ios::app);
	int temp;
	string encryptText;
	if (key.length() < str.length() || key.length() > str.length())
	{
		cout << "Error" << endl;
	}
	else 
	{
		for (int i = 0; i < str.length(); i++)
		{
			for (int j = 0; j < lib.length(); j++)
			{
				if ((char)str[i] == lib[j])
				{
					temp = (j + (char(key[i] - 48))) % lib.length();
					encryptText += lib[temp];
				}
			}
		}
	}
	if (language == 0)
	{
		cout << "Введенное вами слово: " << str << endl;
		cout << "Программа зашифровала его как: " << encryptText << endl;
		cout << endl;
	}
	else if (language == 1)
	{
		cout << "The word you entered: " << str << endl;
		cout << "The program encrypted it as: " << encryptText << endl;
		cout << endl;
	}
	fileOu << "Введенное вами слово: " << str << "\n";
	fileOu << "Программа зашифровала его как: " << encryptText << endl;
	fileOu.close();
	return encryptText;
}
string decrypt(string str, string key, int language)
{
	string file = "C:\\Users\\User\\source\\repos\\ConsoleApplication4\\ConsoleApplication4\\O.txt";
	fstream fileOu(file, ios::out | ios::app);
	int temp;
	string decryptText;
	for (int i = 0; i < str.length(); i++)
	{
		for (int j = 0; j < lib.length(); j++)
		{
			if ((char)str[i] == lib[j])
			{
				temp = j - (char(key[i] - 48));
				if (temp < 0) {
					temp += lib.length();
				}
				else {
					temp = (j - (char(key[i] - 48))) % lib.length();
				}
				
				decryptText += lib[temp];
			}
		}
	}
	if (language == 0)
	{
		cout << "Зашифрованное слово: " << str << endl;
		cout<<"Разшифрованное слово: " << decryptText << endl;
		cout << endl;
	}
	else if (language == 1)
	{
		cout << "Encrypted word: " << str << endl;
		cout << "Decrypted word: " << decryptText << endl;
		cout << endl;
	}
	fileOu << "Зашифрованное слово: " << str << "\n";
	fileOu << "Разшифрованное слово: " << decryptText << endl << endl;
	fileOu.close();
	return decryptText;
}
string makeLibE()
{
	for (int i = 65; i <= 90; i++) {
		lib += (char)i;
	}
	for (int i = 97; i <= 122; i++) {
		lib += (char)i;
	}
	for (int i = 48; i <= 57; i++) {
		lib += (char)i;
	}
	lib += (char)32;
	return lib;
}
string makeLibR()
{
	for (int i = 192; i <= 256; i++) {
		lib += (char)i;
	}
	for (int i = 48; i <= 57; i++) {
		lib += (char)i;
	}
	lib += (char)32;
	return lib;
} 
string makeLib()
{
	for (int i = 65; i <= 90; i++) {
		lib += (char)i;
	}
	for (int i = 97; i <= 122; i++) {
		lib += (char)i;
	}
	for (int i = 192; i <= 256; i++) {
		lib += (char)i;
	}
	for (int i = 48; i <= 57; i++) {
		lib += (char)i;
	}
	lib += (char)32;
	return lib;
}
bool CheckNum(string str) 
{
	for (int i = 0; i < str.length(); i++)
	{
		if (!isdigit(str[i]))
		{
			cout << "Error" << endl;
			return false;
		}

	}
	return true;
}
void PrintLib(string str) 
{
	int n = 0;
	for (size_t i = 0; i <= str.length(); i++)
	{
		if (i <= 8)
		{
			cout << " ";
		}
		cout << i + 1 << " " << str[i] << " | ";
		n++;
		if (n == 20) 
		{
			cout << endl << endl;
			n = 0;
		}
	}
	cout << endl << endl;
}
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int file;
	int language;
	int var;
	string str;
	string key;
	string encryptText;
	cout << "Выберите: " << endl;;
	cout << "(1) - консоль (2) - файл: ";
	cin >> file;
	if (file == 1)
	{
		cout << "Выберите язык: " << endl;;
		cout << "(1) - русский (2) - Английский: ";
		cin >> language;
		if (language == 1) {
			PrintLib(makeLibR());
			while (true)
			{
				cout << "Выберите: " << endl;;
				cout << "(1) - Разшифровать (2) - Зашифровать: ";
				cin >> var;
				getline(cin, str);
				switch (var)
				{
				case 1:
					cout << "Вы выбрали разшифровку!" << endl;
					cout << "Введите Зашифрованое слово: ";
					getline(cin, str);
					cout << "Введите ключ: ";
					(cin >> key).get();
					if (CheckNum(key))
					{
						decrypt(str, key, 0);
					}
					break;
				case 2:
					cout << "Вы выбрали зашифровку!" << endl;
					cout << "Введите слово, которое хотите зашифровать: ";
					getline(cin, str);
					cout << "Введите ключ: ";
					(cin >> key).get();
					if (CheckNum(key))
					{
						encrypt(str, key, 0);
					}
					break;
				default:
					cout << "Error" << endl;
					break;
				}
			}
		}
		else if (language == 2)
		{
			PrintLib(makeLibE());
			while (true)
			{

				cout << "Select: " << endl;
				cout << "(1) - Decrypt (2) - Encrypt: ";
				cin >> var;
				getline(cin, str);
				switch (var)
				{
				case 1:
					cout << "You have chosen decryption!" << endl;
					cout << "Enter an encrypted word: ";
					getline(cin, str);
					cout << "Enter the key: ";
					(cin >> key).get();
					if (CheckNum(key))
					{
						decrypt(str, key, 1);
					}
					break;
				case 2:
					cout << "You have chosen enryption!" << endl;
					cout << "Enter an decrypted word: ";
					getline(cin, str);
					cout << "Enter the key: ";
					(cin >> key).get();
					if (CheckNum(key))
					{
						encrypt(str, key, 1);
					}
					break;

				default:
					cout << "Error" << endl;
					break;
				}
			}
		}
		else
		{
			cout << "Error";
		}
	}
	else if (file == 2)
	{
		string filename = "C:\\Users\\User\\source\\repos\\ConsoleApplication4\\ConsoleApplication4\\Text.txt";
		ifstream fileIn;
		fileIn.open(filename);
		if (fileIn.fail())
		{
			cout << "Error opening file!\a";
			return 1;
		}
		while (!fileIn.eof())
		{
			string line;
			getline(fileIn, line);
			str += line;
		}
		PrintLib(makeLib());
		cout << "Выберите: " << endl;;
		cout << "(1) - Разшифровать (2) - Зашифровать: ";
		cin >> var;
		switch (var)
		{
		case 1:
			cout << "Вы выбрали разшифровку!" << endl;
			cout << endl << "Слово в файле: " << str << endl;
			cout << "Введите ключ: ";
			(cin >> key).get();
			if (CheckNum(key))
			{
				decrypt(str, key, 0);
			}
			break;
		case 2:
			cout << "Вы выбрали зашифровку!" << endl;
			cout << endl << "Слово в файле: " << str << endl;
			cout << "Введите ключ: ";
			(cin >> key).get();
			if (CheckNum(key))
			{
				encrypt(str, key, 0);
			}
			break;
		default:
			cout << "Error" << endl;
			break;
		}
		fileIn.close();

	}
}