#include <iostream>
#include <fstream>
#include <string>

class String {
	char* string_content;
	int string_length;
public:
	String(const char* c);
	~String() { delete[] string_content; }

	void println() const;
	void print() const;
	int getLength() { return string_length; }
	char getString(int num) { return string_content[num]; }
	void putString(int num, char c) { string_content[num] = c; }
};
String::String(const char* str)
{
	string_length = strlen(str);
	string_content = new char[string_length];
	for (int i = 0; i != string_length; i++) {
		string_content[i] = str[i];
	}
}
void String::println() const {
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}
	std::cout << std::endl;
}
void String::print() const {
	for (int i = 0; i != string_length; i++) {
		std::cout << string_content[i];
	}
}

class String_Manager {
	String** string_list;
	int row;
public:
	String_Manager() {
		string_list = new String * [10];
		row = 0;
	}
	void add_string(String* string) {
		string_list[row] = string;
		string_list[row]->println();
		row++;
	}
	void d();		// ���� ��ü�� ������
	void e();		// ������ �������� ���⸦ ���� ���� �����ϱ�
	void f();		// ���⸦ �������� ���� ������
	void g();		// ���� ������ Ư�� ���ڿ��� �ٸ� ���ڿ��� �ٲٱ�
	void h();		// �յڿ��� �о��� �� ������ ���� �������� ����ϱ�
};
void String_Manager::d()
{
	char* cmd;
	for (int i = 0; i < row; i++) {
		cmd = new char[string_list[i]->getLength()];
		for (int j = string_list[i]->getLength(); j > 0; j--) {
			cmd[string_list[i]->getLength() - j] = string_list[i]->getString(j - 1);
		}
		for (int j = 0; j < string_list[i]->getLength(); j++) {
			string_list[i]->putString(j, cmd[j]);
		}
		delete[] cmd;
		string_list[i]->println();
	}
}
void String_Manager::e()
{
	
}
void String_Manager::f()
{

}
void String_Manager::g()
{

}
void String_Manager::h()
{
	int front = 0, end = 0;
	for (int i = 0; i < row; i++) {
		front = 0, end = string_list[i]->getLength() - 1;
		while (string_list[i]->getString(front) == string_list[i]->getString(end)) {
			front++;
			end--;
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
	std::cout << "ã���� �ϴ� ������ �̸��� �Է��Ͻÿ� : ";
	std::cin >> filename;
	char str[110];
	int filenum = 0;

	std::ifstream in(filename);
	if (!in.is_open()) {
		std::cout << "�ش��ϴ� ������ �������� �ʽ��ϴ�" << std::endl;
		return 0;
	}
	else {
		std::cout << "������ �̸��� ������ �����ϴ� : " << filename << std::endl;
	}

	while (in) {
		in.getline(str, 100);
		string_list.add_string(new String(str));
	}
	
	char c;
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
			string_list.g();
			break;
		case 'h':
			string_list.h();
			break;
		case 'q':
			return 0;
		}
	}
}