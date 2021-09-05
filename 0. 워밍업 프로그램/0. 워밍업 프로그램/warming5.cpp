#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Save {
	int x, y, z;
public:
	Save() {
		x = 0;
		y = 0;
		z = 0;
	}
	Save(int x, int y, int z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Save(const Save& tmp) {
		x = tmp.x;
		y = tmp.y;
		z = tmp.z;
	}
public:
	int getLength() {
		return x * x + y * y + z * z;
	}
	void printlnCoordinate() {
		std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
	}
	void insert(Save tmp) {
		x = tmp.x;
		y = tmp.y;
		z = tmp.z;
	}
};

class Save_Manager {
	Save** save_list;
	bool* listed;
	int list_count;
	int uplist, downlist;
public:
	Save_Manager() {
		save_list = new Save*[10];
		listed = new bool[10];

		list_count = 0;
		uplist = 0;
		downlist = 0;
		for (int i = 0; i < 10; i++) {
			listed[i] = false;
		}
	}
	Save_Manager(const Save_Manager& tmp) {
		save_list = new Save*[10];
		listed = new bool[10];
		

		list_count = tmp.list_count;
		uplist = tmp.uplist;
		downlist = tmp.downlist;
		for (int i = 0; i < 10; i++) {
			listed[i] = tmp.listed[i];
		}
		for (int i = 0; i < 10; i++) {
			if (tmp.listed[i] == true) {
				save_list[i] = new Save(*tmp.save_list[i]);
			}
		}
	}
	void insert(const Save_Manager& tmp) {
		list_count = tmp.list_count;
		uplist = tmp.uplist;
		downlist = tmp.downlist;
		for (int i = 0; i < 10; i++) {
			listed[i] = tmp.listed[i];
		}
		for (int i = 0; i < 10; i++) {
			if (tmp.listed[i] == true) {
				save_list[i] = new Save(*tmp.save_list[i]);
			}
		}
	}
	void printlist();

	void addup(Save* save);
	void removeup();
	void adddown(Save* save);
	void removedown();
	void printdot();
	void removeall();
	void far();
	void close();
	void sort();

};
void Save_Manager::printlist()
{
	for (int i = 9; i >= 0; i--) {
		if (listed[i] == true) {
			std::cout << i + 1 << "번 리스트 : ";
			save_list[i]->printlnCoordinate();
		}
		else {
			std::cout << i + 1 << "번 리스트 : " << std::endl;
		}
	}
}
void Save_Manager::addup(Save* save)
{
	if (list_count == 10) {
		std::cout << "리스트가 가득 차 있습니다." << std::endl;
		return;
	}
	if (uplist == 9 && listed[uplist] == true) {
		for (int i = 0; i < 10; i++) {
			if (listed[i] == false) {
				uplist = i;
				break;
			}
		}
	}
	save_list[uplist] = save;
	listed[uplist] = true;
	list_count++;
	for (int i = uplist; i < 10; i++) {
		if (listed[i] == false) {
			uplist = i;
			break;
		}
	}
	printlist();
}
void Save_Manager::removeup()
{
	if (list_count == 0) {
		std::cout << "리스트가 비어있습니다." << std::endl;
		return;
	}
	for (int i = 9; i >= 0; i--) {
		if (listed[i] == true) {
			uplist = i;
			delete save_list[uplist];
			listed[uplist] = false;
			list_count--;
			break;
		}
	}
	printlist();
}
void Save_Manager::adddown(Save* save)
{
	if (list_count == 10) {
		std::cout << "리스트가 가득 차 있습니다." << std::endl;
		return;
	}
	if (downlist == 0 && listed[downlist] == true) {
		for (int i = 9; i > 0; i--) {
			if (listed[i] == true) {
			}
			else {
				if (listed[i - 1] == true) {
					std::cout << "run" << std::endl;
					save_list[i] = new Save(*save_list[i - 1]);
					listed[i] = true;
					delete save_list[i - 1];
					listed[i - 1] = false;
				}
			}
		}
	}
	save_list[downlist] = save;
	listed[downlist] = true;
	list_count++;
	for (int i = downlist; i >= 0; i--) {
		if (listed[i] == false) {
			downlist = i;
			break;
		}
	}
	printlist();
}
void Save_Manager::removedown()
{
	if (list_count == 0) {
		std::cout << "리스트가 비어있습니다." << std::endl;
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (listed[i] == true) {
			downlist = i;
			delete save_list[downlist];
			listed[downlist] = false;
			list_count--;
			break;
		}
	}
	printlist();
}
void Save_Manager::printdot()
{
	std::cout << "리스트 길이 : " << list_count << std::endl;
}
void Save_Manager::removeall()
{
	list_count = 0;
	uplist = 0;
	downlist = 0;
	for (int i = 0; i < 10; i++) {
		if (listed[i] == true) {
			listed[i] = false;
			delete save_list[i];
		}
	}
	printlist();
}
void Save_Manager::far()
{
	int max = 0, maxnum;
	if (list_count == 0) {
		std::cout << "리스트가 비어있습니다." << std::endl;
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (listed[i] == true && max < save_list[i]->getLength()) {
			max = save_list[i]->getLength();
			maxnum = i;
		}
	}
	std::cout << "가장 먼 거리의 좌표는 ";
	save_list[maxnum]->printlnCoordinate();
}
void Save_Manager::close()
{
	int min = INT_MAX, minnum;
	if (list_count == 0) {
		std::cout << "리스트가 비어있습니다." << std::endl;
		return;
	}
	for (int i = 0; i < 10; i++) {
		if (listed[i] == true && min > save_list[i]->getLength()) {
			min = save_list[i]->getLength();
			minnum = i;
		}
	}
	std::cout << "가장 가까운 거리의 좌표는 ";
	save_list[minnum]->printlnCoordinate();
}
void Save_Manager::sort()
{
	Save tmp;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (listed[i] == true && listed[j] == true) {
				if (save_list[i]->getLength() > save_list[j]->getLength()) {
					tmp.insert(*save_list[i]);
					save_list[i]->insert(*save_list[j]);
					save_list[j]->insert(tmp);
				}
			}
		}
	}
	for (int i = 0; i < 10; i++) {
		if (listed[i] == true) {
		}
		else {
			for (int j = i + 1; j < 10; j++) {
				if (listed[j] == true) {
					save_list[i] = new Save(*save_list[j]);
					delete save_list[j];
					listed[j] = false;
					listed[i] = true;
					break;
				}
			}
		}
	}
	downlist = 0;
	uplist = list_count;
	printlist();
}

int main()
{
	Save_Manager save_list;
	Save_Manager sm_tmp;
	char c;
	int x, y, z;
	bool sorton = false;

	while (1) {
		std::cout << "input the command : ";
		std::cin >> c;
		switch (c) {
		case '+':
			scanf(" %d %d %d", &x, &y, &z);
			save_list.addup(new Save(x, y, z));
			break;
		case '-':
			save_list.removeup();
			break;
		case 'e':
			scanf(" %d %d %d", &x, &y, &z);
			save_list.adddown(new Save(x, y, z));
			break;
		case 'd':
			save_list.removedown();
			break;
		case 'l':
			save_list.printdot();
			break;
		case 'c':
			save_list.removeall();
			break;
		case 'm':
			save_list.far();
			break;
		case 'n':
			save_list.close();
			break;
		case 's':
			if (sorton == false) {
				sorton = true;
				sm_tmp.insert(save_list);
				save_list.sort();
			}
			else {
				save_list.insert(sm_tmp);
				save_list.printlist();
				sorton = false;
			}
			break;
		case 'q':
			return 0;
		}
	}
}