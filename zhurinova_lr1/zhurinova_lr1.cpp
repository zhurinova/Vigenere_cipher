#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string alphabet = " AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuWwXxYyZz\n,.!?\"–'()0123456789";

int get_correct_number(int min, int max){
	int n = 0;
	while (((std::cin >> n).fail()) || (n < min) || (n > max) || (std::cin.get() != '\n')) {
		std::cin.clear();
		std::cin.ignore(1000000, '\n');
		std::cout << "Enter correct number: ";
	}
	return n;
}

void menu()
{
	cout << "0.Exit" << endl;
	cout << "1.Encode" << endl;
	cout << "2.Decode" << endl;
}

string load() {
	string text, line;
	cout << "Enter the file name: " << endl;
	string file_name;
	cin >> ws;
	getline(cin, file_name);
	file_name += ".txt";
	ifstream fin;
	fin.open(file_name);
	if (!fin.is_open()) {
		cerr << "File open error" << endl;
	}
	else {
		while (getline(fin, line)) {
			text += line + "\n";
		}
		fin.close();
		return text;
	}
}

void save(string code) {
	cout << "Enter the file name: " << endl;
	string file_name;
	getline(cin, file_name);
	file_name += ".txt";
	ofstream fout(file_name);
	if (!fout.is_open()) {
		cerr << "File open error" << endl;
	}
	else {
		for (int i = 0; i < code.length(); i++) {
			fout << code[i];
		}
	}
	fout.close();
}

int keycode(char s) {
	for (int i = 0; i < alphabet.length(); i++) {
		if (s == alphabet[i]) return i;
	}
	return 0;
}

string Encode(string text, string key) {
	string code;
	for (int i = 0; i < text.length(); i++) {
		code += alphabet[(keycode(text[i]) + keycode(key[i % key.length()])) % alphabet.length()];
	}
	return code;
}

//string Encode() {
//	while ()
//	{
//
//	}
//}

string Decode(string text, string key) {
	string code;
	for (int i = 0; i < text.length(); i++) {
		code += alphabet[(keycode(text[i]) - keycode(key[i % key.length()]) + alphabet.length()) % alphabet.length()];
	}
	return code;
}

int main()
{
	//setlocale(LC_ALL, "Russian");
	string text, key;
	cout << "Enter keyword please" << endl;
	cin >> key;
	//for (auto& c : key) c = toupper(c);

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
			string code;
			text = load();
			cout << text;
			//for (auto& c : text) c = toupper(c);
			code = Encode(text, key);
			cout << code << endl;
			save(code);
			break;
		}
		case 2:
		{
			string code;
			text = load();
			code = Decode(text, key);
			cout << code << endl;
			save(code);
			break;
		}
		}
	}
}

