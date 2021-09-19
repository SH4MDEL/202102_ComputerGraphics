#include <iostream>
#include <fstream>
#include <string>

char cache[100][100];
int intcache[100];
int cachecount = 0, numcount = 0;

class String {
	char* string_content;
	int string_length, word_count, number_count;
public:
	String(const char* c);
	~String() { delete[] string_content; }

	int getWord() { return word_count; }
	int getNum() { return number_count; }
	void println() const;
};
String::String(const char* str)
{
	int status = 0;
	word_count = 0, number_count = 0;
	string_length = strlen(str);
	string_content = new char[string_length];
	for (int i = 0; i != string_length; i++) {
		string_content[i] = str[i];
	}
	for (int i = 0; i != string_length; i++) {
		cache[cachecount][numcount] = string_content[i];
		if (string_content[i] == 32) {
			if (status == 2) {
				number_count++;
				status = 0;
				intcache[cachecount] = numcount;
				cachecount++;
				numcount = 0;
			}
			else if (status == 1) {
				word_count++;
				status = 0;
				numcount = 0;
			}
			else {
			}
		}
		else if (string_content[i] >= 48 && string_content[i] <= 57) {
			status = 2;
		}
		else {
			if (status == 2) {
			}
			else {
				status = 1;
			}
		}
		numcount++;
	}
	if (status == 2) {
		number_count++;
		status = 0;
		intcache[cachecount] = numcount;
		cachecount++;
		numcount = 0;
	}
	else if (status == 1) {
		word_count++;
		status = 0;
		numcount = 0;
	}
}
void String::println() const {
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}
	std::cout << std::endl;
}

class String_Manager {
	String** string_list;
	int row, word_count, number_count;
public:
	String_Manager() {
		string_list = new String*[10];
		row = 0;
		word_count = 0;
		number_count = 0;
	}
	void add_string(String* string) {
		string_list[row] = string;
		word_count += string_list[row]->getWord();
		number_count += string_list[row]->getNum();
		string_list[row]->println();
		row++;
	}
	int getWord() { return word_count; }
	int getNum() { return number_count; }
};

int main()
{
	String_Manager string_list;
	std::string filename;
	std::cout << "찾고자 하는 파일의 이름을 입력하시오 : ";
	std::cin >> filename;
	char str[110];
	int filenum = 0;

	std::ifstream in(filename);
	if (!in.is_open()) {
		std::cout << "해당하는 파일이 존재하지 않습니다" << std::endl;
		return 0;
	}
	else {
		std::cout << "파일의 이름은 다음과 같습니다 : " << filename << std::endl;
	}

	while (in) {
		in.getline(str, 100);
		string_list.add_string(new String(str));
	}
	std::cout << std::endl << "word count : " << string_list.getWord() << std::endl;
	std::cout << "number count : " << string_list.getNum() << std::endl;
	std::cout << "(";
	for (int i = 0; i < cachecount; i++) {
		if (i != 0) {
			printf(" ");
		}
		for (int j = 0; j < intcache[i]; j++) {
			printf("%c", cache[i][j]);
		}
	}
	std::cout << ")" << std::endl;
}

