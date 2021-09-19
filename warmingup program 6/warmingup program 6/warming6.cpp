#include <iostream>
#include <random>
#define LIMIT 20

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 6);
std::uniform_int_distribution<int> boool(0, 1);

class Field {
	int field[LIMIT][LIMIT];
public:
	Field() {
		for (int i = 0; i < LIMIT; i++) {
			for (int j = 0; j < LIMIT; j++) {
				field[i][j] = 0;
			}
		}
		field[0][0] = 1;
	}
	void reset() {
		for (int i = 0; i < LIMIT; i++) {
			for (int j = 0; j < LIMIT; j++) {
				field[i][j] = 0;
			}
		}
		field[0][0] = 1;
	}
	void insert(int x, int y, int foot) {
		field[y][x] = foot;
	}
	void printField() {
		for (int i = 0; i < LIMIT; i++) {
			for (int j = 0; j < LIMIT; j++) {
				printf("%4d", field[i][j]);
			}
			printf("\n");
		}
	}
};

class Field_Manager {
	Field* field;
	int foot_count = 1;
	int x = 0, y = 0;
	int upcount = 0, downcount = 0, leftcount = 0, rightcount = 0;
	bool right = false, down = false;
public:
	Field_Manager() {
		field = new Field;
	}
	~Field_Manager() {
		delete field;
	}
	void reset() {
		field[0].reset();
		foot_count = 1;
		x = 0, y = 0;
		upcount = 0, downcount = 0, leftcount = 0, rightcount = 0;
		right = false, down = false;
	}
	void run();
	void move_up();
	void move_down();
	void move_right();
	void move_left();
	void printField() { field[0].printField(); }
};
void Field_Manager::run()
{
	reset();
	while (x != LIMIT - 1 || y != LIMIT - 1) {
		if (x == 0) {
			right = true;
		}
		else if (x == LIMIT - 1) {
			right = false;
		}
		else if (dis(gen) >= 3) {
			right = true;
		}
		else {
			right = false;
		}
		if (y == 0) {
			down = true;
		}
		else if (y == LIMIT - 1) {
			down = false;
		}
		else if (dis(gen) >= 3) {
			down = true;
		}
		else {
			down = false;
		}

		if (right == true && down == true) {
			if (boool(gen) == 1 && rightcount < 5) {
				move_right();
				upcount = 0;
				downcount = 0;
				leftcount = 0;
				rightcount++;
			}
			else {
				if (downcount < 5) {
					move_down();
					upcount = 0;
					downcount++;
					leftcount = 0;
					rightcount = 0;
				}
				else {
					move_right();
					upcount = 0;
					downcount = 0;
					leftcount = 0;
					rightcount++;
				}
			}
		}
		else if (right == true && down == false) {
			if (boool(gen) == 1 && rightcount < 5) {
				move_right();
				upcount = 0;
				downcount = 0;
				leftcount = 0;
				rightcount++;
			}
			else {
				if (upcount < 5) {
					move_up();
					upcount++;
					downcount = 0;
					leftcount = 0;
					rightcount = 0;
				}
				else {
					move_right();
					upcount = 0;
					downcount = 0;
					leftcount = 0;
					rightcount++;
				}
			}
		}
		else if (right == false && down == true) {
			if (boool(gen) == 1 && leftcount < 5) {
				move_left();
				upcount = 0;
				downcount = 0;
				leftcount++;
				rightcount = 0;
			}
			else {
				if (downcount < 5) {
					move_down();
					upcount = 0;
					downcount++;
					leftcount = 0;
					rightcount = 0;
				}
				else {
					move_left();
					upcount = 0;
					downcount = 0;
					leftcount++;
					rightcount = 0;
				}
			}
		}
		else if (right == false && down == false) {
			if (boool(gen) == 1 && leftcount < 5) {
				move_left();
				upcount = 0;
				downcount = 0;
				leftcount++;
				rightcount = 0;
			}
			else {
				if (upcount < 5) {
					move_up();
					upcount++;
					downcount = 0;
					leftcount = 0;
					rightcount = 0;
				}
				else {
					move_left();
					upcount = 0;
					downcount = 0;
					leftcount++;
					rightcount = 0;
				}
			}
		}
	}
	field[0].printField();
}
void Field_Manager::move_up()
{
	y -= 1;
	foot_count++;
	field[0].insert(x, y, foot_count);
}
void Field_Manager::move_down()
{
	y += 1;
	foot_count++;
	field[0].insert(x, y, foot_count);
}
void Field_Manager::move_right()
{
	x += 1; 
	foot_count++;
	field[0].insert(x, y, foot_count);
}
void Field_Manager::move_left()
{
	x -= 1;
	foot_count++;
	field[0].insert(x, y, foot_count);
}

int main()
{
	Field_Manager field;
	char c;
	while (1) {
		std::cout << "input the command : ";
		std::cin >> c;
		switch (c) {
		case 'r':
			field.run();
			break;
		case 'q':
			return 0;
		}
	}
}