#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

bool don, eon, fon;

class String {
	char* string_content;
	int string_length;
	bool* inserted;
public:
	String(const char* c);
	~String() { delete[] string_content; }

	void println() const;
	void print() const;
	int getLength() { return string_length; }
	char getString(int num) { return string_content[num]; }
	bool getInsert(int num) { return inserted[num]; }
	void putString(int num, char c) { string_content[num] = c; }
	void putInsert(int num, bool data) { inserted[num] = data; }
};
String::String(const char* str)
{
	string_length = strlen(str);
	string_content = new char[string_length];
	inserted = new bool[string_length];
	for (int i = 0; i != string_length; i++) {
		string_content[i] = str[i];
		inserted[i] = false;
	}
}
void String::println() const {
	for (int i = 0; i != string_length; i++) {
		if (don == true && inserted[i] == true) {
			std::cout << "**";
		}
		std::cout << string_content[i];
		if (don == false && inserted[i] == true) {
			std::cout << "**";
		}
	}
	std::cout << std::endl;
}
void String::print() const {
	for (int i = 0; i != string_length; i++) {
		if (don == true && inserted[i] == true) {
			std::cout << "**";
		}
		std::cout << string_content[i];
		if (don == false && inserted[i] == true) {
			std::cout << "**";
		}
	}
}

class String_Manager {
	String** string_list;
	int row;
public:
	String_Manager() {
		string_list = new String * [10];
		row = -1;
		don = false;
		eon = false;
		fon = false;
	}
	void add_string(String* string) {
		row++;
		string_list[row] = string;
		string_list[row]->println();
	}
	void d();		// 문장 전체를 뒤집기
	void e();		// 동일한 간격으로 띄어쓰기를 일정 개수 삽입하기
	void f();		// 띄어쓰기를 기준으로 문자 뒤집기
	void g(char changed, char changing);		// 문자 내부의 특정 문자열을 다른 문자열로 바꾸기
	void h();		// 앞뒤에서 읽었을 때 어디까지 같은 문자인지 출력하기
};
void String_Manager::d()
{
	char* tmp;
	bool* insert;
	if (don == true) {
		don = false;
	}
	else {
		don = true;
	}
	for (int i = 0; i < row; i++) {
		tmp = new char[string_list[i]->getLength()];
		insert = new bool[string_list[i]->getLength()];
		for (int j = string_list[i]->getLength(); j > 0; j--) {
			tmp[string_list[i]->getLength() - j] = string_list[i]->getString(j - 1);
			insert[string_list[i]->getLength() - j] = string_list[i]->getInsert(j - 1);
		}
		for (int j = 0; j < string_list[i]->getLength(); j++) {
			string_list[i]->putString(j, tmp[j]);
			string_list[i]->putInsert(j, insert[j]);
		}
		delete[] tmp;
		delete[] insert;
		string_list[i]->println();
	}
	std::cout << std::endl;
}
void String_Manager::e()
{
	if (fon == true) {
		std::cout << "f 명령어를 실행한 상태로 e 명령어를 취소할 수 없습니다." << std::endl;
	}
	else {
		if (eon == false) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < string_list[i]->getLength() - 1; j++) {
					if (j % 3 == 2) {
						string_list[i]->putInsert(j, true);
					}
				}
				string_list[i]->println();
			}
			eon = true;
		}
		else {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < string_list[i]->getLength(); j++) {
					string_list[i]->putInsert(j, false);
				}
				string_list[i]->println();
			}
			eon = false;
		}
		std::cout << std::endl;
	}
}
void String_Manager::f()
{
	char tmp;
	if (eon == false) {
		std::cout << "e 명령어를 실행하지 않고 f 명령어를 적용할 수 없습니다." << std::endl;
	}
	else {
		if (fon == true) {
			fon = false;
		}
		else {
			fon = true;
		}
		for (int i = 0; i < row; i++) {
			if (don == false) {
				for (int j = 0; j < string_list[i]->getLength() - 1; j++) {
					if (string_list[i]->getInsert(j) == true) {
						tmp = string_list[i]->getString(j);
						string_list[i]->putString(j, string_list[i]->getString(j - 2));
						string_list[i]->putString(j - 2, tmp);
					}
				}
				if (string_list[i]->getLength() % 3 == 2) {
					tmp = string_list[i]->getString(string_list[i]->getLength() - 1);
					string_list[i]->putString(string_list[i]->getLength() - 1, string_list[i]->getString(string_list[i]->getLength() - 2));
					string_list[i]->putString(string_list[i]->getLength() - 2, tmp);
				}
				else if (string_list[i]->getLength() % 3 == 0) {
					tmp = string_list[i]->getString(string_list[i]->getLength() - 1);
					string_list[i]->putString(string_list[i]->getLength() - 1, string_list[i]->getString(string_list[i]->getLength() - 3));
					string_list[i]->putString(string_list[i]->getLength() - 3, tmp);
				}
			}
			else if (don == true) {
				for (int j = string_list[i]->getLength() - 1; j >= 0; j--) {
					if (string_list[i]->getInsert(j) == true) {
						tmp = string_list[i]->getString(j);
						string_list[i]->putString(j, string_list[i]->getString(j + 2));
						string_list[i]->putString(j + 2, tmp);
					}
				}
				if (string_list[i]->getLength() % 3 == 2) {
					tmp = string_list[i]->getString(0);
					string_list[i]->putString(0, string_list[i]->getString(1));
					string_list[i]->putString(1, tmp);
				}
				else if (string_list[i]->getLength() % 3 == 0) {
					tmp = string_list[i]->getString(0);
					string_list[i]->putString(0, string_list[i]->getString(2));
					string_list[i]->putString(2, tmp);
				}
			}
			string_list[i]->println();
		}
	}
	std::cout << std::endl;
}
void String_Manager::g(char changed, char changing)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < string_list[i]->getLength(); j++) {
			if (string_list[i]->getString(j) == changed) {
				string_list[i]->putString(j, changing);
			}
		}
		string_list[i]->println();
	}
	std::cout << std::endl;
}
void String_Manager::h()
{
	int front = 0, end = 0;
	for (int i = 0; i < row; i++) {
		front = 0, end = string_list[i]->getLength() - 1;
		while (string_list[i]->getString(front) == string_list[i]->getString(end)) {
			front++;
			end--;
			if (front == end || front + 1 == end) {
				break;
			}
		}
		if (front == 0) {
			string_list[i]->print();
			std::cout << " : 0" << std::endl;
		}
		else {
			string_list[i]->print();
			std::cout << " : ";
			for (int j = 0; j < front; j++) {
				std::cout << string_list[i]->getString(j);
			}
			std::cout << std::endl;
		}
	}
}

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
	
	char c, changed, changing;
	while (1) {
		std::cout << "input the command : ";
		std::cin >> c;
		switch (c) {
		case 'd':
			string_list.d();
			break;
		case 'e':
			string_list.e();
			break;
		case 'f':
			string_list.f();
			break;
		case 'g':
			scanf(" %c %c", &changed, &changing);
			string_list.g(changed, changing);
			break;
		case 'h':
			string_list.h();
			break;
		case 'q':
			return 0;
		}
	}
}