#include <iostream>
#include <Windows.h> 
#include <string>
#include <fstream>

using namespace std;

void menu()
{
	cout << "0.Exit" << endl;
	cout << "1.Encode" << endl;
	cout << "2.Decode" << endl;
}

int get_correct_number(int min, int max){
	int n = 0;
	while (((cin >> n).fail()) || (n < min) || (n > max) || (cin.get() != '\n')) {
		cin.clear();
		cin.ignore(1000000, '\n');
		cout << "Enter correct number: ";
	}
	return n;
}

string read_from_file() {
	string file_name;
	cin >> ws;
	getline(cin, file_name);
	file_name += ".txt";
	return file_name;
}

void Encode(string key, string read_file, string record_file) {
	basic_ifstream<unsigned char> fin;
	basic_ofstream<unsigned char> fout;

	unsigned char code = 0;
	int i = 0;

	fin.open(read_file, ios::binary);
	fout.open(record_file, ios::binary);

	if (!fin.is_open()) {
		cerr << "File open error" << endl;
	}
	else {
		while (fin.get(code)) {
			if (code == '\n')
			{
				fout << endl;
			}
			else {
				fout << (unsigned char)(code + key[i % key.length()]);
				i++;
			}
		}
		fin.close();
		fout.close();
	}
}



void Decode(string key, string read_file, string record_file) {
	basic_ifstream <unsigned char> fin;
	basic_ofstream <unsigned char> fout;

	unsigned char code = 0;
	int i = 0;

	fin.open(read_file, ios::binary);
	fout.open(record_file, ios::binary);

	if (!fin.is_open()) {
		cerr << "File open error" << endl;
	}
	else {
		while (fin.get(code)) {
			if (code == '\n')
			{
				fout << endl;
			}
		else {
			fout << (unsigned char)(code - key[i % key.length()]);
			i++;
		}
		}
		fin.close();
		fout.close();
	}
}

int main()
{

	string key;
	cout << "Enter keyword please" << endl;
	cin >> key;

	string read_file, record_file;

	while (true) {
		menu();
		switch (get_correct_number(0, 2))
		{
		case 0:
		{
			cout << "Goodbye!\n" << endl;
			return 0;
			break;
		}
		case 1:
		{
			cout << "Enter the file name to read from: " << endl;
			read_file = read_from_file();
			cout << "Enter the file name to record to: " << endl;
			record_file = read_from_file();

			Encode(key, read_file, record_file);
			break;
		}
		case 2:
		{
			cout << "Enter the file name to read from: " << endl;
			read_file = read_from_file();
			cout << "Enter the file name to record to: " << endl;
			record_file = read_from_file();

			Decode(key, read_file, record_file);
			break;
		}
		}
	}
}

